// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "lib_common/msg_common_interface.h"
#include "lib_encode/lib_encoder.h"
#include "lib_common/BufferPixMapMeta.h"
#include "lib_common/BufferStreamMeta.h"
#include "lib_common_enc/RateCtrlStats.h"

#define MAX_STREAM_SECTION_IN_MESSAGE 8

enum {
  MSG_INTERFACE_TYPE_CREATE_ENCODER_REQ = MSG_INTERFACE_TYPE_NEXT_REQ,
  MSG_INTERFACE_TYPE_DESTROY_ENCODER_REQ,
  MSG_INTERFACE_TYPE_GET_INFO_REQ,
  MSG_INTERFACE_TYPE_PUSH_STREAM_BUFFER_REQ,
  MSG_INTERFACE_TYPE_PROCESS_REQ,
  MSG_INTERFACE_TYPE_GET_REC_REQ,
  MSG_INTERFACE_TYPE_RELEASE_REC_REQ,
  MSG_INTERFACE_TYPE_GET_LAST_ERROR_REQ,
  MSG_INTERFACE_TYPE_NOTIFY_REQ,
  MSG_INTERFACE_TYPE_SMART_REQ,
  MSG_INTERFACE_TYPE_HDR_REQ,

  MSG_INTERFACE_TYPE_CREATE_ENCODER_REPLY = MSG_INTERFACE_TYPE_NEXT_REPLY,
  MSG_INTERFACE_TYPE_DESTROY_ENCODER_REPLY,
  MSG_INTERFACE_TYPE_GET_INFO_REPLY,
  MSG_INTERFACE_TYPE_PUSH_STREAM_BUFFER_REPLY,
  MSG_INTERFACE_TYPE_PROCESS_REPLY,
  MSG_INTERFACE_TYPE_GET_REC_REPLY,
  MSG_INTERFACE_TYPE_RELEASE_REC_REPLY,
  MSG_INTERFACE_TYPE_GET_LAST_ERROR_REPLY,
  MSG_INTERFACE_TYPE_NOTIFY_REPLY,
  MSG_INTERFACE_TYPE_SMART_REPLY,
  MSG_INTERFACE_TYPE_HDR_REPLY,

  MSG_INTERFACE_TYPE_EVT_BUFFER_REFCOUNT = MSG_INTERFACE_TYPE_NEXT_EVT,
  MSG_INTERFACE_TYPE_EVT_END_ENCODING,
  MSG_INTERFACE_TYPE_EVT_END_ENCODING_WITH_STAT,
  MSG_INTERFACE_TYPE_EVT_DESTROY_MARKER
};

enum {
  NOTIFY_CMD_SCENE_CHANGE,
  NOTIFY_CMD_IS_LONG_TERM,
  NOTIFY_CMD_USE_LONG_TERM,
  NOTIFY_CMD_IS_SKIP,
  NOTIFY_CMD_IS_DROP,
  NOTIFY_CMD_GMV,
  NOTIFY_CMD_MV_PER_BLOCK,
};

enum {
  SMART_CMD_SET_COST_MODE,
  SMART_CMD_SET_AUTO_QP_THRESHOLD_AND_DELTA,
  SMART_CMD_RESTART_GOP,
  SMART_CMD_RESTART_GOP_RECOVERY_POINT,
  SMART_CMD_SET_GOP_LENGTH,
  SMART_CMD_SET_GOP_NUMB,
  SMART_CMD_SET_FREQ_IDR,
  SMART_CMD_SET_BITRATE,
  SMART_CMD_SET_MAXBITRATE,
  SMART_CMD_SET_FRAMERATE,
  SMART_CMD_SET_QP,
  SMART_CMD_SET_QP_OFFSET,
  SMART_CMD_SET_QP_BOUNDS,
  SMART_CMD_SET_QP_BOUNDS_PER_FRAME_TYPE,
  SMART_CMD_SET_QPIP_DELTA,
  SMART_CMD_SET_QPPB_DELTA,
  SMART_CMD_SET_INPUT_RES,
  SMART_CMD_SET_LOOP_FILTER_BETA_OFFSET,
  SMART_CMD_SET_LOOP_FILTER_TC_OFFSET,
  SMART_CMD_SET_QP_CHROMA_OFFSETS,
  SMART_CMD_SET_AUTO_QP,
};

/* Like AL_TStreamSection but with well defined sizes so we have same layout on
 * host and fw side.
 */
typedef struct AL_TStreamSectionInBuffer {
  uint32_t uOffset;
  uint32_t uLength;
  uint32_t eFlags;
} AL_TStreamSectionInBuffer;

typedef struct AL_TChunkInfo {
  uint64_t pAddr;
  uint64_t uSize;
} AL_TChunkInfo;

struct msg_interface_create_encoder_req {
  uint64_t hWrapper;
  AL_TEncSettings settings;
};
DECLARE_FULL_REQ(msg_interface_create_encoder_req);

struct msg_interface_create_encoder_reply {
  int32_t ret;
  uint64_t hEnc;
};
DECLARE_FULL_REPLY(msg_interface_create_encoder_reply);

struct msg_interface_destroy_encoder_req {
  uint64_t hEnc;
};
DECLARE_FULL_REQ(msg_interface_destroy_encoder_req);

struct msg_interface_destroy_encoder_reply {
  uint32_t unused;
};
DECLARE_FULL_REPLY(msg_interface_destroy_encoder_reply);

struct msg_interface_get_info_req {
  uint64_t hEnc;
};
DECLARE_FULL_REQ(msg_interface_get_info_req);

struct msg_interface_get_info_reply {
  AL_TEncoderInfo tEncInfo;
};
DECLARE_FULL_REPLY(msg_interface_get_info_reply);

struct msg_interface_push_stream_buffer_req {
  uint64_t hEnc;
  uint64_t pStream;
  uint64_t pAddr;
  uint64_t uSize;
  int32_t iLayerID;
  uint64_t pAddrStats;
  uint64_t uSizeStats;
};
DECLARE_FULL_REQ(msg_interface_push_stream_buffer_req);

struct msg_interface_push_stream_buffer_reply {
  uint8_t res;
};
DECLARE_FULL_REPLY(msg_interface_push_stream_buffer_reply);

struct msg_interface_process_req {
  uint64_t hEnc;
  uint64_t pFrame;
  AL_TChunkInfo chunks[AL_BUFFER_MAX_CHUNK];
  AL_TDimension tDim;
  AL_TPlane tPlanes[AL_PLANE_MAX_ENUM];
  TFourCC tFourCC;
  uint64_t pQpTable;
  uint64_t pAddr;
  uint64_t uSize;
  int32_t iLayerID;
};
DECLARE_FULL_REQ(msg_interface_process_req);

struct msg_interface_process_reply {
  uint8_t res;
};
DECLARE_FULL_REPLY(msg_interface_process_reply);

struct msg_interface_get_rec_req {
  uint64_t hEnc;
  int32_t iLayerID;
};
DECLARE_FULL_REQ(msg_interface_get_rec_req);

struct msg_interface_get_rec_reply {
  uint64_t pRec;
  AL_TChunkInfo chunk;
  AL_TReconstructedInfo recInfo;
  uint8_t res;
  int32_t iLayerID;
};
DECLARE_FULL_REPLY(msg_interface_get_rec_reply);

struct msg_interface_get_last_error_req {
  uint64_t hEnc;
};
DECLARE_FULL_REQ(msg_interface_get_last_error_req);

struct msg_interface_release_rec_req {
  uint64_t hEnc;
  uint64_t pRec;
  AL_TReconstructedInfo recInfo;
  int32_t iLayerID;
};
DECLARE_FULL_REQ(msg_interface_release_rec_req);

struct msg_interface_release_rec_reply {
  uint32_t unused;
};
DECLARE_FULL_REPLY(msg_interface_release_rec_reply);

struct msg_interface_get_last_error_reply {
  int32_t res;
};
DECLARE_FULL_REPLY(msg_interface_get_last_error_reply);

struct msg_interface_notify_req {
  uint64_t hEnc;
  uint32_t cmd;
  uint32_t iAhead;
  uint32_t iNumFrame;
  int32_t GMV_x;
  int32_t GMV_y;
};
DECLARE_FULL_REQ(msg_interface_notify_req);

struct msg_interface_notify_reply {
  int32_t res;
};
DECLARE_FULL_REPLY(msg_interface_notify_reply);

struct msg_interface_smart_req {
  uint64_t hEnc;
  uint32_t cmd;
  bool costMode;
  bool bUserAutoQP;
  AL_TAutoQPCtrl userAutoQPValues;
  int32_t iGopLength;
  int32_t iNumB;
  int32_t iFreqIDR;
  int32_t iBitRate;
  int32_t iTargetBitRate;
  int32_t iMaxBitRate;
  uint16_t uFrameRate;
  uint16_t uClkRatio;
  int16_t iQP;
  int16_t iQPOffset;
  int16_t iMinQP;
  int16_t iMaxQP;
  AL_ESliceType sliceType;
  int16_t uIPDelta;
  int16_t uPBDelta;
  AL_TDimension tDim;
  int8_t iBetaOffset;
  int8_t iTcOffset;
  int8_t iQp1Offset;
  int8_t iQp2Offset;
  bool useAutoQP;
};
DECLARE_FULL_REQ(msg_interface_smart_req);

struct msg_interface_smart_reply {
  int32_t res;
};
DECLARE_FULL_REPLY(msg_interface_smart_reply);

struct msg_interface_hdr_req {
  uint64_t hEnc;
 AL_THDRSEIs pHDRSEIs;
};
DECLARE_FULL_REQ(msg_interface_hdr_req);

struct msg_interface_hdr_reply {
  int32_t res;
};
DECLARE_FULL_REPLY(msg_interface_hdr_reply);

struct msg_interface_evt_buffer_refcount {
  uint64_t pBuf;
};
DECLARE_FULL_EVENT(msg_interface_evt_buffer_refcount);

/* Section info for host AL_META_TYPE_STREAM use copy into sections field
 * up to MAX_STREAM_SECTION_IN_MESSAGE. Remaining section info use a
 * cma buffer allocated in fw side and destroyed in host side.
 */
struct msg_interface_evt_end_encoding {
  uint64_t hWrapper;
  uint64_t pStream;
  uint64_t pSrc;
  int32_t iLayerID;
  uint16_t uNumSection;
  AL_TStreamSection sections[MAX_STREAM_SECTION_IN_MESSAGE];
  uint16_t uNumSectionInBuffer;
  uint64_t pSectionBufferAddr;
  uint64_t uSectionBufferSize;
  uint64_t uSectionBufferOffset;
  AL_ESliceType eType;
  bool bSkipped;
};
DECLARE_FULL_EVENT(msg_interface_evt_end_encoding);

struct msg_interface_evt_end_encoding_with_stat {
  struct msg_interface_evt_end_encoding end_encoding;
  bool bFilled;
  AL_RateCtrl_Statistics stats;
};
DECLARE_FULL_EVENT(msg_interface_evt_end_encoding_with_stat);

struct msg_interface_evt_destroy_marker {
  uint64_t hWrapper;
};
DECLARE_FULL_EVENT(msg_interface_evt_destroy_marker);
