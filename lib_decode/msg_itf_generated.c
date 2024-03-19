// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/* Code generated DO NOT EDIT */

#include <stdint.h>
#include "msg_itf.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "runtime_generated.h"
struct AL_TDimension {
	int32_t iWidth;
	int32_t iHeight;
};
struct AL_TStreamSettings {
	AL_TDimension tDim;
	AL_EChromaMode eChroma;
	int iBitDepth;
	int iLevel;
	AL_EProfile eProfile;
	AL_ESequenceMode eSequenceMode;
	_Bool bDecodeIntraOnly;
	int iMaxRef;
};
struct AL_TPosition {
	int32_t iX;
	int32_t iY;
};
struct AL_TDecSettings {
	int iStackSize;
	int iStreamBufSize;
	uint8_t uNumCore;
	_Bool bNonRealtime;
	uint32_t uFrameRate;
	uint32_t uClkRatio;
	AL_ECodec eCodec;
	_Bool bParallelWPP;
	uint8_t uDDRWidth;
	_Bool bDisableCache;
	_Bool bLowLat;
	_Bool bForceFrameRate;
	uint16_t uConcealMaxFps;
	_Bool bFrameBufferCompression;
	AL_EFbStorageMode eFBStorageMode;
	AL_EDecUnit eDecUnit;
	AL_EDpbMode eDpbMode;
	AL_TStreamSettings tStream;
	AL_TPosition tOutputPosition;
	_Bool bUseIFramesAsSyncPoint;
	uint32_t uNumBuffersHeldByNextComponent;
	_Bool bUseEarlyCallback;
	AL_EDecInputMode eInputMode;
};
struct AL_TWindow {
	AL_TPosition tPos;
	AL_TDimension tDim;
};
static int get_size_struct_msg_itf_header(void);
static void marshall_struct_msg_itf_header(struct msg_itf_header *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_header(struct msg_itf_header *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_cma_req(void);
static void marshall_struct_msg_itf_get_cma_req(struct msg_itf_get_cma_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_cma_req(struct msg_itf_get_cma_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_cma_req_full(void);
static void marshall_struct_msg_itf_get_cma_req_full(struct msg_itf_get_cma_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_cma_req_full(struct msg_itf_get_cma_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_cma_reply(void);
static void marshall_struct_msg_itf_get_cma_reply(struct msg_itf_get_cma_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_cma_reply(struct msg_itf_get_cma_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_cma_reply_full(void);
static void marshall_struct_msg_itf_get_cma_reply_full(struct msg_itf_get_cma_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_cma_reply_full(struct msg_itf_get_cma_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_put_cma_req(void);
static void marshall_struct_msg_itf_put_cma_req(struct msg_itf_put_cma_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_put_cma_req(struct msg_itf_put_cma_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_put_cma_req_full(void);
static void marshall_struct_msg_itf_put_cma_req_full(struct msg_itf_put_cma_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_put_cma_req_full(struct msg_itf_put_cma_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_put_cma_reply(void);
static void marshall_struct_msg_itf_put_cma_reply(struct msg_itf_put_cma_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_put_cma_reply(struct msg_itf_put_cma_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_put_cma_reply_full(void);
static void marshall_struct_msg_itf_put_cma_reply_full(struct msg_itf_put_cma_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_put_cma_reply_full(struct msg_itf_put_cma_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_perf_info_req(void);
static void marshall_struct_msg_itf_perf_info_req(struct msg_itf_perf_info_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_perf_info_req(struct msg_itf_perf_info_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_perf_info_req_full(void);
static void marshall_struct_msg_itf_perf_info_req_full(struct msg_itf_perf_info_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_perf_info_req_full(struct msg_itf_perf_info_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_perf_info_reply(void);
static void marshall_struct_msg_itf_perf_info_reply(struct msg_itf_perf_info_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_perf_info_reply(struct msg_itf_perf_info_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_perf_info_reply_full(void);
static void marshall_struct_msg_itf_perf_info_reply_full(struct msg_itf_perf_info_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_perf_info_reply_full(struct msg_itf_perf_info_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_write_req(void);
static void marshall_struct_msg_itf_write_req(struct msg_itf_write_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_write_req(struct msg_itf_write_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_write_req_full(void);
static void marshall_struct_msg_itf_write_req_full(struct msg_itf_write_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_write_req_full(struct msg_itf_write_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_chunk_info(void);
static void marshall_struct_chunk_info(struct chunk_info *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_chunk_info(struct chunk_info *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TDimension(void);
static void marshall_struct_AL_TDimension(struct AL_TDimension *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TDimension(struct AL_TDimension *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TStreamSettings(void);
static void marshall_struct_AL_TStreamSettings(struct AL_TStreamSettings *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TStreamSettings(struct AL_TStreamSettings *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TPosition(void);
static void marshall_struct_AL_TPosition(struct AL_TPosition *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TPosition(struct AL_TPosition *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TDecSettings(void);
static void marshall_struct_AL_TDecSettings(struct AL_TDecSettings *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TDecSettings(struct AL_TDecSettings *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_create_decoder_req(void);
static void marshall_struct_msg_itf_create_decoder_req(struct msg_itf_create_decoder_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_create_decoder_req(struct msg_itf_create_decoder_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_create_decoder_req_full(void);
static void marshall_struct_msg_itf_create_decoder_req_full(struct msg_itf_create_decoder_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_create_decoder_req_full(struct msg_itf_create_decoder_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_create_decoder_reply(void);
static void marshall_struct_msg_itf_create_decoder_reply(struct msg_itf_create_decoder_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_create_decoder_reply(struct msg_itf_create_decoder_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_create_decoder_reply_full(void);
static void marshall_struct_msg_itf_create_decoder_reply_full(struct msg_itf_create_decoder_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_create_decoder_reply_full(struct msg_itf_create_decoder_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_destroy_decoder_req(void);
static void marshall_struct_msg_itf_destroy_decoder_req(struct msg_itf_destroy_decoder_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_destroy_decoder_req(struct msg_itf_destroy_decoder_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_destroy_decoder_req_full(void);
static void marshall_struct_msg_itf_destroy_decoder_req_full(struct msg_itf_destroy_decoder_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_destroy_decoder_req_full(struct msg_itf_destroy_decoder_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_destroy_decoder_reply(void);
static void marshall_struct_msg_itf_destroy_decoder_reply(struct msg_itf_destroy_decoder_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_destroy_decoder_reply(struct msg_itf_destroy_decoder_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_destroy_decoder_reply_full(void);
static void marshall_struct_msg_itf_destroy_decoder_reply_full(struct msg_itf_destroy_decoder_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_destroy_decoder_reply_full(struct msg_itf_destroy_decoder_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_push_bitstream_buffer_req(void);
static void marshall_struct_msg_itf_push_bitstream_buffer_req(struct msg_itf_push_bitstream_buffer_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_push_bitstream_buffer_req(struct msg_itf_push_bitstream_buffer_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_push_bitstream_buffer_req_full(void);
static void marshall_struct_msg_itf_push_bitstream_buffer_req_full(struct msg_itf_push_bitstream_buffer_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_push_bitstream_buffer_req_full(struct msg_itf_push_bitstream_buffer_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_push_bitstream_buffer_reply(void);
static void marshall_struct_msg_itf_push_bitstream_buffer_reply(struct msg_itf_push_bitstream_buffer_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_push_bitstream_buffer_reply(struct msg_itf_push_bitstream_buffer_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_push_bitstream_buffer_reply_full(void);
static void marshall_struct_msg_itf_push_bitstream_buffer_reply_full(struct msg_itf_push_bitstream_buffer_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_push_bitstream_buffer_reply_full(struct msg_itf_push_bitstream_buffer_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_flush_req(void);
static void marshall_struct_msg_itf_flush_req(struct msg_itf_flush_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_flush_req(struct msg_itf_flush_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_flush_req_full(void);
static void marshall_struct_msg_itf_flush_req_full(struct msg_itf_flush_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_flush_req_full(struct msg_itf_flush_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_flush_reply(void);
static void marshall_struct_msg_itf_flush_reply(struct msg_itf_flush_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_flush_reply(struct msg_itf_flush_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_flush_reply_full(void);
static void marshall_struct_msg_itf_flush_reply_full(struct msg_itf_flush_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_flush_reply_full(struct msg_itf_flush_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_maxdepth_req(void);
static void marshall_struct_msg_itf_get_maxdepth_req(struct msg_itf_get_maxdepth_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_maxdepth_req(struct msg_itf_get_maxdepth_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_maxdepth_req_full(void);
static void marshall_struct_msg_itf_get_maxdepth_req_full(struct msg_itf_get_maxdepth_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_maxdepth_req_full(struct msg_itf_get_maxdepth_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_maxdepth_reply(void);
static void marshall_struct_msg_itf_get_maxdepth_reply(struct msg_itf_get_maxdepth_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_maxdepth_reply(struct msg_itf_get_maxdepth_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_maxdepth_reply_full(void);
static void marshall_struct_msg_itf_get_maxdepth_reply_full(struct msg_itf_get_maxdepth_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_maxdepth_reply_full(struct msg_itf_get_maxdepth_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_codec_req(void);
static void marshall_struct_msg_itf_get_codec_req(struct msg_itf_get_codec_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_codec_req(struct msg_itf_get_codec_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_codec_req_full(void);
static void marshall_struct_msg_itf_get_codec_req_full(struct msg_itf_get_codec_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_codec_req_full(struct msg_itf_get_codec_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_codec_reply(void);
static void marshall_struct_msg_itf_get_codec_reply(struct msg_itf_get_codec_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_codec_reply(struct msg_itf_get_codec_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_codec_reply_full(void);
static void marshall_struct_msg_itf_get_codec_reply_full(struct msg_itf_get_codec_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_codec_reply_full(struct msg_itf_get_codec_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_last_error_req(void);
static void marshall_struct_msg_itf_get_last_error_req(struct msg_itf_get_last_error_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_last_error_req(struct msg_itf_get_last_error_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_last_error_req_full(void);
static void marshall_struct_msg_itf_get_last_error_req_full(struct msg_itf_get_last_error_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_last_error_req_full(struct msg_itf_get_last_error_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_last_error_reply(void);
static void marshall_struct_msg_itf_get_last_error_reply(struct msg_itf_get_last_error_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_last_error_reply(struct msg_itf_get_last_error_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_last_error_reply_full(void);
static void marshall_struct_msg_itf_get_last_error_reply_full(struct msg_itf_get_last_error_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_last_error_reply_full(struct msg_itf_get_last_error_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_preallocate_buffers_req(void);
static void marshall_struct_msg_itf_preallocate_buffers_req(struct msg_itf_preallocate_buffers_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_preallocate_buffers_req(struct msg_itf_preallocate_buffers_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_preallocate_buffers_req_full(void);
static void marshall_struct_msg_itf_preallocate_buffers_req_full(struct msg_itf_preallocate_buffers_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_preallocate_buffers_req_full(struct msg_itf_preallocate_buffers_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_preallocate_buffers_reply(void);
static void marshall_struct_msg_itf_preallocate_buffers_reply(struct msg_itf_preallocate_buffers_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_preallocate_buffers_reply(struct msg_itf_preallocate_buffers_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_preallocate_buffers_reply_full(void);
static void marshall_struct_msg_itf_preallocate_buffers_reply_full(struct msg_itf_preallocate_buffers_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_preallocate_buffers_reply_full(struct msg_itf_preallocate_buffers_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_setparam_req(void);
static void marshall_struct_msg_itf_setparam_req(struct msg_itf_setparam_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_setparam_req(struct msg_itf_setparam_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_setparam_req_full(void);
static void marshall_struct_msg_itf_setparam_req_full(struct msg_itf_setparam_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_setparam_req_full(struct msg_itf_setparam_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_setparam_reply(void);
static void marshall_struct_msg_itf_setparam_reply(struct msg_itf_setparam_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_setparam_reply(struct msg_itf_setparam_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_setparam_reply_full(void);
static void marshall_struct_msg_itf_setparam_reply_full(struct msg_itf_setparam_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_setparam_reply_full(struct msg_itf_setparam_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TPlane(void);
static void marshall_struct_AL_TPlane(struct AL_TPlane *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TPlane(struct AL_TPlane *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_put_display_picture_req(void);
static void marshall_struct_msg_itf_put_display_picture_req(struct msg_itf_put_display_picture_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_put_display_picture_req(struct msg_itf_put_display_picture_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_put_display_picture_req_full(void);
static void marshall_struct_msg_itf_put_display_picture_req_full(struct msg_itf_put_display_picture_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_put_display_picture_req_full(struct msg_itf_put_display_picture_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_put_display_picture_reply(void);
static void marshall_struct_msg_itf_put_display_picture_reply(struct msg_itf_put_display_picture_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_put_display_picture_reply(struct msg_itf_put_display_picture_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_put_display_picture_reply_full(void);
static void marshall_struct_msg_itf_put_display_picture_reply_full(struct msg_itf_put_display_picture_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_put_display_picture_reply_full(struct msg_itf_put_display_picture_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TWindow(void);
static void marshall_struct_AL_TWindow(struct AL_TWindow *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TWindow(struct AL_TWindow *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TPicFormat(void);
static void marshall_struct_AL_TPicFormat(struct AL_TPicFormat *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TPicFormat(struct AL_TPicFormat *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_configure_output_settings_req(void);
static void marshall_struct_msg_itf_configure_output_settings_req(struct msg_itf_configure_output_settings_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_configure_output_settings_req(struct msg_itf_configure_output_settings_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_configure_output_settings_req_full(void);
static void marshall_struct_msg_itf_configure_output_settings_req_full(struct msg_itf_configure_output_settings_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_configure_output_settings_req_full(struct msg_itf_configure_output_settings_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_configure_output_settings_reply(void);
static void marshall_struct_msg_itf_configure_output_settings_reply(struct msg_itf_configure_output_settings_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_configure_output_settings_reply(struct msg_itf_configure_output_settings_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_configure_output_settings_reply_full(void);
static void marshall_struct_msg_itf_configure_output_settings_reply_full(struct msg_itf_configure_output_settings_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_configure_output_settings_reply_full(struct msg_itf_configure_output_settings_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_bitstream_buffer_refcount(void);
static void marshall_struct_msg_itf_evt_bitstream_buffer_refcount(struct msg_itf_evt_bitstream_buffer_refcount *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_bitstream_buffer_refcount(struct msg_itf_evt_bitstream_buffer_refcount *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_bitstream_buffer_refcount_full(void);
static void marshall_struct_msg_itf_evt_bitstream_buffer_refcount_full(struct msg_itf_evt_bitstream_buffer_refcount_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_bitstream_buffer_refcount_full(struct msg_itf_evt_bitstream_buffer_refcount_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_display_picture_refcount(void);
static void marshall_struct_msg_itf_evt_display_picture_refcount(struct msg_itf_evt_display_picture_refcount *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_display_picture_refcount(struct msg_itf_evt_display_picture_refcount *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_display_picture_refcount_full(void);
static void marshall_struct_msg_itf_evt_display_picture_refcount_full(struct msg_itf_evt_display_picture_refcount_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_display_picture_refcount_full(struct msg_itf_evt_display_picture_refcount_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_t_CropInfo(void);
static void marshall_struct_t_CropInfo(struct t_CropInfo *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_t_CropInfo(struct t_CropInfo *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_resolution_found(void);
static void marshall_struct_msg_itf_evt_resolution_found(struct msg_itf_evt_resolution_found *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_resolution_found(struct msg_itf_evt_resolution_found *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_resolution_found_full(void);
static void marshall_struct_msg_itf_evt_resolution_found_full(struct msg_itf_evt_resolution_found_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_resolution_found_full(struct msg_itf_evt_resolution_found_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_end_parsing(void);
static void marshall_struct_msg_itf_evt_end_parsing(struct msg_itf_evt_end_parsing *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_end_parsing(struct msg_itf_evt_end_parsing *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_end_parsing_full(void);
static void marshall_struct_msg_itf_evt_end_parsing_full(struct msg_itf_evt_end_parsing_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_end_parsing_full(struct msg_itf_evt_end_parsing_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_end_decoding(void);
static void marshall_struct_msg_itf_evt_end_decoding(struct msg_itf_evt_end_decoding *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_end_decoding(struct msg_itf_evt_end_decoding *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_end_decoding_full(void);
static void marshall_struct_msg_itf_evt_end_decoding_full(struct msg_itf_evt_end_decoding_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_end_decoding_full(struct msg_itf_evt_end_decoding_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_t_InfoDecode(void);
static void marshall_struct_t_InfoDecode(struct t_InfoDecode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_t_InfoDecode(struct t_InfoDecode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_display(void);
static void marshall_struct_msg_itf_evt_display(struct msg_itf_evt_display *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_display(struct msg_itf_evt_display *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_display_full(void);
static void marshall_struct_msg_itf_evt_display_full(struct msg_itf_evt_display_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_display_full(struct msg_itf_evt_display_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TChromaCoordinates(void);
static void marshall_struct_AL_TChromaCoordinates(struct AL_TChromaCoordinates *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TChromaCoordinates(struct AL_TChromaCoordinates *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TMasteringDisplayColourVolume(void);
static void marshall_struct_AL_TMasteringDisplayColourVolume(struct AL_TMasteringDisplayColourVolume *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TMasteringDisplayColourVolume(struct AL_TMasteringDisplayColourVolume *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TContentLightLevel(void);
static void marshall_struct_AL_TContentLightLevel(struct AL_TContentLightLevel *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TContentLightLevel(struct AL_TContentLightLevel *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TAlternativeTransferCharacteristics(void);
static void marshall_struct_AL_TAlternativeTransferCharacteristics(struct AL_TAlternativeTransferCharacteristics *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TAlternativeTransferCharacteristics(struct AL_TAlternativeTransferCharacteristics *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TProcessingWindow_ST2094_10(void);
static void marshall_struct_AL_TProcessingWindow_ST2094_10(struct AL_TProcessingWindow_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TProcessingWindow_ST2094_10(struct AL_TProcessingWindow_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TTImageCharacteristics_ST2094_10(void);
static void marshall_struct_AL_TTImageCharacteristics_ST2094_10(struct AL_TTImageCharacteristics_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TTImageCharacteristics_ST2094_10(struct AL_TTImageCharacteristics_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TManualAdjustment_ST2094_10(void);
static void marshall_struct_AL_TManualAdjustment_ST2094_10(struct AL_TManualAdjustment_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TManualAdjustment_ST2094_10(struct AL_TManualAdjustment_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TDynamicMeta_ST2094_10(void);
static void marshall_struct_AL_TDynamicMeta_ST2094_10(struct AL_TDynamicMeta_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TDynamicMeta_ST2094_10(struct AL_TDynamicMeta_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TProcessingWindow_ST2094_1(void);
static void marshall_struct_AL_TProcessingWindow_ST2094_1(struct AL_TProcessingWindow_ST2094_1 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TProcessingWindow_ST2094_1(struct AL_TProcessingWindow_ST2094_1 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TProcessingWindow_ST2094_40(void);
static void marshall_struct_AL_TProcessingWindow_ST2094_40(struct AL_TProcessingWindow_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TProcessingWindow_ST2094_40(struct AL_TProcessingWindow_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TDisplayPeakLuminance_ST2094_40(void);
static void marshall_struct_AL_TDisplayPeakLuminance_ST2094_40(struct AL_TDisplayPeakLuminance_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TDisplayPeakLuminance_ST2094_40(struct AL_TDisplayPeakLuminance_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TTargetedSystemDisplay_ST2094_40(void);
static void marshall_struct_AL_TTargetedSystemDisplay_ST2094_40(struct AL_TTargetedSystemDisplay_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TTargetedSystemDisplay_ST2094_40(struct AL_TTargetedSystemDisplay_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TToneMapping_ST2094_40(void);
static void marshall_struct_AL_TToneMapping_ST2094_40(struct AL_TToneMapping_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TToneMapping_ST2094_40(struct AL_TToneMapping_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TProcessingWindowTransform_ST2094_40(void);
static void marshall_struct_AL_TProcessingWindowTransform_ST2094_40(struct AL_TProcessingWindowTransform_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TProcessingWindowTransform_ST2094_40(struct AL_TProcessingWindowTransform_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TDynamicMeta_ST2094_40(void);
static void marshall_struct_AL_TDynamicMeta_ST2094_40(struct AL_TDynamicMeta_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TDynamicMeta_ST2094_40(struct AL_TDynamicMeta_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_THDRSEIs(void);
static void marshall_struct_AL_THDRSEIs(struct AL_THDRSEIs *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_THDRSEIs(struct AL_THDRSEIs *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_display_with_hdr(void);
static void marshall_struct_msg_itf_evt_display_with_hdr(struct msg_itf_evt_display_with_hdr *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_display_with_hdr(struct msg_itf_evt_display_with_hdr *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_display_with_hdr_full(void);
static void marshall_struct_msg_itf_evt_display_with_hdr_full(struct msg_itf_evt_display_with_hdr_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_display_with_hdr_full(struct msg_itf_evt_display_with_hdr_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_sei_buf(void);
static void marshall_struct_msg_itf_evt_sei_buf(struct msg_itf_evt_sei_buf *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_sei_buf(struct msg_itf_evt_sei_buf *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_sei_buf_full(void);
static void marshall_struct_msg_itf_evt_sei_buf_full(struct msg_itf_evt_sei_buf_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_sei_buf_full(struct msg_itf_evt_sei_buf_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_sei_msg(void);
static void marshall_struct_msg_itf_evt_sei_msg(struct msg_itf_evt_sei_msg *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_sei_msg(struct msg_itf_evt_sei_msg *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_sei_msg_full(void);
static void marshall_struct_msg_itf_evt_sei_msg_full(struct msg_itf_evt_sei_msg_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_sei_msg_full(struct msg_itf_evt_sei_msg_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_error(void);
static void marshall_struct_msg_itf_evt_error(struct msg_itf_evt_error *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_error(struct msg_itf_evt_error *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_error_full(void);
static void marshall_struct_msg_itf_evt_error_full(struct msg_itf_evt_error_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_error_full(struct msg_itf_evt_error_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_destroy_marker(void);
static void marshall_struct_msg_itf_evt_destroy_marker(struct msg_itf_evt_destroy_marker *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_destroy_marker(struct msg_itf_evt_destroy_marker *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_destroy_marker_full(void);
static void marshall_struct_msg_itf_evt_destroy_marker_full(struct msg_itf_evt_destroy_marker_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_destroy_marker_full(struct msg_itf_evt_destroy_marker_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_ECodec(void);
static void marshall_AL_ECodec(AL_ECodec *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_ECodec(AL_ECodec *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EFbStorageMode(void);
static void marshall_AL_EFbStorageMode(AL_EFbStorageMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EFbStorageMode(AL_EFbStorageMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EDecUnit(void);
static void marshall_AL_EDecUnit(AL_EDecUnit *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EDecUnit(AL_EDecUnit *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EDpbMode(void);
static void marshall_AL_EDpbMode(AL_EDpbMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EDpbMode(AL_EDpbMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TDimension(void);
static void marshall_AL_TDimension(AL_TDimension *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TDimension(AL_TDimension *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EChromaMode(void);
static void marshall_AL_EChromaMode(AL_EChromaMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EChromaMode(AL_EChromaMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EProfile(void);
static void marshall_AL_EProfile(AL_EProfile *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EProfile(AL_EProfile *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_ESequenceMode(void);
static void marshall_AL_ESequenceMode(AL_ESequenceMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_ESequenceMode(AL_ESequenceMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TStreamSettings(void);
static void marshall_AL_TStreamSettings(AL_TStreamSettings *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TStreamSettings(AL_TStreamSettings *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TPosition(void);
static void marshall_AL_TPosition(AL_TPosition *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TPosition(AL_TPosition *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EDecInputMode(void);
static void marshall_AL_EDecInputMode(AL_EDecInputMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EDecInputMode(AL_EDecInputMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TDecSettings(void);
static void marshall_AL_TDecSettings(AL_TDecSettings *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TDecSettings(AL_TDecSettings *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TPlane(void);
static void marshall_AL_TPlane(AL_TPlane *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TPlane(AL_TPlane *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TWindow(void);
static void marshall_AL_TWindow(AL_TWindow *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TWindow(AL_TWindow *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EAlphaMode(void);
static void marshall_AL_EAlphaMode(AL_EAlphaMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EAlphaMode(AL_EAlphaMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EPlaneMode(void);
static void marshall_AL_EPlaneMode(AL_EPlaneMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EPlaneMode(AL_EPlaneMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EComponentOrder(void);
static void marshall_AL_EComponentOrder(AL_EComponentOrder *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EComponentOrder(AL_EComponentOrder *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_ESamplePackMode(void);
static void marshall_AL_ESamplePackMode(AL_ESamplePackMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_ESamplePackMode(AL_ESamplePackMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TPicFormat(void);
static void marshall_AL_TPicFormat(AL_TPicFormat *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TPicFormat(AL_TPicFormat *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TCropInfo(void);
static void marshall_AL_TCropInfo(AL_TCropInfo *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TCropInfo(AL_TCropInfo *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EPicStruct(void);
static void marshall_AL_EPicStruct(AL_EPicStruct *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EPicStruct(AL_EPicStruct *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EOutputType(void);
static void marshall_AL_EOutputType(AL_EOutputType *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EOutputType(AL_EOutputType *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TInfoDecode(void);
static void marshall_AL_TInfoDecode(AL_TInfoDecode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TInfoDecode(AL_TInfoDecode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EColourDescription(void);
static void marshall_AL_EColourDescription(AL_EColourDescription *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EColourDescription(AL_EColourDescription *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_ETransferCharacteristics(void);
static void marshall_AL_ETransferCharacteristics(AL_ETransferCharacteristics *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_ETransferCharacteristics(AL_ETransferCharacteristics *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EColourMatrixCoefficients(void);
static void marshall_AL_EColourMatrixCoefficients(AL_EColourMatrixCoefficients *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EColourMatrixCoefficients(AL_EColourMatrixCoefficients *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TChromaCoordinates(void);
static void marshall_AL_TChromaCoordinates(AL_TChromaCoordinates *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TChromaCoordinates(AL_TChromaCoordinates *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TMasteringDisplayColourVolume(void);
static void marshall_AL_TMasteringDisplayColourVolume(AL_TMasteringDisplayColourVolume *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TMasteringDisplayColourVolume(AL_TMasteringDisplayColourVolume *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TContentLightLevel(void);
static void marshall_AL_TContentLightLevel(AL_TContentLightLevel *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TContentLightLevel(AL_TContentLightLevel *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TAlternativeTransferCharacteristics(void);
static void marshall_AL_TAlternativeTransferCharacteristics(AL_TAlternativeTransferCharacteristics *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TAlternativeTransferCharacteristics(AL_TAlternativeTransferCharacteristics *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TProcessingWindow_ST2094_10(void);
static void marshall_AL_TProcessingWindow_ST2094_10(AL_TProcessingWindow_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TProcessingWindow_ST2094_10(AL_TProcessingWindow_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TImageCharacteristics_ST2094_10(void);
static void marshall_AL_TImageCharacteristics_ST2094_10(AL_TImageCharacteristics_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TImageCharacteristics_ST2094_10(AL_TImageCharacteristics_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TManualAdjustment_ST2094_10(void);
static void marshall_AL_TManualAdjustment_ST2094_10(AL_TManualAdjustment_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TManualAdjustment_ST2094_10(AL_TManualAdjustment_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TDynamicMeta_ST2094_10(void);
static void marshall_AL_TDynamicMeta_ST2094_10(AL_TDynamicMeta_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TDynamicMeta_ST2094_10(AL_TDynamicMeta_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TProcessingWindow_ST2094_1(void);
static void marshall_AL_TProcessingWindow_ST2094_1(AL_TProcessingWindow_ST2094_1 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TProcessingWindow_ST2094_1(AL_TProcessingWindow_ST2094_1 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TProcessingWindow_ST2094_40(void);
static void marshall_AL_TProcessingWindow_ST2094_40(AL_TProcessingWindow_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TProcessingWindow_ST2094_40(AL_TProcessingWindow_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TDisplayPeakLuminance_ST2094_40(void);
static void marshall_AL_TDisplayPeakLuminance_ST2094_40(AL_TDisplayPeakLuminance_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TDisplayPeakLuminance_ST2094_40(AL_TDisplayPeakLuminance_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TTargetedSystemDisplay_ST2094_40(void);
static void marshall_AL_TTargetedSystemDisplay_ST2094_40(AL_TTargetedSystemDisplay_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TTargetedSystemDisplay_ST2094_40(AL_TTargetedSystemDisplay_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TToneMapping_ST2094_40(void);
static void marshall_AL_TToneMapping_ST2094_40(AL_TToneMapping_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TToneMapping_ST2094_40(AL_TToneMapping_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TProcessingWindowTransform_ST2094_40(void);
static void marshall_AL_TProcessingWindowTransform_ST2094_40(AL_TProcessingWindowTransform_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TProcessingWindowTransform_ST2094_40(AL_TProcessingWindowTransform_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TDynamicMeta_ST2094_40(void);
static void marshall_AL_TDynamicMeta_ST2094_40(AL_TDynamicMeta_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TDynamicMeta_ST2094_40(AL_TDynamicMeta_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_THDRSEIs(void);
static void marshall_AL_THDRSEIs(AL_THDRSEIs *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_THDRSEIs(AL_THDRSEIs *in, void (*read_cb)(int, void *, void *), void *arg);

static int get_size_struct_msg_itf_header()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += 2 * get_size_uint16_t();

	return res;
}
static void marshall_struct_msg_itf_header(struct msg_itf_header *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->drv_client_hdl, write_cb, arg);
	marshall_uint64_t(&in->drv_cmd_hdl, write_cb, arg);
	marshall_uint16_t(&in->type, write_cb, arg);
	marshall_uint16_t(&in->payload_len, write_cb, arg);
	{
		uint16_t *padding__ptr__ = (uint16_t *)((uintptr_t)in->padding);
		for (int i = 0; i < 2; i++)
			marshall_uint16_t(&padding__ptr__[i], write_cb, arg);
	}
}
static void unmarshall_struct_msg_itf_header(struct msg_itf_header *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->drv_client_hdl, read_cb, arg);
	unmarshall_uint64_t(&in->drv_cmd_hdl, read_cb, arg);
	unmarshall_uint16_t(&in->type, read_cb, arg);
	unmarshall_uint16_t(&in->payload_len, read_cb, arg);
	{
		uint16_t *padding__ptr__ = (uint16_t *)((uintptr_t)in->padding);
		for (int i = 0; i < 2; i++)
			unmarshall_uint16_t(&padding__ptr__[i], read_cb, arg);
	}
}
static int get_size_struct_msg_itf_get_cma_req()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_get_cma_req(struct msg_itf_get_cma_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->uSize, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_cma_req(struct msg_itf_get_cma_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->uSize, read_cb, arg);
}
static int get_size_struct_msg_itf_get_cma_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_get_cma_req();

	return res;
}
static void marshall_struct_msg_itf_get_cma_req_full(struct msg_itf_get_cma_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_get_cma_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_cma_req_full(struct msg_itf_get_cma_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_get_cma_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_get_cma_reply()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_get_cma_reply(struct msg_itf_get_cma_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->phyAddr, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_cma_reply(struct msg_itf_get_cma_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->phyAddr, read_cb, arg);
}
static int get_size_struct_msg_itf_get_cma_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_get_cma_reply();

	return res;
}
static void marshall_struct_msg_itf_get_cma_reply_full(struct msg_itf_get_cma_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_get_cma_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_cma_reply_full(struct msg_itf_get_cma_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_get_cma_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_put_cma_req()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_put_cma_req(struct msg_itf_put_cma_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->phyAddr, write_cb, arg);
}
static void unmarshall_struct_msg_itf_put_cma_req(struct msg_itf_put_cma_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->phyAddr, read_cb, arg);
}
static int get_size_struct_msg_itf_put_cma_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_put_cma_req();

	return res;
}
static void marshall_struct_msg_itf_put_cma_req_full(struct msg_itf_put_cma_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_put_cma_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_put_cma_req_full(struct msg_itf_put_cma_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_put_cma_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_put_cma_reply()
{
	int res = 0;

	res += get_size_int64_t();

	return res;
}
static void marshall_struct_msg_itf_put_cma_reply(struct msg_itf_put_cma_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_int64_t(&in->ret, write_cb, arg);
}
static void unmarshall_struct_msg_itf_put_cma_reply(struct msg_itf_put_cma_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_int64_t(&in->ret, read_cb, arg);
}
static int get_size_struct_msg_itf_put_cma_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_put_cma_reply();

	return res;
}
static void marshall_struct_msg_itf_put_cma_reply_full(struct msg_itf_put_cma_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_put_cma_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_put_cma_reply_full(struct msg_itf_put_cma_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_put_cma_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_perf_info_req()
{
	int res = 0;

	res += get_size_uint8_t();

	return res;
}
static void marshall_struct_msg_itf_perf_info_req(struct msg_itf_perf_info_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint8_t(&in->isProfile, write_cb, arg);
}
static void unmarshall_struct_msg_itf_perf_info_req(struct msg_itf_perf_info_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint8_t(&in->isProfile, read_cb, arg);
}
static int get_size_struct_msg_itf_perf_info_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_perf_info_req();

	return res;
}
static void marshall_struct_msg_itf_perf_info_req_full(struct msg_itf_perf_info_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_perf_info_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_perf_info_req_full(struct msg_itf_perf_info_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_perf_info_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_perf_info_reply()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint32_t();

	return res;
}
static void marshall_struct_msg_itf_perf_info_reply(struct msg_itf_perf_info_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->offset, write_cb, arg);
	marshall_uint32_t(&in->size, write_cb, arg);
}
static void unmarshall_struct_msg_itf_perf_info_reply(struct msg_itf_perf_info_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->offset, read_cb, arg);
	unmarshall_uint32_t(&in->size, read_cb, arg);
}
static int get_size_struct_msg_itf_perf_info_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_perf_info_reply();

	return res;
}
static void marshall_struct_msg_itf_perf_info_reply_full(struct msg_itf_perf_info_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_perf_info_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_perf_info_reply_full(struct msg_itf_perf_info_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_perf_info_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_write_req()
{
	int res = 0;

	res += get_size_int32_t();
	res += get_size_int32_t();

	return res;
}
static void marshall_struct_msg_itf_write_req(struct msg_itf_write_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_int32_t(&in->fd, write_cb, arg);
	marshall_int32_t(&in->len, write_cb, arg);
}
static void unmarshall_struct_msg_itf_write_req(struct msg_itf_write_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_int32_t(&in->fd, read_cb, arg);
	unmarshall_int32_t(&in->len, read_cb, arg);
}
static int get_size_struct_msg_itf_write_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_write_req();

	return res;
}
static void marshall_struct_msg_itf_write_req_full(struct msg_itf_write_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_write_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_write_req_full(struct msg_itf_write_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_write_req(&in->req, read_cb, arg);
}
static int get_size_struct_chunk_info()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_chunk_info(struct chunk_info *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->pAddr, write_cb, arg);
	marshall_uint64_t(&in->uSize, write_cb, arg);
}
static void unmarshall_struct_chunk_info(struct chunk_info *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->pAddr, read_cb, arg);
	unmarshall_uint64_t(&in->uSize, read_cb, arg);
}
static int get_size_struct_AL_TDimension()
{
	int res = 0;

	res += get_size_int32_t();
	res += get_size_int32_t();

	return res;
}
static void marshall_struct_AL_TDimension(struct AL_TDimension *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_int32_t(&in->iWidth, write_cb, arg);
	marshall_int32_t(&in->iHeight, write_cb, arg);
}
static void unmarshall_struct_AL_TDimension(struct AL_TDimension *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_int32_t(&in->iWidth, read_cb, arg);
	unmarshall_int32_t(&in->iHeight, read_cb, arg);
}
static int get_size_struct_AL_TStreamSettings()
{
	int res = 0;

	res += get_size_AL_TDimension();
	res += get_size_AL_EChromaMode();
	res += get_size_int();
	res += get_size_int();
	res += get_size_AL_EProfile();
	res += get_size_AL_ESequenceMode();
	res += get_size__Bool();
	res += get_size_int();

	return res;
}
static void marshall_struct_AL_TStreamSettings(struct AL_TStreamSettings *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_AL_TDimension(&in->tDim, write_cb, arg);
	marshall_AL_EChromaMode(&in->eChroma, write_cb, arg);
	marshall_int(&in->iBitDepth, write_cb, arg);
	marshall_int(&in->iLevel, write_cb, arg);
	marshall_AL_EProfile(&in->eProfile, write_cb, arg);
	marshall_AL_ESequenceMode(&in->eSequenceMode, write_cb, arg);
	marshall__Bool(&in->bDecodeIntraOnly, write_cb, arg);
	marshall_int(&in->iMaxRef, write_cb, arg);
}
static void unmarshall_struct_AL_TStreamSettings(struct AL_TStreamSettings *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_AL_TDimension(&in->tDim, read_cb, arg);
	unmarshall_AL_EChromaMode(&in->eChroma, read_cb, arg);
	unmarshall_int(&in->iBitDepth, read_cb, arg);
	unmarshall_int(&in->iLevel, read_cb, arg);
	unmarshall_AL_EProfile(&in->eProfile, read_cb, arg);
	unmarshall_AL_ESequenceMode(&in->eSequenceMode, read_cb, arg);
	unmarshall__Bool(&in->bDecodeIntraOnly, read_cb, arg);
	unmarshall_int(&in->iMaxRef, read_cb, arg);
}
static int get_size_struct_AL_TPosition()
{
	int res = 0;

	res += get_size_int32_t();
	res += get_size_int32_t();

	return res;
}
static void marshall_struct_AL_TPosition(struct AL_TPosition *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_int32_t(&in->iX, write_cb, arg);
	marshall_int32_t(&in->iY, write_cb, arg);
}
static void unmarshall_struct_AL_TPosition(struct AL_TPosition *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_int32_t(&in->iX, read_cb, arg);
	unmarshall_int32_t(&in->iY, read_cb, arg);
}
static int get_size_struct_AL_TDecSettings()
{
	int res = 0;

	res += get_size_int();
	res += get_size_int();
	res += get_size_uint8_t();
	res += get_size__Bool();
	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_AL_ECodec();
	res += get_size__Bool();
	res += get_size_uint8_t();
	res += get_size__Bool();
	res += get_size__Bool();
	res += get_size__Bool();
	res += get_size_uint16_t();
	res += get_size__Bool();
	res += get_size_AL_EFbStorageMode();
	res += get_size_AL_EDecUnit();
	res += get_size_AL_EDpbMode();
	res += get_size_AL_TStreamSettings();
	res += get_size_AL_TPosition();
	res += get_size__Bool();
	res += get_size_uint32_t();
	res += get_size__Bool();
	res += get_size_AL_EDecInputMode();

	return res;
}
static void marshall_struct_AL_TDecSettings(struct AL_TDecSettings *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_int(&in->iStackSize, write_cb, arg);
	marshall_int(&in->iStreamBufSize, write_cb, arg);
	marshall_uint8_t(&in->uNumCore, write_cb, arg);
	marshall__Bool(&in->bNonRealtime, write_cb, arg);
	marshall_uint32_t(&in->uFrameRate, write_cb, arg);
	marshall_uint32_t(&in->uClkRatio, write_cb, arg);
	marshall_AL_ECodec(&in->eCodec, write_cb, arg);
	marshall__Bool(&in->bParallelWPP, write_cb, arg);
	marshall_uint8_t(&in->uDDRWidth, write_cb, arg);
	marshall__Bool(&in->bDisableCache, write_cb, arg);
	marshall__Bool(&in->bLowLat, write_cb, arg);
	marshall__Bool(&in->bForceFrameRate, write_cb, arg);
	marshall_uint16_t(&in->uConcealMaxFps, write_cb, arg);
	marshall__Bool(&in->bFrameBufferCompression, write_cb, arg);
	marshall_AL_EFbStorageMode(&in->eFBStorageMode, write_cb, arg);
	marshall_AL_EDecUnit(&in->eDecUnit, write_cb, arg);
	marshall_AL_EDpbMode(&in->eDpbMode, write_cb, arg);
	marshall_AL_TStreamSettings(&in->tStream, write_cb, arg);
	marshall_AL_TPosition(&in->tOutputPosition, write_cb, arg);
	marshall__Bool(&in->bUseIFramesAsSyncPoint, write_cb, arg);
	marshall_uint32_t(&in->uNumBuffersHeldByNextComponent, write_cb, arg);
	marshall__Bool(&in->bUseEarlyCallback, write_cb, arg);
	marshall_AL_EDecInputMode(&in->eInputMode, write_cb, arg);
}
static void unmarshall_struct_AL_TDecSettings(struct AL_TDecSettings *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_int(&in->iStackSize, read_cb, arg);
	unmarshall_int(&in->iStreamBufSize, read_cb, arg);
	unmarshall_uint8_t(&in->uNumCore, read_cb, arg);
	unmarshall__Bool(&in->bNonRealtime, read_cb, arg);
	unmarshall_uint32_t(&in->uFrameRate, read_cb, arg);
	unmarshall_uint32_t(&in->uClkRatio, read_cb, arg);
	unmarshall_AL_ECodec(&in->eCodec, read_cb, arg);
	unmarshall__Bool(&in->bParallelWPP, read_cb, arg);
	unmarshall_uint8_t(&in->uDDRWidth, read_cb, arg);
	unmarshall__Bool(&in->bDisableCache, read_cb, arg);
	unmarshall__Bool(&in->bLowLat, read_cb, arg);
	unmarshall__Bool(&in->bForceFrameRate, read_cb, arg);
	unmarshall_uint16_t(&in->uConcealMaxFps, read_cb, arg);
	unmarshall__Bool(&in->bFrameBufferCompression, read_cb, arg);
	unmarshall_AL_EFbStorageMode(&in->eFBStorageMode, read_cb, arg);
	unmarshall_AL_EDecUnit(&in->eDecUnit, read_cb, arg);
	unmarshall_AL_EDpbMode(&in->eDpbMode, read_cb, arg);
	unmarshall_AL_TStreamSettings(&in->tStream, read_cb, arg);
	unmarshall_AL_TPosition(&in->tOutputPosition, read_cb, arg);
	unmarshall__Bool(&in->bUseIFramesAsSyncPoint, read_cb, arg);
	unmarshall_uint32_t(&in->uNumBuffersHeldByNextComponent, read_cb, arg);
	unmarshall__Bool(&in->bUseEarlyCallback, read_cb, arg);
	unmarshall_AL_EDecInputMode(&in->eInputMode, read_cb, arg);
}
static int get_size_struct_msg_itf_create_decoder_req()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_AL_TDecSettings();

	return res;
}
static void marshall_struct_msg_itf_create_decoder_req(struct msg_itf_create_decoder_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hWrapper, write_cb, arg);
	marshall_AL_TDecSettings(&in->settings, write_cb, arg);
}
static void unmarshall_struct_msg_itf_create_decoder_req(struct msg_itf_create_decoder_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hWrapper, read_cb, arg);
	unmarshall_AL_TDecSettings(&in->settings, read_cb, arg);
}
static int get_size_struct_msg_itf_create_decoder_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_create_decoder_req();

	return res;
}
static void marshall_struct_msg_itf_create_decoder_req_full(struct msg_itf_create_decoder_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_create_decoder_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_create_decoder_req_full(struct msg_itf_create_decoder_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_create_decoder_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_create_decoder_reply()
{
	int res = 0;

	res += get_size_int32_t();
	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_create_decoder_reply(struct msg_itf_create_decoder_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_int32_t(&in->ret, write_cb, arg);
	marshall_uint64_t(&in->hDec, write_cb, arg);
}
static void unmarshall_struct_msg_itf_create_decoder_reply(struct msg_itf_create_decoder_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_int32_t(&in->ret, read_cb, arg);
	unmarshall_uint64_t(&in->hDec, read_cb, arg);
}
static int get_size_struct_msg_itf_create_decoder_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_create_decoder_reply();

	return res;
}
static void marshall_struct_msg_itf_create_decoder_reply_full(struct msg_itf_create_decoder_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_create_decoder_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_create_decoder_reply_full(struct msg_itf_create_decoder_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_create_decoder_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_destroy_decoder_req()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_destroy_decoder_req(struct msg_itf_destroy_decoder_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hDec, write_cb, arg);
}
static void unmarshall_struct_msg_itf_destroy_decoder_req(struct msg_itf_destroy_decoder_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hDec, read_cb, arg);
}
static int get_size_struct_msg_itf_destroy_decoder_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_destroy_decoder_req();

	return res;
}
static void marshall_struct_msg_itf_destroy_decoder_req_full(struct msg_itf_destroy_decoder_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_destroy_decoder_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_destroy_decoder_req_full(struct msg_itf_destroy_decoder_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_destroy_decoder_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_destroy_decoder_reply()
{
	int res = 0;

	res += get_size_uint32_t();

	return res;
}
static void marshall_struct_msg_itf_destroy_decoder_reply(struct msg_itf_destroy_decoder_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint32_t(&in->unused, write_cb, arg);
}
static void unmarshall_struct_msg_itf_destroy_decoder_reply(struct msg_itf_destroy_decoder_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint32_t(&in->unused, read_cb, arg);
}
static int get_size_struct_msg_itf_destroy_decoder_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_destroy_decoder_reply();

	return res;
}
static void marshall_struct_msg_itf_destroy_decoder_reply_full(struct msg_itf_destroy_decoder_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_destroy_decoder_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_destroy_decoder_reply_full(struct msg_itf_destroy_decoder_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_destroy_decoder_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_push_bitstream_buffer_req()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_uint8_t();

	return res;
}
static void marshall_struct_msg_itf_push_bitstream_buffer_req(struct msg_itf_push_bitstream_buffer_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hDec, write_cb, arg);
	marshall_uint64_t(&in->pBuf, write_cb, arg);
	marshall_uint64_t(&in->pAddr, write_cb, arg);
	marshall_uint64_t(&in->uSize, write_cb, arg);
	marshall_uint64_t(&in->uBufferSize, write_cb, arg);
	marshall_uint8_t(&in->uFlags, write_cb, arg);
}
static void unmarshall_struct_msg_itf_push_bitstream_buffer_req(struct msg_itf_push_bitstream_buffer_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hDec, read_cb, arg);
	unmarshall_uint64_t(&in->pBuf, read_cb, arg);
	unmarshall_uint64_t(&in->pAddr, read_cb, arg);
	unmarshall_uint64_t(&in->uSize, read_cb, arg);
	unmarshall_uint64_t(&in->uBufferSize, read_cb, arg);
	unmarshall_uint8_t(&in->uFlags, read_cb, arg);
}
static int get_size_struct_msg_itf_push_bitstream_buffer_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_push_bitstream_buffer_req();

	return res;
}
static void marshall_struct_msg_itf_push_bitstream_buffer_req_full(struct msg_itf_push_bitstream_buffer_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_push_bitstream_buffer_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_push_bitstream_buffer_req_full(struct msg_itf_push_bitstream_buffer_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_push_bitstream_buffer_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_push_bitstream_buffer_reply()
{
	int res = 0;

	res += get_size_uint8_t();

	return res;
}
static void marshall_struct_msg_itf_push_bitstream_buffer_reply(struct msg_itf_push_bitstream_buffer_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint8_t(&in->res, write_cb, arg);
}
static void unmarshall_struct_msg_itf_push_bitstream_buffer_reply(struct msg_itf_push_bitstream_buffer_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint8_t(&in->res, read_cb, arg);
}
static int get_size_struct_msg_itf_push_bitstream_buffer_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_push_bitstream_buffer_reply();

	return res;
}
static void marshall_struct_msg_itf_push_bitstream_buffer_reply_full(struct msg_itf_push_bitstream_buffer_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_push_bitstream_buffer_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_push_bitstream_buffer_reply_full(struct msg_itf_push_bitstream_buffer_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_push_bitstream_buffer_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_flush_req()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_flush_req(struct msg_itf_flush_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hDec, write_cb, arg);
}
static void unmarshall_struct_msg_itf_flush_req(struct msg_itf_flush_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hDec, read_cb, arg);
}
static int get_size_struct_msg_itf_flush_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_flush_req();

	return res;
}
static void marshall_struct_msg_itf_flush_req_full(struct msg_itf_flush_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_flush_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_flush_req_full(struct msg_itf_flush_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_flush_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_flush_reply()
{
	int res = 0;

	res += get_size_uint32_t();

	return res;
}
static void marshall_struct_msg_itf_flush_reply(struct msg_itf_flush_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint32_t(&in->unused, write_cb, arg);
}
static void unmarshall_struct_msg_itf_flush_reply(struct msg_itf_flush_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint32_t(&in->unused, read_cb, arg);
}
static int get_size_struct_msg_itf_flush_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_flush_reply();

	return res;
}
static void marshall_struct_msg_itf_flush_reply_full(struct msg_itf_flush_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_flush_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_flush_reply_full(struct msg_itf_flush_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_flush_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_get_maxdepth_req()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_get_maxdepth_req(struct msg_itf_get_maxdepth_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hDec, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_maxdepth_req(struct msg_itf_get_maxdepth_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hDec, read_cb, arg);
}
static int get_size_struct_msg_itf_get_maxdepth_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_get_maxdepth_req();

	return res;
}
static void marshall_struct_msg_itf_get_maxdepth_req_full(struct msg_itf_get_maxdepth_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_get_maxdepth_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_maxdepth_req_full(struct msg_itf_get_maxdepth_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_get_maxdepth_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_get_maxdepth_reply()
{
	int res = 0;

	res += get_size_int32_t();

	return res;
}
static void marshall_struct_msg_itf_get_maxdepth_reply(struct msg_itf_get_maxdepth_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_int32_t(&in->iMaxDepth, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_maxdepth_reply(struct msg_itf_get_maxdepth_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_int32_t(&in->iMaxDepth, read_cb, arg);
}
static int get_size_struct_msg_itf_get_maxdepth_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_get_maxdepth_reply();

	return res;
}
static void marshall_struct_msg_itf_get_maxdepth_reply_full(struct msg_itf_get_maxdepth_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_get_maxdepth_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_maxdepth_reply_full(struct msg_itf_get_maxdepth_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_get_maxdepth_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_get_codec_req()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_get_codec_req(struct msg_itf_get_codec_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hDec, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_codec_req(struct msg_itf_get_codec_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hDec, read_cb, arg);
}
static int get_size_struct_msg_itf_get_codec_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_get_codec_req();

	return res;
}
static void marshall_struct_msg_itf_get_codec_req_full(struct msg_itf_get_codec_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_get_codec_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_codec_req_full(struct msg_itf_get_codec_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_get_codec_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_get_codec_reply()
{
	int res = 0;

	res += get_size_AL_ECodec();

	return res;
}
static void marshall_struct_msg_itf_get_codec_reply(struct msg_itf_get_codec_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_AL_ECodec(&in->eCodec, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_codec_reply(struct msg_itf_get_codec_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_AL_ECodec(&in->eCodec, read_cb, arg);
}
static int get_size_struct_msg_itf_get_codec_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_get_codec_reply();

	return res;
}
static void marshall_struct_msg_itf_get_codec_reply_full(struct msg_itf_get_codec_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_get_codec_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_codec_reply_full(struct msg_itf_get_codec_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_get_codec_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_get_last_error_req()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_get_last_error_req(struct msg_itf_get_last_error_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hDec, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_last_error_req(struct msg_itf_get_last_error_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hDec, read_cb, arg);
}
static int get_size_struct_msg_itf_get_last_error_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_get_last_error_req();

	return res;
}
static void marshall_struct_msg_itf_get_last_error_req_full(struct msg_itf_get_last_error_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_get_last_error_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_last_error_req_full(struct msg_itf_get_last_error_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_get_last_error_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_get_last_error_reply()
{
	int res = 0;

	res += get_size_uint32_t();

	return res;
}
static void marshall_struct_msg_itf_get_last_error_reply(struct msg_itf_get_last_error_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint32_t(&in->uLastError, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_last_error_reply(struct msg_itf_get_last_error_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint32_t(&in->uLastError, read_cb, arg);
}
static int get_size_struct_msg_itf_get_last_error_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_get_last_error_reply();

	return res;
}
static void marshall_struct_msg_itf_get_last_error_reply_full(struct msg_itf_get_last_error_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_get_last_error_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_last_error_reply_full(struct msg_itf_get_last_error_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_get_last_error_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_preallocate_buffers_req()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_preallocate_buffers_req(struct msg_itf_preallocate_buffers_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hDec, write_cb, arg);
}
static void unmarshall_struct_msg_itf_preallocate_buffers_req(struct msg_itf_preallocate_buffers_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hDec, read_cb, arg);
}
static int get_size_struct_msg_itf_preallocate_buffers_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_preallocate_buffers_req();

	return res;
}
static void marshall_struct_msg_itf_preallocate_buffers_req_full(struct msg_itf_preallocate_buffers_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_preallocate_buffers_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_preallocate_buffers_req_full(struct msg_itf_preallocate_buffers_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_preallocate_buffers_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_preallocate_buffers_reply()
{
	int res = 0;

	res += get_size_uint8_t();

	return res;
}
static void marshall_struct_msg_itf_preallocate_buffers_reply(struct msg_itf_preallocate_buffers_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint8_t(&in->res, write_cb, arg);
}
static void unmarshall_struct_msg_itf_preallocate_buffers_reply(struct msg_itf_preallocate_buffers_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint8_t(&in->res, read_cb, arg);
}
static int get_size_struct_msg_itf_preallocate_buffers_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_preallocate_buffers_reply();

	return res;
}
static void marshall_struct_msg_itf_preallocate_buffers_reply_full(struct msg_itf_preallocate_buffers_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_preallocate_buffers_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_preallocate_buffers_reply_full(struct msg_itf_preallocate_buffers_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_preallocate_buffers_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_setparam_req()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint8_t();

	return res;
}
static void marshall_struct_msg_itf_setparam_req(struct msg_itf_setparam_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hDec, write_cb, arg);
	marshall_uint8_t(&in->bForceCleanBuffers, write_cb, arg);
}
static void unmarshall_struct_msg_itf_setparam_req(struct msg_itf_setparam_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hDec, read_cb, arg);
	unmarshall_uint8_t(&in->bForceCleanBuffers, read_cb, arg);
}
static int get_size_struct_msg_itf_setparam_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_setparam_req();

	return res;
}
static void marshall_struct_msg_itf_setparam_req_full(struct msg_itf_setparam_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_setparam_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_setparam_req_full(struct msg_itf_setparam_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_setparam_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_setparam_reply()
{
	int res = 0;

	res += get_size_uint32_t();

	return res;
}
static void marshall_struct_msg_itf_setparam_reply(struct msg_itf_setparam_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint32_t(&in->unused, write_cb, arg);
}
static void unmarshall_struct_msg_itf_setparam_reply(struct msg_itf_setparam_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint32_t(&in->unused, read_cb, arg);
}
static int get_size_struct_msg_itf_setparam_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_setparam_reply();

	return res;
}
static void marshall_struct_msg_itf_setparam_reply_full(struct msg_itf_setparam_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_setparam_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_setparam_reply_full(struct msg_itf_setparam_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_setparam_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_AL_TPlane()
{
	int res = 0;

	res += get_size_int();
	res += get_size_int();
	res += get_size_int();

	return res;
}
static void marshall_struct_AL_TPlane(struct AL_TPlane *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_int(&in->iChunkIdx, write_cb, arg);
	marshall_int(&in->iOffset, write_cb, arg);
	marshall_int(&in->iPitch, write_cb, arg);
}
static void unmarshall_struct_AL_TPlane(struct AL_TPlane *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_int(&in->iChunkIdx, read_cb, arg);
	unmarshall_int(&in->iOffset, read_cb, arg);
	unmarshall_int(&in->iPitch, read_cb, arg);
}
static int get_size_struct_msg_itf_put_display_picture_req()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += 6 * get_size_struct_chunk_info();
	res += get_size_AL_TDimension();
	res += 9 * get_size_AL_TPlane();
	res += get_size_TFourCC();
	res += get_size_uint8_t();

	return res;
}
static void marshall_struct_msg_itf_put_display_picture_req(struct msg_itf_put_display_picture_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hDec, write_cb, arg);
	marshall_uint64_t(&in->pDisplay, write_cb, arg);
	{
		struct chunk_info *chunks__ptr__ = (struct chunk_info *)((uintptr_t)in->chunks);
		for (int i = 0; i < 6; i++)
			marshall_struct_chunk_info(&chunks__ptr__[i], write_cb, arg);
	}
	marshall_AL_TDimension(&in->tDim, write_cb, arg);
	{
		AL_TPlane *tPlanes__ptr__ = (AL_TPlane *)((uintptr_t)in->tPlanes);
		for (int i = 0; i < 9; i++)
			marshall_AL_TPlane(&tPlanes__ptr__[i], write_cb, arg);
	}
	marshall_TFourCC(&in->tFourCC, write_cb, arg);
	marshall_uint8_t(&in->hasHdrMeta, write_cb, arg);
}
static void unmarshall_struct_msg_itf_put_display_picture_req(struct msg_itf_put_display_picture_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hDec, read_cb, arg);
	unmarshall_uint64_t(&in->pDisplay, read_cb, arg);
	{
		struct chunk_info *chunks__ptr__ = (struct chunk_info *)((uintptr_t)in->chunks);
		for (int i = 0; i < 6; i++)
			unmarshall_struct_chunk_info(&chunks__ptr__[i], read_cb, arg);
	}
	unmarshall_AL_TDimension(&in->tDim, read_cb, arg);
	{
		AL_TPlane *tPlanes__ptr__ = (AL_TPlane *)((uintptr_t)in->tPlanes);
		for (int i = 0; i < 9; i++)
			unmarshall_AL_TPlane(&tPlanes__ptr__[i], read_cb, arg);
	}
	unmarshall_TFourCC(&in->tFourCC, read_cb, arg);
	unmarshall_uint8_t(&in->hasHdrMeta, read_cb, arg);
}
static int get_size_struct_msg_itf_put_display_picture_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_put_display_picture_req();

	return res;
}
static void marshall_struct_msg_itf_put_display_picture_req_full(struct msg_itf_put_display_picture_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_put_display_picture_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_put_display_picture_req_full(struct msg_itf_put_display_picture_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_put_display_picture_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_put_display_picture_reply()
{
	int res = 0;

	res += get_size_uint8_t();

	return res;
}
static void marshall_struct_msg_itf_put_display_picture_reply(struct msg_itf_put_display_picture_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint8_t(&in->res, write_cb, arg);
}
static void unmarshall_struct_msg_itf_put_display_picture_reply(struct msg_itf_put_display_picture_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint8_t(&in->res, read_cb, arg);
}
static int get_size_struct_msg_itf_put_display_picture_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_put_display_picture_reply();

	return res;
}
static void marshall_struct_msg_itf_put_display_picture_reply_full(struct msg_itf_put_display_picture_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_put_display_picture_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_put_display_picture_reply_full(struct msg_itf_put_display_picture_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_put_display_picture_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_AL_TWindow()
{
	int res = 0;

	res += get_size_AL_TPosition();
	res += get_size_AL_TDimension();

	return res;
}
static void marshall_struct_AL_TWindow(struct AL_TWindow *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_AL_TPosition(&in->tPos, write_cb, arg);
	marshall_AL_TDimension(&in->tDim, write_cb, arg);
}
static void unmarshall_struct_AL_TWindow(struct AL_TWindow *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_AL_TPosition(&in->tPos, read_cb, arg);
	unmarshall_AL_TDimension(&in->tDim, read_cb, arg);
}
static int get_size_struct_AL_TPicFormat()
{
	int res = 0;

	res += get_size_AL_EChromaMode();
	res += get_size_AL_EAlphaMode();
	res += get_size_uint8_t();
	res += get_size_AL_EFbStorageMode();
	res += get_size_AL_EPlaneMode();
	res += get_size_AL_EComponentOrder();
	res += get_size_AL_ESamplePackMode();
	res += get_size__Bool();
	res += get_size__Bool();

	return res;
}
static void marshall_struct_AL_TPicFormat(struct AL_TPicFormat *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_AL_EChromaMode(&in->eChromaMode, write_cb, arg);
	marshall_AL_EAlphaMode(&in->eAlphaMode, write_cb, arg);
	marshall_uint8_t(&in->uBitDepth, write_cb, arg);
	marshall_AL_EFbStorageMode(&in->eStorageMode, write_cb, arg);
	marshall_AL_EPlaneMode(&in->ePlaneMode, write_cb, arg);
	marshall_AL_EComponentOrder(&in->eComponentOrder, write_cb, arg);
	marshall_AL_ESamplePackMode(&in->eSamplePackMode, write_cb, arg);
	marshall__Bool(&in->bCompressed, write_cb, arg);
	marshall__Bool(&in->bMSB, write_cb, arg);
}
static void unmarshall_struct_AL_TPicFormat(struct AL_TPicFormat *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_AL_EChromaMode(&in->eChromaMode, read_cb, arg);
	unmarshall_AL_EAlphaMode(&in->eAlphaMode, read_cb, arg);
	unmarshall_uint8_t(&in->uBitDepth, read_cb, arg);
	unmarshall_AL_EFbStorageMode(&in->eStorageMode, read_cb, arg);
	unmarshall_AL_EPlaneMode(&in->ePlaneMode, read_cb, arg);
	unmarshall_AL_EComponentOrder(&in->eComponentOrder, read_cb, arg);
	unmarshall_AL_ESamplePackMode(&in->eSamplePackMode, read_cb, arg);
	unmarshall__Bool(&in->bCompressed, read_cb, arg);
	unmarshall__Bool(&in->bMSB, read_cb, arg);
}
static int get_size_struct_msg_itf_configure_output_settings_req()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size__Bool();
	res += get_size__Bool();
	res += get_size__Bool();
	res += get_size_AL_TWindow();
	res += get_size_AL_TPicFormat();

	return res;
}
static void marshall_struct_msg_itf_configure_output_settings_req(struct msg_itf_configure_output_settings_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hDec, write_cb, arg);
	marshall_uint64_t(&in->pDisplay, write_cb, arg);
	marshall__Bool(&in->bCustomFormat, write_cb, arg);
	marshall__Bool(&in->bOutputAll, write_cb, arg);
	marshall__Bool(&in->bDisableFilmGrain, write_cb, arg);
	marshall_AL_TWindow(&in->tFbcDisableWindow, write_cb, arg);
	marshall_AL_TPicFormat(&in->tPicFormat, write_cb, arg);
}
static void unmarshall_struct_msg_itf_configure_output_settings_req(struct msg_itf_configure_output_settings_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hDec, read_cb, arg);
	unmarshall_uint64_t(&in->pDisplay, read_cb, arg);
	unmarshall__Bool(&in->bCustomFormat, read_cb, arg);
	unmarshall__Bool(&in->bOutputAll, read_cb, arg);
	unmarshall__Bool(&in->bDisableFilmGrain, read_cb, arg);
	unmarshall_AL_TWindow(&in->tFbcDisableWindow, read_cb, arg);
	unmarshall_AL_TPicFormat(&in->tPicFormat, read_cb, arg);
}
static int get_size_struct_msg_itf_configure_output_settings_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_configure_output_settings_req();

	return res;
}
static void marshall_struct_msg_itf_configure_output_settings_req_full(struct msg_itf_configure_output_settings_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_configure_output_settings_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_configure_output_settings_req_full(struct msg_itf_configure_output_settings_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_configure_output_settings_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_configure_output_settings_reply()
{
	int res = 0;

	res += get_size_uint8_t();

	return res;
}
static void marshall_struct_msg_itf_configure_output_settings_reply(struct msg_itf_configure_output_settings_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint8_t(&in->res, write_cb, arg);
}
static void unmarshall_struct_msg_itf_configure_output_settings_reply(struct msg_itf_configure_output_settings_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint8_t(&in->res, read_cb, arg);
}
static int get_size_struct_msg_itf_configure_output_settings_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_configure_output_settings_reply();

	return res;
}
static void marshall_struct_msg_itf_configure_output_settings_reply_full(struct msg_itf_configure_output_settings_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_configure_output_settings_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_configure_output_settings_reply_full(struct msg_itf_configure_output_settings_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_configure_output_settings_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_bitstream_buffer_refcount()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_evt_bitstream_buffer_refcount(struct msg_itf_evt_bitstream_buffer_refcount *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->pBuf, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_bitstream_buffer_refcount(struct msg_itf_evt_bitstream_buffer_refcount *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->pBuf, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_bitstream_buffer_refcount_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_evt_bitstream_buffer_refcount();

	return res;
}
static void marshall_struct_msg_itf_evt_bitstream_buffer_refcount_full(struct msg_itf_evt_bitstream_buffer_refcount_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_evt_bitstream_buffer_refcount(&in->event, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_bitstream_buffer_refcount_full(struct msg_itf_evt_bitstream_buffer_refcount_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_evt_bitstream_buffer_refcount(&in->event, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_display_picture_refcount()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_evt_display_picture_refcount(struct msg_itf_evt_display_picture_refcount *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->pDisplay, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_display_picture_refcount(struct msg_itf_evt_display_picture_refcount *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->pDisplay, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_display_picture_refcount_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_evt_display_picture_refcount();

	return res;
}
static void marshall_struct_msg_itf_evt_display_picture_refcount_full(struct msg_itf_evt_display_picture_refcount_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_evt_display_picture_refcount(&in->event, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_display_picture_refcount_full(struct msg_itf_evt_display_picture_refcount_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_evt_display_picture_refcount(&in->event, read_cb, arg);
}
static int get_size_struct_t_CropInfo()
{
	int res = 0;

	res += get_size__Bool();
	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_uint32_t();

	return res;
}
static void marshall_struct_t_CropInfo(struct t_CropInfo *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall__Bool(&in->bCropping, write_cb, arg);
	marshall_uint32_t(&in->uCropOffsetLeft, write_cb, arg);
	marshall_uint32_t(&in->uCropOffsetRight, write_cb, arg);
	marshall_uint32_t(&in->uCropOffsetTop, write_cb, arg);
	marshall_uint32_t(&in->uCropOffsetBottom, write_cb, arg);
}
static void unmarshall_struct_t_CropInfo(struct t_CropInfo *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall__Bool(&in->bCropping, read_cb, arg);
	unmarshall_uint32_t(&in->uCropOffsetLeft, read_cb, arg);
	unmarshall_uint32_t(&in->uCropOffsetRight, read_cb, arg);
	unmarshall_uint32_t(&in->uCropOffsetTop, read_cb, arg);
	unmarshall_uint32_t(&in->uCropOffsetBottom, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_resolution_found()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_int32_t();
	res += get_size_AL_TStreamSettings();
	res += get_size_AL_TCropInfo();

	return res;
}
static void marshall_struct_msg_itf_evt_resolution_found(struct msg_itf_evt_resolution_found *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hWrapper, write_cb, arg);
	marshall_int32_t(&in->BufferNumber, write_cb, arg);
	marshall_AL_TStreamSettings(&in->settings, write_cb, arg);
	marshall_AL_TCropInfo(&in->cropInfo, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_resolution_found(struct msg_itf_evt_resolution_found *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hWrapper, read_cb, arg);
	unmarshall_int32_t(&in->BufferNumber, read_cb, arg);
	unmarshall_AL_TStreamSettings(&in->settings, read_cb, arg);
	unmarshall_AL_TCropInfo(&in->cropInfo, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_resolution_found_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_evt_resolution_found();

	return res;
}
static void marshall_struct_msg_itf_evt_resolution_found_full(struct msg_itf_evt_resolution_found_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_evt_resolution_found(&in->event, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_resolution_found_full(struct msg_itf_evt_resolution_found_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_evt_resolution_found(&in->event, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_end_parsing()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_int32_t();

	return res;
}
static void marshall_struct_msg_itf_evt_end_parsing(struct msg_itf_evt_end_parsing *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hWrapper, write_cb, arg);
	marshall_uint64_t(&in->pParsedFrame, write_cb, arg);
	marshall_int32_t(&in->iParsingID, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_end_parsing(struct msg_itf_evt_end_parsing *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hWrapper, read_cb, arg);
	unmarshall_uint64_t(&in->pParsedFrame, read_cb, arg);
	unmarshall_int32_t(&in->iParsingID, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_end_parsing_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_evt_end_parsing();

	return res;
}
static void marshall_struct_msg_itf_evt_end_parsing_full(struct msg_itf_evt_end_parsing_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_evt_end_parsing(&in->event, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_end_parsing_full(struct msg_itf_evt_end_parsing_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_evt_end_parsing(&in->event, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_end_decoding()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_evt_end_decoding(struct msg_itf_evt_end_decoding *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hWrapper, write_cb, arg);
	marshall_uint64_t(&in->pDecodedFrame, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_end_decoding(struct msg_itf_evt_end_decoding *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hWrapper, read_cb, arg);
	unmarshall_uint64_t(&in->pDecodedFrame, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_end_decoding_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_evt_end_decoding();

	return res;
}
static void marshall_struct_msg_itf_evt_end_decoding_full(struct msg_itf_evt_end_decoding_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_evt_end_decoding(&in->event, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_end_decoding_full(struct msg_itf_evt_end_decoding_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_evt_end_decoding(&in->event, read_cb, arg);
}
static int get_size_struct_t_InfoDecode()
{
	int res = 0;

	res += get_size_AL_TDimension();
	res += get_size_AL_EChromaMode();
	res += get_size_uint8_t();
	res += get_size_uint8_t();
	res += get_size_AL_TCropInfo();
	res += get_size_AL_EFbStorageMode();
	res += get_size_AL_EPicStruct();
	res += get_size_uint32_t();
	res += get_size_AL_EOutputType();
	res += get_size_AL_TPosition();

	return res;
}
static void marshall_struct_t_InfoDecode(struct t_InfoDecode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_AL_TDimension(&in->tDim, write_cb, arg);
	marshall_AL_EChromaMode(&in->eChromaMode, write_cb, arg);
	marshall_uint8_t(&in->uBitDepthY, write_cb, arg);
	marshall_uint8_t(&in->uBitDepthC, write_cb, arg);
	marshall_AL_TCropInfo(&in->tCrop, write_cb, arg);
	marshall_AL_EFbStorageMode(&in->eFbStorageMode, write_cb, arg);
	marshall_AL_EPicStruct(&in->ePicStruct, write_cb, arg);
	marshall_uint32_t(&in->uCRC, write_cb, arg);
	marshall_AL_EOutputType(&in->eOutputID, write_cb, arg);
	marshall_AL_TPosition(&in->tPos, write_cb, arg);
}
static void unmarshall_struct_t_InfoDecode(struct t_InfoDecode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_AL_TDimension(&in->tDim, read_cb, arg);
	unmarshall_AL_EChromaMode(&in->eChromaMode, read_cb, arg);
	unmarshall_uint8_t(&in->uBitDepthY, read_cb, arg);
	unmarshall_uint8_t(&in->uBitDepthC, read_cb, arg);
	unmarshall_AL_TCropInfo(&in->tCrop, read_cb, arg);
	unmarshall_AL_EFbStorageMode(&in->eFbStorageMode, read_cb, arg);
	unmarshall_AL_EPicStruct(&in->ePicStruct, read_cb, arg);
	unmarshall_uint32_t(&in->uCRC, read_cb, arg);
	unmarshall_AL_EOutputType(&in->eOutputID, read_cb, arg);
	unmarshall_AL_TPosition(&in->tPos, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_display()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_AL_TInfoDecode();
	res += get_size_uint32_t();
	res += get_size_AL_TDimension();
	res += get_size_TFourCC();

	return res;
}
static void marshall_struct_msg_itf_evt_display(struct msg_itf_evt_display *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hWrapper, write_cb, arg);
	marshall_uint64_t(&in->pDisplayedFrame, write_cb, arg);
	marshall_uint64_t(&in->pInfo, write_cb, arg);
	marshall_AL_TInfoDecode(&in->info, write_cb, arg);
	marshall_uint32_t(&in->decodedError, write_cb, arg);
	marshall_AL_TDimension(&in->tDim, write_cb, arg);
	marshall_TFourCC(&in->tFourCC, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_display(struct msg_itf_evt_display *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hWrapper, read_cb, arg);
	unmarshall_uint64_t(&in->pDisplayedFrame, read_cb, arg);
	unmarshall_uint64_t(&in->pInfo, read_cb, arg);
	unmarshall_AL_TInfoDecode(&in->info, read_cb, arg);
	unmarshall_uint32_t(&in->decodedError, read_cb, arg);
	unmarshall_AL_TDimension(&in->tDim, read_cb, arg);
	unmarshall_TFourCC(&in->tFourCC, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_display_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_evt_display();

	return res;
}
static void marshall_struct_msg_itf_evt_display_full(struct msg_itf_evt_display_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_evt_display(&in->event, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_display_full(struct msg_itf_evt_display_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_evt_display(&in->event, read_cb, arg);
}
static int get_size_struct_AL_TChromaCoordinates()
{
	int res = 0;

	res += get_size_uint16_t();
	res += get_size_uint16_t();

	return res;
}
static void marshall_struct_AL_TChromaCoordinates(struct AL_TChromaCoordinates *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint16_t(&in->x, write_cb, arg);
	marshall_uint16_t(&in->y, write_cb, arg);
}
static void unmarshall_struct_AL_TChromaCoordinates(struct AL_TChromaCoordinates *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint16_t(&in->x, read_cb, arg);
	unmarshall_uint16_t(&in->y, read_cb, arg);
}
static int get_size_struct_AL_TMasteringDisplayColourVolume()
{
	int res = 0;

	res += 3 * get_size_AL_TChromaCoordinates();
	res += get_size_AL_TChromaCoordinates();
	res += get_size_uint32_t();
	res += get_size_uint32_t();

	return res;
}
static void marshall_struct_AL_TMasteringDisplayColourVolume(struct AL_TMasteringDisplayColourVolume *in, void (*write_cb)(int, void *, void *), void *arg)
{
	{
		AL_TChromaCoordinates *display_primaries__ptr__ = (AL_TChromaCoordinates *)((uintptr_t)in->display_primaries);
		for (int i = 0; i < 3; i++)
			marshall_AL_TChromaCoordinates(&display_primaries__ptr__[i], write_cb, arg);
	}
	marshall_AL_TChromaCoordinates(&in->white_point, write_cb, arg);
	marshall_uint32_t(&in->max_display_mastering_luminance, write_cb, arg);
	marshall_uint32_t(&in->min_display_mastering_luminance, write_cb, arg);
}
static void unmarshall_struct_AL_TMasteringDisplayColourVolume(struct AL_TMasteringDisplayColourVolume *in, void (*read_cb)(int, void *, void *), void *arg)
{
	{
		AL_TChromaCoordinates *display_primaries__ptr__ = (AL_TChromaCoordinates *)((uintptr_t)in->display_primaries);
		for (int i = 0; i < 3; i++)
			unmarshall_AL_TChromaCoordinates(&display_primaries__ptr__[i], read_cb, arg);
	}
	unmarshall_AL_TChromaCoordinates(&in->white_point, read_cb, arg);
	unmarshall_uint32_t(&in->max_display_mastering_luminance, read_cb, arg);
	unmarshall_uint32_t(&in->min_display_mastering_luminance, read_cb, arg);
}
static int get_size_struct_AL_TContentLightLevel()
{
	int res = 0;

	res += get_size_uint16_t();
	res += get_size_uint16_t();

	return res;
}
static void marshall_struct_AL_TContentLightLevel(struct AL_TContentLightLevel *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint16_t(&in->max_content_light_level, write_cb, arg);
	marshall_uint16_t(&in->max_pic_average_light_level, write_cb, arg);
}
static void unmarshall_struct_AL_TContentLightLevel(struct AL_TContentLightLevel *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint16_t(&in->max_content_light_level, read_cb, arg);
	unmarshall_uint16_t(&in->max_pic_average_light_level, read_cb, arg);
}
static int get_size_struct_AL_TAlternativeTransferCharacteristics()
{
	int res = 0;

	res += get_size_AL_ETransferCharacteristics();

	return res;
}
static void marshall_struct_AL_TAlternativeTransferCharacteristics(struct AL_TAlternativeTransferCharacteristics *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_AL_ETransferCharacteristics(&in->preferred_transfer_characteristics, write_cb, arg);
}
static void unmarshall_struct_AL_TAlternativeTransferCharacteristics(struct AL_TAlternativeTransferCharacteristics *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_AL_ETransferCharacteristics(&in->preferred_transfer_characteristics, read_cb, arg);
}
static int get_size_struct_AL_TProcessingWindow_ST2094_10()
{
	int res = 0;

	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();

	return res;
}
static void marshall_struct_AL_TProcessingWindow_ST2094_10(struct AL_TProcessingWindow_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint16_t(&in->active_area_left_offset, write_cb, arg);
	marshall_uint16_t(&in->active_area_right_offset, write_cb, arg);
	marshall_uint16_t(&in->active_area_top_offset, write_cb, arg);
	marshall_uint16_t(&in->active_area_bottom_offset, write_cb, arg);
}
static void unmarshall_struct_AL_TProcessingWindow_ST2094_10(struct AL_TProcessingWindow_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint16_t(&in->active_area_left_offset, read_cb, arg);
	unmarshall_uint16_t(&in->active_area_right_offset, read_cb, arg);
	unmarshall_uint16_t(&in->active_area_top_offset, read_cb, arg);
	unmarshall_uint16_t(&in->active_area_bottom_offset, read_cb, arg);
}
static int get_size_struct_AL_TTImageCharacteristics_ST2094_10()
{
	int res = 0;

	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();

	return res;
}
static void marshall_struct_AL_TTImageCharacteristics_ST2094_10(struct AL_TTImageCharacteristics_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint16_t(&in->min_pq, write_cb, arg);
	marshall_uint16_t(&in->max_pq, write_cb, arg);
	marshall_uint16_t(&in->avg_pq, write_cb, arg);
}
static void unmarshall_struct_AL_TTImageCharacteristics_ST2094_10(struct AL_TTImageCharacteristics_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint16_t(&in->min_pq, read_cb, arg);
	unmarshall_uint16_t(&in->max_pq, read_cb, arg);
	unmarshall_uint16_t(&in->avg_pq, read_cb, arg);
}
static int get_size_struct_AL_TManualAdjustment_ST2094_10()
{
	int res = 0;

	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_int16_t();

	return res;
}
static void marshall_struct_AL_TManualAdjustment_ST2094_10(struct AL_TManualAdjustment_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint16_t(&in->target_max_pq, write_cb, arg);
	marshall_uint16_t(&in->trim_slope, write_cb, arg);
	marshall_uint16_t(&in->trim_offset, write_cb, arg);
	marshall_uint16_t(&in->trim_power, write_cb, arg);
	marshall_uint16_t(&in->trim_chroma_weight, write_cb, arg);
	marshall_uint16_t(&in->trim_saturation_gain, write_cb, arg);
	marshall_int16_t(&in->ms_weight, write_cb, arg);
}
static void unmarshall_struct_AL_TManualAdjustment_ST2094_10(struct AL_TManualAdjustment_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint16_t(&in->target_max_pq, read_cb, arg);
	unmarshall_uint16_t(&in->trim_slope, read_cb, arg);
	unmarshall_uint16_t(&in->trim_offset, read_cb, arg);
	unmarshall_uint16_t(&in->trim_power, read_cb, arg);
	unmarshall_uint16_t(&in->trim_chroma_weight, read_cb, arg);
	unmarshall_uint16_t(&in->trim_saturation_gain, read_cb, arg);
	unmarshall_int16_t(&in->ms_weight, read_cb, arg);
}
static int get_size_struct_AL_TDynamicMeta_ST2094_10()
{
	int res = 0;

	res += get_size_uint8_t();
	res += get_size__Bool();
	res += get_size_AL_TProcessingWindow_ST2094_10();
	res += get_size_AL_TImageCharacteristics_ST2094_10();
	res += get_size_uint8_t();
	res += 16 * get_size_AL_TManualAdjustment_ST2094_10();

	return res;
}
static void marshall_struct_AL_TDynamicMeta_ST2094_10(struct AL_TDynamicMeta_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint8_t(&in->application_version, write_cb, arg);
	marshall__Bool(&in->processing_window_flag, write_cb, arg);
	marshall_AL_TProcessingWindow_ST2094_10(&in->processing_window, write_cb, arg);
	marshall_AL_TImageCharacteristics_ST2094_10(&in->image_characteristics, write_cb, arg);
	marshall_uint8_t(&in->num_manual_adjustments, write_cb, arg);
	{
		AL_TManualAdjustment_ST2094_10 *manual_adjustments__ptr__ = (AL_TManualAdjustment_ST2094_10 *)((uintptr_t)in->manual_adjustments);
		for (int i = 0; i < 16; i++)
			marshall_AL_TManualAdjustment_ST2094_10(&manual_adjustments__ptr__[i], write_cb, arg);
	}
}
static void unmarshall_struct_AL_TDynamicMeta_ST2094_10(struct AL_TDynamicMeta_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint8_t(&in->application_version, read_cb, arg);
	unmarshall__Bool(&in->processing_window_flag, read_cb, arg);
	unmarshall_AL_TProcessingWindow_ST2094_10(&in->processing_window, read_cb, arg);
	unmarshall_AL_TImageCharacteristics_ST2094_10(&in->image_characteristics, read_cb, arg);
	unmarshall_uint8_t(&in->num_manual_adjustments, read_cb, arg);
	{
		AL_TManualAdjustment_ST2094_10 *manual_adjustments__ptr__ = (AL_TManualAdjustment_ST2094_10 *)((uintptr_t)in->manual_adjustments);
		for (int i = 0; i < 16; i++)
			unmarshall_AL_TManualAdjustment_ST2094_10(&manual_adjustments__ptr__[i], read_cb, arg);
	}
}
static int get_size_struct_AL_TProcessingWindow_ST2094_1()
{
	int res = 0;

	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();

	return res;
}
static void marshall_struct_AL_TProcessingWindow_ST2094_1(struct AL_TProcessingWindow_ST2094_1 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint16_t(&in->upper_left_corner_x, write_cb, arg);
	marshall_uint16_t(&in->upper_left_corner_y, write_cb, arg);
	marshall_uint16_t(&in->lower_right_corner_x, write_cb, arg);
	marshall_uint16_t(&in->lower_right_corner_y, write_cb, arg);
}
static void unmarshall_struct_AL_TProcessingWindow_ST2094_1(struct AL_TProcessingWindow_ST2094_1 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint16_t(&in->upper_left_corner_x, read_cb, arg);
	unmarshall_uint16_t(&in->upper_left_corner_y, read_cb, arg);
	unmarshall_uint16_t(&in->lower_right_corner_x, read_cb, arg);
	unmarshall_uint16_t(&in->lower_right_corner_y, read_cb, arg);
}
static int get_size_struct_AL_TProcessingWindow_ST2094_40()
{
	int res = 0;

	res += get_size_AL_TProcessingWindow_ST2094_1();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint8_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint8_t();

	return res;
}
static void marshall_struct_AL_TProcessingWindow_ST2094_40(struct AL_TProcessingWindow_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_AL_TProcessingWindow_ST2094_1(&in->base_processing_window, write_cb, arg);
	marshall_uint16_t(&in->center_of_ellipse_x, write_cb, arg);
	marshall_uint16_t(&in->center_of_ellipse_y, write_cb, arg);
	marshall_uint8_t(&in->rotation_angle, write_cb, arg);
	marshall_uint16_t(&in->semimajor_axis_internal_ellipse, write_cb, arg);
	marshall_uint16_t(&in->semimajor_axis_external_ellipse, write_cb, arg);
	marshall_uint16_t(&in->semiminor_axis_external_ellipse, write_cb, arg);
	marshall_uint8_t(&in->overlap_process_option, write_cb, arg);
}
static void unmarshall_struct_AL_TProcessingWindow_ST2094_40(struct AL_TProcessingWindow_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_AL_TProcessingWindow_ST2094_1(&in->base_processing_window, read_cb, arg);
	unmarshall_uint16_t(&in->center_of_ellipse_x, read_cb, arg);
	unmarshall_uint16_t(&in->center_of_ellipse_y, read_cb, arg);
	unmarshall_uint8_t(&in->rotation_angle, read_cb, arg);
	unmarshall_uint16_t(&in->semimajor_axis_internal_ellipse, read_cb, arg);
	unmarshall_uint16_t(&in->semimajor_axis_external_ellipse, read_cb, arg);
	unmarshall_uint16_t(&in->semiminor_axis_external_ellipse, read_cb, arg);
	unmarshall_uint8_t(&in->overlap_process_option, read_cb, arg);
}
static int get_size_struct_AL_TDisplayPeakLuminance_ST2094_40()
{
	int res = 0;

	res += get_size__Bool();
	res += get_size_uint8_t();
	res += get_size_uint8_t();
	res += 625 * get_size_uint8_t();

	return res;
}
static void marshall_struct_AL_TDisplayPeakLuminance_ST2094_40(struct AL_TDisplayPeakLuminance_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall__Bool(&in->actual_peak_luminance_flag, write_cb, arg);
	marshall_uint8_t(&in->num_rows_actual_peak_luminance, write_cb, arg);
	marshall_uint8_t(&in->num_cols_actual_peak_luminance, write_cb, arg);
	{
		uint8_t *actual_peak_luminance__ptr__ = (uint8_t *)((uintptr_t)in->actual_peak_luminance);
		for (int i = 0; i < 625; i++)
			marshall_uint8_t(&actual_peak_luminance__ptr__[i], write_cb, arg);
	}
}
static void unmarshall_struct_AL_TDisplayPeakLuminance_ST2094_40(struct AL_TDisplayPeakLuminance_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall__Bool(&in->actual_peak_luminance_flag, read_cb, arg);
	unmarshall_uint8_t(&in->num_rows_actual_peak_luminance, read_cb, arg);
	unmarshall_uint8_t(&in->num_cols_actual_peak_luminance, read_cb, arg);
	{
		uint8_t *actual_peak_luminance__ptr__ = (uint8_t *)((uintptr_t)in->actual_peak_luminance);
		for (int i = 0; i < 625; i++)
			unmarshall_uint8_t(&actual_peak_luminance__ptr__[i], read_cb, arg);
	}
}
static int get_size_struct_AL_TTargetedSystemDisplay_ST2094_40()
{
	int res = 0;

	res += get_size_uint32_t();
	res += get_size_AL_TDisplayPeakLuminance_ST2094_40();

	return res;
}
static void marshall_struct_AL_TTargetedSystemDisplay_ST2094_40(struct AL_TTargetedSystemDisplay_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint32_t(&in->maximum_luminance, write_cb, arg);
	marshall_AL_TDisplayPeakLuminance_ST2094_40(&in->peak_luminance, write_cb, arg);
}
static void unmarshall_struct_AL_TTargetedSystemDisplay_ST2094_40(struct AL_TTargetedSystemDisplay_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint32_t(&in->maximum_luminance, read_cb, arg);
	unmarshall_AL_TDisplayPeakLuminance_ST2094_40(&in->peak_luminance, read_cb, arg);
}
static int get_size_struct_AL_TToneMapping_ST2094_40()
{
	int res = 0;

	res += get_size__Bool();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint8_t();
	res += 15 * get_size_uint16_t();

	return res;
}
static void marshall_struct_AL_TToneMapping_ST2094_40(struct AL_TToneMapping_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall__Bool(&in->tone_mapping_flag, write_cb, arg);
	marshall_uint16_t(&in->knee_point_x, write_cb, arg);
	marshall_uint16_t(&in->knee_point_y, write_cb, arg);
	marshall_uint8_t(&in->num_bezier_curve_anchors, write_cb, arg);
	{
		uint16_t *bezier_curve_anchors__ptr__ = (uint16_t *)((uintptr_t)in->bezier_curve_anchors);
		for (int i = 0; i < 15; i++)
			marshall_uint16_t(&bezier_curve_anchors__ptr__[i], write_cb, arg);
	}
}
static void unmarshall_struct_AL_TToneMapping_ST2094_40(struct AL_TToneMapping_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall__Bool(&in->tone_mapping_flag, read_cb, arg);
	unmarshall_uint16_t(&in->knee_point_x, read_cb, arg);
	unmarshall_uint16_t(&in->knee_point_y, read_cb, arg);
	unmarshall_uint8_t(&in->num_bezier_curve_anchors, read_cb, arg);
	{
		uint16_t *bezier_curve_anchors__ptr__ = (uint16_t *)((uintptr_t)in->bezier_curve_anchors);
		for (int i = 0; i < 15; i++)
			unmarshall_uint16_t(&bezier_curve_anchors__ptr__[i], read_cb, arg);
	}
}
static int get_size_struct_AL_TProcessingWindowTransform_ST2094_40()
{
	int res = 0;

	res += 3 * get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_uint8_t();
	res += 15 * get_size_uint8_t();
	res += 15 * get_size_uint32_t();
	res += get_size_uint8_t();
	res += get_size_AL_TToneMapping_ST2094_40();
	res += get_size__Bool();
	res += get_size_uint8_t();

	return res;
}
static void marshall_struct_AL_TProcessingWindowTransform_ST2094_40(struct AL_TProcessingWindowTransform_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	{
		uint32_t *maxscl__ptr__ = (uint32_t *)((uintptr_t)in->maxscl);
		for (int i = 0; i < 3; i++)
			marshall_uint32_t(&maxscl__ptr__[i], write_cb, arg);
	}
	marshall_uint32_t(&in->average_maxrgb, write_cb, arg);
	marshall_uint8_t(&in->num_distribution_maxrgb_percentiles, write_cb, arg);
	{
		uint8_t *distribution_maxrgb_percentages__ptr__ = (uint8_t *)((uintptr_t)in->distribution_maxrgb_percentages);
		for (int i = 0; i < 15; i++)
			marshall_uint8_t(&distribution_maxrgb_percentages__ptr__[i], write_cb, arg);
	}
	{
		uint32_t *distribution_maxrgb_percentiles__ptr__ = (uint32_t *)((uintptr_t)in->distribution_maxrgb_percentiles);
		for (int i = 0; i < 15; i++)
			marshall_uint32_t(&distribution_maxrgb_percentiles__ptr__[i], write_cb, arg);
	}
	marshall_uint8_t(&in->fraction_bright_pixels, write_cb, arg);
	marshall_AL_TToneMapping_ST2094_40(&in->tone_mapping, write_cb, arg);
	marshall__Bool(&in->color_saturation_mapping_flag, write_cb, arg);
	marshall_uint8_t(&in->color_saturation_weight, write_cb, arg);
}
static void unmarshall_struct_AL_TProcessingWindowTransform_ST2094_40(struct AL_TProcessingWindowTransform_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	{
		uint32_t *maxscl__ptr__ = (uint32_t *)((uintptr_t)in->maxscl);
		for (int i = 0; i < 3; i++)
			unmarshall_uint32_t(&maxscl__ptr__[i], read_cb, arg);
	}
	unmarshall_uint32_t(&in->average_maxrgb, read_cb, arg);
	unmarshall_uint8_t(&in->num_distribution_maxrgb_percentiles, read_cb, arg);
	{
		uint8_t *distribution_maxrgb_percentages__ptr__ = (uint8_t *)((uintptr_t)in->distribution_maxrgb_percentages);
		for (int i = 0; i < 15; i++)
			unmarshall_uint8_t(&distribution_maxrgb_percentages__ptr__[i], read_cb, arg);
	}
	{
		uint32_t *distribution_maxrgb_percentiles__ptr__ = (uint32_t *)((uintptr_t)in->distribution_maxrgb_percentiles);
		for (int i = 0; i < 15; i++)
			unmarshall_uint32_t(&distribution_maxrgb_percentiles__ptr__[i], read_cb, arg);
	}
	unmarshall_uint8_t(&in->fraction_bright_pixels, read_cb, arg);
	unmarshall_AL_TToneMapping_ST2094_40(&in->tone_mapping, read_cb, arg);
	unmarshall__Bool(&in->color_saturation_mapping_flag, read_cb, arg);
	unmarshall_uint8_t(&in->color_saturation_weight, read_cb, arg);
}
static int get_size_struct_AL_TDynamicMeta_ST2094_40()
{
	int res = 0;

	res += get_size_uint8_t();
	res += get_size_uint8_t();
	res += 2 * get_size_AL_TProcessingWindow_ST2094_40();
	res += get_size_AL_TTargetedSystemDisplay_ST2094_40();
	res += get_size_AL_TDisplayPeakLuminance_ST2094_40();
	res += 3 * get_size_AL_TProcessingWindowTransform_ST2094_40();

	return res;
}
static void marshall_struct_AL_TDynamicMeta_ST2094_40(struct AL_TDynamicMeta_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint8_t(&in->application_version, write_cb, arg);
	marshall_uint8_t(&in->num_windows, write_cb, arg);
	{
		AL_TProcessingWindow_ST2094_40 *processing_windows__ptr__ = (AL_TProcessingWindow_ST2094_40 *)((uintptr_t)in->processing_windows);
		for (int i = 0; i < 2; i++)
			marshall_AL_TProcessingWindow_ST2094_40(&processing_windows__ptr__[i], write_cb, arg);
	}
	marshall_AL_TTargetedSystemDisplay_ST2094_40(&in->targeted_system_display, write_cb, arg);
	marshall_AL_TDisplayPeakLuminance_ST2094_40(&in->mastering_display_peak_luminance, write_cb, arg);
	{
		AL_TProcessingWindowTransform_ST2094_40 *processing_window_transforms__ptr__ = (AL_TProcessingWindowTransform_ST2094_40 *)((uintptr_t)in->processing_window_transforms);
		for (int i = 0; i < 3; i++)
			marshall_AL_TProcessingWindowTransform_ST2094_40(&processing_window_transforms__ptr__[i], write_cb, arg);
	}
}
static void unmarshall_struct_AL_TDynamicMeta_ST2094_40(struct AL_TDynamicMeta_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint8_t(&in->application_version, read_cb, arg);
	unmarshall_uint8_t(&in->num_windows, read_cb, arg);
	{
		AL_TProcessingWindow_ST2094_40 *processing_windows__ptr__ = (AL_TProcessingWindow_ST2094_40 *)((uintptr_t)in->processing_windows);
		for (int i = 0; i < 2; i++)
			unmarshall_AL_TProcessingWindow_ST2094_40(&processing_windows__ptr__[i], read_cb, arg);
	}
	unmarshall_AL_TTargetedSystemDisplay_ST2094_40(&in->targeted_system_display, read_cb, arg);
	unmarshall_AL_TDisplayPeakLuminance_ST2094_40(&in->mastering_display_peak_luminance, read_cb, arg);
	{
		AL_TProcessingWindowTransform_ST2094_40 *processing_window_transforms__ptr__ = (AL_TProcessingWindowTransform_ST2094_40 *)((uintptr_t)in->processing_window_transforms);
		for (int i = 0; i < 3; i++)
			unmarshall_AL_TProcessingWindowTransform_ST2094_40(&processing_window_transforms__ptr__[i], read_cb, arg);
	}
}
static int get_size_struct_AL_THDRSEIs()
{
	int res = 0;

	res += get_size__Bool();
	res += get_size_AL_TMasteringDisplayColourVolume();
	res += get_size__Bool();
	res += get_size_AL_TContentLightLevel();
	res += get_size__Bool();
	res += get_size_AL_TAlternativeTransferCharacteristics();
	res += get_size__Bool();
	res += get_size_AL_TDynamicMeta_ST2094_10();
	res += get_size__Bool();
	res += get_size_AL_TDynamicMeta_ST2094_40();

	return res;
}
static void marshall_struct_AL_THDRSEIs(struct AL_THDRSEIs *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall__Bool(&in->bHasMDCV, write_cb, arg);
	marshall_AL_TMasteringDisplayColourVolume(&in->tMDCV, write_cb, arg);
	marshall__Bool(&in->bHasCLL, write_cb, arg);
	marshall_AL_TContentLightLevel(&in->tCLL, write_cb, arg);
	marshall__Bool(&in->bHasATC, write_cb, arg);
	marshall_AL_TAlternativeTransferCharacteristics(&in->tATC, write_cb, arg);
	marshall__Bool(&in->bHasST2094_10, write_cb, arg);
	marshall_AL_TDynamicMeta_ST2094_10(&in->tST2094_10, write_cb, arg);
	marshall__Bool(&in->bHasST2094_40, write_cb, arg);
	marshall_AL_TDynamicMeta_ST2094_40(&in->tST2094_40, write_cb, arg);
}
static void unmarshall_struct_AL_THDRSEIs(struct AL_THDRSEIs *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall__Bool(&in->bHasMDCV, read_cb, arg);
	unmarshall_AL_TMasteringDisplayColourVolume(&in->tMDCV, read_cb, arg);
	unmarshall__Bool(&in->bHasCLL, read_cb, arg);
	unmarshall_AL_TContentLightLevel(&in->tCLL, read_cb, arg);
	unmarshall__Bool(&in->bHasATC, read_cb, arg);
	unmarshall_AL_TAlternativeTransferCharacteristics(&in->tATC, read_cb, arg);
	unmarshall__Bool(&in->bHasST2094_10, read_cb, arg);
	unmarshall_AL_TDynamicMeta_ST2094_10(&in->tST2094_10, read_cb, arg);
	unmarshall__Bool(&in->bHasST2094_40, read_cb, arg);
	unmarshall_AL_TDynamicMeta_ST2094_40(&in->tST2094_40, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_display_with_hdr()
{
	int res = 0;

	res += get_size_struct_msg_itf_evt_display();
	res += get_size_AL_EColourDescription();
	res += get_size_AL_ETransferCharacteristics();
	res += get_size_AL_EColourMatrixCoefficients();
	res += get_size_AL_THDRSEIs();

	return res;
}
static void marshall_struct_msg_itf_evt_display_with_hdr(struct msg_itf_evt_display_with_hdr *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_display(&in->evt_display, write_cb, arg);
	marshall_AL_EColourDescription(&in->eColourDescription, write_cb, arg);
	marshall_AL_ETransferCharacteristics(&in->eTransferCharacteristics, write_cb, arg);
	marshall_AL_EColourMatrixCoefficients(&in->eColourMatrixCoeffs, write_cb, arg);
	marshall_AL_THDRSEIs(&in->tHDRSEIs, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_display_with_hdr(struct msg_itf_evt_display_with_hdr *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_display(&in->evt_display, read_cb, arg);
	unmarshall_AL_EColourDescription(&in->eColourDescription, read_cb, arg);
	unmarshall_AL_ETransferCharacteristics(&in->eTransferCharacteristics, read_cb, arg);
	unmarshall_AL_EColourMatrixCoefficients(&in->eColourMatrixCoeffs, read_cb, arg);
	unmarshall_AL_THDRSEIs(&in->tHDRSEIs, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_display_with_hdr_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_evt_display_with_hdr();

	return res;
}
static void marshall_struct_msg_itf_evt_display_with_hdr_full(struct msg_itf_evt_display_with_hdr_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_evt_display_with_hdr(&in->event, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_display_with_hdr_full(struct msg_itf_evt_display_with_hdr_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_evt_display_with_hdr(&in->event, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_sei_buf()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_int32_t();
	res += get_size_int32_t();
	res += get_size_uint8_t();

	return res;
}
static void marshall_struct_msg_itf_evt_sei_buf(struct msg_itf_evt_sei_buf *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hWrapper, write_cb, arg);
	marshall_uint64_t(&in->uOffsetSei, write_cb, arg);
	marshall_uint64_t(&in->pAddrSei, write_cb, arg);
	marshall_int32_t(&in->iPayloadType, write_cb, arg);
	marshall_int32_t(&in->iPayloadSize, write_cb, arg);
	marshall_uint8_t(&in->bIsPrefix, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_sei_buf(struct msg_itf_evt_sei_buf *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hWrapper, read_cb, arg);
	unmarshall_uint64_t(&in->uOffsetSei, read_cb, arg);
	unmarshall_uint64_t(&in->pAddrSei, read_cb, arg);
	unmarshall_int32_t(&in->iPayloadType, read_cb, arg);
	unmarshall_int32_t(&in->iPayloadSize, read_cb, arg);
	unmarshall_uint8_t(&in->bIsPrefix, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_sei_buf_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_evt_sei_buf();

	return res;
}
static void marshall_struct_msg_itf_evt_sei_buf_full(struct msg_itf_evt_sei_buf_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_evt_sei_buf(&in->event, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_sei_buf_full(struct msg_itf_evt_sei_buf_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_evt_sei_buf(&in->event, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_sei_msg()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_int32_t();
	res += get_size_int32_t();
	res += get_size_uint8_t();
	res += 32 * get_size_uint8_t();

	return res;
}
static void marshall_struct_msg_itf_evt_sei_msg(struct msg_itf_evt_sei_msg *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hWrapper, write_cb, arg);
	marshall_int32_t(&in->iPayloadType, write_cb, arg);
	marshall_int32_t(&in->iPayloadSize, write_cb, arg);
	marshall_uint8_t(&in->bIsPrefix, write_cb, arg);
	{
		uint8_t *payload__ptr__ = (uint8_t *)((uintptr_t)in->payload);
		for (int i = 0; i < 32; i++)
			marshall_uint8_t(&payload__ptr__[i], write_cb, arg);
	}
}
static void unmarshall_struct_msg_itf_evt_sei_msg(struct msg_itf_evt_sei_msg *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hWrapper, read_cb, arg);
	unmarshall_int32_t(&in->iPayloadType, read_cb, arg);
	unmarshall_int32_t(&in->iPayloadSize, read_cb, arg);
	unmarshall_uint8_t(&in->bIsPrefix, read_cb, arg);
	{
		uint8_t *payload__ptr__ = (uint8_t *)((uintptr_t)in->payload);
		for (int i = 0; i < 32; i++)
			unmarshall_uint8_t(&payload__ptr__[i], read_cb, arg);
	}
}
static int get_size_struct_msg_itf_evt_sei_msg_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_evt_sei_msg();

	return res;
}
static void marshall_struct_msg_itf_evt_sei_msg_full(struct msg_itf_evt_sei_msg_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_evt_sei_msg(&in->event, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_sei_msg_full(struct msg_itf_evt_sei_msg_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_evt_sei_msg(&in->event, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_error()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint32_t();

	return res;
}
static void marshall_struct_msg_itf_evt_error(struct msg_itf_evt_error *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hWrapper, write_cb, arg);
	marshall_uint32_t(&in->uError, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_error(struct msg_itf_evt_error *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hWrapper, read_cb, arg);
	unmarshall_uint32_t(&in->uError, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_error_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_evt_error();

	return res;
}
static void marshall_struct_msg_itf_evt_error_full(struct msg_itf_evt_error_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_evt_error(&in->event, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_error_full(struct msg_itf_evt_error_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_evt_error(&in->event, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_destroy_marker()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_evt_destroy_marker(struct msg_itf_evt_destroy_marker *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hWrapper, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_destroy_marker(struct msg_itf_evt_destroy_marker *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hWrapper, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_destroy_marker_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_evt_destroy_marker();

	return res;
}
static void marshall_struct_msg_itf_evt_destroy_marker_full(struct msg_itf_evt_destroy_marker_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_evt_destroy_marker(&in->event, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_destroy_marker_full(struct msg_itf_evt_destroy_marker_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_evt_destroy_marker(&in->event, read_cb, arg);
}
static int get_size_AL_ECodec()
{
	return sizeof(AL_ECodec);
}
static void marshall_AL_ECodec(AL_ECodec *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_ECodec(AL_ECodec *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EFbStorageMode()
{
	return sizeof(AL_EFbStorageMode);
}
static void marshall_AL_EFbStorageMode(AL_EFbStorageMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EFbStorageMode(AL_EFbStorageMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EDecUnit()
{
	return sizeof(AL_EDecUnit);
}
static void marshall_AL_EDecUnit(AL_EDecUnit *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EDecUnit(AL_EDecUnit *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EDpbMode()
{
	return sizeof(AL_EDpbMode);
}
static void marshall_AL_EDpbMode(AL_EDpbMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EDpbMode(AL_EDpbMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_TDimension()
{
	return get_size_struct_AL_TDimension();
}
static void marshall_AL_TDimension(AL_TDimension *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TDimension((struct AL_TDimension *) in, write_cb, arg);
}
static void unmarshall_AL_TDimension(AL_TDimension *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TDimension((struct AL_TDimension *) in, read_cb, arg);
}
static int get_size_AL_EChromaMode()
{
	return sizeof(AL_EChromaMode);
}
static void marshall_AL_EChromaMode(AL_EChromaMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EChromaMode(AL_EChromaMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EProfile()
{
	return sizeof(AL_EProfile);
}
static void marshall_AL_EProfile(AL_EProfile *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EProfile(AL_EProfile *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_ESequenceMode()
{
	return sizeof(AL_ESequenceMode);
}
static void marshall_AL_ESequenceMode(AL_ESequenceMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_ESequenceMode(AL_ESequenceMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_TStreamSettings()
{
	return get_size_struct_AL_TStreamSettings();
}
static void marshall_AL_TStreamSettings(AL_TStreamSettings *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TStreamSettings((struct AL_TStreamSettings *) in, write_cb, arg);
}
static void unmarshall_AL_TStreamSettings(AL_TStreamSettings *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TStreamSettings((struct AL_TStreamSettings *) in, read_cb, arg);
}
static int get_size_AL_TPosition()
{
	return get_size_struct_AL_TPosition();
}
static void marshall_AL_TPosition(AL_TPosition *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TPosition((struct AL_TPosition *) in, write_cb, arg);
}
static void unmarshall_AL_TPosition(AL_TPosition *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TPosition((struct AL_TPosition *) in, read_cb, arg);
}
static int get_size_AL_EDecInputMode()
{
	return sizeof(AL_EDecInputMode);
}
static void marshall_AL_EDecInputMode(AL_EDecInputMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EDecInputMode(AL_EDecInputMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_TDecSettings()
{
	return get_size_struct_AL_TDecSettings();
}
static void marshall_AL_TDecSettings(AL_TDecSettings *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TDecSettings((struct AL_TDecSettings *) in, write_cb, arg);
}
static void unmarshall_AL_TDecSettings(AL_TDecSettings *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TDecSettings((struct AL_TDecSettings *) in, read_cb, arg);
}
static int get_size_AL_TPlane()
{
	return get_size_struct_AL_TPlane();
}
static void marshall_AL_TPlane(AL_TPlane *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TPlane((struct AL_TPlane *) in, write_cb, arg);
}
static void unmarshall_AL_TPlane(AL_TPlane *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TPlane((struct AL_TPlane *) in, read_cb, arg);
}
static int get_size_AL_TWindow()
{
	return get_size_struct_AL_TWindow();
}
static void marshall_AL_TWindow(AL_TWindow *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TWindow((struct AL_TWindow *) in, write_cb, arg);
}
static void unmarshall_AL_TWindow(AL_TWindow *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TWindow((struct AL_TWindow *) in, read_cb, arg);
}
static int get_size_AL_EAlphaMode()
{
	return sizeof(AL_EAlphaMode);
}
static void marshall_AL_EAlphaMode(AL_EAlphaMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EAlphaMode(AL_EAlphaMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EPlaneMode()
{
	return sizeof(AL_EPlaneMode);
}
static void marshall_AL_EPlaneMode(AL_EPlaneMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EPlaneMode(AL_EPlaneMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EComponentOrder()
{
	return sizeof(AL_EComponentOrder);
}
static void marshall_AL_EComponentOrder(AL_EComponentOrder *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EComponentOrder(AL_EComponentOrder *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_ESamplePackMode()
{
	return sizeof(AL_ESamplePackMode);
}
static void marshall_AL_ESamplePackMode(AL_ESamplePackMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_ESamplePackMode(AL_ESamplePackMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_TPicFormat()
{
	return get_size_struct_AL_TPicFormat();
}
static void marshall_AL_TPicFormat(AL_TPicFormat *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TPicFormat((struct AL_TPicFormat *) in, write_cb, arg);
}
static void unmarshall_AL_TPicFormat(AL_TPicFormat *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TPicFormat((struct AL_TPicFormat *) in, read_cb, arg);
}
static int get_size_AL_TCropInfo()
{
	return get_size_struct_t_CropInfo();
}
static void marshall_AL_TCropInfo(AL_TCropInfo *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_t_CropInfo((struct t_CropInfo *) in, write_cb, arg);
}
static void unmarshall_AL_TCropInfo(AL_TCropInfo *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_t_CropInfo((struct t_CropInfo *) in, read_cb, arg);
}
static int get_size_AL_EPicStruct()
{
	return sizeof(AL_EPicStruct);
}
static void marshall_AL_EPicStruct(AL_EPicStruct *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EPicStruct(AL_EPicStruct *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EOutputType()
{
	return sizeof(AL_EOutputType);
}
static void marshall_AL_EOutputType(AL_EOutputType *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EOutputType(AL_EOutputType *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_TInfoDecode()
{
	return get_size_struct_t_InfoDecode();
}
static void marshall_AL_TInfoDecode(AL_TInfoDecode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_t_InfoDecode((struct t_InfoDecode *) in, write_cb, arg);
}
static void unmarshall_AL_TInfoDecode(AL_TInfoDecode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_t_InfoDecode((struct t_InfoDecode *) in, read_cb, arg);
}
static int get_size_AL_EColourDescription()
{
	return sizeof(AL_EColourDescription);
}
static void marshall_AL_EColourDescription(AL_EColourDescription *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EColourDescription(AL_EColourDescription *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_ETransferCharacteristics()
{
	return sizeof(AL_ETransferCharacteristics);
}
static void marshall_AL_ETransferCharacteristics(AL_ETransferCharacteristics *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_ETransferCharacteristics(AL_ETransferCharacteristics *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EColourMatrixCoefficients()
{
	return sizeof(AL_EColourMatrixCoefficients);
}
static void marshall_AL_EColourMatrixCoefficients(AL_EColourMatrixCoefficients *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EColourMatrixCoefficients(AL_EColourMatrixCoefficients *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_TChromaCoordinates()
{
	return get_size_struct_AL_TChromaCoordinates();
}
static void marshall_AL_TChromaCoordinates(AL_TChromaCoordinates *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TChromaCoordinates((struct AL_TChromaCoordinates *) in, write_cb, arg);
}
static void unmarshall_AL_TChromaCoordinates(AL_TChromaCoordinates *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TChromaCoordinates((struct AL_TChromaCoordinates *) in, read_cb, arg);
}
static int get_size_AL_TMasteringDisplayColourVolume()
{
	return get_size_struct_AL_TMasteringDisplayColourVolume();
}
static void marshall_AL_TMasteringDisplayColourVolume(AL_TMasteringDisplayColourVolume *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TMasteringDisplayColourVolume((struct AL_TMasteringDisplayColourVolume *) in, write_cb, arg);
}
static void unmarshall_AL_TMasteringDisplayColourVolume(AL_TMasteringDisplayColourVolume *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TMasteringDisplayColourVolume((struct AL_TMasteringDisplayColourVolume *) in, read_cb, arg);
}
static int get_size_AL_TContentLightLevel()
{
	return get_size_struct_AL_TContentLightLevel();
}
static void marshall_AL_TContentLightLevel(AL_TContentLightLevel *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TContentLightLevel((struct AL_TContentLightLevel *) in, write_cb, arg);
}
static void unmarshall_AL_TContentLightLevel(AL_TContentLightLevel *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TContentLightLevel((struct AL_TContentLightLevel *) in, read_cb, arg);
}
static int get_size_AL_TAlternativeTransferCharacteristics()
{
	return get_size_struct_AL_TAlternativeTransferCharacteristics();
}
static void marshall_AL_TAlternativeTransferCharacteristics(AL_TAlternativeTransferCharacteristics *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TAlternativeTransferCharacteristics((struct AL_TAlternativeTransferCharacteristics *) in, write_cb, arg);
}
static void unmarshall_AL_TAlternativeTransferCharacteristics(AL_TAlternativeTransferCharacteristics *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TAlternativeTransferCharacteristics((struct AL_TAlternativeTransferCharacteristics *) in, read_cb, arg);
}
static int get_size_AL_TProcessingWindow_ST2094_10()
{
	return get_size_struct_AL_TProcessingWindow_ST2094_10();
}
static void marshall_AL_TProcessingWindow_ST2094_10(AL_TProcessingWindow_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TProcessingWindow_ST2094_10((struct AL_TProcessingWindow_ST2094_10 *) in, write_cb, arg);
}
static void unmarshall_AL_TProcessingWindow_ST2094_10(AL_TProcessingWindow_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TProcessingWindow_ST2094_10((struct AL_TProcessingWindow_ST2094_10 *) in, read_cb, arg);
}
static int get_size_AL_TImageCharacteristics_ST2094_10()
{
	return get_size_struct_AL_TTImageCharacteristics_ST2094_10();
}
static void marshall_AL_TImageCharacteristics_ST2094_10(AL_TImageCharacteristics_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TTImageCharacteristics_ST2094_10((struct AL_TTImageCharacteristics_ST2094_10 *) in, write_cb, arg);
}
static void unmarshall_AL_TImageCharacteristics_ST2094_10(AL_TImageCharacteristics_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TTImageCharacteristics_ST2094_10((struct AL_TTImageCharacteristics_ST2094_10 *) in, read_cb, arg);
}
static int get_size_AL_TManualAdjustment_ST2094_10()
{
	return get_size_struct_AL_TManualAdjustment_ST2094_10();
}
static void marshall_AL_TManualAdjustment_ST2094_10(AL_TManualAdjustment_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TManualAdjustment_ST2094_10((struct AL_TManualAdjustment_ST2094_10 *) in, write_cb, arg);
}
static void unmarshall_AL_TManualAdjustment_ST2094_10(AL_TManualAdjustment_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TManualAdjustment_ST2094_10((struct AL_TManualAdjustment_ST2094_10 *) in, read_cb, arg);
}
static int get_size_AL_TDynamicMeta_ST2094_10()
{
	return get_size_struct_AL_TDynamicMeta_ST2094_10();
}
static void marshall_AL_TDynamicMeta_ST2094_10(AL_TDynamicMeta_ST2094_10 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TDynamicMeta_ST2094_10((struct AL_TDynamicMeta_ST2094_10 *) in, write_cb, arg);
}
static void unmarshall_AL_TDynamicMeta_ST2094_10(AL_TDynamicMeta_ST2094_10 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TDynamicMeta_ST2094_10((struct AL_TDynamicMeta_ST2094_10 *) in, read_cb, arg);
}
static int get_size_AL_TProcessingWindow_ST2094_1()
{
	return get_size_struct_AL_TProcessingWindow_ST2094_1();
}
static void marshall_AL_TProcessingWindow_ST2094_1(AL_TProcessingWindow_ST2094_1 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TProcessingWindow_ST2094_1((struct AL_TProcessingWindow_ST2094_1 *) in, write_cb, arg);
}
static void unmarshall_AL_TProcessingWindow_ST2094_1(AL_TProcessingWindow_ST2094_1 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TProcessingWindow_ST2094_1((struct AL_TProcessingWindow_ST2094_1 *) in, read_cb, arg);
}
static int get_size_AL_TProcessingWindow_ST2094_40()
{
	return get_size_struct_AL_TProcessingWindow_ST2094_40();
}
static void marshall_AL_TProcessingWindow_ST2094_40(AL_TProcessingWindow_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TProcessingWindow_ST2094_40((struct AL_TProcessingWindow_ST2094_40 *) in, write_cb, arg);
}
static void unmarshall_AL_TProcessingWindow_ST2094_40(AL_TProcessingWindow_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TProcessingWindow_ST2094_40((struct AL_TProcessingWindow_ST2094_40 *) in, read_cb, arg);
}
static int get_size_AL_TDisplayPeakLuminance_ST2094_40()
{
	return get_size_struct_AL_TDisplayPeakLuminance_ST2094_40();
}
static void marshall_AL_TDisplayPeakLuminance_ST2094_40(AL_TDisplayPeakLuminance_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TDisplayPeakLuminance_ST2094_40((struct AL_TDisplayPeakLuminance_ST2094_40 *) in, write_cb, arg);
}
static void unmarshall_AL_TDisplayPeakLuminance_ST2094_40(AL_TDisplayPeakLuminance_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TDisplayPeakLuminance_ST2094_40((struct AL_TDisplayPeakLuminance_ST2094_40 *) in, read_cb, arg);
}
static int get_size_AL_TTargetedSystemDisplay_ST2094_40()
{
	return get_size_struct_AL_TTargetedSystemDisplay_ST2094_40();
}
static void marshall_AL_TTargetedSystemDisplay_ST2094_40(AL_TTargetedSystemDisplay_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TTargetedSystemDisplay_ST2094_40((struct AL_TTargetedSystemDisplay_ST2094_40 *) in, write_cb, arg);
}
static void unmarshall_AL_TTargetedSystemDisplay_ST2094_40(AL_TTargetedSystemDisplay_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TTargetedSystemDisplay_ST2094_40((struct AL_TTargetedSystemDisplay_ST2094_40 *) in, read_cb, arg);
}
static int get_size_AL_TToneMapping_ST2094_40()
{
	return get_size_struct_AL_TToneMapping_ST2094_40();
}
static void marshall_AL_TToneMapping_ST2094_40(AL_TToneMapping_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TToneMapping_ST2094_40((struct AL_TToneMapping_ST2094_40 *) in, write_cb, arg);
}
static void unmarshall_AL_TToneMapping_ST2094_40(AL_TToneMapping_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TToneMapping_ST2094_40((struct AL_TToneMapping_ST2094_40 *) in, read_cb, arg);
}
static int get_size_AL_TProcessingWindowTransform_ST2094_40()
{
	return get_size_struct_AL_TProcessingWindowTransform_ST2094_40();
}
static void marshall_AL_TProcessingWindowTransform_ST2094_40(AL_TProcessingWindowTransform_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TProcessingWindowTransform_ST2094_40((struct AL_TProcessingWindowTransform_ST2094_40 *) in, write_cb, arg);
}
static void unmarshall_AL_TProcessingWindowTransform_ST2094_40(AL_TProcessingWindowTransform_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TProcessingWindowTransform_ST2094_40((struct AL_TProcessingWindowTransform_ST2094_40 *) in, read_cb, arg);
}
static int get_size_AL_TDynamicMeta_ST2094_40()
{
	return get_size_struct_AL_TDynamicMeta_ST2094_40();
}
static void marshall_AL_TDynamicMeta_ST2094_40(AL_TDynamicMeta_ST2094_40 *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TDynamicMeta_ST2094_40((struct AL_TDynamicMeta_ST2094_40 *) in, write_cb, arg);
}
static void unmarshall_AL_TDynamicMeta_ST2094_40(AL_TDynamicMeta_ST2094_40 *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TDynamicMeta_ST2094_40((struct AL_TDynamicMeta_ST2094_40 *) in, read_cb, arg);
}
static int get_size_AL_THDRSEIs()
{
	return get_size_struct_AL_THDRSEIs();
}
static void marshall_AL_THDRSEIs(AL_THDRSEIs *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_THDRSEIs((struct AL_THDRSEIs *) in, write_cb, arg);
}
static void unmarshall_AL_THDRSEIs(AL_THDRSEIs *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_THDRSEIs((struct AL_THDRSEIs *) in, read_cb, arg);
}

int msg_itf_header_get_size(void)
{
	return get_size_struct_msg_itf_header();
}

void msg_itf_header_marshall(struct msg_itf_header *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(in, write_cb, arg);
}

void msg_itf_header_unmarshall(struct msg_itf_header *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(out, read_cb, arg);
}

int msg_itf_get_cma_req_get_size(void)
{
	return get_size_struct_msg_itf_get_cma_req();
}

void msg_itf_get_cma_req_marshall(struct msg_itf_get_cma_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_cma_req(in, write_cb, arg);
}

void msg_itf_get_cma_req_unmarshall(struct msg_itf_get_cma_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_cma_req(out, read_cb, arg);
}

int msg_itf_get_cma_req_full_get_size(void)
{
	return get_size_struct_msg_itf_get_cma_req_full();
}

void msg_itf_get_cma_req_full_marshall(struct msg_itf_get_cma_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_cma_req_full(in, write_cb, arg);
}

void msg_itf_get_cma_req_full_unmarshall(struct msg_itf_get_cma_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_cma_req_full(out, read_cb, arg);
}

int msg_itf_get_cma_reply_get_size(void)
{
	return get_size_struct_msg_itf_get_cma_reply();
}

void msg_itf_get_cma_reply_marshall(struct msg_itf_get_cma_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_cma_reply(in, write_cb, arg);
}

void msg_itf_get_cma_reply_unmarshall(struct msg_itf_get_cma_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_cma_reply(out, read_cb, arg);
}

int msg_itf_get_cma_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_get_cma_reply_full();
}

void msg_itf_get_cma_reply_full_marshall(struct msg_itf_get_cma_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_cma_reply_full(in, write_cb, arg);
}

void msg_itf_get_cma_reply_full_unmarshall(struct msg_itf_get_cma_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_cma_reply_full(out, read_cb, arg);
}

int msg_itf_put_cma_req_get_size(void)
{
	return get_size_struct_msg_itf_put_cma_req();
}

void msg_itf_put_cma_req_marshall(struct msg_itf_put_cma_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_put_cma_req(in, write_cb, arg);
}

void msg_itf_put_cma_req_unmarshall(struct msg_itf_put_cma_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_put_cma_req(out, read_cb, arg);
}

int msg_itf_put_cma_req_full_get_size(void)
{
	return get_size_struct_msg_itf_put_cma_req_full();
}

void msg_itf_put_cma_req_full_marshall(struct msg_itf_put_cma_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_put_cma_req_full(in, write_cb, arg);
}

void msg_itf_put_cma_req_full_unmarshall(struct msg_itf_put_cma_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_put_cma_req_full(out, read_cb, arg);
}

int msg_itf_put_cma_reply_get_size(void)
{
	return get_size_struct_msg_itf_put_cma_reply();
}

void msg_itf_put_cma_reply_marshall(struct msg_itf_put_cma_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_put_cma_reply(in, write_cb, arg);
}

void msg_itf_put_cma_reply_unmarshall(struct msg_itf_put_cma_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_put_cma_reply(out, read_cb, arg);
}

int msg_itf_put_cma_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_put_cma_reply_full();
}

void msg_itf_put_cma_reply_full_marshall(struct msg_itf_put_cma_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_put_cma_reply_full(in, write_cb, arg);
}

void msg_itf_put_cma_reply_full_unmarshall(struct msg_itf_put_cma_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_put_cma_reply_full(out, read_cb, arg);
}

int msg_itf_perf_info_req_get_size(void)
{
	return get_size_struct_msg_itf_perf_info_req();
}

void msg_itf_perf_info_req_marshall(struct msg_itf_perf_info_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_perf_info_req(in, write_cb, arg);
}

void msg_itf_perf_info_req_unmarshall(struct msg_itf_perf_info_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_perf_info_req(out, read_cb, arg);
}

int msg_itf_perf_info_req_full_get_size(void)
{
	return get_size_struct_msg_itf_perf_info_req_full();
}

void msg_itf_perf_info_req_full_marshall(struct msg_itf_perf_info_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_perf_info_req_full(in, write_cb, arg);
}

void msg_itf_perf_info_req_full_unmarshall(struct msg_itf_perf_info_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_perf_info_req_full(out, read_cb, arg);
}

int msg_itf_perf_info_reply_get_size(void)
{
	return get_size_struct_msg_itf_perf_info_reply();
}

void msg_itf_perf_info_reply_marshall(struct msg_itf_perf_info_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_perf_info_reply(in, write_cb, arg);
}

void msg_itf_perf_info_reply_unmarshall(struct msg_itf_perf_info_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_perf_info_reply(out, read_cb, arg);
}

int msg_itf_perf_info_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_perf_info_reply_full();
}

void msg_itf_perf_info_reply_full_marshall(struct msg_itf_perf_info_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_perf_info_reply_full(in, write_cb, arg);
}

void msg_itf_perf_info_reply_full_unmarshall(struct msg_itf_perf_info_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_perf_info_reply_full(out, read_cb, arg);
}

int msg_itf_write_req_get_size(void)
{
	return get_size_struct_msg_itf_write_req();
}

void msg_itf_write_req_marshall(struct msg_itf_write_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_write_req(in, write_cb, arg);
}

void msg_itf_write_req_unmarshall(struct msg_itf_write_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_write_req(out, read_cb, arg);
}

int msg_itf_write_req_full_get_size(void)
{
	return get_size_struct_msg_itf_write_req_full();
}

void msg_itf_write_req_full_marshall(struct msg_itf_write_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_write_req_full(in, write_cb, arg);
}

void msg_itf_write_req_full_unmarshall(struct msg_itf_write_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_write_req_full(out, read_cb, arg);
}

int chunk_info_get_size(void)
{
	return get_size_struct_chunk_info();
}

void chunk_info_marshall(struct chunk_info *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_chunk_info(in, write_cb, arg);
}

void chunk_info_unmarshall(struct chunk_info *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_chunk_info(out, read_cb, arg);
}

int msg_itf_create_decoder_req_get_size(void)
{
	return get_size_struct_msg_itf_create_decoder_req();
}

void msg_itf_create_decoder_req_marshall(struct msg_itf_create_decoder_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_create_decoder_req(in, write_cb, arg);
}

void msg_itf_create_decoder_req_unmarshall(struct msg_itf_create_decoder_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_create_decoder_req(out, read_cb, arg);
}

int msg_itf_create_decoder_req_full_get_size(void)
{
	return get_size_struct_msg_itf_create_decoder_req_full();
}

void msg_itf_create_decoder_req_full_marshall(struct msg_itf_create_decoder_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_create_decoder_req_full(in, write_cb, arg);
}

void msg_itf_create_decoder_req_full_unmarshall(struct msg_itf_create_decoder_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_create_decoder_req_full(out, read_cb, arg);
}

int msg_itf_create_decoder_reply_get_size(void)
{
	return get_size_struct_msg_itf_create_decoder_reply();
}

void msg_itf_create_decoder_reply_marshall(struct msg_itf_create_decoder_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_create_decoder_reply(in, write_cb, arg);
}

void msg_itf_create_decoder_reply_unmarshall(struct msg_itf_create_decoder_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_create_decoder_reply(out, read_cb, arg);
}

int msg_itf_create_decoder_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_create_decoder_reply_full();
}

void msg_itf_create_decoder_reply_full_marshall(struct msg_itf_create_decoder_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_create_decoder_reply_full(in, write_cb, arg);
}

void msg_itf_create_decoder_reply_full_unmarshall(struct msg_itf_create_decoder_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_create_decoder_reply_full(out, read_cb, arg);
}

int msg_itf_destroy_decoder_req_get_size(void)
{
	return get_size_struct_msg_itf_destroy_decoder_req();
}

void msg_itf_destroy_decoder_req_marshall(struct msg_itf_destroy_decoder_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_destroy_decoder_req(in, write_cb, arg);
}

void msg_itf_destroy_decoder_req_unmarshall(struct msg_itf_destroy_decoder_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_destroy_decoder_req(out, read_cb, arg);
}

int msg_itf_destroy_decoder_req_full_get_size(void)
{
	return get_size_struct_msg_itf_destroy_decoder_req_full();
}

void msg_itf_destroy_decoder_req_full_marshall(struct msg_itf_destroy_decoder_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_destroy_decoder_req_full(in, write_cb, arg);
}

void msg_itf_destroy_decoder_req_full_unmarshall(struct msg_itf_destroy_decoder_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_destroy_decoder_req_full(out, read_cb, arg);
}

int msg_itf_destroy_decoder_reply_get_size(void)
{
	return get_size_struct_msg_itf_destroy_decoder_reply();
}

void msg_itf_destroy_decoder_reply_marshall(struct msg_itf_destroy_decoder_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_destroy_decoder_reply(in, write_cb, arg);
}

void msg_itf_destroy_decoder_reply_unmarshall(struct msg_itf_destroy_decoder_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_destroy_decoder_reply(out, read_cb, arg);
}

int msg_itf_destroy_decoder_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_destroy_decoder_reply_full();
}

void msg_itf_destroy_decoder_reply_full_marshall(struct msg_itf_destroy_decoder_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_destroy_decoder_reply_full(in, write_cb, arg);
}

void msg_itf_destroy_decoder_reply_full_unmarshall(struct msg_itf_destroy_decoder_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_destroy_decoder_reply_full(out, read_cb, arg);
}

int msg_itf_push_bitstream_buffer_req_get_size(void)
{
	return get_size_struct_msg_itf_push_bitstream_buffer_req();
}

void msg_itf_push_bitstream_buffer_req_marshall(struct msg_itf_push_bitstream_buffer_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_push_bitstream_buffer_req(in, write_cb, arg);
}

void msg_itf_push_bitstream_buffer_req_unmarshall(struct msg_itf_push_bitstream_buffer_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_push_bitstream_buffer_req(out, read_cb, arg);
}

int msg_itf_push_bitstream_buffer_req_full_get_size(void)
{
	return get_size_struct_msg_itf_push_bitstream_buffer_req_full();
}

void msg_itf_push_bitstream_buffer_req_full_marshall(struct msg_itf_push_bitstream_buffer_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_push_bitstream_buffer_req_full(in, write_cb, arg);
}

void msg_itf_push_bitstream_buffer_req_full_unmarshall(struct msg_itf_push_bitstream_buffer_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_push_bitstream_buffer_req_full(out, read_cb, arg);
}

int msg_itf_push_bitstream_buffer_reply_get_size(void)
{
	return get_size_struct_msg_itf_push_bitstream_buffer_reply();
}

void msg_itf_push_bitstream_buffer_reply_marshall(struct msg_itf_push_bitstream_buffer_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_push_bitstream_buffer_reply(in, write_cb, arg);
}

void msg_itf_push_bitstream_buffer_reply_unmarshall(struct msg_itf_push_bitstream_buffer_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_push_bitstream_buffer_reply(out, read_cb, arg);
}

int msg_itf_push_bitstream_buffer_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_push_bitstream_buffer_reply_full();
}

void msg_itf_push_bitstream_buffer_reply_full_marshall(struct msg_itf_push_bitstream_buffer_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_push_bitstream_buffer_reply_full(in, write_cb, arg);
}

void msg_itf_push_bitstream_buffer_reply_full_unmarshall(struct msg_itf_push_bitstream_buffer_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_push_bitstream_buffer_reply_full(out, read_cb, arg);
}

int msg_itf_flush_req_get_size(void)
{
	return get_size_struct_msg_itf_flush_req();
}

void msg_itf_flush_req_marshall(struct msg_itf_flush_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_flush_req(in, write_cb, arg);
}

void msg_itf_flush_req_unmarshall(struct msg_itf_flush_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_flush_req(out, read_cb, arg);
}

int msg_itf_flush_req_full_get_size(void)
{
	return get_size_struct_msg_itf_flush_req_full();
}

void msg_itf_flush_req_full_marshall(struct msg_itf_flush_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_flush_req_full(in, write_cb, arg);
}

void msg_itf_flush_req_full_unmarshall(struct msg_itf_flush_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_flush_req_full(out, read_cb, arg);
}

int msg_itf_flush_reply_get_size(void)
{
	return get_size_struct_msg_itf_flush_reply();
}

void msg_itf_flush_reply_marshall(struct msg_itf_flush_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_flush_reply(in, write_cb, arg);
}

void msg_itf_flush_reply_unmarshall(struct msg_itf_flush_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_flush_reply(out, read_cb, arg);
}

int msg_itf_flush_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_flush_reply_full();
}

void msg_itf_flush_reply_full_marshall(struct msg_itf_flush_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_flush_reply_full(in, write_cb, arg);
}

void msg_itf_flush_reply_full_unmarshall(struct msg_itf_flush_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_flush_reply_full(out, read_cb, arg);
}

int msg_itf_get_maxdepth_req_get_size(void)
{
	return get_size_struct_msg_itf_get_maxdepth_req();
}

void msg_itf_get_maxdepth_req_marshall(struct msg_itf_get_maxdepth_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_maxdepth_req(in, write_cb, arg);
}

void msg_itf_get_maxdepth_req_unmarshall(struct msg_itf_get_maxdepth_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_maxdepth_req(out, read_cb, arg);
}

int msg_itf_get_maxdepth_req_full_get_size(void)
{
	return get_size_struct_msg_itf_get_maxdepth_req_full();
}

void msg_itf_get_maxdepth_req_full_marshall(struct msg_itf_get_maxdepth_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_maxdepth_req_full(in, write_cb, arg);
}

void msg_itf_get_maxdepth_req_full_unmarshall(struct msg_itf_get_maxdepth_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_maxdepth_req_full(out, read_cb, arg);
}

int msg_itf_get_maxdepth_reply_get_size(void)
{
	return get_size_struct_msg_itf_get_maxdepth_reply();
}

void msg_itf_get_maxdepth_reply_marshall(struct msg_itf_get_maxdepth_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_maxdepth_reply(in, write_cb, arg);
}

void msg_itf_get_maxdepth_reply_unmarshall(struct msg_itf_get_maxdepth_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_maxdepth_reply(out, read_cb, arg);
}

int msg_itf_get_maxdepth_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_get_maxdepth_reply_full();
}

void msg_itf_get_maxdepth_reply_full_marshall(struct msg_itf_get_maxdepth_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_maxdepth_reply_full(in, write_cb, arg);
}

void msg_itf_get_maxdepth_reply_full_unmarshall(struct msg_itf_get_maxdepth_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_maxdepth_reply_full(out, read_cb, arg);
}

int msg_itf_get_codec_req_get_size(void)
{
	return get_size_struct_msg_itf_get_codec_req();
}

void msg_itf_get_codec_req_marshall(struct msg_itf_get_codec_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_codec_req(in, write_cb, arg);
}

void msg_itf_get_codec_req_unmarshall(struct msg_itf_get_codec_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_codec_req(out, read_cb, arg);
}

int msg_itf_get_codec_req_full_get_size(void)
{
	return get_size_struct_msg_itf_get_codec_req_full();
}

void msg_itf_get_codec_req_full_marshall(struct msg_itf_get_codec_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_codec_req_full(in, write_cb, arg);
}

void msg_itf_get_codec_req_full_unmarshall(struct msg_itf_get_codec_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_codec_req_full(out, read_cb, arg);
}

int msg_itf_get_codec_reply_get_size(void)
{
	return get_size_struct_msg_itf_get_codec_reply();
}

void msg_itf_get_codec_reply_marshall(struct msg_itf_get_codec_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_codec_reply(in, write_cb, arg);
}

void msg_itf_get_codec_reply_unmarshall(struct msg_itf_get_codec_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_codec_reply(out, read_cb, arg);
}

int msg_itf_get_codec_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_get_codec_reply_full();
}

void msg_itf_get_codec_reply_full_marshall(struct msg_itf_get_codec_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_codec_reply_full(in, write_cb, arg);
}

void msg_itf_get_codec_reply_full_unmarshall(struct msg_itf_get_codec_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_codec_reply_full(out, read_cb, arg);
}

int msg_itf_get_last_error_req_get_size(void)
{
	return get_size_struct_msg_itf_get_last_error_req();
}

void msg_itf_get_last_error_req_marshall(struct msg_itf_get_last_error_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_last_error_req(in, write_cb, arg);
}

void msg_itf_get_last_error_req_unmarshall(struct msg_itf_get_last_error_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_last_error_req(out, read_cb, arg);
}

int msg_itf_get_last_error_req_full_get_size(void)
{
	return get_size_struct_msg_itf_get_last_error_req_full();
}

void msg_itf_get_last_error_req_full_marshall(struct msg_itf_get_last_error_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_last_error_req_full(in, write_cb, arg);
}

void msg_itf_get_last_error_req_full_unmarshall(struct msg_itf_get_last_error_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_last_error_req_full(out, read_cb, arg);
}

int msg_itf_get_last_error_reply_get_size(void)
{
	return get_size_struct_msg_itf_get_last_error_reply();
}

void msg_itf_get_last_error_reply_marshall(struct msg_itf_get_last_error_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_last_error_reply(in, write_cb, arg);
}

void msg_itf_get_last_error_reply_unmarshall(struct msg_itf_get_last_error_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_last_error_reply(out, read_cb, arg);
}

int msg_itf_get_last_error_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_get_last_error_reply_full();
}

void msg_itf_get_last_error_reply_full_marshall(struct msg_itf_get_last_error_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_last_error_reply_full(in, write_cb, arg);
}

void msg_itf_get_last_error_reply_full_unmarshall(struct msg_itf_get_last_error_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_last_error_reply_full(out, read_cb, arg);
}

int msg_itf_preallocate_buffers_req_get_size(void)
{
	return get_size_struct_msg_itf_preallocate_buffers_req();
}

void msg_itf_preallocate_buffers_req_marshall(struct msg_itf_preallocate_buffers_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_preallocate_buffers_req(in, write_cb, arg);
}

void msg_itf_preallocate_buffers_req_unmarshall(struct msg_itf_preallocate_buffers_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_preallocate_buffers_req(out, read_cb, arg);
}

int msg_itf_preallocate_buffers_req_full_get_size(void)
{
	return get_size_struct_msg_itf_preallocate_buffers_req_full();
}

void msg_itf_preallocate_buffers_req_full_marshall(struct msg_itf_preallocate_buffers_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_preallocate_buffers_req_full(in, write_cb, arg);
}

void msg_itf_preallocate_buffers_req_full_unmarshall(struct msg_itf_preallocate_buffers_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_preallocate_buffers_req_full(out, read_cb, arg);
}

int msg_itf_preallocate_buffers_reply_get_size(void)
{
	return get_size_struct_msg_itf_preallocate_buffers_reply();
}

void msg_itf_preallocate_buffers_reply_marshall(struct msg_itf_preallocate_buffers_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_preallocate_buffers_reply(in, write_cb, arg);
}

void msg_itf_preallocate_buffers_reply_unmarshall(struct msg_itf_preallocate_buffers_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_preallocate_buffers_reply(out, read_cb, arg);
}

int msg_itf_preallocate_buffers_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_preallocate_buffers_reply_full();
}

void msg_itf_preallocate_buffers_reply_full_marshall(struct msg_itf_preallocate_buffers_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_preallocate_buffers_reply_full(in, write_cb, arg);
}

void msg_itf_preallocate_buffers_reply_full_unmarshall(struct msg_itf_preallocate_buffers_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_preallocate_buffers_reply_full(out, read_cb, arg);
}

int msg_itf_setparam_req_get_size(void)
{
	return get_size_struct_msg_itf_setparam_req();
}

void msg_itf_setparam_req_marshall(struct msg_itf_setparam_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_setparam_req(in, write_cb, arg);
}

void msg_itf_setparam_req_unmarshall(struct msg_itf_setparam_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_setparam_req(out, read_cb, arg);
}

int msg_itf_setparam_req_full_get_size(void)
{
	return get_size_struct_msg_itf_setparam_req_full();
}

void msg_itf_setparam_req_full_marshall(struct msg_itf_setparam_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_setparam_req_full(in, write_cb, arg);
}

void msg_itf_setparam_req_full_unmarshall(struct msg_itf_setparam_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_setparam_req_full(out, read_cb, arg);
}

int msg_itf_setparam_reply_get_size(void)
{
	return get_size_struct_msg_itf_setparam_reply();
}

void msg_itf_setparam_reply_marshall(struct msg_itf_setparam_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_setparam_reply(in, write_cb, arg);
}

void msg_itf_setparam_reply_unmarshall(struct msg_itf_setparam_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_setparam_reply(out, read_cb, arg);
}

int msg_itf_setparam_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_setparam_reply_full();
}

void msg_itf_setparam_reply_full_marshall(struct msg_itf_setparam_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_setparam_reply_full(in, write_cb, arg);
}

void msg_itf_setparam_reply_full_unmarshall(struct msg_itf_setparam_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_setparam_reply_full(out, read_cb, arg);
}

int msg_itf_put_display_picture_req_get_size(void)
{
	return get_size_struct_msg_itf_put_display_picture_req();
}

void msg_itf_put_display_picture_req_marshall(struct msg_itf_put_display_picture_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_put_display_picture_req(in, write_cb, arg);
}

void msg_itf_put_display_picture_req_unmarshall(struct msg_itf_put_display_picture_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_put_display_picture_req(out, read_cb, arg);
}

int msg_itf_put_display_picture_req_full_get_size(void)
{
	return get_size_struct_msg_itf_put_display_picture_req_full();
}

void msg_itf_put_display_picture_req_full_marshall(struct msg_itf_put_display_picture_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_put_display_picture_req_full(in, write_cb, arg);
}

void msg_itf_put_display_picture_req_full_unmarshall(struct msg_itf_put_display_picture_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_put_display_picture_req_full(out, read_cb, arg);
}

int msg_itf_put_display_picture_reply_get_size(void)
{
	return get_size_struct_msg_itf_put_display_picture_reply();
}

void msg_itf_put_display_picture_reply_marshall(struct msg_itf_put_display_picture_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_put_display_picture_reply(in, write_cb, arg);
}

void msg_itf_put_display_picture_reply_unmarshall(struct msg_itf_put_display_picture_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_put_display_picture_reply(out, read_cb, arg);
}

int msg_itf_put_display_picture_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_put_display_picture_reply_full();
}

void msg_itf_put_display_picture_reply_full_marshall(struct msg_itf_put_display_picture_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_put_display_picture_reply_full(in, write_cb, arg);
}

void msg_itf_put_display_picture_reply_full_unmarshall(struct msg_itf_put_display_picture_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_put_display_picture_reply_full(out, read_cb, arg);
}

int msg_itf_configure_output_settings_req_get_size(void)
{
	return get_size_struct_msg_itf_configure_output_settings_req();
}

void msg_itf_configure_output_settings_req_marshall(struct msg_itf_configure_output_settings_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_configure_output_settings_req(in, write_cb, arg);
}

void msg_itf_configure_output_settings_req_unmarshall(struct msg_itf_configure_output_settings_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_configure_output_settings_req(out, read_cb, arg);
}

int msg_itf_configure_output_settings_req_full_get_size(void)
{
	return get_size_struct_msg_itf_configure_output_settings_req_full();
}

void msg_itf_configure_output_settings_req_full_marshall(struct msg_itf_configure_output_settings_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_configure_output_settings_req_full(in, write_cb, arg);
}

void msg_itf_configure_output_settings_req_full_unmarshall(struct msg_itf_configure_output_settings_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_configure_output_settings_req_full(out, read_cb, arg);
}

int msg_itf_configure_output_settings_reply_get_size(void)
{
	return get_size_struct_msg_itf_configure_output_settings_reply();
}

void msg_itf_configure_output_settings_reply_marshall(struct msg_itf_configure_output_settings_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_configure_output_settings_reply(in, write_cb, arg);
}

void msg_itf_configure_output_settings_reply_unmarshall(struct msg_itf_configure_output_settings_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_configure_output_settings_reply(out, read_cb, arg);
}

int msg_itf_configure_output_settings_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_configure_output_settings_reply_full();
}

void msg_itf_configure_output_settings_reply_full_marshall(struct msg_itf_configure_output_settings_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_configure_output_settings_reply_full(in, write_cb, arg);
}

void msg_itf_configure_output_settings_reply_full_unmarshall(struct msg_itf_configure_output_settings_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_configure_output_settings_reply_full(out, read_cb, arg);
}

int msg_itf_evt_bitstream_buffer_refcount_get_size(void)
{
	return get_size_struct_msg_itf_evt_bitstream_buffer_refcount();
}

void msg_itf_evt_bitstream_buffer_refcount_marshall(struct msg_itf_evt_bitstream_buffer_refcount *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_bitstream_buffer_refcount(in, write_cb, arg);
}

void msg_itf_evt_bitstream_buffer_refcount_unmarshall(struct msg_itf_evt_bitstream_buffer_refcount *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_bitstream_buffer_refcount(out, read_cb, arg);
}

int msg_itf_evt_bitstream_buffer_refcount_full_get_size(void)
{
	return get_size_struct_msg_itf_evt_bitstream_buffer_refcount_full();
}

void msg_itf_evt_bitstream_buffer_refcount_full_marshall(struct msg_itf_evt_bitstream_buffer_refcount_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_bitstream_buffer_refcount_full(in, write_cb, arg);
}

void msg_itf_evt_bitstream_buffer_refcount_full_unmarshall(struct msg_itf_evt_bitstream_buffer_refcount_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_bitstream_buffer_refcount_full(out, read_cb, arg);
}

int msg_itf_evt_display_picture_refcount_get_size(void)
{
	return get_size_struct_msg_itf_evt_display_picture_refcount();
}

void msg_itf_evt_display_picture_refcount_marshall(struct msg_itf_evt_display_picture_refcount *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_display_picture_refcount(in, write_cb, arg);
}

void msg_itf_evt_display_picture_refcount_unmarshall(struct msg_itf_evt_display_picture_refcount *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_display_picture_refcount(out, read_cb, arg);
}

int msg_itf_evt_display_picture_refcount_full_get_size(void)
{
	return get_size_struct_msg_itf_evt_display_picture_refcount_full();
}

void msg_itf_evt_display_picture_refcount_full_marshall(struct msg_itf_evt_display_picture_refcount_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_display_picture_refcount_full(in, write_cb, arg);
}

void msg_itf_evt_display_picture_refcount_full_unmarshall(struct msg_itf_evt_display_picture_refcount_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_display_picture_refcount_full(out, read_cb, arg);
}

int msg_itf_evt_resolution_found_get_size(void)
{
	return get_size_struct_msg_itf_evt_resolution_found();
}

void msg_itf_evt_resolution_found_marshall(struct msg_itf_evt_resolution_found *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_resolution_found(in, write_cb, arg);
}

void msg_itf_evt_resolution_found_unmarshall(struct msg_itf_evt_resolution_found *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_resolution_found(out, read_cb, arg);
}

int msg_itf_evt_resolution_found_full_get_size(void)
{
	return get_size_struct_msg_itf_evt_resolution_found_full();
}

void msg_itf_evt_resolution_found_full_marshall(struct msg_itf_evt_resolution_found_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_resolution_found_full(in, write_cb, arg);
}

void msg_itf_evt_resolution_found_full_unmarshall(struct msg_itf_evt_resolution_found_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_resolution_found_full(out, read_cb, arg);
}

int msg_itf_evt_end_parsing_get_size(void)
{
	return get_size_struct_msg_itf_evt_end_parsing();
}

void msg_itf_evt_end_parsing_marshall(struct msg_itf_evt_end_parsing *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_end_parsing(in, write_cb, arg);
}

void msg_itf_evt_end_parsing_unmarshall(struct msg_itf_evt_end_parsing *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_end_parsing(out, read_cb, arg);
}

int msg_itf_evt_end_parsing_full_get_size(void)
{
	return get_size_struct_msg_itf_evt_end_parsing_full();
}

void msg_itf_evt_end_parsing_full_marshall(struct msg_itf_evt_end_parsing_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_end_parsing_full(in, write_cb, arg);
}

void msg_itf_evt_end_parsing_full_unmarshall(struct msg_itf_evt_end_parsing_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_end_parsing_full(out, read_cb, arg);
}

int msg_itf_evt_end_decoding_get_size(void)
{
	return get_size_struct_msg_itf_evt_end_decoding();
}

void msg_itf_evt_end_decoding_marshall(struct msg_itf_evt_end_decoding *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_end_decoding(in, write_cb, arg);
}

void msg_itf_evt_end_decoding_unmarshall(struct msg_itf_evt_end_decoding *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_end_decoding(out, read_cb, arg);
}

int msg_itf_evt_end_decoding_full_get_size(void)
{
	return get_size_struct_msg_itf_evt_end_decoding_full();
}

void msg_itf_evt_end_decoding_full_marshall(struct msg_itf_evt_end_decoding_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_end_decoding_full(in, write_cb, arg);
}

void msg_itf_evt_end_decoding_full_unmarshall(struct msg_itf_evt_end_decoding_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_end_decoding_full(out, read_cb, arg);
}

int msg_itf_evt_display_get_size(void)
{
	return get_size_struct_msg_itf_evt_display();
}

void msg_itf_evt_display_marshall(struct msg_itf_evt_display *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_display(in, write_cb, arg);
}

void msg_itf_evt_display_unmarshall(struct msg_itf_evt_display *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_display(out, read_cb, arg);
}

int msg_itf_evt_display_full_get_size(void)
{
	return get_size_struct_msg_itf_evt_display_full();
}

void msg_itf_evt_display_full_marshall(struct msg_itf_evt_display_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_display_full(in, write_cb, arg);
}

void msg_itf_evt_display_full_unmarshall(struct msg_itf_evt_display_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_display_full(out, read_cb, arg);
}

int msg_itf_evt_display_with_hdr_get_size(void)
{
	return get_size_struct_msg_itf_evt_display_with_hdr();
}

void msg_itf_evt_display_with_hdr_marshall(struct msg_itf_evt_display_with_hdr *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_display_with_hdr(in, write_cb, arg);
}

void msg_itf_evt_display_with_hdr_unmarshall(struct msg_itf_evt_display_with_hdr *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_display_with_hdr(out, read_cb, arg);
}

int msg_itf_evt_display_with_hdr_full_get_size(void)
{
	return get_size_struct_msg_itf_evt_display_with_hdr_full();
}

void msg_itf_evt_display_with_hdr_full_marshall(struct msg_itf_evt_display_with_hdr_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_display_with_hdr_full(in, write_cb, arg);
}

void msg_itf_evt_display_with_hdr_full_unmarshall(struct msg_itf_evt_display_with_hdr_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_display_with_hdr_full(out, read_cb, arg);
}

int msg_itf_evt_sei_buf_get_size(void)
{
	return get_size_struct_msg_itf_evt_sei_buf();
}

void msg_itf_evt_sei_buf_marshall(struct msg_itf_evt_sei_buf *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_sei_buf(in, write_cb, arg);
}

void msg_itf_evt_sei_buf_unmarshall(struct msg_itf_evt_sei_buf *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_sei_buf(out, read_cb, arg);
}

int msg_itf_evt_sei_buf_full_get_size(void)
{
	return get_size_struct_msg_itf_evt_sei_buf_full();
}

void msg_itf_evt_sei_buf_full_marshall(struct msg_itf_evt_sei_buf_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_sei_buf_full(in, write_cb, arg);
}

void msg_itf_evt_sei_buf_full_unmarshall(struct msg_itf_evt_sei_buf_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_sei_buf_full(out, read_cb, arg);
}

int msg_itf_evt_sei_msg_get_size(void)
{
	return get_size_struct_msg_itf_evt_sei_msg();
}

void msg_itf_evt_sei_msg_marshall(struct msg_itf_evt_sei_msg *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_sei_msg(in, write_cb, arg);
}

void msg_itf_evt_sei_msg_unmarshall(struct msg_itf_evt_sei_msg *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_sei_msg(out, read_cb, arg);
}

int msg_itf_evt_sei_msg_full_get_size(void)
{
	return get_size_struct_msg_itf_evt_sei_msg_full();
}

void msg_itf_evt_sei_msg_full_marshall(struct msg_itf_evt_sei_msg_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_sei_msg_full(in, write_cb, arg);
}

void msg_itf_evt_sei_msg_full_unmarshall(struct msg_itf_evt_sei_msg_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_sei_msg_full(out, read_cb, arg);
}

int msg_itf_evt_error_get_size(void)
{
	return get_size_struct_msg_itf_evt_error();
}

void msg_itf_evt_error_marshall(struct msg_itf_evt_error *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_error(in, write_cb, arg);
}

void msg_itf_evt_error_unmarshall(struct msg_itf_evt_error *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_error(out, read_cb, arg);
}

int msg_itf_evt_error_full_get_size(void)
{
	return get_size_struct_msg_itf_evt_error_full();
}

void msg_itf_evt_error_full_marshall(struct msg_itf_evt_error_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_error_full(in, write_cb, arg);
}

void msg_itf_evt_error_full_unmarshall(struct msg_itf_evt_error_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_error_full(out, read_cb, arg);
}

int msg_itf_evt_destroy_marker_get_size(void)
{
	return get_size_struct_msg_itf_evt_destroy_marker();
}

void msg_itf_evt_destroy_marker_marshall(struct msg_itf_evt_destroy_marker *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_destroy_marker(in, write_cb, arg);
}

void msg_itf_evt_destroy_marker_unmarshall(struct msg_itf_evt_destroy_marker *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_destroy_marker(out, read_cb, arg);
}

int msg_itf_evt_destroy_marker_full_get_size(void)
{
	return get_size_struct_msg_itf_evt_destroy_marker_full();
}

void msg_itf_evt_destroy_marker_full_marshall(struct msg_itf_evt_destroy_marker_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_destroy_marker_full(in, write_cb, arg);
}

void msg_itf_evt_destroy_marker_full_unmarshall(struct msg_itf_evt_destroy_marker_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_destroy_marker_full(out, read_cb, arg);
}
#pragma GCC diagnostic pop
