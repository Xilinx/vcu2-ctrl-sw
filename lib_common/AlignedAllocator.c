// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_common/Allocator.h"
#include "Utils.h"

typedef struct
{
  AL_TAllocator base;
  AL_HANDLE this;
  AL_TAllocator* pRealAllocator;
  AL_TAllocator* pMemoryAllocator;
  uint32_t uAlign;
}AL_TAlignedAllocator;

typedef struct
{
  AL_HANDLE pRealBuf;
  AL_VADDR vAddr;
  AL_PADDR pAddr;
}AL_TAlignedHandle;

static void AL_AlignedAllocator_Destroy(AL_TAllocator* pAllocator)
{
  AL_TAlignedAllocator* p = (AL_TAlignedAllocator*)pAllocator;
  AL_Allocator_Free(p->pMemoryAllocator, p->this);
}

static AL_HANDLE AL_AlignedAllocator_AllocNamed(AL_TAllocator* pAllocator, size_t zSize, char const* pBufName)
{
  AL_TAlignedAllocator* p = (AL_TAlignedAllocator*)pAllocator;

  zSize += p->uAlign;

  AL_HANDLE h = AL_Allocator_Alloc(p->pMemoryAllocator, sizeof(AL_TAlignedHandle));

  if(h == NULL)
    return NULL;

  AL_HANDLE pBuf = AL_Allocator_AllocNamed(p->pRealAllocator, zSize, pBufName);

  if(pBuf == NULL)
  {
    AL_Allocator_Free(p->pMemoryAllocator, h);
    return NULL;
  }

  AL_PADDR pAddr = AL_Allocator_GetPhysicalAddr(p->pRealAllocator, pBuf);
  uint32_t uAlignmentOffset = UnsignedRoundUp(pAddr, p->uAlign) - pAddr;

  AL_TAlignedHandle* pAlignedHandle = (AL_TAlignedHandle*)AL_Allocator_GetVirtualAddr(p->pMemoryAllocator, h);
  pAlignedHandle->pRealBuf = pBuf;
  pAlignedHandle->pAddr = pAddr + uAlignmentOffset;
  pAlignedHandle->vAddr = AL_Allocator_GetVirtualAddr(p->pRealAllocator, pBuf) + uAlignmentOffset;

  return h;
}

static AL_HANDLE AL_AlignedAllocator_Alloc(AL_TAllocator* pAllocator, size_t zSize)
{
  return AL_AlignedAllocator_AllocNamed(pAllocator, zSize, "");
}

static bool AL_AlignedAllocator_Free(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  if(hBuf == NULL)
    return true;
  AL_TAlignedAllocator* p = (AL_TAlignedAllocator*)pAllocator;
  AL_TAlignedHandle* pAlignedHandle = (AL_TAlignedHandle*)AL_Allocator_GetVirtualAddr(p->pMemoryAllocator, hBuf);
  bool ret = AL_Allocator_Free(p->pRealAllocator, pAlignedHandle->pRealBuf);
  ret &= AL_Allocator_Free(p->pMemoryAllocator, hBuf);
  return ret;
}

static AL_VADDR AL_AlignedAllocator_GetVirtualAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  AL_TAlignedAllocator* p = (AL_TAlignedAllocator*)pAllocator;
  AL_TAlignedHandle* pAlignedHandle = (AL_TAlignedHandle*)AL_Allocator_GetVirtualAddr(p->pMemoryAllocator, hBuf);
  return pAlignedHandle->vAddr;
}

static AL_PADDR AL_AlignedAllocator_GetPhysicalAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  AL_TAlignedAllocator* p = (AL_TAlignedAllocator*)pAllocator;
  AL_TAlignedHandle* pAlignedHandle = (AL_TAlignedHandle*)AL_Allocator_GetVirtualAddr(p->pMemoryAllocator, hBuf);
  return pAlignedHandle->pAddr;
}

static AL_TAllocatorVTable const s_AlignedAllocatorVtable =
{
  AL_AlignedAllocator_Destroy,
  AL_AlignedAllocator_Alloc,
  AL_AlignedAllocator_Free,
  AL_AlignedAllocator_GetVirtualAddr,
  AL_AlignedAllocator_GetPhysicalAddr,
  AL_AlignedAllocator_AllocNamed,
  NULL,
  NULL,
};

AL_TAllocator* AL_AlignedAllocator_Create(AL_TAllocator* pMemoryAllocator, AL_TAllocator* pRealAllocator, uint32_t uAlign)
{
  AL_HANDLE h = AL_Allocator_Alloc(pMemoryAllocator, sizeof(AL_TAlignedAllocator));

  if(h == NULL)
    return NULL;
  AL_TAlignedAllocator* pAllocator = (AL_TAlignedAllocator*)AL_Allocator_GetVirtualAddr(pMemoryAllocator, h);
  pAllocator->base.vtable = &s_AlignedAllocatorVtable;
  pAllocator->this = h;
  pAllocator->pRealAllocator = pRealAllocator;
  pAllocator->pMemoryAllocator = pMemoryAllocator;
  pAllocator->uAlign = uAlign;
  return (AL_TAllocator*)pAllocator;
}
