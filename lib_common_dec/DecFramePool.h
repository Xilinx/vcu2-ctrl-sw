// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "lib_common/BufCommonInternal.h"

#define MAX_FRAME_POOL_SIZE 50

typedef struct AL_TDecFramePoolElem
{
  AL_TBuffer* pFrameBuf;
  uint8_t uNext;
}AL_TDecFramePoolElem;

typedef struct AL_TDecFramePool
{
  AL_TDecFramePoolElem tPoolElems[MAX_FRAME_POOL_SIZE];
  uint8_t uFrameNum;
  uint8_t uFreeHead;
  uint8_t uFreeTail;
}AL_TDecFramePool;

void AL_DecFramePool_Init(AL_TDecFramePool* pCtx);

bool AL_DecFramePool_Alloc(AL_TDecFramePool* pCtx, AL_TAllocator* pAllocator, AL_TDimension tDim, AL_TPicFormat tPicFormat, uint8_t uFrameNum);

void AL_DecFramePool_Deinit(AL_TDecFramePool* pCtx);

AL_TBuffer* AL_DecFramePool_Get(AL_TDecFramePool* pCtx);

void AL_DecFramePool_Release(AL_TDecFramePool const* pCtx, AL_TBuffer* pBuf);

