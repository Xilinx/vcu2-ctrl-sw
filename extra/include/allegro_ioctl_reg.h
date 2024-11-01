// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <linux/types.h>

#define AL_CMD_UNBLOCK_CHANNEL _IO('q', 1)

#define AL_CMD_IP_WRITE_REG         _IOWR('q', 10, struct al5_reg)
#define AL_CMD_IP_READ_REG          _IOWR('q', 11, struct al5_reg)
#define AL_CMD_IP_WAIT_IRQ          _IOWR('q', 12, __s32)
#define GET_DMA32_FD                _IOWR('q', 13, struct al5_dma32_info)
#define GET_DMA32_MMAP              _IOWR('q', 26, struct al5_dma32_info)
#define GET_DMA32_PHY               _IOWR('q', 18, struct al5_dma32_info)
#define GET_DMA64_FD                _IOWR('q', 113, struct al5_dma64_info)
#define GET_DMA64_MMAP              _IOWR('q', 126, struct al5_dma64_info)
#define GET_DMA64_PHY               _IOWR('q', 118, struct al5_dma64_info)


struct al5_reg {
	__u32 id;
	__u32 value;
};

struct al5_dma32_info {
	__u32 fd;
	__u32 size;
	__u32 phy_addr;
};

struct al5_dma64_info {
	__u32 fd;
	__u32 size;
	__u64 phy_addr;
};

#if   __SIZEOF_POINTER__ == 4
#define GET_DMA_FD GET_DMA32_FD
#define GET_DMA_MMAP GET_DMA32_MMAP
#define GET_DMA_PHY GET_DMA32_PHY
#define al5_dma_info al5_dma32_info
#else
#define GET_DMA_FD GET_DMA64_FD
#define GET_DMA_MMAP GET_DMA64_MMAP
#define GET_DMA_PHY GET_DMA64_PHY
#define al5_dma_info al5_dma64_info
#endif
