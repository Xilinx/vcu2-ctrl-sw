// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_common/Allocator.h"
#include "lib_rtos/lib_rtos.h"

static AL_HANDLE AL_sDefaultAllocator_Alloc(AL_TAllocator* pAllocator, size_t zSize)
{
  (void)pAllocator;
  return (AL_HANDLE)Rtos_Malloc(zSize);
}

static bool AL_sDefaultAllocator_Free(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  (void)pAllocator;
  Rtos_Free(hBuf);
  return true;
}

static AL_VADDR AL_sDefaultAllocator_GetVirtualAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  (void)pAllocator;
  return (AL_VADDR)hBuf;
}

static AL_PADDR AL_sDefaultAllocator_GetPhysicalAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  (void)pAllocator;
  (void)hBuf;
  /* 32 is an ugly hack: we do not want to have 0 for an address */
  return (AL_PADDR)32;
}

static void AL_sDefaultAllocator_Destroy(AL_TAllocator* pAllocator)
{
  (void)pAllocator;
}

static AL_TAllocatorVTable const s_DefaultAllocatorVtable =
{
  &AL_sDefaultAllocator_Destroy,
  &AL_sDefaultAllocator_Alloc,
  &AL_sDefaultAllocator_Free,
  &AL_sDefaultAllocator_GetVirtualAddr,
  &AL_sDefaultAllocator_GetPhysicalAddr,
  NULL,
  NULL,
  NULL,
};

typedef struct
{
  uint8_t* pData;
  void* pUserData;
  void (* destructor)(void* pUserData, uint8_t* pData);
}AL_TWrapperHandle;

static AL_HANDLE WrapData(AL_TAllocator* pAllocator, uint8_t* pData, void (* destructor)(void* pUserData, uint8_t* pData), void* pUserData)
{
  (void)pAllocator;
  AL_TWrapperHandle* h = (AL_TWrapperHandle*)Rtos_Malloc(sizeof(*h));

  if(!h)
    return NULL;
  h->pData = pData;
  h->pUserData = pUserData;
  h->destructor = destructor;
  return (AL_HANDLE)h;
}

static void WrapperFree(void* pUserParam, uint8_t* pData)
{
  (void)pUserParam;
  Rtos_Free(pData);
}

static AL_HANDLE AL_sWrapperAllocator_Alloc(AL_TAllocator* pAllocator, size_t zSize)
{
  uint8_t* pData = (uint8_t*)Rtos_Malloc(zSize);

  if(!pData)
    return NULL;
  return WrapData(pAllocator, pData, WrapperFree, NULL);
}

static bool AL_sWrapperAllocator_Free(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  (void)pAllocator;
  AL_TWrapperHandle* h = (AL_TWrapperHandle*)hBuf;

  if(h->destructor)
    h->destructor(h->pUserData, h->pData);
  Rtos_Free(h);
  return true;
}

static AL_VADDR AL_sWrapperAllocator_GetVirtualAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  (void)pAllocator;
  AL_TWrapperHandle* h = (AL_TWrapperHandle*)hBuf;
  return h->pData;
}

static AL_PADDR AL_sWrapperAllocator_GetPhysicalAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  /* The wrapped data doesn't have a physical address */
  (void)pAllocator, (void)hBuf;
  Rtos_Assert(false);
  return (AL_PADDR)0xdeaddead;
}

static void AL_sWrapperAllocator_Destroy(AL_TAllocator* pAllocator)
{
  (void)pAllocator;
}

static AL_TAllocatorVTable const s_WrapperAllocatorVtable =
{
  &AL_sWrapperAllocator_Destroy,
  &AL_sWrapperAllocator_Alloc,
  &AL_sWrapperAllocator_Free,
  &AL_sWrapperAllocator_GetVirtualAddr,
  &AL_sWrapperAllocator_GetPhysicalAddr,
  NULL,
  NULL,
  NULL,
};

static AL_TAllocator s_WrapperAllocator =
{
  &s_WrapperAllocatorVtable
};

static AL_TAllocator s_DefaultAllocator =
{
  &s_DefaultAllocatorVtable
};

AL_TAllocator* AL_GetWrapperAllocator(void)
{
  return &s_WrapperAllocator;
}

AL_TAllocator* AL_GetDefaultAllocator(void)
{
  return &s_DefaultAllocator;
}

AL_HANDLE AL_WrapperAllocator_WrapData(uint8_t* pData, void (* destructor)(void* pUserData, uint8_t* pData), void* pUserData)
{
  return WrapData(AL_GetWrapperAllocator(), pData, destructor, pUserData);
}
