// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "lib_common/msg_common_interface.h"
#include "lib_decode/DecSettings.h"
#include "lib_common/BufferPixMapMeta.h"
#include "lib_common/BufferAPI.h"
#include "lib_common/HDR.h"

enum {
  MSG_INTERFACE_TYPE_CREATE_DECODER_REQ = MSG_INTERFACE_TYPE_NEXT_REQ,
  MSG_INTERFACE_TYPE_DESTROY_DECODER_REQ,
  MSG_INTERFACE_TYPE_PUSH_BITSTREAM_BUFFER_REQ,
  MSG_INTERFACE_TYPE_CONFIGURE_OUTPUT_SETTINGS_REQ,
  MSG_INTERFACE_TYPE_PUT_DISPLAY_PICTURE_REQ,
  MSG_INTERFACE_TYPE_FLUSH_REQ,
  MSG_INTERFACE_TYPE_GET_MAXDEPTH_REQ,
  MSG_INTERFACE_TYPE_GET_CODEC_REQ,
  MSG_INTERFACE_TYPE_GET_LAST_ERROR_REQ,
  MSG_INTERFACE_TYPE_PREALLOCATE_BUFFERS_REQ,
  MSG_INTERFACE_TYPE_SETPARAM_REQ,
  MSG_INTERFACE_TYPE_CREATE_DECODER_REPLY = MSG_INTERFACE_TYPE_NEXT_REPLY,
  MSG_INTERFACE_TYPE_DESTROY_DECODER_REPLY,
  MSG_INTERFACE_TYPE_PUSH_BITSTREAM_BUFFER_REPLY,
  MSG_INTERFACE_TYPE_CONFIGURE_OUTPUT_SETTINGS_REPLY,
  MSG_INTERFACE_TYPE_PUT_DISPLAY_PICTURE_REPLY,
  MSG_INTERFACE_TYPE_FLUSH_REPLY,
  MSG_INTERFACE_TYPE_GET_MAXDEPTH_REPLY,
  MSG_INTERFACE_TYPE_GET_CODEC_REPLY,
  MSG_INTERFACE_TYPE_GET_LAST_ERROR_REPLY,
  MSG_INTERFACE_TYPE_PREALLOCATE_BUFFERS_REPLY,
  MSG_INTERFACE_TYPE_SETPARAM_REPLY,
  MSG_INTERFACE_TYPE_EVT_BITSTREAM_BUFFER_REFCOUNT = MSG_INTERFACE_TYPE_NEXT_EVT,
  MSG_INTERFACE_TYPE_EVT_DISPLAY_PICTURE_REFCOUNT,
  MSG_INTERFACE_TYPE_EVT_RESOLUTION_FOUND,
  MSG_INTERFACE_TYPE_EVT_END_PARSING,
  MSG_INTERFACE_TYPE_EVT_END_DECODING,
  MSG_INTERFACE_TYPE_EVT_DISPLAY,
  MSG_INTERFACE_TYPE_EVT_DISPLAY_WITH_HDR,
  MSG_INTERFACE_TYPE_EVT_SEI_BUF,
  MSG_INTERFACE_TYPE_EVT_SEI_MSG,
  MSG_INTERFACE_TYPE_EVT_ERROR,
  MSG_INTERFACE_TYPE_EVT_DESTROY_MARKER
};

#define MAX_SEI_MSG_SIZE 32

typedef struct AL_TChunkInfo {
  uint64_t pAddr;
  uint64_t uSize;
} AL_TChunkInfo;

struct msg_interface_create_decoder_req {
   uint64_t hWrapper;
  AL_TDecSettings settings;
};
DECLARE_FULL_REQ(msg_interface_create_decoder_req);

struct msg_interface_create_decoder_reply {
  int32_t ret;
  uint64_t hDec;
};
DECLARE_FULL_REPLY(msg_interface_create_decoder_reply);

struct msg_interface_destroy_decoder_req {
  uint64_t hDec;
};
DECLARE_FULL_REQ(msg_interface_destroy_decoder_req);

struct msg_interface_destroy_decoder_reply {
  uint32_t unused;
};
DECLARE_FULL_REPLY(msg_interface_destroy_decoder_reply);

struct msg_interface_push_bitstream_buffer_req {
  uint64_t hDec;
  uint64_t pBuf;
  uint64_t pAddr;
  uint64_t uSize;
  uint64_t uBufferSize;
  uint8_t uFlags;
};
DECLARE_FULL_REQ(msg_interface_push_bitstream_buffer_req);

struct msg_interface_push_bitstream_buffer_reply {
  uint8_t res;
};
DECLARE_FULL_REPLY(msg_interface_push_bitstream_buffer_reply);

struct msg_interface_flush_req {
  uint64_t hDec;
};
DECLARE_FULL_REQ(msg_interface_flush_req);

struct msg_interface_flush_reply {
  uint32_t unused;
};
DECLARE_FULL_REPLY(msg_interface_flush_reply);

struct msg_interface_get_maxdepth_req {
  uint64_t hDec;
};
DECLARE_FULL_REQ(msg_interface_get_maxdepth_req);

struct msg_interface_get_maxdepth_reply {
  int32_t iMaxDepth;
};
DECLARE_FULL_REPLY(msg_interface_get_maxdepth_reply);

struct msg_interface_get_codec_req {
  uint64_t hDec;
};
DECLARE_FULL_REQ(msg_interface_get_codec_req);

struct msg_interface_get_codec_reply {
  AL_ECodec eCodec;
};
DECLARE_FULL_REPLY(msg_interface_get_codec_reply);

struct msg_interface_get_last_error_req {
  uint64_t hDec;
};
DECLARE_FULL_REQ(msg_interface_get_last_error_req);

struct msg_interface_get_last_error_reply {
  uint32_t uLastError;
};
DECLARE_FULL_REPLY(msg_interface_get_last_error_reply);

struct msg_interface_preallocate_buffers_req {
  uint64_t hDec;
};
DECLARE_FULL_REQ(msg_interface_preallocate_buffers_req);

struct msg_interface_preallocate_buffers_reply {
  uint8_t res;
};
DECLARE_FULL_REPLY(msg_interface_preallocate_buffers_reply);

struct msg_interface_setparam_req {
  uint64_t hDec;
  uint8_t bForceCleanBuffers;
};
DECLARE_FULL_REQ(msg_interface_setparam_req);

struct msg_interface_setparam_reply {
  uint32_t unused;
};
DECLARE_FULL_REPLY(msg_interface_setparam_reply);

struct msg_interface_put_display_picture_req {
  uint64_t hDec;
  uint64_t pDisplay;
  AL_TChunkInfo chunks[AL_BUFFER_MAX_CHUNK];
  AL_TDimension tDim;
  AL_TPlane tPlanes[AL_PLANE_MAX_ENUM];
  TFourCC tFourCC;
  uint8_t hasHdrMeta;
};
DECLARE_FULL_REQ(msg_interface_put_display_picture_req);

struct msg_interface_put_display_picture_reply {
  uint8_t res;
};
DECLARE_FULL_REPLY(msg_interface_put_display_picture_reply);

struct msg_interface_configure_output_settings_req {
  uint64_t hDec;
  uint64_t pDisplay;
  bool bCustomFormat;
  bool bOutputAll;
  bool bDisableFilmGrain;
  AL_TWindow tFbcDisableWindow;
  AL_TPicFormat tPicFormat;
};
DECLARE_FULL_REQ(msg_interface_configure_output_settings_req);

struct msg_interface_configure_output_settings_reply {
  uint8_t res;
};
DECLARE_FULL_REPLY(msg_interface_configure_output_settings_reply);

struct msg_interface_evt_bitstream_buffer_refcount {
  uint64_t pBuf;
};
DECLARE_FULL_EVENT(msg_interface_evt_bitstream_buffer_refcount);

struct msg_interface_evt_display_picture_refcount {
  uint64_t pDisplay;
};
DECLARE_FULL_EVENT(msg_interface_evt_display_picture_refcount);

struct msg_interface_evt_resolution_found {
  uint64_t hWrapper;
  int32_t BufferNumber;
  AL_TStreamSettings settings;
  AL_TCropInfo cropInfo;
};
DECLARE_FULL_EVENT(msg_interface_evt_resolution_found);

struct msg_interface_evt_end_parsing {
  uint64_t hWrapper;
  uint64_t pParsedFrame;
  int32_t iParsingID;
};
DECLARE_FULL_EVENT(msg_interface_evt_end_parsing);

struct msg_interface_evt_end_decoding {
  uint64_t hWrapper;
  uint64_t pDecodedFrame;
};
DECLARE_FULL_EVENT(msg_interface_evt_end_decoding);

struct msg_interface_evt_display {
  uint64_t hWrapper;
  uint64_t pDisplayedFrame;
  uint64_t pInfo;
  AL_TInfoDecode info;
  uint32_t decodedError;
  AL_TDimension tDim;
  TFourCC tFourCC;
};
DECLARE_FULL_EVENT(msg_interface_evt_display);

struct msg_interface_evt_display_with_hdr {
  struct msg_interface_evt_display evt_display;
  AL_EColourDescription eColourDescription;
  AL_ETransferCharacteristics eTransferCharacteristics;
  AL_EColourMatrixCoefficients eColourMatrixCoeffs;
  AL_THDRSEIs tHDRSEIs;
};
DECLARE_FULL_EVENT(msg_interface_evt_display_with_hdr);

struct msg_interface_evt_sei_buf {
  uint64_t hWrapper;
  uint64_t uOffsetSei;
  uint64_t pAddrSei;
  int32_t iPayloadType;
  int32_t iPayloadSize;
  uint8_t bIsPrefix;
};
DECLARE_FULL_EVENT(msg_interface_evt_sei_buf);

struct msg_interface_evt_sei_msg {
  uint64_t hWrapper;
  int32_t iPayloadType;
  int32_t iPayloadSize;
  uint8_t bIsPrefix;
  uint8_t payload[MAX_SEI_MSG_SIZE];
};
DECLARE_FULL_EVENT(msg_interface_evt_sei_msg);

struct msg_interface_evt_error {
  uint64_t hWrapper;
  uint32_t uError;
};
DECLARE_FULL_EVENT(msg_interface_evt_error);

struct msg_interface_evt_destroy_marker {
  uint64_t hWrapper;
};
DECLARE_FULL_EVENT(msg_interface_evt_destroy_marker);
