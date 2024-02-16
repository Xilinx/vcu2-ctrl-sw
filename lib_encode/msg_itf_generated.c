// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/* Code generated DO NOT EDIT */

#include <stdint.h>
#include "msg_itf.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "runtime_generated.h"
struct AL_TEncoderInfo {
	uint8_t uNumCore;
};
struct AL_TDimension {
	int32_t iWidth;
	int32_t iHeight;
};
struct AL_TReconstructedInfo {
	uint32_t uID;
	AL_EPicStruct ePicStruct;
	uint32_t iPOC;
	AL_TDimension tPicDim;
};
struct AL_TStreamSection {
	uint32_t uOffset;
	uint32_t uLength;
	AL_ESectionFlags eFlags;
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
static int get_size_struct_AL_StreamSectionInBuffer(void);
static void marshall_struct_AL_StreamSectionInBuffer(struct AL_StreamSectionInBuffer *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_StreamSectionInBuffer(struct AL_StreamSectionInBuffer *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_chunk_info(void);
static void marshall_struct_chunk_info(struct chunk_info *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_chunk_info(struct chunk_info *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TMultiChipParam(void);
static void marshall_struct_AL_TMultiChipParam(struct AL_TMultiChipParam *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TMultiChipParam(struct AL_TMultiChipParam *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TRCParam(void);
static void marshall_struct_AL_TRCParam(struct AL_TRCParam *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TRCParam(struct AL_TRCParam *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TGopParam(void);
static void marshall_struct_AL_TGopParam(struct AL_TGopParam *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TGopParam(struct AL_TGopParam *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TAutoQPCtrl(void);
static void marshall_struct_AL_TAutoQPCtrl(struct AL_TAutoQPCtrl *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TAutoQPCtrl(struct AL_TAutoQPCtrl *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TEncChanParam(void);
static void marshall_struct_AL_TEncChanParam(struct AL_TEncChanParam *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TEncChanParam(struct AL_TEncChanParam *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_t_ColorConfig(void);
static void marshall_struct_t_ColorConfig(struct t_ColorConfig *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_t_ColorConfig(struct t_ColorConfig *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_t_EncSettings(void);
static void marshall_struct_t_EncSettings(struct t_EncSettings *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_t_EncSettings(struct t_EncSettings *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_create_encoder_req(void);
static void marshall_struct_msg_itf_create_encoder_req(struct msg_itf_create_encoder_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_create_encoder_req(struct msg_itf_create_encoder_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_create_encoder_req_full(void);
static void marshall_struct_msg_itf_create_encoder_req_full(struct msg_itf_create_encoder_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_create_encoder_req_full(struct msg_itf_create_encoder_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_create_encoder_reply(void);
static void marshall_struct_msg_itf_create_encoder_reply(struct msg_itf_create_encoder_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_create_encoder_reply(struct msg_itf_create_encoder_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_create_encoder_reply_full(void);
static void marshall_struct_msg_itf_create_encoder_reply_full(struct msg_itf_create_encoder_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_create_encoder_reply_full(struct msg_itf_create_encoder_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_destroy_encoder_req(void);
static void marshall_struct_msg_itf_destroy_encoder_req(struct msg_itf_destroy_encoder_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_destroy_encoder_req(struct msg_itf_destroy_encoder_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_destroy_encoder_req_full(void);
static void marshall_struct_msg_itf_destroy_encoder_req_full(struct msg_itf_destroy_encoder_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_destroy_encoder_req_full(struct msg_itf_destroy_encoder_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_destroy_encoder_reply(void);
static void marshall_struct_msg_itf_destroy_encoder_reply(struct msg_itf_destroy_encoder_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_destroy_encoder_reply(struct msg_itf_destroy_encoder_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_destroy_encoder_reply_full(void);
static void marshall_struct_msg_itf_destroy_encoder_reply_full(struct msg_itf_destroy_encoder_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_destroy_encoder_reply_full(struct msg_itf_destroy_encoder_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_info_req(void);
static void marshall_struct_msg_itf_get_info_req(struct msg_itf_get_info_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_info_req(struct msg_itf_get_info_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_info_req_full(void);
static void marshall_struct_msg_itf_get_info_req_full(struct msg_itf_get_info_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_info_req_full(struct msg_itf_get_info_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TEncoderInfo(void);
static void marshall_struct_AL_TEncoderInfo(struct AL_TEncoderInfo *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TEncoderInfo(struct AL_TEncoderInfo *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_info_reply(void);
static void marshall_struct_msg_itf_get_info_reply(struct msg_itf_get_info_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_info_reply(struct msg_itf_get_info_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_info_reply_full(void);
static void marshall_struct_msg_itf_get_info_reply_full(struct msg_itf_get_info_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_info_reply_full(struct msg_itf_get_info_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_push_stream_buffer_req(void);
static void marshall_struct_msg_itf_push_stream_buffer_req(struct msg_itf_push_stream_buffer_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_push_stream_buffer_req(struct msg_itf_push_stream_buffer_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_push_stream_buffer_req_full(void);
static void marshall_struct_msg_itf_push_stream_buffer_req_full(struct msg_itf_push_stream_buffer_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_push_stream_buffer_req_full(struct msg_itf_push_stream_buffer_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_push_stream_buffer_reply(void);
static void marshall_struct_msg_itf_push_stream_buffer_reply(struct msg_itf_push_stream_buffer_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_push_stream_buffer_reply(struct msg_itf_push_stream_buffer_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_push_stream_buffer_reply_full(void);
static void marshall_struct_msg_itf_push_stream_buffer_reply_full(struct msg_itf_push_stream_buffer_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_push_stream_buffer_reply_full(struct msg_itf_push_stream_buffer_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TDimension(void);
static void marshall_struct_AL_TDimension(struct AL_TDimension *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TDimension(struct AL_TDimension *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TPlane(void);
static void marshall_struct_AL_TPlane(struct AL_TPlane *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TPlane(struct AL_TPlane *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_process_req(void);
static void marshall_struct_msg_itf_process_req(struct msg_itf_process_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_process_req(struct msg_itf_process_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_process_req_full(void);
static void marshall_struct_msg_itf_process_req_full(struct msg_itf_process_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_process_req_full(struct msg_itf_process_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_process_reply(void);
static void marshall_struct_msg_itf_process_reply(struct msg_itf_process_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_process_reply(struct msg_itf_process_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_process_reply_full(void);
static void marshall_struct_msg_itf_process_reply_full(struct msg_itf_process_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_process_reply_full(struct msg_itf_process_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_rec_req(void);
static void marshall_struct_msg_itf_get_rec_req(struct msg_itf_get_rec_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_rec_req(struct msg_itf_get_rec_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_rec_req_full(void);
static void marshall_struct_msg_itf_get_rec_req_full(struct msg_itf_get_rec_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_rec_req_full(struct msg_itf_get_rec_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TReconstructedInfo(void);
static void marshall_struct_AL_TReconstructedInfo(struct AL_TReconstructedInfo *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TReconstructedInfo(struct AL_TReconstructedInfo *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_rec_reply(void);
static void marshall_struct_msg_itf_get_rec_reply(struct msg_itf_get_rec_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_rec_reply(struct msg_itf_get_rec_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_rec_reply_full(void);
static void marshall_struct_msg_itf_get_rec_reply_full(struct msg_itf_get_rec_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_rec_reply_full(struct msg_itf_get_rec_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_last_error_req(void);
static void marshall_struct_msg_itf_get_last_error_req(struct msg_itf_get_last_error_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_last_error_req(struct msg_itf_get_last_error_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_last_error_req_full(void);
static void marshall_struct_msg_itf_get_last_error_req_full(struct msg_itf_get_last_error_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_last_error_req_full(struct msg_itf_get_last_error_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_release_rec_req(void);
static void marshall_struct_msg_itf_release_rec_req(struct msg_itf_release_rec_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_release_rec_req(struct msg_itf_release_rec_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_release_rec_req_full(void);
static void marshall_struct_msg_itf_release_rec_req_full(struct msg_itf_release_rec_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_release_rec_req_full(struct msg_itf_release_rec_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_release_rec_reply(void);
static void marshall_struct_msg_itf_release_rec_reply(struct msg_itf_release_rec_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_release_rec_reply(struct msg_itf_release_rec_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_release_rec_reply_full(void);
static void marshall_struct_msg_itf_release_rec_reply_full(struct msg_itf_release_rec_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_release_rec_reply_full(struct msg_itf_release_rec_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_last_error_reply(void);
static void marshall_struct_msg_itf_get_last_error_reply(struct msg_itf_get_last_error_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_last_error_reply(struct msg_itf_get_last_error_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_get_last_error_reply_full(void);
static void marshall_struct_msg_itf_get_last_error_reply_full(struct msg_itf_get_last_error_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_get_last_error_reply_full(struct msg_itf_get_last_error_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_notify_req(void);
static void marshall_struct_msg_itf_notify_req(struct msg_itf_notify_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_notify_req(struct msg_itf_notify_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_notify_req_full(void);
static void marshall_struct_msg_itf_notify_req_full(struct msg_itf_notify_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_notify_req_full(struct msg_itf_notify_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_notify_reply(void);
static void marshall_struct_msg_itf_notify_reply(struct msg_itf_notify_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_notify_reply(struct msg_itf_notify_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_notify_reply_full(void);
static void marshall_struct_msg_itf_notify_reply_full(struct msg_itf_notify_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_notify_reply_full(struct msg_itf_notify_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_smart_req(void);
static void marshall_struct_msg_itf_smart_req(struct msg_itf_smart_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_smart_req(struct msg_itf_smart_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_smart_req_full(void);
static void marshall_struct_msg_itf_smart_req_full(struct msg_itf_smart_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_smart_req_full(struct msg_itf_smart_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_smart_reply(void);
static void marshall_struct_msg_itf_smart_reply(struct msg_itf_smart_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_smart_reply(struct msg_itf_smart_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_smart_reply_full(void);
static void marshall_struct_msg_itf_smart_reply_full(struct msg_itf_smart_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_smart_reply_full(struct msg_itf_smart_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
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
static int get_size_struct_msg_itf_hdr_req(void);
static void marshall_struct_msg_itf_hdr_req(struct msg_itf_hdr_req *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_hdr_req(struct msg_itf_hdr_req *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_hdr_req_full(void);
static void marshall_struct_msg_itf_hdr_req_full(struct msg_itf_hdr_req_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_hdr_req_full(struct msg_itf_hdr_req_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_hdr_reply(void);
static void marshall_struct_msg_itf_hdr_reply(struct msg_itf_hdr_reply *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_hdr_reply(struct msg_itf_hdr_reply *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_hdr_reply_full(void);
static void marshall_struct_msg_itf_hdr_reply_full(struct msg_itf_hdr_reply_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_hdr_reply_full(struct msg_itf_hdr_reply_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_buffer_refcount(void);
static void marshall_struct_msg_itf_evt_buffer_refcount(struct msg_itf_evt_buffer_refcount *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_buffer_refcount(struct msg_itf_evt_buffer_refcount *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_buffer_refcount_full(void);
static void marshall_struct_msg_itf_evt_buffer_refcount_full(struct msg_itf_evt_buffer_refcount_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_buffer_refcount_full(struct msg_itf_evt_buffer_refcount_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_AL_TStreamSection(void);
static void marshall_struct_AL_TStreamSection(struct AL_TStreamSection *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_AL_TStreamSection(struct AL_TStreamSection *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_end_encoding(void);
static void marshall_struct_msg_itf_evt_end_encoding(struct msg_itf_evt_end_encoding *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_end_encoding(struct msg_itf_evt_end_encoding *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_end_encoding_full(void);
static void marshall_struct_msg_itf_evt_end_encoding_full(struct msg_itf_evt_end_encoding_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_end_encoding_full(struct msg_itf_evt_end_encoding_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_al_t_RateCtrl_Statistics(void);
static void marshall_struct_al_t_RateCtrl_Statistics(struct al_t_RateCtrl_Statistics *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_al_t_RateCtrl_Statistics(struct al_t_RateCtrl_Statistics *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_end_encoding_with_stat(void);
static void marshall_struct_msg_itf_evt_end_encoding_with_stat(struct msg_itf_evt_end_encoding_with_stat *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_end_encoding_with_stat(struct msg_itf_evt_end_encoding_with_stat *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_end_encoding_with_stat_full(void);
static void marshall_struct_msg_itf_evt_end_encoding_with_stat_full(struct msg_itf_evt_end_encoding_with_stat_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_end_encoding_with_stat_full(struct msg_itf_evt_end_encoding_with_stat_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_destroy_marker(void);
static void marshall_struct_msg_itf_evt_destroy_marker(struct msg_itf_evt_destroy_marker *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_destroy_marker(struct msg_itf_evt_destroy_marker *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_struct_msg_itf_evt_destroy_marker_full(void);
static void marshall_struct_msg_itf_evt_destroy_marker_full(struct msg_itf_evt_destroy_marker_full *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_struct_msg_itf_evt_destroy_marker_full(struct msg_itf_evt_destroy_marker_full *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_enum_AL_e_VideoMode(void);
static void marshall_enum_AL_e_VideoMode(enum AL_e_VideoMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_enum_AL_e_VideoMode(enum AL_e_VideoMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_enum_e_EntropyMode(void);
static void marshall_enum_e_EntropyMode(enum e_EntropyMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_enum_e_EntropyMode(enum e_EntropyMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_enum_e_WPMode(void);
static void marshall_enum_e_WPMode(enum e_WPMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_enum_e_WPMode(enum e_WPMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_enum_e_StartCodeBytesAlignedMode(void);
static void marshall_enum_e_StartCodeBytesAlignedMode(enum e_StartCodeBytesAlignedMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_enum_e_StartCodeBytesAlignedMode(enum e_StartCodeBytesAlignedMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_enum_e_FillerCtrlMode(void);
static void marshall_enum_e_FillerCtrlMode(enum e_FillerCtrlMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_enum_e_FillerCtrlMode(enum e_FillerCtrlMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_enum_e_ColourDescription(void);
static void marshall_enum_e_ColourDescription(enum e_ColourDescription *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_enum_e_ColourDescription(enum e_ColourDescription *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_enum_e_TransferCharacteristics(void);
static void marshall_enum_e_TransferCharacteristics(enum e_TransferCharacteristics *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_enum_e_TransferCharacteristics(enum e_TransferCharacteristics *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_enum_e_ColourMatrixCoefficients(void);
static void marshall_enum_e_ColourMatrixCoefficients(enum e_ColourMatrixCoefficients *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_enum_e_ColourMatrixCoefficients(enum e_ColourMatrixCoefficients *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_enum_e_AspectRatio(void);
static void marshall_enum_e_AspectRatio(enum e_AspectRatio *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_enum_e_AspectRatio(enum e_AspectRatio *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_enum_e_ScalingList(void);
static void marshall_enum_e_ScalingList(enum e_ScalingList *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_enum_e_ScalingList(enum e_ScalingList *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_enum_e_QpCtrlMode(void);
static void marshall_enum_e_QpCtrlMode(enum e_QpCtrlMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_enum_e_QpCtrlMode(enum e_QpCtrlMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_enum_e_QpTableMode(void);
static void marshall_enum_e_QpTableMode(enum e_QpTableMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_enum_e_QpTableMode(enum e_QpTableMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_enum_e_PicStruct(void);
static void marshall_enum_e_PicStruct(enum e_PicStruct *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_enum_e_PicStruct(enum e_PicStruct *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_enum_e_SliceType(void);
static void marshall_enum_e_SliceType(enum e_SliceType *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_enum_e_SliceType(enum e_SliceType *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EVideoMode(void);
static void marshall_AL_EVideoMode(AL_EVideoMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EVideoMode(AL_EVideoMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EPicFormat(void);
static void marshall_AL_EPicFormat(AL_EPicFormat *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EPicFormat(AL_EPicFormat *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_ESrcMode(void);
static void marshall_AL_ESrcMode(AL_ESrcMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_ESrcMode(AL_ESrcMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EProfile(void);
static void marshall_AL_EProfile(AL_EProfile *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EProfile(AL_EProfile *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EChEncOption(void);
static void marshall_AL_EChEncOption(AL_EChEncOption *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EChEncOption(AL_EChEncOption *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EChEncTool(void);
static void marshall_AL_EChEncTool(AL_EChEncTool *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EChEncTool(AL_EChEncTool *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EMultiChipClipMode(void);
static void marshall_AL_EMultiChipClipMode(AL_EMultiChipClipMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EMultiChipClipMode(AL_EMultiChipClipMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TMultiChipParam(void);
static void marshall_AL_TMultiChipParam(AL_TMultiChipParam *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TMultiChipParam(AL_TMultiChipParam *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EEntropyMode(void);
static void marshall_AL_EEntropyMode(AL_EEntropyMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EEntropyMode(AL_EEntropyMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EWPMode(void);
static void marshall_AL_EWPMode(AL_EWPMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EWPMode(AL_EWPMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_ERateCtrlMode(void);
static void marshall_AL_ERateCtrlMode(AL_ERateCtrlMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_ERateCtrlMode(AL_ERateCtrlMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_ERateCtrlOption(void);
static void marshall_AL_ERateCtrlOption(AL_ERateCtrlOption *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_ERateCtrlOption(AL_ERateCtrlOption *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TRCParam(void);
static void marshall_AL_TRCParam(AL_TRCParam *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TRCParam(AL_TRCParam *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EGopCtrlMode(void);
static void marshall_AL_EGopCtrlMode(AL_EGopCtrlMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EGopCtrlMode(AL_EGopCtrlMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EGdrMode(void);
static void marshall_AL_EGdrMode(AL_EGdrMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EGdrMode(AL_EGdrMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TGopParam(void);
static void marshall_AL_TGopParam(AL_TGopParam *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TGopParam(AL_TGopParam *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_ELdaCtrlMode(void);
static void marshall_AL_ELdaCtrlMode(AL_ELdaCtrlMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_ELdaCtrlMode(AL_ELdaCtrlMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EStartCodeBytesAlignedMode(void);
static void marshall_AL_EStartCodeBytesAlignedMode(AL_EStartCodeBytesAlignedMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EStartCodeBytesAlignedMode(AL_EStartCodeBytesAlignedMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TAutoQPCtrl(void);
static void marshall_AL_TAutoQPCtrl(AL_TAutoQPCtrl *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TAutoQPCtrl(AL_TAutoQPCtrl *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TEncChanParam(void);
static void marshall_AL_TEncChanParam(AL_TEncChanParam *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TEncChanParam(AL_TEncChanParam *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EFillerCtrlMode(void);
static void marshall_AL_EFillerCtrlMode(AL_EFillerCtrlMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EFillerCtrlMode(AL_EFillerCtrlMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EColourDescription(void);
static void marshall_AL_EColourDescription(AL_EColourDescription *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EColourDescription(AL_EColourDescription *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_ETransferCharacteristics(void);
static void marshall_AL_ETransferCharacteristics(AL_ETransferCharacteristics *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_ETransferCharacteristics(AL_ETransferCharacteristics *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EColourMatrixCoefficients(void);
static void marshall_AL_EColourMatrixCoefficients(AL_EColourMatrixCoefficients *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EColourMatrixCoefficients(AL_EColourMatrixCoefficients *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TColorConfig(void);
static void marshall_AL_TColorConfig(AL_TColorConfig *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TColorConfig(AL_TColorConfig *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EAspectRatio(void);
static void marshall_AL_EAspectRatio(AL_EAspectRatio *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EAspectRatio(AL_EAspectRatio *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EScalingList(void);
static void marshall_AL_EScalingList(AL_EScalingList *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EScalingList(AL_EScalingList *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EQpCtrlMode(void);
static void marshall_AL_EQpCtrlMode(AL_EQpCtrlMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EQpCtrlMode(AL_EQpCtrlMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EQpTableMode(void);
static void marshall_AL_EQpTableMode(AL_EQpTableMode *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EQpTableMode(AL_EQpTableMode *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TEncSettings(void);
static void marshall_AL_TEncSettings(AL_TEncSettings *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TEncSettings(AL_TEncSettings *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TEncoderInfo(void);
static void marshall_AL_TEncoderInfo(AL_TEncoderInfo *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TEncoderInfo(AL_TEncoderInfo *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TDimension(void);
static void marshall_AL_TDimension(AL_TDimension *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TDimension(AL_TDimension *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TPlane(void);
static void marshall_AL_TPlane(AL_TPlane *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TPlane(AL_TPlane *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_EPicStruct(void);
static void marshall_AL_EPicStruct(AL_EPicStruct *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_EPicStruct(AL_EPicStruct *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TReconstructedInfo(void);
static void marshall_AL_TReconstructedInfo(AL_TReconstructedInfo *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TReconstructedInfo(AL_TReconstructedInfo *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_ESliceType(void);
static void marshall_AL_ESliceType(AL_ESliceType *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_ESliceType(AL_ESliceType *in, void (*read_cb)(int, void *, void *), void *arg);
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
static int get_size_AL_ESectionFlags(void);
static void marshall_AL_ESectionFlags(AL_ESectionFlags *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_ESectionFlags(AL_ESectionFlags *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_TStreamSection(void);
static void marshall_AL_TStreamSection(AL_TStreamSection *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_TStreamSection(AL_TStreamSection *in, void (*read_cb)(int, void *, void *), void *arg);
static int get_size_AL_RateCtrl_Statistics(void);
static void marshall_AL_RateCtrl_Statistics(AL_RateCtrl_Statistics *in, void (*write_cb)(int, void *, void *), void *arg);
static void unmarshall_AL_RateCtrl_Statistics(AL_RateCtrl_Statistics *in, void (*read_cb)(int, void *, void *), void *arg);

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
static int get_size_struct_AL_StreamSectionInBuffer()
{
	int res = 0;

	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_uint32_t();

	return res;
}
static void marshall_struct_AL_StreamSectionInBuffer(struct AL_StreamSectionInBuffer *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint32_t(&in->uOffset, write_cb, arg);
	marshall_uint32_t(&in->uLength, write_cb, arg);
	marshall_uint32_t(&in->eFlags, write_cb, arg);
}
static void unmarshall_struct_AL_StreamSectionInBuffer(struct AL_StreamSectionInBuffer *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint32_t(&in->uOffset, read_cb, arg);
	unmarshall_uint32_t(&in->uLength, read_cb, arg);
	unmarshall_uint32_t(&in->eFlags, read_cb, arg);
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
static int get_size_struct_AL_TMultiChipParam()
{
	int res = 0;

	res += get_size_AL_EMultiChipClipMode();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();

	return res;
}
static void marshall_struct_AL_TMultiChipParam(struct AL_TMultiChipParam *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_AL_EMultiChipClipMode(&in->eMCClipMode, write_cb, arg);
	marshall_uint16_t(&in->uMCWidth, write_cb, arg);
	marshall_uint16_t(&in->uMCHeight, write_cb, arg);
	marshall_uint16_t(&in->uMCPosX, write_cb, arg);
	marshall_uint16_t(&in->uMCPosY, write_cb, arg);
}
static void unmarshall_struct_AL_TMultiChipParam(struct AL_TMultiChipParam *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_AL_EMultiChipClipMode(&in->eMCClipMode, read_cb, arg);
	unmarshall_uint16_t(&in->uMCWidth, read_cb, arg);
	unmarshall_uint16_t(&in->uMCHeight, read_cb, arg);
	unmarshall_uint16_t(&in->uMCPosX, read_cb, arg);
	unmarshall_uint16_t(&in->uMCPosY, read_cb, arg);
}
static int get_size_struct_AL_TRCParam()
{
	int res = 0;

	res += get_size_AL_ERateCtrlMode();
	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_int16_t();
	res += 3 * get_size_int16_t();
	res += 3 * get_size_int16_t();
	res += get_size_int16_t();
	res += get_size_int16_t();
	res += get_size__Bool();
	res += get_size_int16_t();
	res += get_size_int16_t();
	res += get_size_AL_ERateCtrlOption();
	res += get_size_uint32_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += 3 * get_size_uint32_t();

	return res;
}
static void marshall_struct_AL_TRCParam(struct AL_TRCParam *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_AL_ERateCtrlMode(&in->eRCMode, write_cb, arg);
	marshall_uint32_t(&in->uInitialRemDelay, write_cb, arg);
	marshall_uint32_t(&in->uCPBSize, write_cb, arg);
	marshall_uint16_t(&in->uFrameRate, write_cb, arg);
	marshall_uint16_t(&in->uClkRatio, write_cb, arg);
	marshall_uint32_t(&in->uTargetBitRate, write_cb, arg);
	marshall_uint32_t(&in->uMaxBitRate, write_cb, arg);
	marshall_uint32_t(&in->uMaxConsecSkip, write_cb, arg);
	marshall_int16_t(&in->iInitialQP, write_cb, arg);
	{
		int16_t *iMinQP__ptr__ = (int16_t *)((uintptr_t)in->iMinQP);
		for (int i = 0; i < 3; i++)
			marshall_int16_t(&iMinQP__ptr__[i], write_cb, arg);
	}
	{
		int16_t *iMaxQP__ptr__ = (int16_t *)((uintptr_t)in->iMaxQP);
		for (int i = 0; i < 3; i++)
			marshall_int16_t(&iMaxQP__ptr__[i], write_cb, arg);
	}
	marshall_int16_t(&in->uIPDelta, write_cb, arg);
	marshall_int16_t(&in->uPBDelta, write_cb, arg);
	marshall__Bool(&in->bUseGoldenRef, write_cb, arg);
	marshall_int16_t(&in->uPGoldenDelta, write_cb, arg);
	marshall_int16_t(&in->uGoldenRefFrequency, write_cb, arg);
	marshall_AL_ERateCtrlOption(&in->eOptions, write_cb, arg);
	marshall_uint32_t(&in->uNumPel, write_cb, arg);
	marshall_uint16_t(&in->uMinPSNR, write_cb, arg);
	marshall_uint16_t(&in->uMaxPSNR, write_cb, arg);
	marshall_uint16_t(&in->uMaxPelVal, write_cb, arg);
	{
		uint32_t *pMaxPictureSize__ptr__ = (uint32_t *)((uintptr_t)in->pMaxPictureSize);
		for (int i = 0; i < 3; i++)
			marshall_uint32_t(&pMaxPictureSize__ptr__[i], write_cb, arg);
	}
}
static void unmarshall_struct_AL_TRCParam(struct AL_TRCParam *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_AL_ERateCtrlMode(&in->eRCMode, read_cb, arg);
	unmarshall_uint32_t(&in->uInitialRemDelay, read_cb, arg);
	unmarshall_uint32_t(&in->uCPBSize, read_cb, arg);
	unmarshall_uint16_t(&in->uFrameRate, read_cb, arg);
	unmarshall_uint16_t(&in->uClkRatio, read_cb, arg);
	unmarshall_uint32_t(&in->uTargetBitRate, read_cb, arg);
	unmarshall_uint32_t(&in->uMaxBitRate, read_cb, arg);
	unmarshall_uint32_t(&in->uMaxConsecSkip, read_cb, arg);
	unmarshall_int16_t(&in->iInitialQP, read_cb, arg);
	{
		int16_t *iMinQP__ptr__ = (int16_t *)((uintptr_t)in->iMinQP);
		for (int i = 0; i < 3; i++)
			unmarshall_int16_t(&iMinQP__ptr__[i], read_cb, arg);
	}
	{
		int16_t *iMaxQP__ptr__ = (int16_t *)((uintptr_t)in->iMaxQP);
		for (int i = 0; i < 3; i++)
			unmarshall_int16_t(&iMaxQP__ptr__[i], read_cb, arg);
	}
	unmarshall_int16_t(&in->uIPDelta, read_cb, arg);
	unmarshall_int16_t(&in->uPBDelta, read_cb, arg);
	unmarshall__Bool(&in->bUseGoldenRef, read_cb, arg);
	unmarshall_int16_t(&in->uPGoldenDelta, read_cb, arg);
	unmarshall_int16_t(&in->uGoldenRefFrequency, read_cb, arg);
	unmarshall_AL_ERateCtrlOption(&in->eOptions, read_cb, arg);
	unmarshall_uint32_t(&in->uNumPel, read_cb, arg);
	unmarshall_uint16_t(&in->uMinPSNR, read_cb, arg);
	unmarshall_uint16_t(&in->uMaxPSNR, read_cb, arg);
	unmarshall_uint16_t(&in->uMaxPelVal, read_cb, arg);
	{
		uint32_t *pMaxPictureSize__ptr__ = (uint32_t *)((uintptr_t)in->pMaxPictureSize);
		for (int i = 0; i < 3; i++)
			unmarshall_uint32_t(&pMaxPictureSize__ptr__[i], read_cb, arg);
	}
}
static int get_size_struct_AL_TGopParam()
{
	int res = 0;

	res += get_size_AL_EGopCtrlMode();
	res += get_size_uint16_t();
	res += get_size_uint8_t();
	res += get_size_uint8_t();
	res += get_size_uint32_t();
	res += get_size__Bool();
	res += get_size__Bool();
	res += get_size__Bool();
	res += get_size_uint32_t();
	res += get_size_AL_EGdrMode();
	res += get_size_uint32_t();
	res += 4 * get_size_int8_t();

	return res;
}
static void marshall_struct_AL_TGopParam(struct AL_TGopParam *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_AL_EGopCtrlMode(&in->eMode, write_cb, arg);
	marshall_uint16_t(&in->uGopLength, write_cb, arg);
	marshall_uint8_t(&in->uNumB, write_cb, arg);
	marshall_uint8_t(&in->uFreqGoldenRef, write_cb, arg);
	marshall_uint32_t(&in->uFreqIDR, write_cb, arg);
	marshall__Bool(&in->bEnableLT, write_cb, arg);
	marshall__Bool(&in->bWriteAvcHdrSvcExt, write_cb, arg);
	marshall__Bool(&in->bDoubleRef, write_cb, arg);
	marshall_uint32_t(&in->uFreqLT, write_cb, arg);
	marshall_AL_EGdrMode(&in->eGdrMode, write_cb, arg);
	marshall_uint32_t(&in->uFreqRP, write_cb, arg);
	{
		int8_t *tempDQP__ptr__ = (int8_t *)((uintptr_t)in->tempDQP);
		for (int i = 0; i < 4; i++)
			marshall_int8_t(&tempDQP__ptr__[i], write_cb, arg);
	}
}
static void unmarshall_struct_AL_TGopParam(struct AL_TGopParam *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_AL_EGopCtrlMode(&in->eMode, read_cb, arg);
	unmarshall_uint16_t(&in->uGopLength, read_cb, arg);
	unmarshall_uint8_t(&in->uNumB, read_cb, arg);
	unmarshall_uint8_t(&in->uFreqGoldenRef, read_cb, arg);
	unmarshall_uint32_t(&in->uFreqIDR, read_cb, arg);
	unmarshall__Bool(&in->bEnableLT, read_cb, arg);
	unmarshall__Bool(&in->bWriteAvcHdrSvcExt, read_cb, arg);
	unmarshall__Bool(&in->bDoubleRef, read_cb, arg);
	unmarshall_uint32_t(&in->uFreqLT, read_cb, arg);
	unmarshall_AL_EGdrMode(&in->eGdrMode, read_cb, arg);
	unmarshall_uint32_t(&in->uFreqRP, read_cb, arg);
	{
		int8_t *tempDQP__ptr__ = (int8_t *)((uintptr_t)in->tempDQP);
		for (int i = 0; i < 4; i++)
			unmarshall_int8_t(&tempDQP__ptr__[i], read_cb, arg);
	}
}
static int get_size_struct_AL_TAutoQPCtrl()
{
	int res = 0;

	res += 6 * get_size_uint32_t();
	res += 7 * get_size_int8_t();

	return res;
}
static void marshall_struct_AL_TAutoQPCtrl(struct AL_TAutoQPCtrl *in, void (*write_cb)(int, void *, void *), void *arg)
{
	{
		uint32_t *thresholdQP__ptr__ = (uint32_t *)((uintptr_t)in->thresholdQP);
		for (int i = 0; i < 6; i++)
			marshall_uint32_t(&thresholdQP__ptr__[i], write_cb, arg);
	}
	{
		int8_t *deltaQP__ptr__ = (int8_t *)((uintptr_t)in->deltaQP);
		for (int i = 0; i < 7; i++)
			marshall_int8_t(&deltaQP__ptr__[i], write_cb, arg);
	}
}
static void unmarshall_struct_AL_TAutoQPCtrl(struct AL_TAutoQPCtrl *in, void (*read_cb)(int, void *, void *), void *arg)
{
	{
		uint32_t *thresholdQP__ptr__ = (uint32_t *)((uintptr_t)in->thresholdQP);
		for (int i = 0; i < 6; i++)
			unmarshall_uint32_t(&thresholdQP__ptr__[i], read_cb, arg);
	}
	{
		int8_t *deltaQP__ptr__ = (int8_t *)((uintptr_t)in->deltaQP);
		for (int i = 0; i < 7; i++)
			unmarshall_int8_t(&deltaQP__ptr__[i], read_cb, arg);
	}
}
static int get_size_struct_AL_TEncChanParam()
{
	int res = 0;

	res += get_size_int();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size__Bool();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_AL_EVideoMode();
	res += get_size_AL_EPicFormat();
	res += get_size__Bool();
	res += get_size_AL_ESrcMode();
	res += get_size_uint8_t();
	res += get_size_AL_EProfile();
	res += get_size_uint8_t();
	res += get_size_uint8_t();
	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size__Bool();
	res += get_size_AL_EChEncOption();
	res += get_size_AL_EChEncTool();
	res += get_size_int8_t();
	res += get_size_int8_t();
	res += get_size_int8_t();
	res += get_size_int8_t();
	res += get_size_int8_t();
	res += get_size_int8_t();
	res += get_size_uint8_t();
	res += get_size__Bool();
	res += get_size_uint8_t();
	res += get_size_uint8_t();
	res += get_size_uint8_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_int8_t();
	res += get_size_AL_TMultiChipParam();
	res += get_size_int();
	res += 4 * get_size_int16_t();
	res += get_size_uint8_t();
	res += get_size_uint8_t();
	res += get_size_uint8_t();
	res += get_size_uint8_t();
	res += get_size_uint8_t();
	res += get_size_uint8_t();
	res += get_size_uint8_t();
	res += get_size__Bool();
	res += get_size_AL_EEntropyMode();
	res += get_size_AL_EWPMode();
	res += get_size__Bool();
	res += get_size_AL_TRCParam();
	res += get_size_AL_TGopParam();
	res += get_size__Bool();
	res += get_size__Bool();
	res += get_size_AL_ELdaCtrlMode();
	res += 6 * get_size_int();
	res += get_size_uint16_t();
	res += get_size_int8_t();
	res += get_size_uint32_t();
	res += get_size_AL_64U();
	res += get_size__Bool();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size__Bool();
	res += get_size_uint8_t();
	res += get_size__Bool();
	res += get_size_AL_EStartCodeBytesAlignedMode();
	res += get_size_AL_TAutoQPCtrl();
	res += get_size__Bool();

	return res;
}
static void marshall_struct_AL_TEncChanParam(struct AL_TEncChanParam *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_int(&in->iLayerID, write_cb, arg);
	marshall_uint16_t(&in->uEncWidth, write_cb, arg);
	marshall_uint16_t(&in->uEncHeight, write_cb, arg);
	marshall_uint16_t(&in->uSrcWidth, write_cb, arg);
	marshall_uint16_t(&in->uSrcHeight, write_cb, arg);
	marshall__Bool(&in->bEnableSrcCrop, write_cb, arg);
	marshall_uint16_t(&in->uSrcCropWidth, write_cb, arg);
	marshall_uint16_t(&in->uSrcCropHeight, write_cb, arg);
	marshall_uint16_t(&in->uSrcCropPosX, write_cb, arg);
	marshall_uint16_t(&in->uSrcCropPosY, write_cb, arg);
	marshall_AL_EVideoMode(&in->eVideoMode, write_cb, arg);
	marshall_AL_EPicFormat(&in->ePicFormat, write_cb, arg);
	marshall__Bool(&in->bVideoFullRange, write_cb, arg);
	marshall_AL_ESrcMode(&in->eSrcMode, write_cb, arg);
	marshall_uint8_t(&in->uSrcBitDepth, write_cb, arg);
	marshall_AL_EProfile(&in->eProfile, write_cb, arg);
	marshall_uint8_t(&in->uLevel, write_cb, arg);
	marshall_uint8_t(&in->uTier, write_cb, arg);
	marshall_uint32_t(&in->uSpsParam, write_cb, arg);
	marshall_uint32_t(&in->uPpsParam, write_cb, arg);
	marshall__Bool(&in->bForcePpsIdToZero, write_cb, arg);
	marshall_AL_EChEncOption(&in->eEncOptions, write_cb, arg);
	marshall_AL_EChEncTool(&in->eEncTools, write_cb, arg);
	marshall_int8_t(&in->iBetaOffset, write_cb, arg);
	marshall_int8_t(&in->iTcOffset, write_cb, arg);
	marshall_int8_t(&in->iCbSliceQpOffset, write_cb, arg);
	marshall_int8_t(&in->iCrSliceQpOffset, write_cb, arg);
	marshall_int8_t(&in->iCbPicQpOffset, write_cb, arg);
	marshall_int8_t(&in->iCrPicQpOffset, write_cb, arg);
	marshall_uint8_t(&in->WeightedPred, write_cb, arg);
	marshall__Bool(&in->Direct8x8Infer, write_cb, arg);
	marshall_uint8_t(&in->uCuQPDeltaDepth, write_cb, arg);
	marshall_uint8_t(&in->uCabacInitIdc, write_cb, arg);
	marshall_uint8_t(&in->uNumCore, write_cb, arg);
	marshall_uint16_t(&in->uSliceSize, write_cb, arg);
	marshall_uint16_t(&in->uNumSlices, write_cb, arg);
	marshall_uint16_t(&in->uClipHrzRange, write_cb, arg);
	marshall_uint16_t(&in->uClipVrtRange, write_cb, arg);
	marshall_int8_t(&in->iL2CacheTolerance, write_cb, arg);
	marshall_AL_TMultiChipParam(&in->tMCParam, write_cb, arg);
	marshall_int(&in->iQPTableDepth, write_cb, arg);
	{
		int16_t *pMeRange__ptr__ = (int16_t *)((uintptr_t)in->pMeRange);
		for (int i = 0; i < 4; i++)
			marshall_int16_t(&pMeRange__ptr__[i], write_cb, arg);
	}
	marshall_uint8_t(&in->uLog2MaxCuSize, write_cb, arg);
	marshall_uint8_t(&in->uLog2MinCuSize, write_cb, arg);
	marshall_uint8_t(&in->uLog2MaxTuSize, write_cb, arg);
	marshall_uint8_t(&in->uLog2MaxTuSkipSize, write_cb, arg);
	marshall_uint8_t(&in->uLog2MinTuSize, write_cb, arg);
	marshall_uint8_t(&in->uMaxTransfoDepthIntra, write_cb, arg);
	marshall_uint8_t(&in->uMaxTransfoDepthInter, write_cb, arg);
	marshall__Bool(&in->StrongIntraSmooth, write_cb, arg);
	marshall_AL_EEntropyMode(&in->eEntropyMode, write_cb, arg);
	marshall_AL_EWPMode(&in->eWPMode, write_cb, arg);
	marshall__Bool(&in->bUseGMV, write_cb, arg);
	marshall_AL_TRCParam(&in->tRCParam, write_cb, arg);
	marshall_AL_TGopParam(&in->tGopParam, write_cb, arg);
	marshall__Bool(&in->bNonRealtime, write_cb, arg);
	marshall__Bool(&in->bSubframeLatency, write_cb, arg);
	marshall_AL_ELdaCtrlMode(&in->eLdaCtrlMode, write_cb, arg);
	{
		int *LdaFactors__ptr__ = (int *)((uintptr_t)in->LdaFactors);
		for (int i = 0; i < 6; i++)
			marshall_int(&LdaFactors__ptr__[i], write_cb, arg);
	}
	marshall_uint16_t(&in->uMVVRange, write_cb, arg);
	marshall_int8_t(&in->MaxNumMergeCand, write_cb, arg);
	marshall_uint32_t(&in->zRcPluginDmaSize, write_cb, arg);
	marshall_AL_64U(&in->pRcPluginDmaContext, write_cb, arg);
	marshall__Bool(&in->bEnableOutputCrop, write_cb, arg);
	marshall_uint16_t(&in->uOutputCropWidth, write_cb, arg);
	marshall_uint16_t(&in->uOutputCropHeight, write_cb, arg);
	marshall_uint16_t(&in->uOutputCropPosX, write_cb, arg);
	marshall_uint16_t(&in->uOutputCropPosY, write_cb, arg);
	marshall__Bool(&in->bSrcSync, write_cb, arg);
	marshall_uint8_t(&in->uSrcSyncChanID, write_cb, arg);
	marshall__Bool(&in->bUseUniformSliceType, write_cb, arg);
	marshall_AL_EStartCodeBytesAlignedMode(&in->eStartCodeBytesAligned, write_cb, arg);
	marshall_AL_TAutoQPCtrl(&in->sUserAutoQPValues, write_cb, arg);
	marshall__Bool(&in->bUserAutoQP, write_cb, arg);
}
static void unmarshall_struct_AL_TEncChanParam(struct AL_TEncChanParam *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_int(&in->iLayerID, read_cb, arg);
	unmarshall_uint16_t(&in->uEncWidth, read_cb, arg);
	unmarshall_uint16_t(&in->uEncHeight, read_cb, arg);
	unmarshall_uint16_t(&in->uSrcWidth, read_cb, arg);
	unmarshall_uint16_t(&in->uSrcHeight, read_cb, arg);
	unmarshall__Bool(&in->bEnableSrcCrop, read_cb, arg);
	unmarshall_uint16_t(&in->uSrcCropWidth, read_cb, arg);
	unmarshall_uint16_t(&in->uSrcCropHeight, read_cb, arg);
	unmarshall_uint16_t(&in->uSrcCropPosX, read_cb, arg);
	unmarshall_uint16_t(&in->uSrcCropPosY, read_cb, arg);
	unmarshall_AL_EVideoMode(&in->eVideoMode, read_cb, arg);
	unmarshall_AL_EPicFormat(&in->ePicFormat, read_cb, arg);
	unmarshall__Bool(&in->bVideoFullRange, read_cb, arg);
	unmarshall_AL_ESrcMode(&in->eSrcMode, read_cb, arg);
	unmarshall_uint8_t(&in->uSrcBitDepth, read_cb, arg);
	unmarshall_AL_EProfile(&in->eProfile, read_cb, arg);
	unmarshall_uint8_t(&in->uLevel, read_cb, arg);
	unmarshall_uint8_t(&in->uTier, read_cb, arg);
	unmarshall_uint32_t(&in->uSpsParam, read_cb, arg);
	unmarshall_uint32_t(&in->uPpsParam, read_cb, arg);
	unmarshall__Bool(&in->bForcePpsIdToZero, read_cb, arg);
	unmarshall_AL_EChEncOption(&in->eEncOptions, read_cb, arg);
	unmarshall_AL_EChEncTool(&in->eEncTools, read_cb, arg);
	unmarshall_int8_t(&in->iBetaOffset, read_cb, arg);
	unmarshall_int8_t(&in->iTcOffset, read_cb, arg);
	unmarshall_int8_t(&in->iCbSliceQpOffset, read_cb, arg);
	unmarshall_int8_t(&in->iCrSliceQpOffset, read_cb, arg);
	unmarshall_int8_t(&in->iCbPicQpOffset, read_cb, arg);
	unmarshall_int8_t(&in->iCrPicQpOffset, read_cb, arg);
	unmarshall_uint8_t(&in->WeightedPred, read_cb, arg);
	unmarshall__Bool(&in->Direct8x8Infer, read_cb, arg);
	unmarshall_uint8_t(&in->uCuQPDeltaDepth, read_cb, arg);
	unmarshall_uint8_t(&in->uCabacInitIdc, read_cb, arg);
	unmarshall_uint8_t(&in->uNumCore, read_cb, arg);
	unmarshall_uint16_t(&in->uSliceSize, read_cb, arg);
	unmarshall_uint16_t(&in->uNumSlices, read_cb, arg);
	unmarshall_uint16_t(&in->uClipHrzRange, read_cb, arg);
	unmarshall_uint16_t(&in->uClipVrtRange, read_cb, arg);
	unmarshall_int8_t(&in->iL2CacheTolerance, read_cb, arg);
	unmarshall_AL_TMultiChipParam(&in->tMCParam, read_cb, arg);
	unmarshall_int(&in->iQPTableDepth, read_cb, arg);
	{
		int16_t *pMeRange__ptr__ = (int16_t *)((uintptr_t)in->pMeRange);
		for (int i = 0; i < 4; i++)
			unmarshall_int16_t(&pMeRange__ptr__[i], read_cb, arg);
	}
	unmarshall_uint8_t(&in->uLog2MaxCuSize, read_cb, arg);
	unmarshall_uint8_t(&in->uLog2MinCuSize, read_cb, arg);
	unmarshall_uint8_t(&in->uLog2MaxTuSize, read_cb, arg);
	unmarshall_uint8_t(&in->uLog2MaxTuSkipSize, read_cb, arg);
	unmarshall_uint8_t(&in->uLog2MinTuSize, read_cb, arg);
	unmarshall_uint8_t(&in->uMaxTransfoDepthIntra, read_cb, arg);
	unmarshall_uint8_t(&in->uMaxTransfoDepthInter, read_cb, arg);
	unmarshall__Bool(&in->StrongIntraSmooth, read_cb, arg);
	unmarshall_AL_EEntropyMode(&in->eEntropyMode, read_cb, arg);
	unmarshall_AL_EWPMode(&in->eWPMode, read_cb, arg);
	unmarshall__Bool(&in->bUseGMV, read_cb, arg);
	unmarshall_AL_TRCParam(&in->tRCParam, read_cb, arg);
	unmarshall_AL_TGopParam(&in->tGopParam, read_cb, arg);
	unmarshall__Bool(&in->bNonRealtime, read_cb, arg);
	unmarshall__Bool(&in->bSubframeLatency, read_cb, arg);
	unmarshall_AL_ELdaCtrlMode(&in->eLdaCtrlMode, read_cb, arg);
	{
		int *LdaFactors__ptr__ = (int *)((uintptr_t)in->LdaFactors);
		for (int i = 0; i < 6; i++)
			unmarshall_int(&LdaFactors__ptr__[i], read_cb, arg);
	}
	unmarshall_uint16_t(&in->uMVVRange, read_cb, arg);
	unmarshall_int8_t(&in->MaxNumMergeCand, read_cb, arg);
	unmarshall_uint32_t(&in->zRcPluginDmaSize, read_cb, arg);
	unmarshall_AL_64U(&in->pRcPluginDmaContext, read_cb, arg);
	unmarshall__Bool(&in->bEnableOutputCrop, read_cb, arg);
	unmarshall_uint16_t(&in->uOutputCropWidth, read_cb, arg);
	unmarshall_uint16_t(&in->uOutputCropHeight, read_cb, arg);
	unmarshall_uint16_t(&in->uOutputCropPosX, read_cb, arg);
	unmarshall_uint16_t(&in->uOutputCropPosY, read_cb, arg);
	unmarshall__Bool(&in->bSrcSync, read_cb, arg);
	unmarshall_uint8_t(&in->uSrcSyncChanID, read_cb, arg);
	unmarshall__Bool(&in->bUseUniformSliceType, read_cb, arg);
	unmarshall_AL_EStartCodeBytesAlignedMode(&in->eStartCodeBytesAligned, read_cb, arg);
	unmarshall_AL_TAutoQPCtrl(&in->sUserAutoQPValues, read_cb, arg);
	unmarshall__Bool(&in->bUserAutoQP, read_cb, arg);
}
static int get_size_struct_t_ColorConfig()
{
	int res = 0;

	res += get_size_AL_EColourDescription();
	res += get_size_AL_ETransferCharacteristics();
	res += get_size_AL_EColourMatrixCoefficients();

	return res;
}
static void marshall_struct_t_ColorConfig(struct t_ColorConfig *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_AL_EColourDescription(&in->eColourDescription, write_cb, arg);
	marshall_AL_ETransferCharacteristics(&in->eTransferCharacteristics, write_cb, arg);
	marshall_AL_EColourMatrixCoefficients(&in->eColourMatrixCoeffs, write_cb, arg);
}
static void unmarshall_struct_t_ColorConfig(struct t_ColorConfig *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_AL_EColourDescription(&in->eColourDescription, read_cb, arg);
	unmarshall_AL_ETransferCharacteristics(&in->eTransferCharacteristics, read_cb, arg);
	unmarshall_AL_EColourMatrixCoefficients(&in->eColourMatrixCoeffs, read_cb, arg);
}
static int get_size_struct_t_EncSettings()
{
	int res = 0;

	res += 2 * get_size_AL_TEncChanParam();
	res += get_size__Bool();
	res += get_size_AL_EFillerCtrlMode();
	res += get_size_uint32_t();
	res += get_size_AL_TColorConfig();
	res += get_size_AL_EAspectRatio();
	res += get_size_AL_EScalingList();
	res += get_size__Bool();
	res += get_size__Bool();
	res += get_size__Bool();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_AL_EQpCtrlMode();
	res += get_size_AL_EQpTableMode();
	res += get_size_int();
	res += get_size_int();
	res += 1536 * get_size_uint8_t();
	res += 24 * get_size_uint8_t();
	res += 8 * get_size_uint8_t();
	res += get_size_uint8_t();
	res += get_size__Bool();
	res += get_size_int();
	res += get_size_int();
	res += get_size__Bool();
	res += get_size_AL_HANDLE();
	res += get_size__Bool();

	return res;
}
static void marshall_struct_t_EncSettings(struct t_EncSettings *in, void (*write_cb)(int, void *, void *), void *arg)
{
	{
		AL_TEncChanParam *tChParam__ptr__ = (AL_TEncChanParam *)((uintptr_t)in->tChParam);
		for (int i = 0; i < 2; i++)
			marshall_AL_TEncChanParam(&tChParam__ptr__[i], write_cb, arg);
	}
	marshall__Bool(&in->bEnableAUD, write_cb, arg);
	marshall_AL_EFillerCtrlMode(&in->eEnableFillerData, write_cb, arg);
	marshall_uint32_t(&in->uEnableSEI, write_cb, arg);
	marshall_AL_TColorConfig(&in->tColorConfig, write_cb, arg);
	marshall_AL_EAspectRatio(&in->eAspectRatio, write_cb, arg);
	marshall_AL_EScalingList(&in->eScalingList, write_cb, arg);
	marshall__Bool(&in->bDependentSlice, write_cb, arg);
	marshall__Bool(&in->bDisIntra, write_cb, arg);
	marshall__Bool(&in->bForceLoad, write_cb, arg);
	marshall_uint16_t(&in->uClipHrzRange, write_cb, arg);
	marshall_uint16_t(&in->uClipVrtRange, write_cb, arg);
	marshall_AL_EQpCtrlMode(&in->eQpCtrlMode, write_cb, arg);
	marshall_AL_EQpTableMode(&in->eQpTableMode, write_cb, arg);
	marshall_int(&in->NumView, write_cb, arg);
	marshall_int(&in->NumLayer, write_cb, arg);
	{
		uint8_t *ScalingList__ptr__ = (uint8_t *)((uintptr_t)in->ScalingList);
		for (int i = 0; i < 1536; i++)
			marshall_uint8_t(&ScalingList__ptr__[i], write_cb, arg);
	}
	{
		uint8_t *SclFlag__ptr__ = (uint8_t *)((uintptr_t)in->SclFlag);
		for (int i = 0; i < 24; i++)
			marshall_uint8_t(&SclFlag__ptr__[i], write_cb, arg);
	}
	{
		uint8_t *DcCoeff__ptr__ = (uint8_t *)((uintptr_t)in->DcCoeff);
		for (int i = 0; i < 8; i++)
			marshall_uint8_t(&DcCoeff__ptr__[i], write_cb, arg);
	}
	marshall_uint8_t(&in->DcCoeffFlag, write_cb, arg);
	marshall__Bool(&in->bEnableWatchdog, write_cb, arg);
	marshall_int(&in->LookAhead, write_cb, arg);
	marshall_int(&in->TwoPass, write_cb, arg);
	marshall__Bool(&in->bEnableFirstPassSceneChangeDetection, write_cb, arg);
	marshall_AL_HANDLE(&in->hRcPluginDmaContext, write_cb, arg);
	marshall__Bool(&in->bDiagnostic, write_cb, arg);
}
static void unmarshall_struct_t_EncSettings(struct t_EncSettings *in, void (*read_cb)(int, void *, void *), void *arg)
{
	{
		AL_TEncChanParam *tChParam__ptr__ = (AL_TEncChanParam *)((uintptr_t)in->tChParam);
		for (int i = 0; i < 2; i++)
			unmarshall_AL_TEncChanParam(&tChParam__ptr__[i], read_cb, arg);
	}
	unmarshall__Bool(&in->bEnableAUD, read_cb, arg);
	unmarshall_AL_EFillerCtrlMode(&in->eEnableFillerData, read_cb, arg);
	unmarshall_uint32_t(&in->uEnableSEI, read_cb, arg);
	unmarshall_AL_TColorConfig(&in->tColorConfig, read_cb, arg);
	unmarshall_AL_EAspectRatio(&in->eAspectRatio, read_cb, arg);
	unmarshall_AL_EScalingList(&in->eScalingList, read_cb, arg);
	unmarshall__Bool(&in->bDependentSlice, read_cb, arg);
	unmarshall__Bool(&in->bDisIntra, read_cb, arg);
	unmarshall__Bool(&in->bForceLoad, read_cb, arg);
	unmarshall_uint16_t(&in->uClipHrzRange, read_cb, arg);
	unmarshall_uint16_t(&in->uClipVrtRange, read_cb, arg);
	unmarshall_AL_EQpCtrlMode(&in->eQpCtrlMode, read_cb, arg);
	unmarshall_AL_EQpTableMode(&in->eQpTableMode, read_cb, arg);
	unmarshall_int(&in->NumView, read_cb, arg);
	unmarshall_int(&in->NumLayer, read_cb, arg);
	{
		uint8_t *ScalingList__ptr__ = (uint8_t *)((uintptr_t)in->ScalingList);
		for (int i = 0; i < 1536; i++)
			unmarshall_uint8_t(&ScalingList__ptr__[i], read_cb, arg);
	}
	{
		uint8_t *SclFlag__ptr__ = (uint8_t *)((uintptr_t)in->SclFlag);
		for (int i = 0; i < 24; i++)
			unmarshall_uint8_t(&SclFlag__ptr__[i], read_cb, arg);
	}
	{
		uint8_t *DcCoeff__ptr__ = (uint8_t *)((uintptr_t)in->DcCoeff);
		for (int i = 0; i < 8; i++)
			unmarshall_uint8_t(&DcCoeff__ptr__[i], read_cb, arg);
	}
	unmarshall_uint8_t(&in->DcCoeffFlag, read_cb, arg);
	unmarshall__Bool(&in->bEnableWatchdog, read_cb, arg);
	unmarshall_int(&in->LookAhead, read_cb, arg);
	unmarshall_int(&in->TwoPass, read_cb, arg);
	unmarshall__Bool(&in->bEnableFirstPassSceneChangeDetection, read_cb, arg);
	unmarshall_AL_HANDLE(&in->hRcPluginDmaContext, read_cb, arg);
	unmarshall__Bool(&in->bDiagnostic, read_cb, arg);
}
static int get_size_struct_msg_itf_create_encoder_req()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_AL_TEncSettings();

	return res;
}
static void marshall_struct_msg_itf_create_encoder_req(struct msg_itf_create_encoder_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hWrapper, write_cb, arg);
	marshall_AL_TEncSettings(&in->settings, write_cb, arg);
}
static void unmarshall_struct_msg_itf_create_encoder_req(struct msg_itf_create_encoder_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hWrapper, read_cb, arg);
	unmarshall_AL_TEncSettings(&in->settings, read_cb, arg);
}
static int get_size_struct_msg_itf_create_encoder_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_create_encoder_req();

	return res;
}
static void marshall_struct_msg_itf_create_encoder_req_full(struct msg_itf_create_encoder_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_create_encoder_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_create_encoder_req_full(struct msg_itf_create_encoder_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_create_encoder_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_create_encoder_reply()
{
	int res = 0;

	res += get_size_int32_t();
	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_create_encoder_reply(struct msg_itf_create_encoder_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_int32_t(&in->ret, write_cb, arg);
	marshall_uint64_t(&in->hEnc, write_cb, arg);
}
static void unmarshall_struct_msg_itf_create_encoder_reply(struct msg_itf_create_encoder_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_int32_t(&in->ret, read_cb, arg);
	unmarshall_uint64_t(&in->hEnc, read_cb, arg);
}
static int get_size_struct_msg_itf_create_encoder_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_create_encoder_reply();

	return res;
}
static void marshall_struct_msg_itf_create_encoder_reply_full(struct msg_itf_create_encoder_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_create_encoder_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_create_encoder_reply_full(struct msg_itf_create_encoder_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_create_encoder_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_destroy_encoder_req()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_destroy_encoder_req(struct msg_itf_destroy_encoder_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hEnc, write_cb, arg);
}
static void unmarshall_struct_msg_itf_destroy_encoder_req(struct msg_itf_destroy_encoder_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hEnc, read_cb, arg);
}
static int get_size_struct_msg_itf_destroy_encoder_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_destroy_encoder_req();

	return res;
}
static void marshall_struct_msg_itf_destroy_encoder_req_full(struct msg_itf_destroy_encoder_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_destroy_encoder_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_destroy_encoder_req_full(struct msg_itf_destroy_encoder_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_destroy_encoder_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_destroy_encoder_reply()
{
	int res = 0;

	res += get_size_uint32_t();

	return res;
}
static void marshall_struct_msg_itf_destroy_encoder_reply(struct msg_itf_destroy_encoder_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint32_t(&in->unused, write_cb, arg);
}
static void unmarshall_struct_msg_itf_destroy_encoder_reply(struct msg_itf_destroy_encoder_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint32_t(&in->unused, read_cb, arg);
}
static int get_size_struct_msg_itf_destroy_encoder_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_destroy_encoder_reply();

	return res;
}
static void marshall_struct_msg_itf_destroy_encoder_reply_full(struct msg_itf_destroy_encoder_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_destroy_encoder_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_destroy_encoder_reply_full(struct msg_itf_destroy_encoder_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_destroy_encoder_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_get_info_req()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_get_info_req(struct msg_itf_get_info_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hEnc, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_info_req(struct msg_itf_get_info_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hEnc, read_cb, arg);
}
static int get_size_struct_msg_itf_get_info_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_get_info_req();

	return res;
}
static void marshall_struct_msg_itf_get_info_req_full(struct msg_itf_get_info_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_get_info_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_info_req_full(struct msg_itf_get_info_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_get_info_req(&in->req, read_cb, arg);
}
static int get_size_struct_AL_TEncoderInfo()
{
	int res = 0;

	res += get_size_uint8_t();

	return res;
}
static void marshall_struct_AL_TEncoderInfo(struct AL_TEncoderInfo *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint8_t(&in->uNumCore, write_cb, arg);
}
static void unmarshall_struct_AL_TEncoderInfo(struct AL_TEncoderInfo *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint8_t(&in->uNumCore, read_cb, arg);
}
static int get_size_struct_msg_itf_get_info_reply()
{
	int res = 0;

	res += get_size_AL_TEncoderInfo();

	return res;
}
static void marshall_struct_msg_itf_get_info_reply(struct msg_itf_get_info_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_AL_TEncoderInfo(&in->tEncInfo, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_info_reply(struct msg_itf_get_info_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_AL_TEncoderInfo(&in->tEncInfo, read_cb, arg);
}
static int get_size_struct_msg_itf_get_info_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_get_info_reply();

	return res;
}
static void marshall_struct_msg_itf_get_info_reply_full(struct msg_itf_get_info_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_get_info_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_info_reply_full(struct msg_itf_get_info_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_get_info_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_push_stream_buffer_req()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_int32_t();
	res += get_size_uint64_t();
	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_push_stream_buffer_req(struct msg_itf_push_stream_buffer_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hEnc, write_cb, arg);
	marshall_uint64_t(&in->pStream, write_cb, arg);
	marshall_uint64_t(&in->pAddr, write_cb, arg);
	marshall_uint64_t(&in->uSize, write_cb, arg);
	marshall_int32_t(&in->iLayerID, write_cb, arg);
	marshall_uint64_t(&in->pAddrStats, write_cb, arg);
	marshall_uint64_t(&in->uSizeStats, write_cb, arg);
}
static void unmarshall_struct_msg_itf_push_stream_buffer_req(struct msg_itf_push_stream_buffer_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hEnc, read_cb, arg);
	unmarshall_uint64_t(&in->pStream, read_cb, arg);
	unmarshall_uint64_t(&in->pAddr, read_cb, arg);
	unmarshall_uint64_t(&in->uSize, read_cb, arg);
	unmarshall_int32_t(&in->iLayerID, read_cb, arg);
	unmarshall_uint64_t(&in->pAddrStats, read_cb, arg);
	unmarshall_uint64_t(&in->uSizeStats, read_cb, arg);
}
static int get_size_struct_msg_itf_push_stream_buffer_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_push_stream_buffer_req();

	return res;
}
static void marshall_struct_msg_itf_push_stream_buffer_req_full(struct msg_itf_push_stream_buffer_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_push_stream_buffer_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_push_stream_buffer_req_full(struct msg_itf_push_stream_buffer_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_push_stream_buffer_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_push_stream_buffer_reply()
{
	int res = 0;

	res += get_size_uint8_t();

	return res;
}
static void marshall_struct_msg_itf_push_stream_buffer_reply(struct msg_itf_push_stream_buffer_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint8_t(&in->res, write_cb, arg);
}
static void unmarshall_struct_msg_itf_push_stream_buffer_reply(struct msg_itf_push_stream_buffer_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint8_t(&in->res, read_cb, arg);
}
static int get_size_struct_msg_itf_push_stream_buffer_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_push_stream_buffer_reply();

	return res;
}
static void marshall_struct_msg_itf_push_stream_buffer_reply_full(struct msg_itf_push_stream_buffer_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_push_stream_buffer_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_push_stream_buffer_reply_full(struct msg_itf_push_stream_buffer_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_push_stream_buffer_reply(&in->reply, read_cb, arg);
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
static int get_size_struct_msg_itf_process_req()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += 6 * get_size_struct_chunk_info();
	res += get_size_AL_TDimension();
	res += 9 * get_size_AL_TPlane();
	res += get_size_TFourCC();
	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_int32_t();

	return res;
}
static void marshall_struct_msg_itf_process_req(struct msg_itf_process_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hEnc, write_cb, arg);
	marshall_uint64_t(&in->pFrame, write_cb, arg);
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
	marshall_uint64_t(&in->pQpTable, write_cb, arg);
	marshall_uint64_t(&in->pAddr, write_cb, arg);
	marshall_uint64_t(&in->uSize, write_cb, arg);
	marshall_int32_t(&in->iLayerID, write_cb, arg);
}
static void unmarshall_struct_msg_itf_process_req(struct msg_itf_process_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hEnc, read_cb, arg);
	unmarshall_uint64_t(&in->pFrame, read_cb, arg);
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
	unmarshall_uint64_t(&in->pQpTable, read_cb, arg);
	unmarshall_uint64_t(&in->pAddr, read_cb, arg);
	unmarshall_uint64_t(&in->uSize, read_cb, arg);
	unmarshall_int32_t(&in->iLayerID, read_cb, arg);
}
static int get_size_struct_msg_itf_process_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_process_req();

	return res;
}
static void marshall_struct_msg_itf_process_req_full(struct msg_itf_process_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_process_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_process_req_full(struct msg_itf_process_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_process_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_process_reply()
{
	int res = 0;

	res += get_size_uint8_t();

	return res;
}
static void marshall_struct_msg_itf_process_reply(struct msg_itf_process_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint8_t(&in->res, write_cb, arg);
}
static void unmarshall_struct_msg_itf_process_reply(struct msg_itf_process_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint8_t(&in->res, read_cb, arg);
}
static int get_size_struct_msg_itf_process_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_process_reply();

	return res;
}
static void marshall_struct_msg_itf_process_reply_full(struct msg_itf_process_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_process_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_process_reply_full(struct msg_itf_process_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_process_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_get_rec_req()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_int32_t();

	return res;
}
static void marshall_struct_msg_itf_get_rec_req(struct msg_itf_get_rec_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hEnc, write_cb, arg);
	marshall_int32_t(&in->iLayerID, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_rec_req(struct msg_itf_get_rec_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hEnc, read_cb, arg);
	unmarshall_int32_t(&in->iLayerID, read_cb, arg);
}
static int get_size_struct_msg_itf_get_rec_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_get_rec_req();

	return res;
}
static void marshall_struct_msg_itf_get_rec_req_full(struct msg_itf_get_rec_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_get_rec_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_rec_req_full(struct msg_itf_get_rec_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_get_rec_req(&in->req, read_cb, arg);
}
static int get_size_struct_AL_TReconstructedInfo()
{
	int res = 0;

	res += get_size_uint32_t();
	res += get_size_AL_EPicStruct();
	res += get_size_uint32_t();
	res += get_size_AL_TDimension();

	return res;
}
static void marshall_struct_AL_TReconstructedInfo(struct AL_TReconstructedInfo *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint32_t(&in->uID, write_cb, arg);
	marshall_AL_EPicStruct(&in->ePicStruct, write_cb, arg);
	marshall_uint32_t(&in->iPOC, write_cb, arg);
	marshall_AL_TDimension(&in->tPicDim, write_cb, arg);
}
static void unmarshall_struct_AL_TReconstructedInfo(struct AL_TReconstructedInfo *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint32_t(&in->uID, read_cb, arg);
	unmarshall_AL_EPicStruct(&in->ePicStruct, read_cb, arg);
	unmarshall_uint32_t(&in->iPOC, read_cb, arg);
	unmarshall_AL_TDimension(&in->tPicDim, read_cb, arg);
}
static int get_size_struct_msg_itf_get_rec_reply()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_struct_chunk_info();
	res += get_size_AL_TReconstructedInfo();
	res += get_size_uint8_t();
	res += get_size_int32_t();

	return res;
}
static void marshall_struct_msg_itf_get_rec_reply(struct msg_itf_get_rec_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->pRec, write_cb, arg);
	marshall_struct_chunk_info(&in->chunk, write_cb, arg);
	marshall_AL_TReconstructedInfo(&in->recInfo, write_cb, arg);
	marshall_uint8_t(&in->res, write_cb, arg);
	marshall_int32_t(&in->iLayerID, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_rec_reply(struct msg_itf_get_rec_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->pRec, read_cb, arg);
	unmarshall_struct_chunk_info(&in->chunk, read_cb, arg);
	unmarshall_AL_TReconstructedInfo(&in->recInfo, read_cb, arg);
	unmarshall_uint8_t(&in->res, read_cb, arg);
	unmarshall_int32_t(&in->iLayerID, read_cb, arg);
}
static int get_size_struct_msg_itf_get_rec_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_get_rec_reply();

	return res;
}
static void marshall_struct_msg_itf_get_rec_reply_full(struct msg_itf_get_rec_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_get_rec_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_rec_reply_full(struct msg_itf_get_rec_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_get_rec_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_get_last_error_req()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_get_last_error_req(struct msg_itf_get_last_error_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hEnc, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_last_error_req(struct msg_itf_get_last_error_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hEnc, read_cb, arg);
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
static int get_size_struct_msg_itf_release_rec_req()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_AL_TReconstructedInfo();
	res += get_size_int32_t();

	return res;
}
static void marshall_struct_msg_itf_release_rec_req(struct msg_itf_release_rec_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hEnc, write_cb, arg);
	marshall_uint64_t(&in->pRec, write_cb, arg);
	marshall_AL_TReconstructedInfo(&in->recInfo, write_cb, arg);
	marshall_int32_t(&in->iLayerID, write_cb, arg);
}
static void unmarshall_struct_msg_itf_release_rec_req(struct msg_itf_release_rec_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hEnc, read_cb, arg);
	unmarshall_uint64_t(&in->pRec, read_cb, arg);
	unmarshall_AL_TReconstructedInfo(&in->recInfo, read_cb, arg);
	unmarshall_int32_t(&in->iLayerID, read_cb, arg);
}
static int get_size_struct_msg_itf_release_rec_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_release_rec_req();

	return res;
}
static void marshall_struct_msg_itf_release_rec_req_full(struct msg_itf_release_rec_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_release_rec_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_release_rec_req_full(struct msg_itf_release_rec_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_release_rec_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_release_rec_reply()
{
	int res = 0;

	res += get_size_uint32_t();

	return res;
}
static void marshall_struct_msg_itf_release_rec_reply(struct msg_itf_release_rec_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint32_t(&in->unused, write_cb, arg);
}
static void unmarshall_struct_msg_itf_release_rec_reply(struct msg_itf_release_rec_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint32_t(&in->unused, read_cb, arg);
}
static int get_size_struct_msg_itf_release_rec_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_release_rec_reply();

	return res;
}
static void marshall_struct_msg_itf_release_rec_reply_full(struct msg_itf_release_rec_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_release_rec_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_release_rec_reply_full(struct msg_itf_release_rec_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_release_rec_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_get_last_error_reply()
{
	int res = 0;

	res += get_size_int32_t();

	return res;
}
static void marshall_struct_msg_itf_get_last_error_reply(struct msg_itf_get_last_error_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_int32_t(&in->res, write_cb, arg);
}
static void unmarshall_struct_msg_itf_get_last_error_reply(struct msg_itf_get_last_error_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_int32_t(&in->res, read_cb, arg);
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
static int get_size_struct_msg_itf_notify_req()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_int32_t();
	res += get_size_int32_t();

	return res;
}
static void marshall_struct_msg_itf_notify_req(struct msg_itf_notify_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hEnc, write_cb, arg);
	marshall_uint32_t(&in->cmd, write_cb, arg);
	marshall_uint32_t(&in->iAhead, write_cb, arg);
	marshall_uint32_t(&in->iNumFrame, write_cb, arg);
	marshall_int32_t(&in->GMV_x, write_cb, arg);
	marshall_int32_t(&in->GMV_y, write_cb, arg);
}
static void unmarshall_struct_msg_itf_notify_req(struct msg_itf_notify_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hEnc, read_cb, arg);
	unmarshall_uint32_t(&in->cmd, read_cb, arg);
	unmarshall_uint32_t(&in->iAhead, read_cb, arg);
	unmarshall_uint32_t(&in->iNumFrame, read_cb, arg);
	unmarshall_int32_t(&in->GMV_x, read_cb, arg);
	unmarshall_int32_t(&in->GMV_y, read_cb, arg);
}
static int get_size_struct_msg_itf_notify_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_notify_req();

	return res;
}
static void marshall_struct_msg_itf_notify_req_full(struct msg_itf_notify_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_notify_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_notify_req_full(struct msg_itf_notify_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_notify_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_notify_reply()
{
	int res = 0;

	res += get_size_int32_t();

	return res;
}
static void marshall_struct_msg_itf_notify_reply(struct msg_itf_notify_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_int32_t(&in->res, write_cb, arg);
}
static void unmarshall_struct_msg_itf_notify_reply(struct msg_itf_notify_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_int32_t(&in->res, read_cb, arg);
}
static int get_size_struct_msg_itf_notify_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_notify_reply();

	return res;
}
static void marshall_struct_msg_itf_notify_reply_full(struct msg_itf_notify_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_notify_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_notify_reply_full(struct msg_itf_notify_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_notify_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_smart_req()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint32_t();
	res += get_size__Bool();
	res += get_size__Bool();
	res += get_size_AL_TAutoQPCtrl();
	res += get_size_int32_t();
	res += get_size_int32_t();
	res += get_size_int32_t();
	res += get_size_int32_t();
	res += get_size_int32_t();
	res += get_size_int32_t();
	res += get_size_uint16_t();
	res += get_size_uint16_t();
	res += get_size_int16_t();
	res += get_size_int16_t();
	res += get_size_int16_t();
	res += get_size_int16_t();
	res += get_size_AL_ESliceType();
	res += get_size_int16_t();
	res += get_size_int16_t();
	res += get_size_AL_TDimension();
	res += get_size_int8_t();
	res += get_size_int8_t();
	res += get_size_int8_t();
	res += get_size_int8_t();
	res += get_size__Bool();

	return res;
}
static void marshall_struct_msg_itf_smart_req(struct msg_itf_smart_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hEnc, write_cb, arg);
	marshall_uint32_t(&in->cmd, write_cb, arg);
	marshall__Bool(&in->costMode, write_cb, arg);
	marshall__Bool(&in->bUserAutoQP, write_cb, arg);
	marshall_AL_TAutoQPCtrl(&in->userAutoQPValues, write_cb, arg);
	marshall_int32_t(&in->iGopLength, write_cb, arg);
	marshall_int32_t(&in->iNumB, write_cb, arg);
	marshall_int32_t(&in->iFreqIDR, write_cb, arg);
	marshall_int32_t(&in->iBitRate, write_cb, arg);
	marshall_int32_t(&in->iTargetBitRate, write_cb, arg);
	marshall_int32_t(&in->iMaxBitRate, write_cb, arg);
	marshall_uint16_t(&in->uFrameRate, write_cb, arg);
	marshall_uint16_t(&in->uClkRatio, write_cb, arg);
	marshall_int16_t(&in->iQP, write_cb, arg);
	marshall_int16_t(&in->iQPOffset, write_cb, arg);
	marshall_int16_t(&in->iMinQP, write_cb, arg);
	marshall_int16_t(&in->iMaxQP, write_cb, arg);
	marshall_AL_ESliceType(&in->sliceType, write_cb, arg);
	marshall_int16_t(&in->uIPDelta, write_cb, arg);
	marshall_int16_t(&in->uPBDelta, write_cb, arg);
	marshall_AL_TDimension(&in->tDim, write_cb, arg);
	marshall_int8_t(&in->iBetaOffset, write_cb, arg);
	marshall_int8_t(&in->iTcOffset, write_cb, arg);
	marshall_int8_t(&in->iQp1Offset, write_cb, arg);
	marshall_int8_t(&in->iQp2Offset, write_cb, arg);
	marshall__Bool(&in->useAutoQP, write_cb, arg);
}
static void unmarshall_struct_msg_itf_smart_req(struct msg_itf_smart_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hEnc, read_cb, arg);
	unmarshall_uint32_t(&in->cmd, read_cb, arg);
	unmarshall__Bool(&in->costMode, read_cb, arg);
	unmarshall__Bool(&in->bUserAutoQP, read_cb, arg);
	unmarshall_AL_TAutoQPCtrl(&in->userAutoQPValues, read_cb, arg);
	unmarshall_int32_t(&in->iGopLength, read_cb, arg);
	unmarshall_int32_t(&in->iNumB, read_cb, arg);
	unmarshall_int32_t(&in->iFreqIDR, read_cb, arg);
	unmarshall_int32_t(&in->iBitRate, read_cb, arg);
	unmarshall_int32_t(&in->iTargetBitRate, read_cb, arg);
	unmarshall_int32_t(&in->iMaxBitRate, read_cb, arg);
	unmarshall_uint16_t(&in->uFrameRate, read_cb, arg);
	unmarshall_uint16_t(&in->uClkRatio, read_cb, arg);
	unmarshall_int16_t(&in->iQP, read_cb, arg);
	unmarshall_int16_t(&in->iQPOffset, read_cb, arg);
	unmarshall_int16_t(&in->iMinQP, read_cb, arg);
	unmarshall_int16_t(&in->iMaxQP, read_cb, arg);
	unmarshall_AL_ESliceType(&in->sliceType, read_cb, arg);
	unmarshall_int16_t(&in->uIPDelta, read_cb, arg);
	unmarshall_int16_t(&in->uPBDelta, read_cb, arg);
	unmarshall_AL_TDimension(&in->tDim, read_cb, arg);
	unmarshall_int8_t(&in->iBetaOffset, read_cb, arg);
	unmarshall_int8_t(&in->iTcOffset, read_cb, arg);
	unmarshall_int8_t(&in->iQp1Offset, read_cb, arg);
	unmarshall_int8_t(&in->iQp2Offset, read_cb, arg);
	unmarshall__Bool(&in->useAutoQP, read_cb, arg);
}
static int get_size_struct_msg_itf_smart_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_smart_req();

	return res;
}
static void marshall_struct_msg_itf_smart_req_full(struct msg_itf_smart_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_smart_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_smart_req_full(struct msg_itf_smart_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_smart_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_smart_reply()
{
	int res = 0;

	res += get_size_int32_t();

	return res;
}
static void marshall_struct_msg_itf_smart_reply(struct msg_itf_smart_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_int32_t(&in->res, write_cb, arg);
}
static void unmarshall_struct_msg_itf_smart_reply(struct msg_itf_smart_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_int32_t(&in->res, read_cb, arg);
}
static int get_size_struct_msg_itf_smart_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_smart_reply();

	return res;
}
static void marshall_struct_msg_itf_smart_reply_full(struct msg_itf_smart_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_smart_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_smart_reply_full(struct msg_itf_smart_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_smart_reply(&in->reply, read_cb, arg);
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
static int get_size_struct_msg_itf_hdr_req()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_AL_THDRSEIs();

	return res;
}
static void marshall_struct_msg_itf_hdr_req(struct msg_itf_hdr_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hEnc, write_cb, arg);
	marshall_AL_THDRSEIs(&in->pHDRSEIs, write_cb, arg);
}
static void unmarshall_struct_msg_itf_hdr_req(struct msg_itf_hdr_req *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hEnc, read_cb, arg);
	unmarshall_AL_THDRSEIs(&in->pHDRSEIs, read_cb, arg);
}
static int get_size_struct_msg_itf_hdr_req_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_hdr_req();

	return res;
}
static void marshall_struct_msg_itf_hdr_req_full(struct msg_itf_hdr_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_hdr_req(&in->req, write_cb, arg);
}
static void unmarshall_struct_msg_itf_hdr_req_full(struct msg_itf_hdr_req_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_hdr_req(&in->req, read_cb, arg);
}
static int get_size_struct_msg_itf_hdr_reply()
{
	int res = 0;

	res += get_size_int32_t();

	return res;
}
static void marshall_struct_msg_itf_hdr_reply(struct msg_itf_hdr_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_int32_t(&in->res, write_cb, arg);
}
static void unmarshall_struct_msg_itf_hdr_reply(struct msg_itf_hdr_reply *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_int32_t(&in->res, read_cb, arg);
}
static int get_size_struct_msg_itf_hdr_reply_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_hdr_reply();

	return res;
}
static void marshall_struct_msg_itf_hdr_reply_full(struct msg_itf_hdr_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_hdr_reply(&in->reply, write_cb, arg);
}
static void unmarshall_struct_msg_itf_hdr_reply_full(struct msg_itf_hdr_reply_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_hdr_reply(&in->reply, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_buffer_refcount()
{
	int res = 0;

	res += get_size_uint64_t();

	return res;
}
static void marshall_struct_msg_itf_evt_buffer_refcount(struct msg_itf_evt_buffer_refcount *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->pBuf, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_buffer_refcount(struct msg_itf_evt_buffer_refcount *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->pBuf, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_buffer_refcount_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_evt_buffer_refcount();

	return res;
}
static void marshall_struct_msg_itf_evt_buffer_refcount_full(struct msg_itf_evt_buffer_refcount_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_evt_buffer_refcount(&in->event, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_buffer_refcount_full(struct msg_itf_evt_buffer_refcount_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_evt_buffer_refcount(&in->event, read_cb, arg);
}
static int get_size_struct_AL_TStreamSection()
{
	int res = 0;

	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_AL_ESectionFlags();

	return res;
}
static void marshall_struct_AL_TStreamSection(struct AL_TStreamSection *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint32_t(&in->uOffset, write_cb, arg);
	marshall_uint32_t(&in->uLength, write_cb, arg);
	marshall_AL_ESectionFlags(&in->eFlags, write_cb, arg);
}
static void unmarshall_struct_AL_TStreamSection(struct AL_TStreamSection *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint32_t(&in->uOffset, read_cb, arg);
	unmarshall_uint32_t(&in->uLength, read_cb, arg);
	unmarshall_AL_ESectionFlags(&in->eFlags, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_end_encoding()
{
	int res = 0;

	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_int32_t();
	res += get_size_uint16_t();
	res += 8 * get_size_AL_TStreamSection();
	res += get_size_uint16_t();
	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_uint64_t();
	res += get_size_AL_ESliceType();
	res += get_size__Bool();

	return res;
}
static void marshall_struct_msg_itf_evt_end_encoding(struct msg_itf_evt_end_encoding *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint64_t(&in->hWrapper, write_cb, arg);
	marshall_uint64_t(&in->pStream, write_cb, arg);
	marshall_uint64_t(&in->pSrc, write_cb, arg);
	marshall_int32_t(&in->iLayerID, write_cb, arg);
	marshall_uint16_t(&in->uNumSection, write_cb, arg);
	{
		AL_TStreamSection *sections__ptr__ = (AL_TStreamSection *)((uintptr_t)in->sections);
		for (int i = 0; i < 8; i++)
			marshall_AL_TStreamSection(&sections__ptr__[i], write_cb, arg);
	}
	marshall_uint16_t(&in->uNumSectionInBuffer, write_cb, arg);
	marshall_uint64_t(&in->pSectionBufferAddr, write_cb, arg);
	marshall_uint64_t(&in->uSectionBufferSize, write_cb, arg);
	marshall_uint64_t(&in->uSectionBufferOffset, write_cb, arg);
	marshall_AL_ESliceType(&in->eType, write_cb, arg);
	marshall__Bool(&in->bSkipped, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_end_encoding(struct msg_itf_evt_end_encoding *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint64_t(&in->hWrapper, read_cb, arg);
	unmarshall_uint64_t(&in->pStream, read_cb, arg);
	unmarshall_uint64_t(&in->pSrc, read_cb, arg);
	unmarshall_int32_t(&in->iLayerID, read_cb, arg);
	unmarshall_uint16_t(&in->uNumSection, read_cb, arg);
	{
		AL_TStreamSection *sections__ptr__ = (AL_TStreamSection *)((uintptr_t)in->sections);
		for (int i = 0; i < 8; i++)
			unmarshall_AL_TStreamSection(&sections__ptr__[i], read_cb, arg);
	}
	unmarshall_uint16_t(&in->uNumSectionInBuffer, read_cb, arg);
	unmarshall_uint64_t(&in->pSectionBufferAddr, read_cb, arg);
	unmarshall_uint64_t(&in->uSectionBufferSize, read_cb, arg);
	unmarshall_uint64_t(&in->uSectionBufferOffset, read_cb, arg);
	unmarshall_AL_ESliceType(&in->eType, read_cb, arg);
	unmarshall__Bool(&in->bSkipped, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_end_encoding_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_evt_end_encoding();

	return res;
}
static void marshall_struct_msg_itf_evt_end_encoding_full(struct msg_itf_evt_end_encoding_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_evt_end_encoding(&in->event, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_end_encoding_full(struct msg_itf_evt_end_encoding_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_evt_end_encoding(&in->event, read_cb, arg);
}
static int get_size_struct_al_t_RateCtrl_Statistics()
{
	int res = 0;

	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_uint32_t();
	res += get_size_int32_t();
	res += get_size_int16_t();
	res += get_size_int16_t();

	return res;
}
static void marshall_struct_al_t_RateCtrl_Statistics(struct al_t_RateCtrl_Statistics *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_uint32_t(&in->uNumLCUs, write_cb, arg);
	marshall_uint32_t(&in->uNumBytes, write_cb, arg);
	marshall_uint32_t(&in->uNumBins, write_cb, arg);
	marshall_uint32_t(&in->uNumIntra, write_cb, arg);
	marshall_uint32_t(&in->uNumSkip, write_cb, arg);
	marshall_uint32_t(&in->uNumCU8x8, write_cb, arg);
	marshall_uint32_t(&in->uNumCU16x16, write_cb, arg);
	marshall_uint32_t(&in->uNumCU32x32, write_cb, arg);
	marshall_int32_t(&in->uSumQP, write_cb, arg);
	marshall_int16_t(&in->uMinQP, write_cb, arg);
	marshall_int16_t(&in->uMaxQP, write_cb, arg);
}
static void unmarshall_struct_al_t_RateCtrl_Statistics(struct al_t_RateCtrl_Statistics *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_uint32_t(&in->uNumLCUs, read_cb, arg);
	unmarshall_uint32_t(&in->uNumBytes, read_cb, arg);
	unmarshall_uint32_t(&in->uNumBins, read_cb, arg);
	unmarshall_uint32_t(&in->uNumIntra, read_cb, arg);
	unmarshall_uint32_t(&in->uNumSkip, read_cb, arg);
	unmarshall_uint32_t(&in->uNumCU8x8, read_cb, arg);
	unmarshall_uint32_t(&in->uNumCU16x16, read_cb, arg);
	unmarshall_uint32_t(&in->uNumCU32x32, read_cb, arg);
	unmarshall_int32_t(&in->uSumQP, read_cb, arg);
	unmarshall_int16_t(&in->uMinQP, read_cb, arg);
	unmarshall_int16_t(&in->uMaxQP, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_end_encoding_with_stat()
{
	int res = 0;

	res += get_size_struct_msg_itf_evt_end_encoding();
	res += get_size__Bool();
	res += get_size_AL_RateCtrl_Statistics();

	return res;
}
static void marshall_struct_msg_itf_evt_end_encoding_with_stat(struct msg_itf_evt_end_encoding_with_stat *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_end_encoding(&in->end_encoding, write_cb, arg);
	marshall__Bool(&in->bFilled, write_cb, arg);
	marshall_AL_RateCtrl_Statistics(&in->stats, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_end_encoding_with_stat(struct msg_itf_evt_end_encoding_with_stat *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_end_encoding(&in->end_encoding, read_cb, arg);
	unmarshall__Bool(&in->bFilled, read_cb, arg);
	unmarshall_AL_RateCtrl_Statistics(&in->stats, read_cb, arg);
}
static int get_size_struct_msg_itf_evt_end_encoding_with_stat_full()
{
	int res = 0;

	res += get_size_struct_msg_itf_header();
	res += get_size_struct_msg_itf_evt_end_encoding_with_stat();

	return res;
}
static void marshall_struct_msg_itf_evt_end_encoding_with_stat_full(struct msg_itf_evt_end_encoding_with_stat_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(&in->hdr, write_cb, arg);
	marshall_struct_msg_itf_evt_end_encoding_with_stat(&in->event, write_cb, arg);
}
static void unmarshall_struct_msg_itf_evt_end_encoding_with_stat_full(struct msg_itf_evt_end_encoding_with_stat_full *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(&in->hdr, read_cb, arg);
	unmarshall_struct_msg_itf_evt_end_encoding_with_stat(&in->event, read_cb, arg);
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
static int get_size_enum_AL_e_VideoMode()
{
	return sizeof(enum AL_e_VideoMode);
}
static void marshall_enum_AL_e_VideoMode(enum AL_e_VideoMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_enum_AL_e_VideoMode(enum AL_e_VideoMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_enum_e_EntropyMode()
{
	return sizeof(enum e_EntropyMode);
}
static void marshall_enum_e_EntropyMode(enum e_EntropyMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_enum_e_EntropyMode(enum e_EntropyMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_enum_e_WPMode()
{
	return sizeof(enum e_WPMode);
}
static void marshall_enum_e_WPMode(enum e_WPMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_enum_e_WPMode(enum e_WPMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_enum_e_StartCodeBytesAlignedMode()
{
	return sizeof(enum e_StartCodeBytesAlignedMode);
}
static void marshall_enum_e_StartCodeBytesAlignedMode(enum e_StartCodeBytesAlignedMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_enum_e_StartCodeBytesAlignedMode(enum e_StartCodeBytesAlignedMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_enum_e_FillerCtrlMode()
{
	return sizeof(enum e_FillerCtrlMode);
}
static void marshall_enum_e_FillerCtrlMode(enum e_FillerCtrlMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_enum_e_FillerCtrlMode(enum e_FillerCtrlMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_enum_e_ColourDescription()
{
	return sizeof(enum e_ColourDescription);
}
static void marshall_enum_e_ColourDescription(enum e_ColourDescription *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_enum_e_ColourDescription(enum e_ColourDescription *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_enum_e_TransferCharacteristics()
{
	return sizeof(enum e_TransferCharacteristics);
}
static void marshall_enum_e_TransferCharacteristics(enum e_TransferCharacteristics *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_enum_e_TransferCharacteristics(enum e_TransferCharacteristics *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_enum_e_ColourMatrixCoefficients()
{
	return sizeof(enum e_ColourMatrixCoefficients);
}
static void marshall_enum_e_ColourMatrixCoefficients(enum e_ColourMatrixCoefficients *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_enum_e_ColourMatrixCoefficients(enum e_ColourMatrixCoefficients *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_enum_e_AspectRatio()
{
	return sizeof(enum e_AspectRatio);
}
static void marshall_enum_e_AspectRatio(enum e_AspectRatio *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_enum_e_AspectRatio(enum e_AspectRatio *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_enum_e_ScalingList()
{
	return sizeof(enum e_ScalingList);
}
static void marshall_enum_e_ScalingList(enum e_ScalingList *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_enum_e_ScalingList(enum e_ScalingList *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_enum_e_QpCtrlMode()
{
	return sizeof(enum e_QpCtrlMode);
}
static void marshall_enum_e_QpCtrlMode(enum e_QpCtrlMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_enum_e_QpCtrlMode(enum e_QpCtrlMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_enum_e_QpTableMode()
{
	return sizeof(enum e_QpTableMode);
}
static void marshall_enum_e_QpTableMode(enum e_QpTableMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_enum_e_QpTableMode(enum e_QpTableMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_enum_e_PicStruct()
{
	return sizeof(enum e_PicStruct);
}
static void marshall_enum_e_PicStruct(enum e_PicStruct *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_enum_e_PicStruct(enum e_PicStruct *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_enum_e_SliceType()
{
	return sizeof(enum e_SliceType);
}
static void marshall_enum_e_SliceType(enum e_SliceType *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_enum_e_SliceType(enum e_SliceType *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EVideoMode()
{
	return sizeof(AL_EVideoMode);
}
static void marshall_AL_EVideoMode(AL_EVideoMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EVideoMode(AL_EVideoMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EPicFormat()
{
	return sizeof(AL_EPicFormat);
}
static void marshall_AL_EPicFormat(AL_EPicFormat *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EPicFormat(AL_EPicFormat *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_ESrcMode()
{
	return sizeof(AL_ESrcMode);
}
static void marshall_AL_ESrcMode(AL_ESrcMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_ESrcMode(AL_ESrcMode *in, void (*read_cb)(int, void *, void *), void *arg)
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
static int get_size_AL_EChEncOption()
{
	return sizeof(AL_EChEncOption);
}
static void marshall_AL_EChEncOption(AL_EChEncOption *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EChEncOption(AL_EChEncOption *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EChEncTool()
{
	return sizeof(AL_EChEncTool);
}
static void marshall_AL_EChEncTool(AL_EChEncTool *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EChEncTool(AL_EChEncTool *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EMultiChipClipMode()
{
	return sizeof(AL_EMultiChipClipMode);
}
static void marshall_AL_EMultiChipClipMode(AL_EMultiChipClipMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EMultiChipClipMode(AL_EMultiChipClipMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_TMultiChipParam()
{
	return get_size_struct_AL_TMultiChipParam();
}
static void marshall_AL_TMultiChipParam(AL_TMultiChipParam *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TMultiChipParam((struct AL_TMultiChipParam *) in, write_cb, arg);
}
static void unmarshall_AL_TMultiChipParam(AL_TMultiChipParam *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TMultiChipParam((struct AL_TMultiChipParam *) in, read_cb, arg);
}
static int get_size_AL_EEntropyMode()
{
	return sizeof(AL_EEntropyMode);
}
static void marshall_AL_EEntropyMode(AL_EEntropyMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EEntropyMode(AL_EEntropyMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EWPMode()
{
	return sizeof(AL_EWPMode);
}
static void marshall_AL_EWPMode(AL_EWPMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EWPMode(AL_EWPMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_ERateCtrlMode()
{
	return sizeof(AL_ERateCtrlMode);
}
static void marshall_AL_ERateCtrlMode(AL_ERateCtrlMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_ERateCtrlMode(AL_ERateCtrlMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_ERateCtrlOption()
{
	return sizeof(AL_ERateCtrlOption);
}
static void marshall_AL_ERateCtrlOption(AL_ERateCtrlOption *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_ERateCtrlOption(AL_ERateCtrlOption *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_TRCParam()
{
	return get_size_struct_AL_TRCParam();
}
static void marshall_AL_TRCParam(AL_TRCParam *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TRCParam((struct AL_TRCParam *) in, write_cb, arg);
}
static void unmarshall_AL_TRCParam(AL_TRCParam *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TRCParam((struct AL_TRCParam *) in, read_cb, arg);
}
static int get_size_AL_EGopCtrlMode()
{
	return sizeof(AL_EGopCtrlMode);
}
static void marshall_AL_EGopCtrlMode(AL_EGopCtrlMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EGopCtrlMode(AL_EGopCtrlMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EGdrMode()
{
	return sizeof(AL_EGdrMode);
}
static void marshall_AL_EGdrMode(AL_EGdrMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EGdrMode(AL_EGdrMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_TGopParam()
{
	return get_size_struct_AL_TGopParam();
}
static void marshall_AL_TGopParam(AL_TGopParam *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TGopParam((struct AL_TGopParam *) in, write_cb, arg);
}
static void unmarshall_AL_TGopParam(AL_TGopParam *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TGopParam((struct AL_TGopParam *) in, read_cb, arg);
}
static int get_size_AL_ELdaCtrlMode()
{
	return sizeof(AL_ELdaCtrlMode);
}
static void marshall_AL_ELdaCtrlMode(AL_ELdaCtrlMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_ELdaCtrlMode(AL_ELdaCtrlMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EStartCodeBytesAlignedMode()
{
	return sizeof(AL_EStartCodeBytesAlignedMode);
}
static void marshall_AL_EStartCodeBytesAlignedMode(AL_EStartCodeBytesAlignedMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EStartCodeBytesAlignedMode(AL_EStartCodeBytesAlignedMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_TAutoQPCtrl()
{
	return get_size_struct_AL_TAutoQPCtrl();
}
static void marshall_AL_TAutoQPCtrl(AL_TAutoQPCtrl *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TAutoQPCtrl((struct AL_TAutoQPCtrl *) in, write_cb, arg);
}
static void unmarshall_AL_TAutoQPCtrl(AL_TAutoQPCtrl *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TAutoQPCtrl((struct AL_TAutoQPCtrl *) in, read_cb, arg);
}
static int get_size_AL_TEncChanParam()
{
	return get_size_struct_AL_TEncChanParam();
}
static void marshall_AL_TEncChanParam(AL_TEncChanParam *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TEncChanParam((struct AL_TEncChanParam *) in, write_cb, arg);
}
static void unmarshall_AL_TEncChanParam(AL_TEncChanParam *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TEncChanParam((struct AL_TEncChanParam *) in, read_cb, arg);
}
static int get_size_AL_EFillerCtrlMode()
{
	return sizeof(AL_EFillerCtrlMode);
}
static void marshall_AL_EFillerCtrlMode(AL_EFillerCtrlMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EFillerCtrlMode(AL_EFillerCtrlMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
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
static int get_size_AL_TColorConfig()
{
	return get_size_struct_t_ColorConfig();
}
static void marshall_AL_TColorConfig(AL_TColorConfig *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_t_ColorConfig((struct t_ColorConfig *) in, write_cb, arg);
}
static void unmarshall_AL_TColorConfig(AL_TColorConfig *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_t_ColorConfig((struct t_ColorConfig *) in, read_cb, arg);
}
static int get_size_AL_EAspectRatio()
{
	return sizeof(AL_EAspectRatio);
}
static void marshall_AL_EAspectRatio(AL_EAspectRatio *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EAspectRatio(AL_EAspectRatio *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EScalingList()
{
	return sizeof(AL_EScalingList);
}
static void marshall_AL_EScalingList(AL_EScalingList *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EScalingList(AL_EScalingList *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EQpCtrlMode()
{
	return sizeof(AL_EQpCtrlMode);
}
static void marshall_AL_EQpCtrlMode(AL_EQpCtrlMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EQpCtrlMode(AL_EQpCtrlMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_EQpTableMode()
{
	return sizeof(AL_EQpTableMode);
}
static void marshall_AL_EQpTableMode(AL_EQpTableMode *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_EQpTableMode(AL_EQpTableMode *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_TEncSettings()
{
	return get_size_struct_t_EncSettings();
}
static void marshall_AL_TEncSettings(AL_TEncSettings *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_t_EncSettings((struct t_EncSettings *) in, write_cb, arg);
}
static void unmarshall_AL_TEncSettings(AL_TEncSettings *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_t_EncSettings((struct t_EncSettings *) in, read_cb, arg);
}
static int get_size_AL_TEncoderInfo()
{
	return get_size_struct_AL_TEncoderInfo();
}
static void marshall_AL_TEncoderInfo(AL_TEncoderInfo *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TEncoderInfo((struct AL_TEncoderInfo *) in, write_cb, arg);
}
static void unmarshall_AL_TEncoderInfo(AL_TEncoderInfo *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TEncoderInfo((struct AL_TEncoderInfo *) in, read_cb, arg);
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
static int get_size_AL_TReconstructedInfo()
{
	return get_size_struct_AL_TReconstructedInfo();
}
static void marshall_AL_TReconstructedInfo(AL_TReconstructedInfo *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TReconstructedInfo((struct AL_TReconstructedInfo *) in, write_cb, arg);
}
static void unmarshall_AL_TReconstructedInfo(AL_TReconstructedInfo *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TReconstructedInfo((struct AL_TReconstructedInfo *) in, read_cb, arg);
}
static int get_size_AL_ESliceType()
{
	return sizeof(AL_ESliceType);
}
static void marshall_AL_ESliceType(AL_ESliceType *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_ESliceType(AL_ESliceType *in, void (*read_cb)(int, void *, void *), void *arg)
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
static int get_size_AL_ESectionFlags()
{
	return sizeof(AL_ESectionFlags);
}
static void marshall_AL_ESectionFlags(AL_ESectionFlags *in, void (*write_cb)(int, void *, void *), void *arg)
{
	write_cb(sizeof(*in), in, arg);
}
static void unmarshall_AL_ESectionFlags(AL_ESectionFlags *in, void (*read_cb)(int, void *, void *), void *arg)
{
	read_cb(sizeof(*in), in, arg);
}
static int get_size_AL_TStreamSection()
{
	return get_size_struct_AL_TStreamSection();
}
static void marshall_AL_TStreamSection(AL_TStreamSection *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_TStreamSection((struct AL_TStreamSection *) in, write_cb, arg);
}
static void unmarshall_AL_TStreamSection(AL_TStreamSection *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_TStreamSection((struct AL_TStreamSection *) in, read_cb, arg);
}
static int get_size_AL_RateCtrl_Statistics()
{
	return get_size_struct_al_t_RateCtrl_Statistics();
}
static void marshall_AL_RateCtrl_Statistics(AL_RateCtrl_Statistics *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_al_t_RateCtrl_Statistics((struct al_t_RateCtrl_Statistics *) in, write_cb, arg);
}
static void unmarshall_AL_RateCtrl_Statistics(AL_RateCtrl_Statistics *in, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_al_t_RateCtrl_Statistics((struct al_t_RateCtrl_Statistics *) in, read_cb, arg);
}

int enc_msg_itf_header_get_size(void)
{
	return get_size_struct_msg_itf_header();
}

void enc_msg_itf_header_marshall(struct msg_itf_header *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_header(in, write_cb, arg);
}

void enc_msg_itf_header_unmarshall(struct msg_itf_header *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_header(out, read_cb, arg);
}

int enc_msg_itf_get_cma_req_get_size(void)
{
	return get_size_struct_msg_itf_get_cma_req();
}

void enc_msg_itf_get_cma_req_marshall(struct msg_itf_get_cma_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_cma_req(in, write_cb, arg);
}

void enc_msg_itf_get_cma_req_unmarshall(struct msg_itf_get_cma_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_cma_req(out, read_cb, arg);
}

int enc_msg_itf_get_cma_req_full_get_size(void)
{
	return get_size_struct_msg_itf_get_cma_req_full();
}

void enc_msg_itf_get_cma_req_full_marshall(struct msg_itf_get_cma_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_cma_req_full(in, write_cb, arg);
}

void enc_msg_itf_get_cma_req_full_unmarshall(struct msg_itf_get_cma_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_cma_req_full(out, read_cb, arg);
}

int enc_msg_itf_get_cma_reply_get_size(void)
{
	return get_size_struct_msg_itf_get_cma_reply();
}

void enc_msg_itf_get_cma_reply_marshall(struct msg_itf_get_cma_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_cma_reply(in, write_cb, arg);
}

void enc_msg_itf_get_cma_reply_unmarshall(struct msg_itf_get_cma_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_cma_reply(out, read_cb, arg);
}

int enc_msg_itf_get_cma_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_get_cma_reply_full();
}

void enc_msg_itf_get_cma_reply_full_marshall(struct msg_itf_get_cma_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_cma_reply_full(in, write_cb, arg);
}

void enc_msg_itf_get_cma_reply_full_unmarshall(struct msg_itf_get_cma_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_cma_reply_full(out, read_cb, arg);
}

int enc_msg_itf_put_cma_req_get_size(void)
{
	return get_size_struct_msg_itf_put_cma_req();
}

void enc_msg_itf_put_cma_req_marshall(struct msg_itf_put_cma_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_put_cma_req(in, write_cb, arg);
}

void enc_msg_itf_put_cma_req_unmarshall(struct msg_itf_put_cma_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_put_cma_req(out, read_cb, arg);
}

int enc_msg_itf_put_cma_req_full_get_size(void)
{
	return get_size_struct_msg_itf_put_cma_req_full();
}

void enc_msg_itf_put_cma_req_full_marshall(struct msg_itf_put_cma_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_put_cma_req_full(in, write_cb, arg);
}

void enc_msg_itf_put_cma_req_full_unmarshall(struct msg_itf_put_cma_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_put_cma_req_full(out, read_cb, arg);
}

int enc_msg_itf_put_cma_reply_get_size(void)
{
	return get_size_struct_msg_itf_put_cma_reply();
}

void enc_msg_itf_put_cma_reply_marshall(struct msg_itf_put_cma_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_put_cma_reply(in, write_cb, arg);
}

void enc_msg_itf_put_cma_reply_unmarshall(struct msg_itf_put_cma_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_put_cma_reply(out, read_cb, arg);
}

int enc_msg_itf_put_cma_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_put_cma_reply_full();
}

void enc_msg_itf_put_cma_reply_full_marshall(struct msg_itf_put_cma_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_put_cma_reply_full(in, write_cb, arg);
}

void enc_msg_itf_put_cma_reply_full_unmarshall(struct msg_itf_put_cma_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_put_cma_reply_full(out, read_cb, arg);
}

int enc_msg_itf_perf_info_req_get_size(void)
{
	return get_size_struct_msg_itf_perf_info_req();
}

void enc_msg_itf_perf_info_req_marshall(struct msg_itf_perf_info_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_perf_info_req(in, write_cb, arg);
}

void enc_msg_itf_perf_info_req_unmarshall(struct msg_itf_perf_info_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_perf_info_req(out, read_cb, arg);
}

int enc_msg_itf_perf_info_req_full_get_size(void)
{
	return get_size_struct_msg_itf_perf_info_req_full();
}

void enc_msg_itf_perf_info_req_full_marshall(struct msg_itf_perf_info_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_perf_info_req_full(in, write_cb, arg);
}

void enc_msg_itf_perf_info_req_full_unmarshall(struct msg_itf_perf_info_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_perf_info_req_full(out, read_cb, arg);
}

int enc_msg_itf_perf_info_reply_get_size(void)
{
	return get_size_struct_msg_itf_perf_info_reply();
}

void enc_msg_itf_perf_info_reply_marshall(struct msg_itf_perf_info_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_perf_info_reply(in, write_cb, arg);
}

void enc_msg_itf_perf_info_reply_unmarshall(struct msg_itf_perf_info_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_perf_info_reply(out, read_cb, arg);
}

int enc_msg_itf_perf_info_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_perf_info_reply_full();
}

void enc_msg_itf_perf_info_reply_full_marshall(struct msg_itf_perf_info_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_perf_info_reply_full(in, write_cb, arg);
}

void enc_msg_itf_perf_info_reply_full_unmarshall(struct msg_itf_perf_info_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_perf_info_reply_full(out, read_cb, arg);
}

int enc_msg_itf_write_req_get_size(void)
{
	return get_size_struct_msg_itf_write_req();
}

void enc_msg_itf_write_req_marshall(struct msg_itf_write_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_write_req(in, write_cb, arg);
}

void enc_msg_itf_write_req_unmarshall(struct msg_itf_write_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_write_req(out, read_cb, arg);
}

int enc_msg_itf_write_req_full_get_size(void)
{
	return get_size_struct_msg_itf_write_req_full();
}

void enc_msg_itf_write_req_full_marshall(struct msg_itf_write_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_write_req_full(in, write_cb, arg);
}

void enc_msg_itf_write_req_full_unmarshall(struct msg_itf_write_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_write_req_full(out, read_cb, arg);
}

int enc_AL_StreamSectionInBuffer_get_size(void)
{
	return get_size_struct_AL_StreamSectionInBuffer();
}

void enc_AL_StreamSectionInBuffer_marshall(struct AL_StreamSectionInBuffer *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_AL_StreamSectionInBuffer(in, write_cb, arg);
}

void enc_AL_StreamSectionInBuffer_unmarshall(struct AL_StreamSectionInBuffer *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_AL_StreamSectionInBuffer(out, read_cb, arg);
}

int enc_chunk_info_get_size(void)
{
	return get_size_struct_chunk_info();
}

void enc_chunk_info_marshall(struct chunk_info *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_chunk_info(in, write_cb, arg);
}

void enc_chunk_info_unmarshall(struct chunk_info *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_chunk_info(out, read_cb, arg);
}

int enc_msg_itf_create_encoder_req_get_size(void)
{
	return get_size_struct_msg_itf_create_encoder_req();
}

void enc_msg_itf_create_encoder_req_marshall(struct msg_itf_create_encoder_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_create_encoder_req(in, write_cb, arg);
}

void enc_msg_itf_create_encoder_req_unmarshall(struct msg_itf_create_encoder_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_create_encoder_req(out, read_cb, arg);
}

int enc_msg_itf_create_encoder_req_full_get_size(void)
{
	return get_size_struct_msg_itf_create_encoder_req_full();
}

void enc_msg_itf_create_encoder_req_full_marshall(struct msg_itf_create_encoder_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_create_encoder_req_full(in, write_cb, arg);
}

void enc_msg_itf_create_encoder_req_full_unmarshall(struct msg_itf_create_encoder_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_create_encoder_req_full(out, read_cb, arg);
}

int enc_msg_itf_create_encoder_reply_get_size(void)
{
	return get_size_struct_msg_itf_create_encoder_reply();
}

void enc_msg_itf_create_encoder_reply_marshall(struct msg_itf_create_encoder_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_create_encoder_reply(in, write_cb, arg);
}

void enc_msg_itf_create_encoder_reply_unmarshall(struct msg_itf_create_encoder_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_create_encoder_reply(out, read_cb, arg);
}

int enc_msg_itf_create_encoder_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_create_encoder_reply_full();
}

void enc_msg_itf_create_encoder_reply_full_marshall(struct msg_itf_create_encoder_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_create_encoder_reply_full(in, write_cb, arg);
}

void enc_msg_itf_create_encoder_reply_full_unmarshall(struct msg_itf_create_encoder_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_create_encoder_reply_full(out, read_cb, arg);
}

int enc_msg_itf_destroy_encoder_req_get_size(void)
{
	return get_size_struct_msg_itf_destroy_encoder_req();
}

void enc_msg_itf_destroy_encoder_req_marshall(struct msg_itf_destroy_encoder_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_destroy_encoder_req(in, write_cb, arg);
}

void enc_msg_itf_destroy_encoder_req_unmarshall(struct msg_itf_destroy_encoder_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_destroy_encoder_req(out, read_cb, arg);
}

int enc_msg_itf_destroy_encoder_req_full_get_size(void)
{
	return get_size_struct_msg_itf_destroy_encoder_req_full();
}

void enc_msg_itf_destroy_encoder_req_full_marshall(struct msg_itf_destroy_encoder_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_destroy_encoder_req_full(in, write_cb, arg);
}

void enc_msg_itf_destroy_encoder_req_full_unmarshall(struct msg_itf_destroy_encoder_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_destroy_encoder_req_full(out, read_cb, arg);
}

int enc_msg_itf_destroy_encoder_reply_get_size(void)
{
	return get_size_struct_msg_itf_destroy_encoder_reply();
}

void enc_msg_itf_destroy_encoder_reply_marshall(struct msg_itf_destroy_encoder_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_destroy_encoder_reply(in, write_cb, arg);
}

void enc_msg_itf_destroy_encoder_reply_unmarshall(struct msg_itf_destroy_encoder_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_destroy_encoder_reply(out, read_cb, arg);
}

int enc_msg_itf_destroy_encoder_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_destroy_encoder_reply_full();
}

void enc_msg_itf_destroy_encoder_reply_full_marshall(struct msg_itf_destroy_encoder_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_destroy_encoder_reply_full(in, write_cb, arg);
}

void enc_msg_itf_destroy_encoder_reply_full_unmarshall(struct msg_itf_destroy_encoder_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_destroy_encoder_reply_full(out, read_cb, arg);
}

int enc_msg_itf_get_info_req_get_size(void)
{
	return get_size_struct_msg_itf_get_info_req();
}

void enc_msg_itf_get_info_req_marshall(struct msg_itf_get_info_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_info_req(in, write_cb, arg);
}

void enc_msg_itf_get_info_req_unmarshall(struct msg_itf_get_info_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_info_req(out, read_cb, arg);
}

int enc_msg_itf_get_info_req_full_get_size(void)
{
	return get_size_struct_msg_itf_get_info_req_full();
}

void enc_msg_itf_get_info_req_full_marshall(struct msg_itf_get_info_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_info_req_full(in, write_cb, arg);
}

void enc_msg_itf_get_info_req_full_unmarshall(struct msg_itf_get_info_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_info_req_full(out, read_cb, arg);
}

int enc_msg_itf_get_info_reply_get_size(void)
{
	return get_size_struct_msg_itf_get_info_reply();
}

void enc_msg_itf_get_info_reply_marshall(struct msg_itf_get_info_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_info_reply(in, write_cb, arg);
}

void enc_msg_itf_get_info_reply_unmarshall(struct msg_itf_get_info_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_info_reply(out, read_cb, arg);
}

int enc_msg_itf_get_info_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_get_info_reply_full();
}

void enc_msg_itf_get_info_reply_full_marshall(struct msg_itf_get_info_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_info_reply_full(in, write_cb, arg);
}

void enc_msg_itf_get_info_reply_full_unmarshall(struct msg_itf_get_info_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_info_reply_full(out, read_cb, arg);
}

int enc_msg_itf_push_stream_buffer_req_get_size(void)
{
	return get_size_struct_msg_itf_push_stream_buffer_req();
}

void enc_msg_itf_push_stream_buffer_req_marshall(struct msg_itf_push_stream_buffer_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_push_stream_buffer_req(in, write_cb, arg);
}

void enc_msg_itf_push_stream_buffer_req_unmarshall(struct msg_itf_push_stream_buffer_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_push_stream_buffer_req(out, read_cb, arg);
}

int enc_msg_itf_push_stream_buffer_req_full_get_size(void)
{
	return get_size_struct_msg_itf_push_stream_buffer_req_full();
}

void enc_msg_itf_push_stream_buffer_req_full_marshall(struct msg_itf_push_stream_buffer_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_push_stream_buffer_req_full(in, write_cb, arg);
}

void enc_msg_itf_push_stream_buffer_req_full_unmarshall(struct msg_itf_push_stream_buffer_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_push_stream_buffer_req_full(out, read_cb, arg);
}

int enc_msg_itf_push_stream_buffer_reply_get_size(void)
{
	return get_size_struct_msg_itf_push_stream_buffer_reply();
}

void enc_msg_itf_push_stream_buffer_reply_marshall(struct msg_itf_push_stream_buffer_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_push_stream_buffer_reply(in, write_cb, arg);
}

void enc_msg_itf_push_stream_buffer_reply_unmarshall(struct msg_itf_push_stream_buffer_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_push_stream_buffer_reply(out, read_cb, arg);
}

int enc_msg_itf_push_stream_buffer_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_push_stream_buffer_reply_full();
}

void enc_msg_itf_push_stream_buffer_reply_full_marshall(struct msg_itf_push_stream_buffer_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_push_stream_buffer_reply_full(in, write_cb, arg);
}

void enc_msg_itf_push_stream_buffer_reply_full_unmarshall(struct msg_itf_push_stream_buffer_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_push_stream_buffer_reply_full(out, read_cb, arg);
}

int enc_msg_itf_process_req_get_size(void)
{
	return get_size_struct_msg_itf_process_req();
}

void enc_msg_itf_process_req_marshall(struct msg_itf_process_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_process_req(in, write_cb, arg);
}

void enc_msg_itf_process_req_unmarshall(struct msg_itf_process_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_process_req(out, read_cb, arg);
}

int enc_msg_itf_process_req_full_get_size(void)
{
	return get_size_struct_msg_itf_process_req_full();
}

void enc_msg_itf_process_req_full_marshall(struct msg_itf_process_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_process_req_full(in, write_cb, arg);
}

void enc_msg_itf_process_req_full_unmarshall(struct msg_itf_process_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_process_req_full(out, read_cb, arg);
}

int enc_msg_itf_process_reply_get_size(void)
{
	return get_size_struct_msg_itf_process_reply();
}

void enc_msg_itf_process_reply_marshall(struct msg_itf_process_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_process_reply(in, write_cb, arg);
}

void enc_msg_itf_process_reply_unmarshall(struct msg_itf_process_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_process_reply(out, read_cb, arg);
}

int enc_msg_itf_process_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_process_reply_full();
}

void enc_msg_itf_process_reply_full_marshall(struct msg_itf_process_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_process_reply_full(in, write_cb, arg);
}

void enc_msg_itf_process_reply_full_unmarshall(struct msg_itf_process_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_process_reply_full(out, read_cb, arg);
}

int enc_msg_itf_get_rec_req_get_size(void)
{
	return get_size_struct_msg_itf_get_rec_req();
}

void enc_msg_itf_get_rec_req_marshall(struct msg_itf_get_rec_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_rec_req(in, write_cb, arg);
}

void enc_msg_itf_get_rec_req_unmarshall(struct msg_itf_get_rec_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_rec_req(out, read_cb, arg);
}

int enc_msg_itf_get_rec_req_full_get_size(void)
{
	return get_size_struct_msg_itf_get_rec_req_full();
}

void enc_msg_itf_get_rec_req_full_marshall(struct msg_itf_get_rec_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_rec_req_full(in, write_cb, arg);
}

void enc_msg_itf_get_rec_req_full_unmarshall(struct msg_itf_get_rec_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_rec_req_full(out, read_cb, arg);
}

int enc_msg_itf_get_rec_reply_get_size(void)
{
	return get_size_struct_msg_itf_get_rec_reply();
}

void enc_msg_itf_get_rec_reply_marshall(struct msg_itf_get_rec_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_rec_reply(in, write_cb, arg);
}

void enc_msg_itf_get_rec_reply_unmarshall(struct msg_itf_get_rec_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_rec_reply(out, read_cb, arg);
}

int enc_msg_itf_get_rec_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_get_rec_reply_full();
}

void enc_msg_itf_get_rec_reply_full_marshall(struct msg_itf_get_rec_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_rec_reply_full(in, write_cb, arg);
}

void enc_msg_itf_get_rec_reply_full_unmarshall(struct msg_itf_get_rec_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_rec_reply_full(out, read_cb, arg);
}

int enc_msg_itf_get_last_error_req_get_size(void)
{
	return get_size_struct_msg_itf_get_last_error_req();
}

void enc_msg_itf_get_last_error_req_marshall(struct msg_itf_get_last_error_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_last_error_req(in, write_cb, arg);
}

void enc_msg_itf_get_last_error_req_unmarshall(struct msg_itf_get_last_error_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_last_error_req(out, read_cb, arg);
}

int enc_msg_itf_get_last_error_req_full_get_size(void)
{
	return get_size_struct_msg_itf_get_last_error_req_full();
}

void enc_msg_itf_get_last_error_req_full_marshall(struct msg_itf_get_last_error_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_last_error_req_full(in, write_cb, arg);
}

void enc_msg_itf_get_last_error_req_full_unmarshall(struct msg_itf_get_last_error_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_last_error_req_full(out, read_cb, arg);
}

int enc_msg_itf_release_rec_req_get_size(void)
{
	return get_size_struct_msg_itf_release_rec_req();
}

void enc_msg_itf_release_rec_req_marshall(struct msg_itf_release_rec_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_release_rec_req(in, write_cb, arg);
}

void enc_msg_itf_release_rec_req_unmarshall(struct msg_itf_release_rec_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_release_rec_req(out, read_cb, arg);
}

int enc_msg_itf_release_rec_req_full_get_size(void)
{
	return get_size_struct_msg_itf_release_rec_req_full();
}

void enc_msg_itf_release_rec_req_full_marshall(struct msg_itf_release_rec_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_release_rec_req_full(in, write_cb, arg);
}

void enc_msg_itf_release_rec_req_full_unmarshall(struct msg_itf_release_rec_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_release_rec_req_full(out, read_cb, arg);
}

int enc_msg_itf_release_rec_reply_get_size(void)
{
	return get_size_struct_msg_itf_release_rec_reply();
}

void enc_msg_itf_release_rec_reply_marshall(struct msg_itf_release_rec_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_release_rec_reply(in, write_cb, arg);
}

void enc_msg_itf_release_rec_reply_unmarshall(struct msg_itf_release_rec_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_release_rec_reply(out, read_cb, arg);
}

int enc_msg_itf_release_rec_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_release_rec_reply_full();
}

void enc_msg_itf_release_rec_reply_full_marshall(struct msg_itf_release_rec_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_release_rec_reply_full(in, write_cb, arg);
}

void enc_msg_itf_release_rec_reply_full_unmarshall(struct msg_itf_release_rec_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_release_rec_reply_full(out, read_cb, arg);
}

int enc_msg_itf_get_last_error_reply_get_size(void)
{
	return get_size_struct_msg_itf_get_last_error_reply();
}

void enc_msg_itf_get_last_error_reply_marshall(struct msg_itf_get_last_error_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_last_error_reply(in, write_cb, arg);
}

void enc_msg_itf_get_last_error_reply_unmarshall(struct msg_itf_get_last_error_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_last_error_reply(out, read_cb, arg);
}

int enc_msg_itf_get_last_error_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_get_last_error_reply_full();
}

void enc_msg_itf_get_last_error_reply_full_marshall(struct msg_itf_get_last_error_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_get_last_error_reply_full(in, write_cb, arg);
}

void enc_msg_itf_get_last_error_reply_full_unmarshall(struct msg_itf_get_last_error_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_get_last_error_reply_full(out, read_cb, arg);
}

int enc_msg_itf_notify_req_get_size(void)
{
	return get_size_struct_msg_itf_notify_req();
}

void enc_msg_itf_notify_req_marshall(struct msg_itf_notify_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_notify_req(in, write_cb, arg);
}

void enc_msg_itf_notify_req_unmarshall(struct msg_itf_notify_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_notify_req(out, read_cb, arg);
}

int enc_msg_itf_notify_req_full_get_size(void)
{
	return get_size_struct_msg_itf_notify_req_full();
}

void enc_msg_itf_notify_req_full_marshall(struct msg_itf_notify_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_notify_req_full(in, write_cb, arg);
}

void enc_msg_itf_notify_req_full_unmarshall(struct msg_itf_notify_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_notify_req_full(out, read_cb, arg);
}

int enc_msg_itf_notify_reply_get_size(void)
{
	return get_size_struct_msg_itf_notify_reply();
}

void enc_msg_itf_notify_reply_marshall(struct msg_itf_notify_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_notify_reply(in, write_cb, arg);
}

void enc_msg_itf_notify_reply_unmarshall(struct msg_itf_notify_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_notify_reply(out, read_cb, arg);
}

int enc_msg_itf_notify_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_notify_reply_full();
}

void enc_msg_itf_notify_reply_full_marshall(struct msg_itf_notify_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_notify_reply_full(in, write_cb, arg);
}

void enc_msg_itf_notify_reply_full_unmarshall(struct msg_itf_notify_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_notify_reply_full(out, read_cb, arg);
}

int enc_msg_itf_smart_req_get_size(void)
{
	return get_size_struct_msg_itf_smart_req();
}

void enc_msg_itf_smart_req_marshall(struct msg_itf_smart_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_smart_req(in, write_cb, arg);
}

void enc_msg_itf_smart_req_unmarshall(struct msg_itf_smart_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_smart_req(out, read_cb, arg);
}

int enc_msg_itf_smart_req_full_get_size(void)
{
	return get_size_struct_msg_itf_smart_req_full();
}

void enc_msg_itf_smart_req_full_marshall(struct msg_itf_smart_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_smart_req_full(in, write_cb, arg);
}

void enc_msg_itf_smart_req_full_unmarshall(struct msg_itf_smart_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_smart_req_full(out, read_cb, arg);
}

int enc_msg_itf_smart_reply_get_size(void)
{
	return get_size_struct_msg_itf_smart_reply();
}

void enc_msg_itf_smart_reply_marshall(struct msg_itf_smart_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_smart_reply(in, write_cb, arg);
}

void enc_msg_itf_smart_reply_unmarshall(struct msg_itf_smart_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_smart_reply(out, read_cb, arg);
}

int enc_msg_itf_smart_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_smart_reply_full();
}

void enc_msg_itf_smart_reply_full_marshall(struct msg_itf_smart_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_smart_reply_full(in, write_cb, arg);
}

void enc_msg_itf_smart_reply_full_unmarshall(struct msg_itf_smart_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_smart_reply_full(out, read_cb, arg);
}

int enc_msg_itf_hdr_req_get_size(void)
{
	return get_size_struct_msg_itf_hdr_req();
}

void enc_msg_itf_hdr_req_marshall(struct msg_itf_hdr_req *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_hdr_req(in, write_cb, arg);
}

void enc_msg_itf_hdr_req_unmarshall(struct msg_itf_hdr_req *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_hdr_req(out, read_cb, arg);
}

int enc_msg_itf_hdr_req_full_get_size(void)
{
	return get_size_struct_msg_itf_hdr_req_full();
}

void enc_msg_itf_hdr_req_full_marshall(struct msg_itf_hdr_req_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_hdr_req_full(in, write_cb, arg);
}

void enc_msg_itf_hdr_req_full_unmarshall(struct msg_itf_hdr_req_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_hdr_req_full(out, read_cb, arg);
}

int enc_msg_itf_hdr_reply_get_size(void)
{
	return get_size_struct_msg_itf_hdr_reply();
}

void enc_msg_itf_hdr_reply_marshall(struct msg_itf_hdr_reply *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_hdr_reply(in, write_cb, arg);
}

void enc_msg_itf_hdr_reply_unmarshall(struct msg_itf_hdr_reply *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_hdr_reply(out, read_cb, arg);
}

int enc_msg_itf_hdr_reply_full_get_size(void)
{
	return get_size_struct_msg_itf_hdr_reply_full();
}

void enc_msg_itf_hdr_reply_full_marshall(struct msg_itf_hdr_reply_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_hdr_reply_full(in, write_cb, arg);
}

void enc_msg_itf_hdr_reply_full_unmarshall(struct msg_itf_hdr_reply_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_hdr_reply_full(out, read_cb, arg);
}

int enc_msg_itf_evt_buffer_refcount_get_size(void)
{
	return get_size_struct_msg_itf_evt_buffer_refcount();
}

void enc_msg_itf_evt_buffer_refcount_marshall(struct msg_itf_evt_buffer_refcount *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_buffer_refcount(in, write_cb, arg);
}

void enc_msg_itf_evt_buffer_refcount_unmarshall(struct msg_itf_evt_buffer_refcount *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_buffer_refcount(out, read_cb, arg);
}

int enc_msg_itf_evt_buffer_refcount_full_get_size(void)
{
	return get_size_struct_msg_itf_evt_buffer_refcount_full();
}

void enc_msg_itf_evt_buffer_refcount_full_marshall(struct msg_itf_evt_buffer_refcount_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_buffer_refcount_full(in, write_cb, arg);
}

void enc_msg_itf_evt_buffer_refcount_full_unmarshall(struct msg_itf_evt_buffer_refcount_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_buffer_refcount_full(out, read_cb, arg);
}

int enc_msg_itf_evt_end_encoding_get_size(void)
{
	return get_size_struct_msg_itf_evt_end_encoding();
}

void enc_msg_itf_evt_end_encoding_marshall(struct msg_itf_evt_end_encoding *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_end_encoding(in, write_cb, arg);
}

void enc_msg_itf_evt_end_encoding_unmarshall(struct msg_itf_evt_end_encoding *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_end_encoding(out, read_cb, arg);
}

int enc_msg_itf_evt_end_encoding_full_get_size(void)
{
	return get_size_struct_msg_itf_evt_end_encoding_full();
}

void enc_msg_itf_evt_end_encoding_full_marshall(struct msg_itf_evt_end_encoding_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_end_encoding_full(in, write_cb, arg);
}

void enc_msg_itf_evt_end_encoding_full_unmarshall(struct msg_itf_evt_end_encoding_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_end_encoding_full(out, read_cb, arg);
}

int enc_msg_itf_evt_end_encoding_with_stat_get_size(void)
{
	return get_size_struct_msg_itf_evt_end_encoding_with_stat();
}

void enc_msg_itf_evt_end_encoding_with_stat_marshall(struct msg_itf_evt_end_encoding_with_stat *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_end_encoding_with_stat(in, write_cb, arg);
}

void enc_msg_itf_evt_end_encoding_with_stat_unmarshall(struct msg_itf_evt_end_encoding_with_stat *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_end_encoding_with_stat(out, read_cb, arg);
}

int enc_msg_itf_evt_end_encoding_with_stat_full_get_size(void)
{
	return get_size_struct_msg_itf_evt_end_encoding_with_stat_full();
}

void enc_msg_itf_evt_end_encoding_with_stat_full_marshall(struct msg_itf_evt_end_encoding_with_stat_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_end_encoding_with_stat_full(in, write_cb, arg);
}

void enc_msg_itf_evt_end_encoding_with_stat_full_unmarshall(struct msg_itf_evt_end_encoding_with_stat_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_end_encoding_with_stat_full(out, read_cb, arg);
}

int enc_msg_itf_evt_destroy_marker_get_size(void)
{
	return get_size_struct_msg_itf_evt_destroy_marker();
}

void enc_msg_itf_evt_destroy_marker_marshall(struct msg_itf_evt_destroy_marker *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_destroy_marker(in, write_cb, arg);
}

void enc_msg_itf_evt_destroy_marker_unmarshall(struct msg_itf_evt_destroy_marker *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_destroy_marker(out, read_cb, arg);
}

int enc_msg_itf_evt_destroy_marker_full_get_size(void)
{
	return get_size_struct_msg_itf_evt_destroy_marker_full();
}

void enc_msg_itf_evt_destroy_marker_full_marshall(struct msg_itf_evt_destroy_marker_full *in, void (*write_cb)(int, void *, void *), void *arg)
{
	marshall_struct_msg_itf_evt_destroy_marker_full(in, write_cb, arg);
}

void enc_msg_itf_evt_destroy_marker_full_unmarshall(struct msg_itf_evt_destroy_marker_full *out, void (*read_cb)(int, void *, void *), void *arg)
{
	unmarshall_struct_msg_itf_evt_destroy_marker_full(out, read_cb, arg);
}
#pragma GCC diagnostic pop
