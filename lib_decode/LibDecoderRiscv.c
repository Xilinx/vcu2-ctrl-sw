// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include <alloca.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>

#include "lib_decode/lib_decode.h"
#include "LibDecoderRiscvInternal.h"
#include "lib_decode/LibDecoderRiscv.h"
#include "lib_common/BufferAPIInternal.h"
#include "lib_common_dec/DecBuffersInternal.h"
#include "lib_common/RiscvDmaAllocator.h"
#include "lib_common/BufferStreamMeta.h"
#include "lib_common_dec/HDRMeta.h"
#include "lib_common/Utils.h"

#include "lib_decode/msg_itf_generated.h"
#include "lib_common/codec_uapi.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define CMD_MARSHALL(cmd, req, type_lower) do { \
    struct rd_wr_ctx ctx; \
\
    req.hdr.payload_len = type_lower ## _req_get_size(); \
    cmd.req_size = type_lower ## _req_full_get_size(); \
    cmd.reply_size = type_lower ## _reply_get_size(); \
    cmd.req = alloca(cmd.req_size); \
    cmd.reply = alloca(cmd.reply_size); \
    ctx.pos = 0; \
    ctx.buffer = cmd.req; \
    type_lower ## _req_full_marshall(&req, write_cb, &ctx); \
} while(0)

#define REPLY_UNMARSHALL(cmd, reply, type_lower) do { \
    struct rd_wr_ctx ctx; \
\
    ctx.pos = 0; \
    ctx.buffer = cmd.reply; \
    type_lower ## _reply_unmarshall(&reply, read_cb, &ctx); \
} while(0)

#define EVENT_UNMARSHALL(event, buffer, type_lower) do { \
    struct rd_wr_ctx ctx; \
\
    ctx.pos = 0; \
    ctx.buffer = buffer; \
    type_lower ## _unmarshall(&event, read_cb, &ctx); \
} while(0)

typedef struct
{
  int fd;
  AL_THREAD poller;
  volatile bool is_shutdown;
}AL_RiscvDecoderCtx;

typedef struct
{
  uint64_t hDec;
  AL_TDecCallBacks CB;
  AL_RiscvDecoderCtx* pCtx;
  AL_EVENT destroyEvent;
}AL_HDecoderWrapper;

typedef struct AL_TRiscvMetaData
{
  AL_TMetaData tMeta;
  uint32_t decodedError;
}AL_TRiscvMetaData;

struct rd_wr_ctx
{
  char* buffer;
  int pos;
};

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

  copy->decodedError = original->decodedError;

  return &copy->tMeta;
}

static AL_TRiscvMetaData* AL_RiscvMetaData_Create()
{
  AL_TRiscvMetaData* pMeta = (AL_TRiscvMetaData*)Rtos_Malloc(sizeof(*pMeta));

  if(!pMeta)
    return NULL;

  pMeta->tMeta.eType = AL_META_TYPE_RISCV;
  pMeta->tMeta.MetaDestroy = RiscvMeta_Destroy;
  pMeta->tMeta.MetaClone = RiscvMeta_Clone;
  pMeta->decodedError = AL_SUCCESS;

  return pMeta;
}

static int getMaxEventSize(void)
{
  int max = 0;

  max = MAX(max, msg_itf_evt_bitstream_buffer_refcount_get_size());
  max = MAX(max, msg_itf_evt_display_picture_refcount_get_size());
  max = MAX(max, msg_itf_evt_resolution_found_get_size());
  max = MAX(max, msg_itf_evt_end_parsing_get_size());
  max = MAX(max, msg_itf_evt_end_decoding_get_size());
  max = MAX(max, msg_itf_evt_display_get_size());
  max = MAX(max, msg_itf_evt_sei_buf_get_size());
  max = MAX(max, msg_itf_evt_sei_msg_get_size());
  max = MAX(max, msg_itf_evt_error_get_size());
  max = MAX(max, msg_itf_evt_display_with_hdr_get_size());
  max = MAX(max, msg_itf_evt_destroy_marker_get_size());

  return max;
}

static void handleEvtBitstreamBufferRefcount(void* buffer)
{
  struct msg_itf_evt_bitstream_buffer_refcount event;

  EVENT_UNMARSHALL(event, buffer, msg_itf_evt_bitstream_buffer_refcount);

  AL_Buffer_Unref((AL_TBuffer*)(intptr_t)event.pBuf);
}

static void handleEvtDisplayPictureBufferRefcount(void* buffer)
{
  struct msg_itf_evt_display_picture_refcount event;

  EVENT_UNMARSHALL(event, buffer, msg_itf_evt_display_picture_refcount);

  AL_Buffer_Unref((AL_TBuffer*)(intptr_t)event.pDisplay);
}

static void handleEvtResolutionFound(void* buffer)
{
  struct msg_itf_evt_resolution_found event;
  AL_HDecoderWrapper* pWrapper;

  EVENT_UNMARSHALL(event, buffer, msg_itf_evt_resolution_found);

  pWrapper = (void*)(intptr_t)event.hWrapper;
  pWrapper->CB.resolutionFoundCB.func(event.BufferNumber, &event.settings, &event.cropInfo,
                                      pWrapper->CB.resolutionFoundCB.userParam);
}

static void handleEvtEndParsing(void* buffer)
{
  struct msg_itf_evt_end_parsing event;
  AL_HDecoderWrapper* pWrapper;
  AL_TBuffer* pParsedFrame;

  EVENT_UNMARSHALL(event, buffer, msg_itf_evt_end_parsing);

  pWrapper = (void*)(intptr_t)event.hWrapper;
  pParsedFrame = (AL_TBuffer*)(intptr_t)event.pParsedFrame;

  /* endParsingCB can be NULL */
  if(pWrapper->CB.endParsingCB.func)
    pWrapper->CB.endParsingCB.func(pParsedFrame, pWrapper->CB.endParsingCB.userParam,
                                   event.iParsingID);
}

static void handleEvtEndDecoding(void* buffer)
{
  struct msg_itf_evt_end_decoding event;
  AL_HDecoderWrapper* pWrapper;
  AL_TBuffer* pDecodedFrame;

  EVENT_UNMARSHALL(event, buffer, msg_itf_evt_end_decoding);

  pWrapper = (void*)(intptr_t)event.hWrapper;
  pDecodedFrame = (AL_TBuffer*)(intptr_t)event.pDecodedFrame;

  pWrapper->CB.endDecodingCB.func(pDecodedFrame, pWrapper->CB.endDecodingCB.userParam);
}

static void handleEvtDisplay(struct msg_itf_evt_display* evt)
{
  AL_TRiscvMetaData* pRiscvMeta;
  AL_HDecoderWrapper* pWrapper;
  AL_TBuffer* pDisplayedFrame;
  AL_TPixMapMetaData* pMeta;

  pWrapper = (void*)(intptr_t)evt->hWrapper;
  pDisplayedFrame = (AL_TBuffer*)(intptr_t)evt->pDisplayedFrame;

  if(pDisplayedFrame)
  {
    pMeta = (AL_TPixMapMetaData*)AL_Buffer_GetMetaData(pDisplayedFrame, AL_META_TYPE_PIXMAP);
    assert(pMeta);
    pMeta->tDim = evt->tDim;
    pMeta->tFourCC = evt->tFourCC;

    pRiscvMeta = (AL_TRiscvMetaData*)AL_Buffer_GetMetaData(pDisplayedFrame, AL_META_TYPE_RISCV);
    assert(pRiscvMeta);
    pRiscvMeta->decodedError = evt->decodedError;
  }

  pWrapper->CB.displayCB.func(pDisplayedFrame, evt->pInfo ? &evt->info : NULL,
                              pWrapper->CB.displayCB.userParam);
}

static void handleEvtDisplayWithoutHdr(void* buffer)
{
  struct msg_itf_evt_display event;

  EVENT_UNMARSHALL(event, buffer, msg_itf_evt_display);

  handleEvtDisplay(&event);
}

static void handleEvtDisplayWithHdr(void* buffer)
{
  struct msg_itf_evt_display_with_hdr event;
  AL_TBuffer* pDisplayedFrame;
  AL_THDRMetaData* pMetaHdr;

  EVENT_UNMARSHALL(event, buffer, msg_itf_evt_display_with_hdr);
  pDisplayedFrame = (AL_TBuffer*)(intptr_t)event.evt_display.pDisplayedFrame;

  pMetaHdr = pDisplayedFrame ? (AL_THDRMetaData*)AL_Buffer_GetMetaData(pDisplayedFrame, AL_META_TYPE_HDR) : NULL;

  if(pMetaHdr)
  {
    pMetaHdr->eColourDescription = event.eColourDescription;
    pMetaHdr->eTransferCharacteristics = event.eTransferCharacteristics;
    pMetaHdr->eColourMatrixCoeffs = event.eColourMatrixCoeffs;
    pMetaHdr->tHDRSEIs = event.tHDRSEIs;
  }

  handleEvtDisplay(&event.evt_display);
}

static void handleEvtSeiBuf(void* buffer)
{
  struct msg_itf_evt_sei_buf event;
  AL_HDecoderWrapper* pWrapper;
  void* pSeiBuffer = NULL;
  int32_t iPayloadSize;

  EVENT_UNMARSHALL(event, buffer, msg_itf_evt_sei_buf);
  pWrapper = (void*)(intptr_t)event.hWrapper;
  pSeiBuffer = AL_RiscvCmaMap(pWrapper->pCtx->fd, event.iPayloadSize, event.uOffsetSei);
  iPayloadSize = pSeiBuffer ? event.iPayloadSize : 0;

  /* parsedSeiCB can be NULL */
  if(pWrapper->CB.parsedSeiCB.func)
    pWrapper->CB.parsedSeiCB.func(event.bIsPrefix, event.iPayloadType, pSeiBuffer,
                                  iPayloadSize, pWrapper->CB.parsedSeiCB.userParam);

  AL_RiscvCmaUnmap(pSeiBuffer, event.iPayloadSize);
  AL_RiscvCmaFree(pWrapper->pCtx->fd, event.pAddrSei);
}

static void handleEvtSeiMsg(void* buffer)
{
  struct msg_itf_evt_sei_msg event;
  AL_HDecoderWrapper* pWrapper;

  EVENT_UNMARSHALL(event, buffer, msg_itf_evt_sei_msg);

  pWrapper = (void*)(intptr_t)event.hWrapper;
  pWrapper->CB.parsedSeiCB.func(event.bIsPrefix, event.iPayloadType, event.payload,
                                event.iPayloadSize, pWrapper->CB.parsedSeiCB.userParam);
}

static void handleErrorMsg(void* buffer)
{
  struct msg_itf_evt_error event;
  AL_HDecoderWrapper* pWrapper;

  EVENT_UNMARSHALL(event, buffer, msg_itf_evt_error);

  pWrapper = (void*)(intptr_t)event.hWrapper;
  pWrapper->CB.errorCB.func(event.uError, pWrapper->CB.errorCB.userParam);
}

static void handleEvtDestroyMarker(void* buffer)
{
  struct msg_itf_evt_destroy_marker event;
  AL_HDecoderWrapper* pWrapper;

  EVENT_UNMARSHALL(event, buffer, msg_itf_evt_destroy_marker);
  pWrapper = (void*)(intptr_t)event.hWrapper;
  Rtos_SetEvent(pWrapper->destroyEvent);
}

static void* pollerThread(void* arg)
{
  AL_RiscvDecoderCtx* pCtx = arg;
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
    case MSG_ITF_TYPE_EVT_BITSTREAM_BUFFER_REFCOUNT:
      handleEvtBitstreamBufferRefcount(event.event);
      break;
    case MSG_ITF_TYPE_EVT_DISPLAY_PICTURE_REFCOUNT:
      handleEvtDisplayPictureBufferRefcount(event.event);
      break;
    case MSG_ITF_TYPE_EVT_RESOLUTION_FOUND:
      handleEvtResolutionFound(event.event);
      break;
    case MSG_ITF_TYPE_EVT_END_PARSING:
      handleEvtEndParsing(event.event);
      break;
    case MSG_ITF_TYPE_EVT_END_DECODING:
      handleEvtEndDecoding(event.event);
      break;
    case MSG_ITF_TYPE_EVT_DISPLAY:
      handleEvtDisplayWithoutHdr(event.event);
      break;
    case MSG_ITF_TYPE_EVT_DISPLAY_WITH_HDR:
      handleEvtDisplayWithHdr(event.event);
      break;
    case MSG_ITF_TYPE_EVT_SEI_BUF:
      handleEvtSeiBuf(event.event);
      break;
    case MSG_ITF_TYPE_EVT_SEI_MSG:
      handleEvtSeiMsg(event.event);
      break;
    case MSG_ITF_TYPE_EVT_ERROR:
      handleErrorMsg(event.event);
      break;
    case MSG_ITF_TYPE_EVT_DESTROY_MARKER:
      handleEvtDestroyMarker(event.event);
      break;
    default:
      assert(0);
    }
  }

  return NULL;
}

/*****************************************************************************/
static AL_ERR AL_Decoder_Create_Riscv(AL_HDecoder* hDec, void* pScheduler, AL_TAllocator* pAllocator, void* pSettings, void* pCB)
{
  (void)hDec;
  (void)pScheduler;
  (void)pAllocator;
  (void)pSettings;
  (void)pCB;

  return AL_ERROR;
}

/*****************************************************************************/
static AL_ERR AL_Decoder_CreateWithCtx_Riscv(AL_HDecoder* hDec, AL_RiscV_Ctx ctx, AL_TAllocator* pAllocator, void* pSet, void* pCallBacks)
{
  struct msg_itf_create_decoder_req_full req;
  struct msg_itf_create_decoder_reply reply;
  struct codec_cmd_reply cmd_reply;
  AL_RiscvDecoderCtx* pCtx = ctx;
  AL_HDecoderWrapper* pWrapper;
  int ret;

  AL_TDecSettings* pSettings = (AL_TDecSettings*)pSet;
  AL_TDecCallBacks* pCB = (AL_TDecCallBacks*)pCallBacks;

  (void)pAllocator;

  pWrapper = Rtos_Malloc(sizeof(*pWrapper));

  if(!pWrapper)
    return AL_ERR_NO_MEMORY;

  pWrapper->destroyEvent = Rtos_CreateEvent(false);

  if(!pWrapper->destroyEvent)
  {
    Rtos_Free(pWrapper);
    return AL_ERR_NO_MEMORY;
  }

  req.hdr.type = MSG_ITF_TYPE_CREATE_DECODER_REQ;
  req.req.hWrapper = (intptr_t)pWrapper;
  req.req.settings = *pSettings;

  CMD_MARSHALL(cmd_reply, req, msg_itf_create_decoder);
  ret = ioctl(pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_itf_create_decoder);

  if(ret || AL_IS_ERROR_CODE(reply.ret))
    goto error;

  pWrapper->pCtx = ctx;
  pWrapper->hDec = reply.hDec;
  pWrapper->CB = *pCB;
  *hDec = pWrapper;

  return reply.ret;

  error:
  Rtos_DeleteEvent(pWrapper->destroyEvent);
  Rtos_Free(pWrapper);

  return ret ? AL_ERROR : reply.ret;
}

/*****************************************************************************/
static void AL_Decoder_Destroy_Riscv(AL_HDecoder hDec)
{
  struct msg_itf_destroy_decoder_req_full req;
  AL_HDecoderWrapper* pWrapper = hDec;
  struct codec_cmd_reply cmd_reply;

  req.hdr.type = MSG_ITF_TYPE_DESTROY_DECODER_REQ;
  req.req.hDec = pWrapper->hDec;

  CMD_MARSHALL(cmd_reply, req, msg_itf_destroy_decoder);
  ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  Rtos_WaitEvent(pWrapper->destroyEvent, AL_WAIT_FOREVER);
  Rtos_DeleteEvent(pWrapper->destroyEvent);
  Rtos_Free(pWrapper);
}

/*****************************************************************************/
static void AL_Decoder_SetParam_Riscv(AL_HDecoder hDec, const char* sPrefix, int iFrmID, int iNumFrm, bool bForceCleanBuffers, bool bShouldPrintFrameDelimiter)
{
  struct msg_itf_setparam_req_full req;
  AL_HDecoderWrapper* pWrapper = hDec;
  struct codec_cmd_reply cmd_reply;

  (void)sPrefix;
  (void)iFrmID;
  (void)iNumFrm;
  (void)bShouldPrintFrameDelimiter;

  req.hdr.type = MSG_ITF_TYPE_SETPARAM_REQ;
  req.req.hDec = pWrapper->hDec;
  req.req.bForceCleanBuffers = bForceCleanBuffers;

  CMD_MARSHALL(cmd_reply, req, msg_itf_setparam);
  ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
}

/*****************************************************************************/

/*****************************************************************************/
static void AL_Decoder_SetInternalFrameBuffersAllocator_Riscv(AL_HDecoder hDec, AL_TAllocator* pAllocator)
{
  /* nothing to do */
  (void)hDec;
  (void)pAllocator;
}

/*****************************************************************************/
static bool AL_Decoder_PushStreamBuffer_Riscv(AL_HDecoder hDec, AL_TBuffer* pBuf, size_t uSize, uint8_t uFlags)
{
  struct msg_itf_push_bitstream_buffer_req_full req;
  struct msg_itf_push_bitstream_buffer_reply reply;
  AL_HDecoderWrapper* pWrapper = hDec;
  struct codec_cmd_reply cmd_reply;
  bool res;
  int ret;

  req.hdr.type = MSG_ITF_TYPE_PUSH_BITSTREAM_BUFFER_REQ;
  req.req.hDec = pWrapper->hDec;
  req.req.pBuf = (intptr_t)pBuf;
  req.req.pAddr = AL_Buffer_GetPhysicalAddress(pBuf);
  req.req.uSize = uSize;
  req.req.uBufferSize = AL_Buffer_GetSize(pBuf);
  req.req.uFlags = uFlags;

  AL_Buffer_Ref(pBuf);
  CMD_MARSHALL(cmd_reply, req, msg_itf_push_bitstream_buffer);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_itf_push_bitstream_buffer);

  res = ret ? false : reply.res;

  if(!res)
    AL_Buffer_Unref(pBuf);

  return res;
}

/*****************************************************************************/
static bool AL_Decoder_PushBuffer_Riscv(AL_HDecoder hDec, AL_TBuffer* pBuf, size_t uSize)
{
  uint8_t uFlags = AL_STREAM_BUF_FLAG_UNKNOWN;

  AL_TStreamMetaData* pStreamMeta = (AL_TStreamMetaData*)AL_Buffer_GetMetaData(pBuf, AL_META_TYPE_STREAM);

  if(pStreamMeta != NULL)
  {
    uFlags = AL_STREAM_BUF_FLAG_ENDOFSLICE;

    if((pStreamMeta->uNumSection != 0) && (pStreamMeta->pSections[0].eFlags & AL_SECTION_END_FRAME_FLAG))
      uFlags |= AL_STREAM_BUF_FLAG_ENDOFFRAME;
  }

  return AL_Decoder_PushStreamBuffer_Riscv(hDec, pBuf, uSize, uFlags);
}

/*****************************************************************************/
static void AL_Decoder_Flush_Riscv(AL_HDecoder hDec)
{
  AL_HDecoderWrapper* pWrapper = hDec;
  struct msg_itf_flush_req_full req;
  struct codec_cmd_reply cmd_reply;

  req.hdr.type = MSG_ITF_TYPE_FLUSH_REQ;
  req.req.hDec = pWrapper->hDec;

  CMD_MARSHALL(cmd_reply, req, msg_itf_flush);
  ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
}

/*****************************************************************************/
static AL_TRiscvMetaData* getOrAllocRiscvMetaData(AL_TBuffer* pDisplay)
{
  AL_TRiscvMetaData* pRiscvMeta;

  pRiscvMeta = (AL_TRiscvMetaData*)AL_Buffer_GetMetaData(pDisplay, AL_META_TYPE_RISCV);

  if(pRiscvMeta)
    return pRiscvMeta;

  pRiscvMeta = AL_RiscvMetaData_Create();

  if(!pRiscvMeta)
    return NULL;

  if(AL_Buffer_AddMetaData(pDisplay, &pRiscvMeta->tMeta))
    return pRiscvMeta;

  AL_MetaData_Destroy(&pRiscvMeta->tMeta);

  return NULL;
}

/*****************************************************************************/
static bool AL_Decoder_PutDisplayPicture_Riscv(AL_HDecoder hDec, AL_TBuffer* pDisplay)
{
  struct msg_itf_put_display_picture_req_full req;
  struct msg_itf_put_display_picture_reply reply;
  AL_HDecoderWrapper* pWrapper = hDec;
  struct codec_cmd_reply cmd_reply;
  AL_TPixMapMetaData* pMeta;
  bool res;
  int ret;
  int i;

  pMeta = (AL_TPixMapMetaData*)AL_Buffer_GetMetaData(pDisplay, AL_META_TYPE_PIXMAP);

  if(!pMeta)
    return false;

  if(!getOrAllocRiscvMetaData(pDisplay))
    return false;

  req.hdr.type = MSG_ITF_TYPE_PUT_DISPLAY_PICTURE_REQ;
  req.req.hDec = pWrapper->hDec;
  req.req.pDisplay = (intptr_t)pDisplay;
  req.req.tDim = pMeta->tDim;
  req.req.tFourCC = pMeta->tFourCC;
  req.req.hasHdrMeta = AL_Buffer_GetMetaData(pDisplay, AL_META_TYPE_HDR) != NULL;

  for(i = 0; i < AL_BUFFER_MAX_CHUNK; i++)
  {
    req.req.chunks[i].pAddr = AL_Buffer_GetPhysicalAddressChunk(pDisplay, i);
    req.req.chunks[i].uSize = AL_Buffer_GetSizeChunk(pDisplay, i);
  }

  for(i = 0; i < AL_PLANE_MAX_ENUM; i++)
    req.req.tPlanes[i] = pMeta->tPlanes[i];

  AL_Buffer_Ref(pDisplay);
  CMD_MARSHALL(cmd_reply, req, msg_itf_put_display_picture);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_itf_put_display_picture);

  res = ret ? false : reply.res;

  if(!res)
    AL_Buffer_Unref(pDisplay);

  return res;
}

/*****************************************************************************/
static bool AL_Decoder_SetDecOutputSettings_Riscv(AL_HDecoder hDec, AL_TDecOutputSettings const* pDecOutputSettings)
{
  struct msg_itf_configure_output_settings_req_full req;
  struct msg_itf_configure_output_settings_reply reply;
  AL_HDecoderWrapper* pWrapper = hDec;
  struct codec_cmd_reply cmd_reply;
  bool res;
  int ret;

  req.hdr.type = MSG_ITF_TYPE_PUT_DISPLAY_PICTURE_REQ;

  req.req.bCustomFormat = pDecOutputSettings->bCustomFormat;

  req.req.tPicFormat = pDecOutputSettings->tPicFormat;

  CMD_MARSHALL(cmd_reply, req, msg_itf_configure_output_settings);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_itf_configure_output_settings);

  res = ret ? false : reply.res;

  return res;
}

/*****************************************************************************/
static int AL_Decoder_GetMaxBD_Riscv(AL_HDecoder hDec)
{
  AL_HDecoderWrapper* pWrapper = hDec;
  struct msg_itf_get_maxdepth_req_full req;
  struct msg_itf_get_maxdepth_reply reply;
  struct codec_cmd_reply cmd_reply;
  int ret;

  req.hdr.type = MSG_ITF_TYPE_GET_MAXDEPTH_REQ;
  req.req.hDec = pWrapper->hDec;

  CMD_MARSHALL(cmd_reply, req, msg_itf_get_maxdepth);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_itf_get_maxdepth);

  return ret ? 0 : reply.iMaxDepth;
}

/*****************************************************************************/
static AL_ECodec AL_Decoder_GetCodec_Riscv(AL_HDecoder hDec)
{
  AL_HDecoderWrapper* pWrapper = hDec;
  struct msg_itf_get_codec_req_full req;
  struct msg_itf_get_codec_reply reply;
  struct codec_cmd_reply cmd_reply;
  int ret;

  req.hdr.type = MSG_ITF_TYPE_GET_CODEC_REQ;
  req.req.hDec = pWrapper->hDec;

  CMD_MARSHALL(cmd_reply, req, msg_itf_get_codec);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_itf_get_codec);

  return ret ? AL_CODEC_INVALID : reply.eCodec;
}

/*****************************************************************************/
static AL_ERR AL_Decoder_GetLastError_Riscv(AL_HDecoder hDec)
{
  AL_HDecoderWrapper* pWrapper = hDec;
  struct msg_itf_get_last_error_req_full req;
  struct msg_itf_get_last_error_reply reply;
  struct codec_cmd_reply cmd_reply;
  int ret;

  req.hdr.type = MSG_ITF_TYPE_GET_LAST_ERROR_REQ;
  req.req.hDec = pWrapper->hDec;

  CMD_MARSHALL(cmd_reply, req, msg_itf_get_last_error);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_itf_get_last_error);

  return ret ? AL_ERROR : reply.uLastError;
}

/*****************************************************************************/
static AL_ERR AL_Decoder_GetFrameError_Riscv(AL_HDecoder hDec, const AL_TBuffer* pBuf)
{
  AL_TRiscvMetaData* pRiscvMeta = NULL;

  if(!pBuf)
    return AL_Decoder_GetLastError_Riscv(hDec);

  pRiscvMeta = (AL_TRiscvMetaData*)AL_Buffer_GetMetaData(pBuf, AL_META_TYPE_RISCV);
  assert(pRiscvMeta);

  return pRiscvMeta->decodedError;
}

/*****************************************************************************/
static bool AL_Decoder_PreallocateBuffers_Riscv(AL_HDecoder hDec)
{
  AL_HDecoderWrapper* pWrapper = hDec;
  struct msg_itf_preallocate_buffers_req_full req;
  struct msg_itf_preallocate_buffers_reply reply;
  struct codec_cmd_reply cmd_reply;
  int ret;

  req.hdr.type = MSG_ITF_TYPE_PREALLOCATE_BUFFERS_REQ;
  req.req.hDec = pWrapper->hDec;

  CMD_MARSHALL(cmd_reply, req, msg_itf_preallocate_buffers);
  ret = ioctl(pWrapper->pCtx->fd, CODEC_FW_CMD_REPLY, &cmd_reply);
  REPLY_UNMARSHALL(cmd_reply, reply, msg_itf_preallocate_buffers);

  return ret ? false : reply.res;
}

static uint32_t AL_Decoder_GetMinPitch_Riscv(uint32_t uWidth, AL_TPicFormat const* pPicFormat)
{
  return RndPitch(uWidth, pPicFormat);
}

static uint32_t AL_Decoder_GetMinStrideHeight_Riscv(uint32_t uHeight)
{
  return RndHeight(uHeight);
}

static void AL_Deinit_Riscv(void)
{
  ;
}

static AL_IDecArchVtable vtable =
{
  .Deinit = AL_Deinit_Riscv,
  .DecoderCreate = AL_Decoder_Create_Riscv,
  .DecoderCreateWithCtx = AL_Decoder_CreateWithCtx_Riscv,
  .DecoderDestroy = AL_Decoder_Destroy_Riscv,
  .DecoderSetParam = AL_Decoder_SetParam_Riscv,
  .DecoderSetInternalFrameBuffersAllocator = AL_Decoder_SetInternalFrameBuffersAllocator_Riscv,
  .DecoderPushStreamBuffer = AL_Decoder_PushStreamBuffer_Riscv,
  .DecoderPushBuffer = AL_Decoder_PushBuffer_Riscv,
  .DecoderFlush = AL_Decoder_Flush_Riscv,
  .DecoderPutDisplayPicture = AL_Decoder_PutDisplayPicture_Riscv,
  .DecoderGetCodec = AL_Decoder_GetCodec_Riscv,
  .DecoderGetMaxBD = AL_Decoder_GetMaxBD_Riscv,
  .DecoderGetLastError = AL_Decoder_GetLastError_Riscv,
  .DecoderGetFrameError = AL_Decoder_GetFrameError_Riscv,
  .DecoderPreallocateBuffers = AL_Decoder_PreallocateBuffers_Riscv,
  .DecoderGetMinPitch = AL_Decoder_GetMinPitch_Riscv,
  .DecoderGetMinStrideHeight = AL_Decoder_GetMinStrideHeight_Riscv,
  .DecoderSetDecOutputSettings = AL_Decoder_SetDecOutputSettings_Riscv,
};

AL_IDecArch decRiscv =
{
  .vtable = &vtable
};

/*****************************************************************************/
AL_IDecArch* LibDecodeRiscvGet(void)
{
  return &decRiscv;
}

/*****************************************************************************/
AL_RiscV_Ctx AL_Riscv_Decode_CreateCtx(const char* deviceName)
{
  AL_RiscvDecoderCtx* pCtx;

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

  return pCtx;

  fail_thread:
  Rtos_DriverClose((void*)(intptr_t)pCtx->fd);
  fail_open:
  Rtos_Free(pCtx);

  return NULL;
}

/*****************************************************************************/
void AL_Riscv_Decode_DestroyCtx(AL_RiscV_Ctx ctx)
{
  AL_RiscvDecoderCtx* pCtx = ctx;

  pCtx->is_shutdown = true;
  Rtos_JoinThread(pCtx->poller);
  Rtos_DeleteThread(pCtx->poller);
  Rtos_DriverClose((void*)(intptr_t)pCtx->fd);
  Rtos_Free(pCtx);
}

/*****************************************************************************/
AL_TAllocator* AL_Riscv_Decode_DmaAlloc_Create(AL_RiscV_Ctx ctx)
{
  AL_RiscvDecoderCtx* pCtx = ctx;

  return AL_RiscvGetDmaAllocator(pCtx->fd);
}
