// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <stdint.h>
#include <lib_common/Allocator.h>

AL_TAllocator* AL_RiscvGetDmaAllocator(int fd);

void* AL_RiscvCmaMap(int fd, uint64_t uSize, uint64_t uOffset);
void AL_RiscvCmaUnmap(void* pAddr, uint64_t uSize);
void AL_RiscvCmaFree(int fd, uint64_t phyAddr);
