// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "lib_common/Allocator.h"

typedef struct AL_TSubAllocator
{
  AL_TAllocator base;

  size_t* pBaseVirtualAddr;
  size_t zBasePhysicalAddr;
  size_t zBaseSize;

  size_t zFirstFreeChunk;
  size_t zMaxFreeChunk;
}AL_TSubAllocator;

bool SubAllocator_Init(AL_TSubAllocator* pAllocator, AL_VADDR VirtualAddr, AL_PADDR PhysicalAddr, int alignmentInBytes, size_t zSize);
bool SubAllocator_Deinit(AL_TSubAllocator* pAllocator);

AL_HANDLE SubAllocator_Alloc(AL_TAllocator* pAllocator, size_t zSize);
bool SubAllocator_Free(AL_TAllocator* pAllocator, AL_HANDLE hBuf);
AL_VADDR SubAllocator_GetVirtualAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf);
AL_PADDR SubAllocator_GetPhysicalAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf);
