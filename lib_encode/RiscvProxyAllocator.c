// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "RiscvProxyAllocator.h"

#include <sys/ioctl.h>
#include <sys/mman.h>
#include <assert.h>

#include "lib_common/RiscvDmaAllocator.h"

#define container_of(ptr, type, member) \
  ((type*)((char*)ptr - offsetof(type, member)))

typedef struct
{
  AL_PADDR pAddr;
  AL_VADDR vAddr;
  size_t zSize;
  off_t offset;
}proxyBuf;

typedef struct
{
  AL_TAllocator dmaAllocator;
  int fd;
}AL_TRiscvProxyAllocator;

static int RiscvProxyAllocToFd(AL_TAllocator* pAllocator)
{
  AL_TRiscvProxyAllocator* pRiscvAllocator;

  pRiscvAllocator = container_of(pAllocator, AL_TRiscvProxyAllocator, dmaAllocator);

  return pRiscvAllocator->fd;
}

static void RiscvProxyDestroy(AL_TAllocator* pAllocator)
{
  AL_TRiscvProxyAllocator* pRiscvAllocator;

  pRiscvAllocator = container_of(pAllocator, AL_TRiscvProxyAllocator, dmaAllocator);
  Rtos_Free(pRiscvAllocator);
}

static AL_HANDLE RiscvProxyAlloc(AL_TAllocator* pAllocator, size_t zSize)
{
  /* Should never be called */
  assert(0);

  (void)pAllocator;
  (void)zSize;

  return NULL;
}

static bool RiscvProxyFree(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  proxyBuf* proxyBuf = hBuf;

  (void)pAllocator;

  AL_RiscvCmaUnmap(proxyBuf->vAddr, proxyBuf->zSize);
  Rtos_Free(hBuf);

  return true;
}

static AL_VADDR RiscvProxyGetVirtualAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  proxyBuf* proxyBuf = hBuf;
  void* vAddr = NULL;

  (void)pAllocator;

  if(proxyBuf->vAddr)
    return proxyBuf->vAddr;

  vAddr = AL_RiscvCmaMap(RiscvProxyAllocToFd(pAllocator), proxyBuf->zSize, proxyBuf->offset);
  proxyBuf->vAddr = vAddr;

  return vAddr;
}

static AL_PADDR RiscvProxyGetPhysicalAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  proxyBuf* proxyBuf = hBuf;

  (void)pAllocator;
  return proxyBuf->pAddr;
}

static AL_HANDLE RiscvProxyAllocNamed(AL_TAllocator* pAllocator, size_t zSize, char const* pBufName)
{
  (void)pBufName;
  return RiscvProxyAlloc(pAllocator, zSize);
}

static AL_TAllocatorVTable const s_RiscvProxyAllocatorVtable =
{
  .pfnDestroy = RiscvProxyDestroy,
  .pfnAlloc = RiscvProxyAlloc,
  .pfnFree = RiscvProxyFree,
  .pfnGetVirtualAddr = RiscvProxyGetVirtualAddr,
  .pfnGetPhysicalAddr = RiscvProxyGetPhysicalAddr,
  .pfnAllocNamed = RiscvProxyAllocNamed,
};

AL_TAllocator* AL_RiscvGetProxyAllocator(int fd)
{
  AL_TRiscvProxyAllocator* pAllocator;

  pAllocator = Rtos_Malloc(sizeof(*pAllocator));

  if(!pAllocator)
    return NULL;

  pAllocator->dmaAllocator.vtable = &s_RiscvProxyAllocatorVtable;
  pAllocator->fd = fd;

  return &pAllocator->dmaAllocator;
}

AL_HANDLE RiscvProxy_CreateByAddr(AL_TAllocator* pAllocator, AL_PADDR phyAddr, size_t zSize)
{
  proxyBuf* proxyBuf;

  (void)pAllocator;
  proxyBuf = Rtos_Malloc(sizeof(*proxyBuf));

  if(!proxyBuf)
    return NULL;

  proxyBuf->pAddr = phyAddr;
  proxyBuf->zSize = zSize;
  proxyBuf->vAddr = NULL;
  proxyBuf->offset = phyAddr;

  return proxyBuf;
}
