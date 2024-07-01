// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "SubAllocator.h"
#include "lib_assert/al_assert.h"

/*****************************************************************************/
#define FREE_FLAG ((size_t)((uintptr_t)(1) << (8 * sizeof(size_t) - 1)))
#define END_LNK ((size_t)(-1))
/* This is used to differentiate NULL handle from 0 value valid handle */
#define ALLOC_IS_VALID 4

/*****************************************************************************/
static void SubAllocator_InsertFreeChunk(AL_TSubAllocator* pAllocator, size_t zPos, size_t zSize)
{
  size_t* pBuf = (size_t*)pAllocator->pBaseVirtualAddr;

  /* Insert new chunk to Free List */
  pBuf[zPos] = zSize | FREE_FLAG;
  pBuf[zPos + zSize + 1] = zPos;

  if(pAllocator->zFirstFreeChunk == END_LNK)
  {
    pAllocator->zFirstFreeChunk = zPos;
    pBuf[zPos + 1] = END_LNK;
    pBuf[zPos + 2] = END_LNK;
  }
  else
  {
    size_t zIns = pAllocator->zFirstFreeChunk;

    while(((pBuf[zIns] & ~FREE_FLAG) <= zSize) && pBuf[zIns + 2] != END_LNK)
      zIns = pBuf[zIns + 2];

    if((pBuf[zIns] & ~FREE_FLAG) > zSize)
    {
      pBuf[zPos + 1] = pBuf[zIns + 1];
      pBuf[zPos + 2] = zIns;

      if(pBuf[zIns + 1] != END_LNK)
        pBuf[pBuf[zIns + 1] + 2] = zPos;
      else
        pAllocator->zFirstFreeChunk = zPos;
      pBuf[zIns + 1] = zPos;
    }
    else
    {
      AL_Assert(pBuf[zIns + 2] == END_LNK);

      /* free bufs are in zSize order, if noone is bigger than us, we should be
       * at the end of the list */
      if(pBuf[zIns + 2] != END_LNK)
        return;

      pBuf[zPos + 1] = zIns;
      pBuf[zPos + 2] = END_LNK;
      pBuf[zIns + 2] = zPos;
    }
  }

  if(pAllocator->zMaxFreeChunk < zSize)
    pAllocator->zMaxFreeChunk = zSize;
}

/*****************************************************************************/
static void SubAllocator_RemoveFreeChunk(AL_TSubAllocator* pAllocator, size_t zPos)
{
  size_t* pBuf = (size_t*)pAllocator->pBaseVirtualAddr;

  if(pBuf[zPos + 2] != END_LNK)
    pBuf[pBuf[zPos + 2] + 1] = pBuf[zPos + 1];
  else if(pBuf[zPos + 1] != END_LNK)
    pAllocator->zMaxFreeChunk = pBuf[pBuf[zPos + 1]] & ~FREE_FLAG;
  else
    pAllocator->zMaxFreeChunk = 0;

  if(pBuf[zPos + 1] != END_LNK)
    pBuf[pBuf[zPos + 1] + 2] = pBuf[zPos + 2];
  else
    pAllocator->zFirstFreeChunk = pBuf[zPos + 2];
}

/*****************************************************************************/
AL_HANDLE SubAllocator_Alloc(AL_TAllocator* pAllocator, size_t zSize)
{
  if(!pAllocator || !zSize)
    return NULL;

  AL_TSubAllocator* pSubAllocator = (AL_TSubAllocator*)pAllocator;
  size_t zAllocSize = (zSize + sizeof(size_t) - 1) / sizeof(size_t);

  if(zAllocSize < 2)
    zAllocSize = 2;

  if(zAllocSize > pSubAllocator->zMaxFreeChunk)
    return NULL;

  size_t* pBuf = (size_t*)pSubAllocator->pBaseVirtualAddr;

  size_t zCur = pSubAllocator->zFirstFreeChunk;

  while((pBuf[zCur] & ~FREE_FLAG) < zAllocSize)
    zCur = pBuf[zCur + 2]; // Next Free Chunk

  AL_Assert(pBuf[zCur] & FREE_FLAG);

  /* zCur can be 0 but handle should never be NULL as this is the invalid case */
  AL_HANDLE hBuf = (AL_HANDLE)(zCur + ALLOC_IS_VALID);

  // adjust size
  size_t zRemSize = (pBuf[zCur] & ~FREE_FLAG) - zAllocSize;
  size_t zNew;

  if(zRemSize < 4)
  {
    zAllocSize = pBuf[zCur] & ~FREE_FLAG;
    zRemSize = 0;
    zNew = END_LNK;
  }
  else
  {
    zRemSize -= 2;
    zNew = zCur + zAllocSize + 2;
  }

  // Update Free List
  SubAllocator_RemoveFreeChunk(pSubAllocator, zCur);

  if(zRemSize)
    SubAllocator_InsertFreeChunk(pSubAllocator, zNew, zRemSize);

  // Update current size
  pBuf[zCur] = zAllocSize;
  pBuf[zCur + zAllocSize + 1] = zCur;

  return hBuf;
}

/*****************************************************************************/
bool SubAllocator_Free(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  if(!pAllocator || !hBuf)
    return false;

  AL_TSubAllocator* pSubAllocator = (AL_TSubAllocator*)pAllocator;

  hBuf = (AL_HANDLE)((size_t)hBuf - ALLOC_IS_VALID);

  AL_Assert((size_t)hBuf <= pSubAllocator->zBaseSize);

  size_t zMaxSize = pSubAllocator->zBaseSize / sizeof(size_t);

  size_t* pBuf = (size_t*)pSubAllocator->pBaseVirtualAddr;

  size_t zNew = (size_t)hBuf;
  size_t zCur = zNew;

  AL_Assert((pBuf[zCur] & FREE_FLAG) == 0);

  /* Trying to free a non allocated chunk */
  if((pBuf[zCur] & FREE_FLAG) != 0)
    return false;

  size_t zFreeSize = pBuf[zCur] & ~FREE_FLAG;

  /* Merge with below chunk */
  size_t zNext = zCur + zFreeSize + 2;
  AL_Assert(zNext <= zMaxSize);

  /* if the next chunk is outside the alloc buffer*/
  if(zNext > zMaxSize)
    return false;

  if((zNext < zMaxSize) && (pBuf[zNext] & FREE_FLAG))
  {
    zFreeSize += (pBuf[zNext] & ~FREE_FLAG) + 2;
    // remove next from Free list
    SubAllocator_RemoveFreeChunk(pSubAllocator, zNext);
  }

  // merge with above chunk
  if(zCur > 0)
  {
    size_t zPrev = pBuf[zCur - 1];
    AL_Assert((zCur - zPrev) == (pBuf[zPrev] & ~FREE_FLAG) + 2);

    /* if size was corrupted */
    if((zCur - zPrev) != (pBuf[zPrev] & ~FREE_FLAG) + 2)
      return false;

    if((zPrev < zCur) && (pBuf[zPrev] & FREE_FLAG))
    {
      zNew = zPrev;
      zFreeSize += (pBuf[zPrev] & ~FREE_FLAG) + 2;
      // remove previous from Free list
      SubAllocator_RemoveFreeChunk(pSubAllocator, zPrev);
    }
  }
  // Insert new chunk to Free List
  SubAllocator_InsertFreeChunk(pSubAllocator, zNew, zFreeSize);

  return true;
}

/*****************************************************************************/
AL_VADDR SubAllocator_GetVirtualAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  size_t zCur = (size_t)hBuf - ALLOC_IS_VALID;

  AL_TSubAllocator* pSubAllocator = (AL_TSubAllocator*)pAllocator;
  return (AL_VADDR)(((uint32_t*)pSubAllocator->pBaseVirtualAddr) + (zCur + 1));
}

/*****************************************************************************/
AL_PADDR SubAllocator_GetPhysicalAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  size_t zCur = (size_t)hBuf - ALLOC_IS_VALID;

  AL_TSubAllocator* pSubAllocator = (AL_TSubAllocator*)pAllocator;
  return pSubAllocator->zBasePhysicalAddr + (zCur + 1) * sizeof(size_t);
}

/*****************************************************************************/
bool SubAllocator_Init(AL_TSubAllocator* pAllocator, AL_VADDR pVirtualAddr, AL_PADDR uPhysicalAddr, int iAlignmentInBytes, size_t zSize)
{
  if(!pAllocator || !pVirtualAddr)
    return false;

  if(((size_t)pVirtualAddr) % sizeof(size_t) != 0)
    return false;

  /* if the base address is not aligned */
  if((size_t)pVirtualAddr % sizeof(size_t))
    return false;

  if(uPhysicalAddr % iAlignmentInBytes != 0)
    return false;

  if(!zSize)
    return false;

  size_t zChunks = zSize / sizeof(size_t);
  size_t const zChunksPrivate = 2;

  if(zChunks <= zChunksPrivate)
    return false;

  size_t zChunksAvailable = zChunks - zChunksPrivate;

  pAllocator->pBaseVirtualAddr = (size_t*)pVirtualAddr;
  pAllocator->zBasePhysicalAddr = (size_t)uPhysicalAddr;
  pAllocator->zBaseSize = zSize;
  pAllocator->zFirstFreeChunk = 0;

  size_t* pBuf = (size_t*)pAllocator->pBaseVirtualAddr;

  pAllocator->zMaxFreeChunk = zChunksAvailable;
  pAllocator->zFirstFreeChunk = 0;

  pBuf[0] = pAllocator->zMaxFreeChunk | FREE_FLAG;
  pBuf[1] = END_LNK;
  pBuf[2] = END_LNK;
  pBuf[zChunksAvailable + 1] = 0;

  static AL_TAllocatorVTable const vtable =
  {
    NULL,
    &SubAllocator_Alloc,
    &SubAllocator_Free,
    &SubAllocator_GetVirtualAddr,
    &SubAllocator_GetPhysicalAddr,
    NULL,
    NULL,
    NULL,
  };

  pAllocator->base.vtable = &vtable;

  return true;
}

/*****************************************************************************/
bool SubAllocator_Deinit(AL_TSubAllocator* pAllocator)
{
  if(!pAllocator)
    return false;

  size_t zMaxSize = pAllocator->zBaseSize / sizeof(size_t) - 2;

  if(pAllocator->zMaxFreeChunk != zMaxSize) // Memory leak
    return false;

  return true;
}
