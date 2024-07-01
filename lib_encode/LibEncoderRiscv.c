// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include <alloca.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <errno.h>

#include "lib_encode/lib_encoder.h"
#include "LibEncoderRiscvInternal.h"
#include "lib_encode/LibEncoderRiscv.h"
#include "lib_common/BufferAPIInternal.h"
#include "lib_encode/EncSchedulerCommon.h"
#include "lib_common/RiscvDmaAllocator.h"
#include "RiscvProxyAllocator.h"
#include "lib_common/BufferStreamMeta.h"
#include "lib_common/BufferPictureMeta.h"
#include "lib_common_enc/RateCtrlMeta.h"
#include "lib_encode/Sections.h"

#include "lib_encode/msg_interface_generated.h"
#include "lib_common/codec_uapi.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define CMD_MARSHALL(cmd, req, type_lower) do { \
    struct rd_wr_ctx ctx; \
\
    req.hdr.payload_len = enc_ ## type_lower ## _req_get_size(); \
    cmd.req_size = enc_ ## type_lower ## _req_full_get_size(); \
    cmd.reply_size = enc_ ## type_lower ## _reply_get_size(); \
    cmd.req = alloca(cmd.req_size); \
    cmd.reply = alloca(cmd.reply_size); \
    ctx.pos = 0; \
    ctx.buffer = cmd.req; \
    enc_ ## type_lower ## _req_full_marshall(&req, write_cb, &ctx); \
} while(0)

#define CMD_MARSHALL_REF(cmd, req, type_lower) do { \
    struct rd_wr_ctx ctx; \
\
    req->hdr.payload_len = enc_ ## type_lower ## _req_get_size(); \
    cmd.req_size = enc_ ## type_lower ## _req_full_get_size(); \
    cmd.reply_size = enc_ ## type_lower ## _reply_get_size(); \
    cmd.req = alloca(cmd.req_size); \
    cmd.reply = alloca(cmd.reply_size); \
    ctx.pos = 0; \
    ctx.buffer = cmd.req; \
    enc_ ## type_lower ## _req_full_marshall(req, write_cb, &ctx); \
} while(0)

#define REPLY_UNMARSHALL(cmd, reply, type_lower) do { \
    struct rd_wr_ctx ctx; \
\
    ctx.pos = 0; \
    ctx.buffer = cmd.reply; \
    enc_ ## type_lower ## _reply_unmarshall(&reply, read_cb, &ctx); \
} while(0)

#define EVENT_UNMARSHALL(event, buffer, type_lower) do { \
    struct rd_wr_ctx ctx; \
\
    ctx.pos = 0; \
    ctx.buffer = buffer; \
    enc_ ## type_lower ## _unmarshall(&event, read_cb, &ctx); \
} while(0)

typedef struct
{
  int fd;
  AL_THREAD poller;
  volatile bool is_shutdown;
  AL_TAllocator* proxyAllocator;
}AL_RiscvEncoderCtx;

typedef struct
{
  uint64_t hEnc;
  AL_CB_EndEncoding CB[MAX_NUM_LAYER];
  AL_EProfile eProfile;
  AL_EStartCodeBytesAlignedMode eStartCodeBytesAligned;
  AL_TCommonChannelInfo chanInfo[MAX_NUM_LAYER];
  AL_RiscvEncoderCtx* pCtx;
  AL_EVENT destroyEvent;
}AL_HEncoderWrapper;

struct rd_wr_ctx
{
  char* buffer;
  int pos;
};

typedef struct AL_TRiscvMetaData
{
  AL_TMetaData tMeta;
  uint64_t pRec;
  AL_TReconstructedInfo recInfo;
}AL_TRiscvMetaData;

static void write_cb(int len, void* in, void* args)
{
  struct rd_wr_ctx* ctx = args;

  memcpy(&ctx->buffer[ctx->pos], in, len);
  ctx->pos += len;
}

static void read_cb(int len, void* out, void* args)
{
  struct rd_wr_ctx* ctx = args;

  memcpy(out, &ctx->buffer[ctx->pos], len);
  ctx->pos += len;
}

static bool RiscvMeta_Destroy(AL_TMetaData* pMeta)
{
  Rtos_Free(pMeta);

  return true;
}

static AL_TRiscvMetaData* AL_RiscvMetaData_Create(void);
static AL_TMetaData* RiscvMeta_Clone(AL_TMetaData* pMeta)
{
  AL_TRiscvMetaData* original = (AL_TRiscvMetaData*)pMeta;
  AL_TRiscvMetaData* copy;

  if(!pMeta)
    return NULL;

  copy = AL_RiscvMetaData_Create();

  if(!copy)
    return NULL;

  copy->pRec = original->pRec;

  return &copy->tMeta;
}

static AL_TRiscvMetaData* AL_RiscvMetaData_Create(void)
{
  AL_TRiscvMetaData* pMeta = (AL_TRiscvMetaData*)Rtos_Malloc(sizeof(*pMeta));

  if(!pMeta)
    return NULL;

  pMeta->tMeta.eType = AL_META_TYPE_RISCV;
  pMeta->tMeta.MetaDestroy = RiscvMeta_Destroy;
  pMeta->tMeta.MetaClone = RiscvMeta_Clone;
  pMeta->pRec = 0;

  return pMeta;
}

static int getMaxEventSize(void)
{
  int max = 0;

  max = MAX(max, enc_msg_interface_evt_buffer_refcount_get_size());
  max = MAX(max, enc_msg_interface_evt_end_encoding_get_size());
  max = MAX(max, enc_msg_interface_evt_end_encoding_with_stat_get_size());
  max = MAX(max, enc_msg_interface_evt_destroy_marker_get_size());

  return max;
}

static void handleEvtBufferRefcount(void* buffer)
{
  struct msg_interface_evt_buffer_refcount event;

  EVENT_UNMARSHALL(event, buffer, msg_interface_evt_buffer_refcount);

  AL_Buffer_Unref((AL_TBuffer*)(intptr_t)event.pBuf);
}

static void copyStreamSections(struct msg_interface_evt_end_encoding* event)
{
  AL_TStreamSectionInBuffer* pSectionInBuffer;
  AL_HEncoderWrapper* pWrapper;
  AL_TStreamMetaData* pMeta;
  AL_TBuffer* pStream;
  int i;
  int j;

  pWrapper = (void*)(intptr_t)event->hWrapper;
  pStream = (AL_TBuffer*)(intptr_t)event->pStream;

  pMeta = (AL_TStreamMetaData*)AL_Buffer_GetMetaData(pStream, AL_META_TYPE_STREAM);
  assert(pMeta);

  pMeta->uNumSection = event->uNumSection;

  for(i = 0; i < event->uNumSection; i++)
    pMeta->pSections[i] = event->sections[i];

  if(!event->uNumSectionInBuffer)
    return;

  /* copy sections info located in section buffer */
  pSectionInBuffer = AL_RiscvCmaMap(pWrapper->pCtx->fd, event->uSectionBufferSize, event->uSectionBufferOffset);

  if(!pSectionInBuffer)
    return;

  pMeta->uNumSection += event->uNumSectionInBuffer;

  for(j = 0; j < event->uNumSectionInBuffer; j++)
  {
    pMeta->pSections[i + j].uOffset = pSectionInBuffer[j].uOffset;
    pMeta->pSections[i + j].uLength = pSectionInBuffer[j].uLength;
    pMeta->pSections[i + j].eFlags = pSectionInBuffer[j].eFlags;
  }

  AL_RiscvCmaUnmap(pSectionInBuffer, event->uSectionBufferSize);
  AL_RiscvCmaFree(pWrapper->pCtx->fd, event->pSectionBufferAddr);
}

static void copyPictureType(struct msg_interface_evt_end_encoding* event)
{
  AL_TPictureMetaData* pMeta;
  AL_TBuffer* pStream;

  pStream = (AL_TBuffer*)(intptr_t)event->pStream;

  pMeta = (AL_TPictureMetaData*)AL_Buffer_GetMetaData(pStream, AL_META_TYPE_PICTURE);

  if(pMeta)
  {
    pMeta->eType = event->eType;
    pMeta->bSkipped = event->bSkipped;
  }
}

static void handleEvtEndEncodingCommon(struct msg_interface_evt_end_encoding* event)
{
  if(event->pStream)
    copyStreamSections(event);

  if(event->pStream)
    copyPictureType(event);
}

static void handleEvtEndEncodingHostCb(struct msg_interface_evt_end_encoding* event)
{
  AL_HEncoderWrapper* pWrapper;
  AL_TBuffer* pStream;
  AL_TBuffer* pSrc;
  int32_t iLayerID;

  pWrapper = (void*)(intptr_t)event->hWrapper;
  pStream = (AL_TBuffer*)(intptr_t)event->pStream;
  pSrc = (AL_TBuffer*)(intptr_t)event->pSrc;

  iLayerID = event->iLayerID;
  pWrapper->CB[iLayerID].func(pWrapper->CB[iLayerID].userParam, pStream, pSrc, iLayerID);
}

static void handleEvtEndEncoding(void* buffer)
{
  struct msg_interface_evt_end_encoding event;

  EVENT_UNMARSHALL(event, buffer, msg_interface_evt_end_encoding);

  handleEvtEndEncodingCommon(&event);
  handleEvtEndEncodingHostCb(&event);
}

static void handleEvtEndEncodingCopyStats(struct msg_interface_evt_end_encoding_with_stat* event)
{
  AL_TBuffer* pStream = (AL_TBuffer*)(intptr_t)event->end_encoding.pStream;
  AL_TRateCtrlMetaData* pMeta;

  assert(pStream);

  pMeta = (AL_TRateCtrlMetaData*)AL_Buffer_GetMetaData(pStream, AL_META_TYPE_RATECTRL);
  assert(pMeta);

  pMeta->bFilled = event->bFilled;
  pMeta->tRateCtrlStats = event->stats;
}

static void handleEvtEndEncodingWithStat(void* buffer)
{
  struct msg_interface_evt_end_encoding_with_stat event;

  EVENT_UNMARSHALL(event, buffer, msg_interface_evt_end_encoding_with_stat);

  handleEvtEndEncodingCommon(&event.end_encoding);
  handleEvtEndEncodingCopyStats(&event);
  handleEvtEndEncodingHostCb(&event.end_encoding);
}

static void handleEvtDestroyMarker(void* buffer)
{
  struct msg_interface_evt_destroy_marker event;
  AL_HEncoderWrapper* pWrapper;

  EVENT_UNMARSHALL(event, buffer, msg_interface_evt_destroy_marker);
  pWrapper = (void*)(intptr_t)event.hWrapper;
  Rtos_SetEvent(pWrapper->destroyEvent);
}

static void* pollerThread(void* arg)
{
  AL_RiscvEncoderCtx* pCtx = arg;
  struct codec_event event;
  int ret;

  (void)arg;

  event.event = alloca(getMaxEventSize());

  while(!pCtx->is_shutdown)
  {
    ret = ioctl(pCtx->fd, CODEC_GET_EVENT, &event);

    /* This ioctl will timeout after 1 second to allow leaving this thread
     * properly.
     */
    if(ret && errno == ETIMEDOUT)
      continue;

    if(ret)
      break;
    switch(event.type)
    {
    case MSG_INTERFACE_TYPE_EVT_BUFFER_REFCOUNT:
      handleEvtBufferRefcount(event.event);
      break;
    case MSG_INTERFACE_TYPE_EVT_END_ENCODING:
      handleEvtEndEncoding(event.event);
      break;
    case MSG_INTERFACE_TYPE_EVT_END_ENCODING_WITH_STAT:
      handleEvtEndEncodingWithStat(event.event);
      break;
    case MSG_INTERFACE_TYPE_EVT_DESTROY_MARKER:
      handleEvtDestroyMarker(event.event);
      break;
    default:
      assert(0);
    }
  }

  return NULL;
}

static AL_ERR AL_Encoder_Create_Riscv(AL_HEncoder* hEnc, AL_IEncScheduler* pScheduler, AL_TAllocator* pAlloc, AL_TEncSettings const* pSettings, AL_CB_EndEncoding callback)
{
  (void)hEnc;
  (void)pScheduler;
  (void)pAlloc;
  (void)pSettings;
  (void)callback;

  return AL_ERROR;
}

static AL_ERR AL_Encoder_CreateWithCtx_Riscv(AL_HEncoder* hEnc, AL_RiscV_Ctx ctx, AL_TAllocator* pAlloc, AL_TEncSettings const* pSettings, AL_CB_EndEncoding callback)
{
  struct msg_interface_create_encoder_req_full req;
  struct msg_interface_create_encoder_reply reply;
  struct codec_cmd_reply cmd_reply;
  AL_RiscvEncoderCtx* pCtx = ctx;
  AL_HEncoderWrapper* pWrapper;
  int ret;

  (void)pAlloc;

  pWrapper = Rtos_Malloc(sizeof(*pWrapper));

  if(!pWrapper)
    return AL_ERR_NO_MEMORY;

  pWrapper->destroyEvent = Rtos_CreateEvent(false);

  if(!pWrapper->destroyEvent)
  {
    Rtos_Free(pWrapper);
    return AL_ERR_NO_MEMORY;
  }

  req.hdr.type = MSG_INTERFACE_TYPE_CREATE_ENCODER_REQ;
  req.req.hWrapper = (intptr_t)pWrapper;
  req.req.settings = *pSettings;

  if(req.req.settings.hRcPluginDmaContext)
    req.req.settings.hRcPluginDmaContext = (AL_HANDLE)(intptr_t)AL_Allocator_GetPhysicalAddr(pAlloc, req.req.settings.hRcPluginDmaContext);

  CMD_MARSHALL(cmd_reply, req, msg_interface_create_encoder);
  ret = ioctl(pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_interface_create_encoder);

  if(ret || AL_IS_ERROR_CODE(reply.ret))
    goto error;

  pWrapper->pCtx = pCtx;
  pWrapper->hEnc = reply.hEnc;
  pWrapper->CB[0] = callback;
  pWrapper->eProfile = pSettings->tChParam[0].eProfile;
  pWrapper->eStartCodeBytesAligned = pSettings->tChParam[0].eStartCodeBytesAligned;
  SetChannelInfo(&pWrapper->chanInfo[0], &pSettings->tChParam[0]);

  *hEnc = pWrapper;

  return reply.ret;

  error:
  Rtos_DeleteEvent(pWrapper->destroyEvent);
  Rtos_Free(pWrapper);

  return ret ? AL_ERROR : reply.ret;
}

static void AL_Encoder_Destroy_Riscv(AL_HEncoder hEnc)
{
  struct msg_interface_destroy_encoder_req_full req;
  AL_HEncoderWrapper* pWrapper = hEnc;
  struct codec_cmd_reply cmd_reply;

  req.hdr.type = MSG_INTERFACE_TYPE_DESTROY_ENCODER_REQ;
  req.req.hEnc = pWrapper->hEnc;

  CMD_MARSHALL(cmd_reply, req, msg_interface_destroy_encoder);
  ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  Rtos_WaitEvent(pWrapper->destroyEvent, AL_WAIT_FOREVER);
  Rtos_DeleteEvent(pWrapper->destroyEvent);
  Rtos_Free(pWrapper);
}

static bool AL_Encoder_GetInfo_Riscv(AL_HEncoder hEnc, AL_TEncoderInfo* pEncInfo)
{
  (void)hEnc;

  AL_HEncoderWrapper* pWrapper = hEnc;
  struct msg_interface_get_info_req_full req;
  struct msg_interface_get_info_reply reply;
  struct codec_cmd_reply cmd_reply;
  int ret;

  req.hdr.type = MSG_INTERFACE_TYPE_GET_INFO_REQ;
  req.req.hEnc = pWrapper->hEnc;

  CMD_MARSHALL(cmd_reply, req, msg_interface_get_info);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_interface_get_info);

  if(ret)
    return false;

  *pEncInfo = reply.tEncInfo;
  return true;
}

static int AL_Encoder_NotifyCommon(AL_HEncoder hEnc, struct msg_interface_notify_req_full* req)
{
  AL_HEncoderWrapper* pWrapper = hEnc;
  struct msg_interface_notify_reply reply;
  struct codec_cmd_reply cmd_reply;
  int ret;

  req->hdr.type = MSG_INTERFACE_TYPE_NOTIFY_REQ;
  req->req.hEnc = pWrapper->hEnc;

  CMD_MARSHALL_REF(cmd_reply, req, msg_interface_notify);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_interface_notify);

  return ret ? AL_ERROR : reply.res;
}

static void AL_Encoder_NotifySceneChange_Riscv(AL_HEncoder hEnc, int iAhead)
{
  struct msg_interface_notify_req_full req;

  req.req.cmd = NOTIFY_CMD_SCENE_CHANGE;
  req.req.iAhead = iAhead;

  AL_Encoder_NotifyCommon(hEnc, &req);
}

static void AL_Encoder_NotifyIsLongTerm_Riscv(AL_HEncoder hEnc)
{
  struct msg_interface_notify_req_full req;

  req.req.cmd = NOTIFY_CMD_IS_LONG_TERM;

  AL_Encoder_NotifyCommon(hEnc, &req);
}

static void AL_Encoder_NotifyUseLongTerm_Riscv(AL_HEncoder hEnc)
{
  struct msg_interface_notify_req_full req;

  req.req.cmd = NOTIFY_CMD_USE_LONG_TERM;

  AL_Encoder_NotifyCommon(hEnc, &req);
}

static void AL_Encoder_NotifyIsSkip_Riscv(AL_HEncoder hEnc)
{
  struct msg_interface_notify_req_full req;

  req.req.cmd = NOTIFY_CMD_IS_SKIP;

  AL_Encoder_NotifyCommon(hEnc, &req);
}

static void AL_Encoder_NotifyGMV_Riscv(AL_HEncoder hEnc, int iNumFrame, int GMV_x, int GMV_y)
{
  struct msg_interface_notify_req_full req;

  req.req.cmd = NOTIFY_CMD_GMV;
  req.req.iNumFrame = iNumFrame;
  req.req.GMV_x = GMV_x;
  req.req.GMV_y = GMV_y;

  AL_Encoder_NotifyCommon(hEnc, &req);
}

static AL_TRiscvMetaData* getOrAllocRiscvMetaData(AL_TBuffer* pBuf)
{
  AL_TRiscvMetaData* pRiscvMeta;

  pRiscvMeta = (AL_TRiscvMetaData*)AL_Buffer_GetMetaData(pBuf, AL_META_TYPE_RISCV);

  if(pRiscvMeta)
    return pRiscvMeta;

  pRiscvMeta = AL_RiscvMetaData_Create();

  if(!pRiscvMeta)
    return NULL;

  if(AL_Buffer_AddMetaData(pBuf, &pRiscvMeta->tMeta))
    return pRiscvMeta;

  AL_MetaData_Destroy(&pRiscvMeta->tMeta);

  return NULL;
}

static void AL_Encoder_ReleaseRecPicture_Common(AL_HEncoderWrapper* pWrapper, uint64_t pRec, AL_TReconstructedInfo* pRecInfo, int iLayerID)
{
  struct msg_interface_release_rec_req_full req;
  struct msg_interface_release_rec_reply reply;
  struct codec_cmd_reply cmd_reply;

  req.hdr.type = MSG_INTERFACE_TYPE_RELEASE_REC_REQ;
  req.req.hEnc = pWrapper->hEnc;
  req.req.pRec = pRec;
  req.req.recInfo = *pRecInfo;
  req.req.iLayerID = iLayerID;

  CMD_MARSHALL(cmd_reply, req, msg_interface_release_rec);
  ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_interface_release_rec);
}

static bool AL_Encoder_GetRecPicture_Layer(AL_HEncoder hEnc, AL_TRecPic* pRecPic, int iLayerID)
{
  struct msg_interface_get_rec_req_full req;
  struct msg_interface_get_rec_reply reply;
  AL_HEncoderWrapper* pWrapper = hEnc;
  struct codec_cmd_reply cmd_reply;
  AL_TRiscvMetaData* pMeta;
  AL_HANDLE hRecBuf;
  bool res;
  int ret;

  req.hdr.type = MSG_INTERFACE_TYPE_GET_REC_REQ;
  req.req.hEnc = pWrapper->hEnc;
  req.req.iLayerID = iLayerID;

  CMD_MARSHALL(cmd_reply, req, msg_interface_get_rec);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_interface_get_rec);

  res = ret ? false : reply.res;

  if(!res)
    return false;

  hRecBuf = RiscvProxy_CreateByAddr(pWrapper->pCtx->proxyAllocator, reply.chunk.pAddr, reply.chunk.uSize);

  if(!hRecBuf)
  {
    AL_Encoder_ReleaseRecPicture_Common(pWrapper, reply.pRec, &reply.recInfo, iLayerID);
    return false;
  }

  SetRecPic(pRecPic, pWrapper->pCtx->proxyAllocator, hRecBuf, &pWrapper->chanInfo[iLayerID], &reply.recInfo);

  pMeta = getOrAllocRiscvMetaData(pRecPic->pBuf);

  if(!pMeta)
  {
    AL_Allocator_Free(pWrapper->pCtx->proxyAllocator, hRecBuf);
    AL_Encoder_ReleaseRecPicture_Common(pWrapper, reply.pRec, &reply.recInfo, iLayerID);
    return false;
  }

  pMeta->pRec = reply.pRec;
  pMeta->recInfo = reply.recInfo;

  return true;
}

static bool AL_Encoder_GetRecPicture_Riscv(AL_HEncoder hEnc, AL_TRecPic* pRecPic)
{
  return AL_Encoder_GetRecPicture_Layer(hEnc, pRecPic, 0);
}

static void AL_Encoder_ReleaseRecPicture_Layer(AL_HEncoder hEnc, AL_TRecPic* pRecPic, int iLayerID)
{
  AL_HEncoderWrapper* pWrapper = hEnc;
  AL_TRiscvMetaData* pMeta;

  pMeta = (AL_TRiscvMetaData*)AL_Buffer_GetMetaData(pRecPic->pBuf, AL_META_TYPE_RISCV);
  assert(pMeta);

  AL_Encoder_ReleaseRecPicture_Common(pWrapper, pMeta->pRec, &pMeta->recInfo, iLayerID);
}

static void AL_Encoder_ReleaseRecPicture_Riscv(AL_HEncoder hEnc, AL_TRecPic* pRecPic)
{
  AL_Encoder_ReleaseRecPicture_Layer(hEnc, pRecPic, 0);
}

static bool AL_Encoder_PutStreamBuffer_Layer(AL_HEncoder hEnc, AL_TBuffer* pStream, int iLayerID)
{
  struct msg_interface_push_stream_buffer_req_full req;
  struct msg_interface_push_stream_buffer_reply reply;
  AL_HEncoderWrapper* pWrapper = hEnc;
  struct codec_cmd_reply cmd_reply;
  AL_TRateCtrlMetaData* pMeta;
  bool res;
  int ret;

  req.hdr.type = MSG_INTERFACE_TYPE_PUSH_STREAM_BUFFER_REQ;
  req.req.hEnc = pWrapper->hEnc;
  req.req.pStream = (intptr_t)pStream;
  req.req.pAddr = AL_Buffer_GetPhysicalAddress(pStream);
  req.req.uSize = AL_Buffer_GetSize(pStream);
  req.req.iLayerID = iLayerID;
  req.req.pAddrStats = 0;
  req.req.uSizeStats = 0;

  pMeta = (AL_TRateCtrlMetaData*)AL_Buffer_GetMetaData(pStream, AL_META_TYPE_RATECTRL);

  if(pMeta)
  {
    req.req.pAddrStats = AL_Buffer_GetPhysicalAddress(pMeta->pMVBuf);
    req.req.uSizeStats = AL_Buffer_GetSize(pMeta->pMVBuf);
  }

  AL_Buffer_Ref(pStream);
  CMD_MARSHALL(cmd_reply, req, msg_interface_push_stream_buffer);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_interface_push_stream_buffer);

  res = ret ? false : reply.res;

  if(!res)
    AL_Buffer_Unref(pStream);

  return res;
}

static bool AL_Encoder_PutStreamBuffer_Riscv(AL_HEncoder hEnc, AL_TBuffer* pStream)
{
  return AL_Encoder_PutStreamBuffer_Layer(hEnc, pStream, 0);
}

static bool AL_Encoder_Process_Frame_Layer(AL_HEncoder hEnc, AL_TBuffer* pFrame, AL_TBuffer* pQpTable, int iLayerID)
{
  AL_HEncoderWrapper* pWrapper = hEnc;
  struct msg_interface_process_req_full req;
  struct msg_interface_process_reply reply;
  struct codec_cmd_reply cmd_reply;
  AL_TPixMapMetaData* pMeta;
  bool res;
  int ret;
  int i;

  (void)pQpTable;

  pMeta = (AL_TPixMapMetaData*)AL_Buffer_GetMetaData(pFrame, AL_META_TYPE_PIXMAP);

  if(!pMeta)
    return false;

  req.hdr.type = MSG_INTERFACE_TYPE_PROCESS_REQ;
  req.req.hEnc = pWrapper->hEnc;
  req.req.pFrame = (intptr_t)pFrame;
  req.req.tDim = pMeta->tDim;
  req.req.tFourCC = pMeta->tFourCC;
  req.req.pQpTable = 0;
  req.req.pAddr = 0;
  req.req.uSize = 0;
  req.req.iLayerID = iLayerID;

  for(i = 0; i < AL_BUFFER_MAX_CHUNK; i++)
  {
    req.req.chunks[i].pAddr = AL_Buffer_GetPhysicalAddressChunk(pFrame, i);
    req.req.chunks[i].uSize = AL_Buffer_GetSizeChunk(pFrame, i);
  }

  for(i = 0; i < AL_PLANE_MAX_ENUM; i++)
    req.req.tPlanes[i] = pMeta->tPlanes[i];

  AL_Buffer_Ref(pFrame);

  if(pQpTable)
  {
    req.req.pQpTable = (intptr_t)pQpTable;
    req.req.pAddr = AL_Buffer_GetPhysicalAddress(pQpTable);
    req.req.uSize = AL_Buffer_GetSize(pQpTable);
    AL_Buffer_Ref(pQpTable);
  }
  CMD_MARSHALL(cmd_reply, req, msg_interface_process);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_interface_process);

  res = ret ? false : reply.res;

  if(!res)
  {
    if(pQpTable)
      AL_Buffer_Unref(pQpTable);
    AL_Buffer_Unref(pFrame);
  }

  return res;
}

static bool AL_Encoder_Process_Flush_Layer(AL_HEncoder hEnc, int iLayerID)
{
  AL_HEncoderWrapper* pWrapper = hEnc;
  struct msg_interface_process_req_full req;
  struct msg_interface_process_reply reply;
  struct codec_cmd_reply cmd_reply;
  int ret;

  req.hdr.type = MSG_INTERFACE_TYPE_PROCESS_REQ;
  req.req.hEnc = pWrapper->hEnc;
  req.req.pFrame = 0;
  req.req.iLayerID = iLayerID;

  CMD_MARSHALL(cmd_reply, req, msg_interface_process);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_interface_process);

  return ret ? false : reply.res;
}

static bool AL_Encoder_Process_Layer(AL_HEncoder hEnc, AL_TBuffer* pFrame, AL_TBuffer* pQpTable, int iLayerID)
{
  if(pFrame)
    return AL_Encoder_Process_Frame_Layer(hEnc, pFrame, pQpTable, iLayerID);
  else
    return AL_Encoder_Process_Flush_Layer(hEnc, iLayerID);
}

static bool AL_Encoder_Process_Riscv(AL_HEncoder hEnc, AL_TBuffer* pFrame, AL_TBuffer* pQpTable)
{
  return AL_Encoder_Process_Layer(hEnc, pFrame, pQpTable, 0);
}

static int AL_Encoder_AddSei_Riscv(AL_HEncoder hEnc, AL_TBuffer* pStream, bool isPrefix, int iPayloadType, uint8_t* pPayload, int iPayloadSize, int iTempId)
{
  AL_HEncoderWrapper* pWrapper = hEnc;
  AL_TNuts nuts;
  bool exists;

  exists = AL_CreateNuts(&nuts, pWrapper->eProfile);

  if(!exists)
    return -1;

  return AL_WriteSeiSection(AL_GET_CODEC(pWrapper->eProfile), nuts, pStream, isPrefix, iPayloadType, pPayload,
                            iPayloadSize, iTempId, pWrapper->eStartCodeBytesAligned);
}

static AL_ERR AL_Encoder_GetLastError_Riscv(AL_HEncoder hEnc)
{
  struct msg_interface_get_last_error_req_full req;
  struct msg_interface_get_last_error_reply reply;
  AL_HEncoderWrapper* pWrapper = hEnc;
  struct codec_cmd_reply cmd_reply;
  int ret;

  req.hdr.type = MSG_INTERFACE_TYPE_GET_LAST_ERROR_REQ;
  req.req.hEnc = pWrapper->hEnc;

  CMD_MARSHALL(cmd_reply, req, msg_interface_get_last_error);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_interface_get_last_error);

  return ret ? AL_ERROR : reply.res;
}

static bool AL_Encoder_SmartCommon(AL_HEncoder hEnc, struct msg_interface_smart_req_full* req)
{
  AL_HEncoderWrapper* pWrapper = hEnc;
  struct msg_interface_smart_reply reply;
  struct codec_cmd_reply cmd_reply;
  int ret;

  req->hdr.type = MSG_INTERFACE_TYPE_SMART_REQ;
  req->req.hEnc = pWrapper->hEnc;

  CMD_MARSHALL_REF(cmd_reply, req, msg_interface_smart);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_interface_smart);

  return ret ? false : reply.res;
}

static bool AL_Encoder_SetCostMode_Riscv(AL_HEncoder hEnc, bool costMode)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_COST_MODE;
  req.req.costMode = costMode;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetAutoQPThresholdAndDelta_Riscv(AL_HEncoder hEnc, bool bUserAutoQP, AL_TAutoQPCtrl* userAutoQPValues)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_AUTO_QP_THRESHOLD_AND_DELTA;
  req.req.bUserAutoQP = bUserAutoQP;
  req.req.userAutoQPValues = *userAutoQPValues;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_RestartGop_Riscv(AL_HEncoder hEnc)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_RESTART_GOP;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_RestartGopRecoveryPoint_Riscv(AL_HEncoder hEnc)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_RESTART_GOP_RECOVERY_POINT;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetGopLength_Riscv(AL_HEncoder hEnc, int iGopLength)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_GOP_LENGTH;
  req.req.iGopLength = iGopLength;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetGopNumB_Riscv(AL_HEncoder hEnc, int iNumB)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_GOP_NUMB;
  req.req.iNumB = iNumB;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetFreqIDR_Riscv(AL_HEncoder hEnc, int iFreqIDR)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_FREQ_IDR;
  req.req.iFreqIDR = iFreqIDR;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetBitRate_Riscv(AL_HEncoder hEnc, int iBitRate)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_BITRATE;
  req.req.iBitRate = iBitRate;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetMaxBitRate_Riscv(AL_HEncoder hEnc, int iTargetBitRate, int iMaxBitRate)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_MAXBITRATE;
  req.req.iTargetBitRate = iTargetBitRate;
  req.req.iMaxBitRate = iMaxBitRate;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetFrameRate_Riscv(AL_HEncoder hEnc, uint16_t uFrameRate, uint16_t uClkRatio)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_FRAMERATE;
  req.req.uFrameRate = uFrameRate;
  req.req.uClkRatio = uClkRatio;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetQP_Riscv(AL_HEncoder hEnc, int16_t iQP)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_QP;
  req.req.iQP = iQP;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetQPOffset_Riscv(AL_HEncoder hEnc, int16_t iQPOffset)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_QP_OFFSET;
  req.req.iQPOffset = iQPOffset;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetQPBounds_Riscv(AL_HEncoder hEnc, int16_t iMinQP, int16_t iMaxQP)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_QP_BOUNDS;
  req.req.iMinQP = iMinQP;
  req.req.iMaxQP = iMaxQP;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetQPBoundsPerFrameType_Riscv(AL_HEncoder hEnc, int16_t iMinQP, int16_t iMaxQP, AL_ESliceType sliceType)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_QP_BOUNDS_PER_FRAME_TYPE;
  req.req.iMinQP = iMinQP;
  req.req.iMaxQP = iMaxQP;
  req.req.sliceType = sliceType;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetQPIPDelta_Riscv(AL_HEncoder hEnc, int16_t uIPDelta)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_QPIP_DELTA;
  req.req.uIPDelta = uIPDelta;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetQPPBDelta_Riscv(AL_HEncoder hEnc, int16_t uPBDelta)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_QPPB_DELTA;
  req.req.uPBDelta = uPBDelta;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetInputResolution_Riscv(AL_HEncoder hEnc, AL_TDimension tDim)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_INPUT_RES;
  req.req.tDim = tDim;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetLoopFilterBetaOffset_Riscv(AL_HEncoder hEnc, int8_t iBetaOffset)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_LOOP_FILTER_BETA_OFFSET;
  req.req.iBetaOffset = iBetaOffset;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetLoopFilterTcOffset_Riscv(AL_HEncoder hEnc, int8_t iTcOffset)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_LOOP_FILTER_TC_OFFSET;
  req.req.iTcOffset = iTcOffset;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetQPChromaOffsets_Riscv(AL_HEncoder hEnc, int8_t iQp1Offset, int8_t iQp2Offset)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_QP_CHROMA_OFFSETS;
  req.req.iQp1Offset = iQp1Offset;
  req.req.iQp2Offset = iQp2Offset;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetAutoQP_Riscv(AL_HEncoder hEnc, bool useAutoQP)
{
  struct msg_interface_smart_req_full req;

  req.req.cmd = SMART_CMD_SET_AUTO_QP;
  req.req.useAutoQP = useAutoQP;

  return AL_Encoder_SmartCommon(hEnc, &req);
}

static bool AL_Encoder_SetHDRSEIs_Riscv(AL_HEncoder hEnc, AL_THDRSEIs* pHDRSEIs)
{
  AL_HEncoderWrapper* pWrapper = hEnc;
  struct msg_interface_hdr_req_full req;
  struct msg_interface_hdr_reply reply;
  struct codec_cmd_reply cmd_reply;
  int ret;

  req.hdr.type = MSG_INTERFACE_TYPE_HDR_REQ;
  req.req.hEnc = pWrapper->hEnc;
  req.req.pHDRSEIs = *pHDRSEIs;

  CMD_MARSHALL(cmd_reply, req, msg_interface_hdr);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_interface_hdr);

  return ret ? false : reply.res;
}

static void AL_Deinit_Riscv(void)
{
  ;
}

static AL_IEncArchVtable vtable =
{
  .Deinit = AL_Deinit_Riscv,
  .EncoderCreate = AL_Encoder_Create_Riscv,
  .EncoderCreateWithCtx = AL_Encoder_CreateWithCtx_Riscv,
  .EncoderDestroy = AL_Encoder_Destroy_Riscv,
  .EncoderGetInfo = AL_Encoder_GetInfo_Riscv,
  .EncoderNotifySceneChange = AL_Encoder_NotifySceneChange_Riscv,
  .EncoderNotifyIsLongTerm = AL_Encoder_NotifyIsLongTerm_Riscv,
  .EncoderNotifyUseLongTerm = AL_Encoder_NotifyUseLongTerm_Riscv,
  .EncoderNotifyIsSkip = AL_Encoder_NotifyIsSkip_Riscv,
  .EncoderNotifyGMV = AL_Encoder_NotifyGMV_Riscv,
  .EncoderGetRecPicture = AL_Encoder_GetRecPicture_Riscv,
  .EncoderReleaseRecPicture = AL_Encoder_ReleaseRecPicture_Riscv,
  .EncoderPutStreamBuffer = AL_Encoder_PutStreamBuffer_Riscv,
  .EncoderProcess = AL_Encoder_Process_Riscv,
  .EncoderAddSei = AL_Encoder_AddSei_Riscv,
  .EncoderGetLastError = AL_Encoder_GetLastError_Riscv,
  .EncoderSetCostMode = AL_Encoder_SetCostMode_Riscv,
  .EncoderSetAutoQPThresholdAndDelta = AL_Encoder_SetAutoQPThresholdAndDelta_Riscv,
  .EncoderRestartGop = AL_Encoder_RestartGop_Riscv,
  .EncoderRestartGopRecoveryPoint = AL_Encoder_RestartGopRecoveryPoint_Riscv,
  .EncoderSetGopLength = AL_Encoder_SetGopLength_Riscv,
  .EncoderSetGopNumB = AL_Encoder_SetGopNumB_Riscv,
  .EncoderSetFreqIDR = AL_Encoder_SetFreqIDR_Riscv,
  .EncoderSetBitRate = AL_Encoder_SetBitRate_Riscv,
  .EncoderSetMaxBitRate = AL_Encoder_SetMaxBitRate_Riscv,
  .EncoderSetFrameRate = AL_Encoder_SetFrameRate_Riscv,
  .EncoderSetQP = AL_Encoder_SetQP_Riscv,
  .EncoderSetQPOffset = AL_Encoder_SetQPOffset_Riscv,
  .EncoderSetQPBounds = AL_Encoder_SetQPBounds_Riscv,
  .EncoderSetQPBoundsPerFrameType = AL_Encoder_SetQPBoundsPerFrameType_Riscv,
  .EncoderSetQPIPDelta = AL_Encoder_SetQPIPDelta_Riscv,
  .EncoderSetQPPBDelta = AL_Encoder_SetQPPBDelta_Riscv,
  .EncoderSetInputResolution = AL_Encoder_SetInputResolution_Riscv,
  .EncoderSetLoopFilterBetaOffset = AL_Encoder_SetLoopFilterBetaOffset_Riscv,
  .EncoderSetLoopFilterTcOffset = AL_Encoder_SetLoopFilterTcOffset_Riscv,
  .EncoderSetQPChromaOffsets = AL_Encoder_SetQPChromaOffsets_Riscv,
  .EncoderSetAutoQP = AL_Encoder_SetAutoQP_Riscv,
  .EncoderSetHDRSEIs = AL_Encoder_SetHDRSEIs_Riscv,
};

AL_IEncArch encRiscv =
{
  .vtable = &vtable
};

/*****************************************************************************/
AL_IEncArch* LibEncodeRiscvGet(void)
{
  return &encRiscv;
}

/*****************************************************************************/
AL_RiscV_Ctx AL_Riscv_Encode_CreateCtx(const char* deviceName)
{
  AL_RiscvEncoderCtx* pCtx;

  pCtx = Rtos_Malloc(sizeof(*pCtx));

  if(!pCtx)
    return NULL;

  pCtx->is_shutdown = false;
  pCtx->fd = (int)(intptr_t)Rtos_DriverOpen(deviceName);

  if(!pCtx->fd)
    goto fail_open;

  pCtx->poller = Rtos_CreateThread(pollerThread, pCtx);

  if(!pCtx->poller)
    goto fail_thread;

  pCtx->proxyAllocator = AL_RiscvGetProxyAllocator(pCtx->fd);

  return pCtx;

  fail_thread:
  Rtos_DriverClose((void*)(intptr_t)pCtx->fd);
  fail_open:
  Rtos_Free(pCtx);

  return NULL;
}

/*****************************************************************************/
void AL_Riscv_Encode_DestroyCtx(AL_RiscV_Ctx ctx)
{
  AL_RiscvEncoderCtx* pCtx = ctx;

  pCtx->is_shutdown = true;
  Rtos_JoinThread(pCtx->poller);
  Rtos_DeleteThread(pCtx->poller);
  AL_Allocator_Destroy(pCtx->proxyAllocator);
  Rtos_DriverClose((void*)(intptr_t)pCtx->fd);
  Rtos_Free(pCtx);
}

/*****************************************************************************/
AL_TAllocator* AL_Riscv_Encode_DmaAlloc_Create(AL_RiscV_Ctx ctx)
{
  AL_RiscvEncoderCtx* pCtx = ctx;

  return AL_RiscvGetDmaAllocator(pCtx->fd);
}
