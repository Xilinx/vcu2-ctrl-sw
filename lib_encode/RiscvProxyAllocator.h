// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <stdint.h>
#include <lib_common/Allocator.h>

AL_TAllocator* AL_RiscvGetProxyAllocator(int fd);
AL_HANDLE RiscvProxy_CreateByAddr(AL_TAllocator* pAllocator, AL_PADDR phyAddr, size_t zSize);
