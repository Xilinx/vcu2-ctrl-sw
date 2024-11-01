// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <stdint.h>

struct codec_cmd_reply {
	uint16_t req_size;
	uint16_t reply_size;
	void *req;
	void *reply;
};

struct codec_dma_info {
	uint64_t phy_addr;
	uint64_t offset;
	uint32_t size;
	int32_t fd;
};

struct codec_event {
	uint32_t type;
	void *event;
};

#define CODEC_FW_CMD_REPLY		_IOWR('c', 1, struct codec_cmd_reply)

#define CODEC_DMA_ALLOC			_IOWR('c', 2, struct codec_dma_info)
#define CODEC_DMA_ALLOC_WITH_FD	_IOWR('c', 6, struct codec_dma_info)

#define CODEC_DMA_FREE			_IOWR('c', 3, struct codec_dma_info)
#define CODEC_GET_EVENT			_IOWR('c', 4, struct codec_event)
#define CODEC_DMA_FREE_MCU		_IOWR('c', 5, struct codec_dma_info)
#define CODEC_DMA_GET_PHY       _IOWR('c', 7, struct codec_dma_info)
