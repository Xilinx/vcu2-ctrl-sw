// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "DecFramePool.h"
#include "lib_common_dec/DecBuffersInternal.h"

#define INVALID_POOL_ID 255

static void AL_DecFramePool_OnRefCntNull(AL_TBuffer* pBuf);

static void AL_DecFramePool_ClearPool(AL_TDecFramePool* pCtx)
{
  pCtx->uFrameNum = 0;
  pCtx->uFreeHead = INVALID_POOL_ID;
  pCtx->uFreeTail = INVALID_POOL_ID;
}

void AL_DecFramePool_Init(AL_TDecFramePool* pCtx)
{
  AL_DecFramePool_ClearPool(pCtx);
}

static AL_TBuffer* CreateBuffer(AL_TDecFramePool* pCtx, AL_TAllocator* pAllocator, AL_TMetaData* pMeta, size_t zSize, char const* pDebugName)
{
  AL_TBuffer* pBuf = AL_Buffer_Create_And_AllocateNamed(pAllocator, zSize, AL_DecFramePool_OnRefCntNull, pDebugName);

  if(!pBuf)
    goto fail_buffer_init;

  if(!AL_Buffer_AddMetaData(pBuf, pMeta))
    goto fail_buffer_add_meta;

  AL_Buffer_SetUserData(pBuf, (void*)pCtx);

  return pBuf;

  fail_buffer_add_meta:
  AL_Buffer_Destroy(pBuf);
  fail_buffer_init:
  AL_MetaData_Destroy(pMeta);
  return NULL;
}

bool AL_DecFramePool_Alloc(AL_TDecFramePool* pCtx, AL_TAllocator* pAllocator, AL_TDimension tDim, AL_TPicFormat tPicFormat, uint8_t uFrameNum)
{
  AL_Assert(uFrameNum <= MAX_FRAME_POOL_SIZE);
  AL_Assert(pCtx->uFrameNum == 0);

  TFourCC tFourCC = AL_GetFourCC(tPicFormat);

  int minPitch = RndPitch(tDim.iWidth, &tPicFormat);
  int iSizeYuv = AL_DecGetAllocSize_Frame(tDim, minPitch, tPicFormat);

  while(pCtx->uFrameNum < uFrameNum)
  {
    AL_TMetaData* pMeta = AL_CreateRecBufMetaData(tDim, minPitch, tFourCC);

    if(!pMeta)
      break;

    AL_TDecFramePoolElem* pElem = &pCtx->tPoolElems[pCtx->uFrameNum];
    pElem->pFrameBuf = CreateBuffer(pCtx, pAllocator, pMeta, iSizeYuv, "yuv-itl");

    if(pElem->pFrameBuf == NULL)
      break;

    if(pCtx->uFrameNum == uFrameNum - 1)
      pElem->uNext = INVALID_POOL_ID;
    else
      pElem->uNext = pCtx->uFrameNum + 1;

    pCtx->uFrameNum++;
  }

  if(pCtx->uFrameNum != 0)
  {
    pCtx->uFreeHead = 0;
    pCtx->uFreeTail = pCtx->uFrameNum - 1;
  }

  return pCtx->uFrameNum == uFrameNum;
}

void AL_DecFramePool_Deinit(AL_TDecFramePool* pCtx)
{
  uint8_t uDestroyCnt = 0;
  uint8_t uCurFrame = pCtx->uFreeHead;

  while(uCurFrame != INVALID_POOL_ID)
  {
    AL_Buffer_Destroy(pCtx->tPoolElems[uCurFrame].pFrameBuf);
    uCurFrame = pCtx->tPoolElems[uCurFrame].uNext;
    uDestroyCnt++;
  }

  AL_Assert(uDestroyCnt == pCtx->uFrameNum);

  AL_DecFramePool_ClearPool(pCtx);
}

AL_TBuffer* AL_DecFramePool_Get(AL_TDecFramePool* pCtx)
{
  if(pCtx->uFreeHead == INVALID_POOL_ID)
    return NULL;

  AL_TDecFramePoolElem* pElem = &pCtx->tPoolElems[pCtx->uFreeHead];
  AL_Buffer_Ref(pElem->pFrameBuf);

  pCtx->uFreeHead = pElem->uNext;

  if(pCtx->uFreeHead == INVALID_POOL_ID)
    pCtx->uFreeTail = INVALID_POOL_ID;

  return pElem->pFrameBuf;
}

static void AL_DecFramePool_OnRefCntNull(AL_TBuffer* pBuf)
{
  AL_TDecFramePool* pCtx = (AL_TDecFramePool*)AL_Buffer_GetUserData(pBuf);
  AL_Assert(pCtx != NULL);

  uint8_t uCurFrame = 0;

  while(uCurFrame < pCtx->uFrameNum && pCtx->tPoolElems[uCurFrame].pFrameBuf != pBuf)
    uCurFrame++;

  AL_Assert(uCurFrame < pCtx->uFrameNum);
  AL_TDecFramePoolElem* pElem = &pCtx->tPoolElems[uCurFrame];

  pElem->uNext = INVALID_POOL_ID;

  if(pCtx->uFreeTail == INVALID_POOL_ID)
  {
    pCtx->uFreeHead = uCurFrame;
    pCtx->uFreeTail = uCurFrame;
  }
  else
  {
    pCtx->tPoolElems[pCtx->uFreeTail].uNext = uCurFrame;
    pCtx->uFreeTail = uCurFrame;
  }
}

void AL_DecFramePool_Release(AL_TDecFramePool const* pCtx, AL_TBuffer* pBuf)
{
  (void)pCtx;
  AL_Buffer_Unref(pBuf);
}

