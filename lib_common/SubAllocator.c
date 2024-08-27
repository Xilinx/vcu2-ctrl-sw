// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "SubAllocator.h"

/*****************************************************************************/
#define FREE_FLAG ((size_t)((uintptr_t)(1) << (8 * sizeof(size_t) - 1)))
#define END_LNK ((size_t)(-1))
/* This is used to differentiate NULL handle from 0 value valid handle */
#define ALLOC_IS_VALID sizeof(size_t)

#define LNK_PREV 1
#define LNK_NEXT 2
#define PRIV_HEADER_SIZE 1
#define PRIV_FOOTER_SIZE 1
#define PRIV_SIZE (PRIV_HEADER_SIZE + PRIV_FOOTER_SIZE)
#define MIN_SIZE 2 // should be big enough to store LinkList of free chunks

/*****************************************************************************/
static void SubAllocator_InsertFreeChunk(AL_TSubAllocator* pAllocator, size_t zPos, size_t zSize)
{
  size_t* pBuf = (size_t*)pAllocator->pBaseVirtualAddr;

  /* Insert new chunk to Free List */
  pBuf[zPos] = zSize | FREE_FLAG;
  pBuf[zPos + PRIV_HEADER_SIZE + zSize] = zPos;  // Footer

  if(pAllocator->zFirstFreeChunk == END_LNK)
  {
    pAllocator->zFirstFreeChunk = zPos;
    pBuf[zPos + LNK_PREV] = END_LNK;
    pBuf[zPos + LNK_NEXT] = END_LNK;
  }
  else
  {
    size_t zIns = pAllocator->zFirstFreeChunk;

    while(((pBuf[zIns] & ~FREE_FLAG) <= zSize) && pBuf[zIns + LNK_NEXT] != END_LNK)
      zIns = pBuf[zIns + LNK_NEXT];

    if((pBuf[zIns] & ~FREE_FLAG) > zSize)
    {
      pBuf[zPos + LNK_PREV] = pBuf[zIns + LNK_PREV];
      pBuf[zPos + LNK_NEXT] = zIns;

      if(pBuf[zIns + LNK_PREV] != END_LNK)
        pBuf[pBuf[zIns + LNK_PREV] + LNK_NEXT] = zPos;
      else
        pAllocator->zFirstFreeChunk = zPos;
      pBuf[zIns + LNK_PREV] = zPos;
    }
    else
    {
      Rtos_Assert(pBuf[zIns + LNK_NEXT] == END_LNK);

      /* free bufs are in zSize order, if noone is bigger than us, we should be
       * at the end of the list */
      if(pBuf[zIns + LNK_NEXT] != END_LNK)
        return;

      pBuf[zPos + LNK_PREV] = zIns;
      pBuf[zPos + LNK_NEXT] = END_LNK;
      pBuf[zIns + LNK_NEXT] = zPos;
    }
  }

  if(pAllocator->zMaxFreeChunk < zSize)
    pAllocator->zMaxFreeChunk = zSize;
}

/*****************************************************************************/
static void SubAllocator_RemoveFreeChunk(AL_TSubAllocator* pAllocator, size_t zPos)
{
  size_t* pBuf = (size_t*)pAllocator->pBaseVirtualAddr;

  if(pBuf[zPos + LNK_NEXT] != END_LNK)
    pBuf[pBuf[zPos + LNK_NEXT] + LNK_PREV] = pBuf[zPos + LNK_PREV];
  else if(pBuf[zPos + LNK_PREV] != END_LNK)
    pAllocator->zMaxFreeChunk = pBuf[pBuf[zPos + LNK_PREV]] & ~FREE_FLAG;
  else
    pAllocator->zMaxFreeChunk = 0;

  if(pBuf[zPos + LNK_PREV] != END_LNK)
    pBuf[pBuf[zPos + LNK_PREV] + LNK_NEXT] = pBuf[zPos + LNK_NEXT];
  else
    pAllocator->zFirstFreeChunk = pBuf[zPos + LNK_NEXT];
}

/*****************************************************************************/
AL_HANDLE SubAllocator_Alloc(AL_TAllocator* pAllocator, size_t zSize)
{
  if(!pAllocator || !zSize)
    return NULL;

  AL_TSubAllocator* pSubAllocator = (AL_TSubAllocator*)pAllocator;
  size_t zAlignment = pSubAllocator->zAlignment;

  if(zAlignment < sizeof(size_t))
    zAlignment = sizeof(size_t);

  size_t zAllocSize = (zSize + zAlignment - 1) / sizeof(size_t);

  if(zAllocSize < MIN_SIZE)
    zAllocSize = MIN_SIZE;

  if(zAllocSize > pSubAllocator->zMaxFreeChunk)
    return NULL;

  size_t* pBuf = (size_t*)pSubAllocator->pBaseVirtualAddr;

  size_t zCur = pSubAllocator->zFirstFreeChunk;

  while((pBuf[zCur] & ~FREE_FLAG) < zAllocSize)
    zCur = pBuf[zCur + LNK_NEXT]; // Next Free Chunk

  Rtos_Assert(pBuf[zCur] & FREE_FLAG);

  /* zCur can be 0 but handle should never be NULL as this is the invalid case */
  AL_HANDLE hBuf = (AL_HANDLE)(zCur + ALLOC_IS_VALID);

  // adjust size
  size_t zRemSize = (pBuf[zCur] & ~FREE_FLAG) - zAllocSize;
  size_t zNew;

  if(zRemSize < (PRIV_SIZE + MIN_SIZE))
  {
    zAllocSize = pBuf[zCur] & ~FREE_FLAG;
    zRemSize = 0;
    zNew = END_LNK;
  }
  else
  {
    zRemSize -= PRIV_SIZE;
    zNew = zCur + zAllocSize + PRIV_SIZE;
  }

  // Update Free List
  SubAllocator_RemoveFreeChunk(pSubAllocator, zCur);

  if(zRemSize)
    SubAllocator_InsertFreeChunk(pSubAllocator, zNew, zRemSize);

  // Update current size
  pBuf[zCur] = zAllocSize;
  pBuf[zCur + PRIV_HEADER_SIZE + zAllocSize] = zCur; // Footer

  return hBuf;
}

/*****************************************************************************/
bool SubAllocator_Free(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  if(!pAllocator || !hBuf)
    return false;

  AL_TSubAllocator* pSubAllocator = (AL_TSubAllocator*)pAllocator;

  hBuf = (AL_HANDLE)((size_t)hBuf - ALLOC_IS_VALID);

  Rtos_Assert((size_t)hBuf <= pSubAllocator->zBaseSize);

  size_t zMaxSize = pSubAllocator->zBaseSize / sizeof(size_t);

  size_t* pBuf = (size_t*)pSubAllocator->pBaseVirtualAddr;

  size_t zNew = (size_t)hBuf;
  size_t zCur = zNew;

  Rtos_Assert((pBuf[zCur] & FREE_FLAG) == 0);

  /* Trying to free a non allocated chunk */
  if((pBuf[zCur] & FREE_FLAG) != 0)
    return false;

  size_t zFreeSize = pBuf[zCur] & ~FREE_FLAG;

  /* Merge with below chunk */
  size_t zNext = zCur + zFreeSize + PRIV_SIZE;
  Rtos_Assert(zNext <= zMaxSize);

  /* if the next chunk is outside the alloc buffer*/
  if(zNext > zMaxSize)
    return false;

  if((zNext < zMaxSize) && (pBuf[zNext] & FREE_FLAG))
  {
    zFreeSize += (pBuf[zNext] & ~FREE_FLAG) + PRIV_SIZE;
    // remove next from Free list
    SubAllocator_RemoveFreeChunk(pSubAllocator, zNext);
  }

  // merge with above chunk
  if(zCur > 0)
  {
    size_t zPrev = pBuf[zCur - PRIV_FOOTER_SIZE];
    Rtos_Assert((zCur - zPrev) == (pBuf[zPrev] & ~FREE_FLAG) + PRIV_SIZE);

    /* if size was corrupted */
    if((zCur - zPrev) != (pBuf[zPrev] & ~FREE_FLAG) + PRIV_SIZE)
      return false;

    if((zPrev < zCur) && (pBuf[zPrev] & FREE_FLAG))
    {
      zNew = zPrev;
      zFreeSize += (pBuf[zPrev] & ~FREE_FLAG) + PRIV_SIZE;
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
  uintptr_t Addr = (uintptr_t)(pSubAllocator->pBaseVirtualAddr + (zCur + PRIV_HEADER_SIZE));
  uintptr_t Alignment = pSubAllocator->zAlignment - 1;
  return (AL_VADDR)((Addr + Alignment) & ~Alignment);
}

/*****************************************************************************/
AL_PADDR SubAllocator_GetPhysicalAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  size_t zCur = (size_t)hBuf - ALLOC_IS_VALID;

  AL_TSubAllocator* pSubAllocator = (AL_TSubAllocator*)pAllocator;
  AL_PADDR Addr = pSubAllocator->uBasePhysicalAddr + (zCur + PRIV_HEADER_SIZE) * sizeof(size_t);
  AL_PADDR Alignment = pSubAllocator->zAlignment - 1;
  return (AL_PADDR)((Addr + Alignment) & ~Alignment);
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

  /* if the base addresses cannot be aligned the same way*/
  if((size_t)pVirtualAddr % iAlignmentInBytes != uPhysicalAddr % iAlignmentInBytes)
    return false;

  if(!zSize)
    return false;

  size_t zChunks = zSize / sizeof(size_t);

  if(zChunks <= PRIV_SIZE)
    return false;

  size_t zChunksAvailable = zChunks - PRIV_SIZE;

  pAllocator->pBaseVirtualAddr = (size_t*)pVirtualAddr;
  pAllocator->uBasePhysicalAddr = uPhysicalAddr;
  pAllocator->zBaseSize = zSize;
  pAllocator->zFirstFreeChunk = 0;
  pAllocator->zAlignment = iAlignmentInBytes;

  size_t* pBuf = (size_t*)pAllocator->pBaseVirtualAddr;

  pAllocator->zMaxFreeChunk = zChunksAvailable;
  pAllocator->zFirstFreeChunk = 0;

  pBuf[0] = pAllocator->zMaxFreeChunk | FREE_FLAG;
  pBuf[LNK_PREV] = END_LNK;
  pBuf[LNK_NEXT] = END_LNK;
  pBuf[PRIV_HEADER_SIZE + zChunksAvailable] = 0;  // Footer

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

  size_t zMaxSize = pAllocator->zBaseSize / sizeof(size_t) - PRIV_SIZE;

  if(pAllocator->zMaxFreeChunk != zMaxSize) // Memory leak
    return false;

  return true;
}
