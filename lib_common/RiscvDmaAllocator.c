// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "RiscvDmaAllocator.h"

#include <stddef.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "lib_common/codec_uapi.h"

#define container_of(ptr, type, member) \
  ((type*)((char*)ptr - offsetof(type, member)))

typedef struct
{
  AL_PADDR pAddr;
  AL_VADDR vAddr;
  size_t zSize;
  off_t offset;
}dmaBuf;

typedef struct
{
  AL_TAllocator dmaAllocator;
  int fd;
}AL_TRiscvAllocator;

static int RiscvAllocToFd(AL_TAllocator* pAllocator)
{
  AL_TRiscvAllocator* pRiscvAllocator;

  pRiscvAllocator = container_of(pAllocator, AL_TRiscvAllocator, dmaAllocator);

  return pRiscvAllocator->fd;
}

static bool RiscvDmaDestroy(AL_TAllocator* pAllocator)
{
  AL_TRiscvAllocator* pRiscvAllocator;

  pRiscvAllocator = container_of(pAllocator, AL_TRiscvAllocator, dmaAllocator);
  Rtos_Free(pRiscvAllocator);

  return true;
}

static AL_HANDLE RiscvDmaAlloc(AL_TAllocator* pAllocator, size_t zSize)
{
  struct codec_dma_info info;
  dmaBuf* dmaBuf;
  int ret;

  dmaBuf = Rtos_Malloc(sizeof(*dmaBuf));

  if(!dmaBuf)
    return NULL;

  info.size = zSize;
  ret = ioctl(RiscvAllocToFd(pAllocator), CODEC_DMA_ALLOC, &info);

  if(ret)
  {
    Rtos_Free(dmaBuf);
    return NULL;
  }

  dmaBuf->pAddr = info.phy_addr;
  dmaBuf->vAddr = NULL;
  dmaBuf->zSize = zSize;
  dmaBuf->offset = info.offset;

  return dmaBuf;
}

static AL_HANDLE RiscvDmaAllocNamed(AL_TAllocator* pAllocator, size_t zSize, char const* pBufName)
{
  (void)pBufName;
  return RiscvDmaAlloc(pAllocator, zSize);
}

static bool RiscvDmaFree(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  struct codec_dma_info info;
  dmaBuf* dmaBuf = hBuf;

  if(!hBuf)
    return false;

  AL_RiscvCmaUnmap(dmaBuf->vAddr, dmaBuf->zSize);

  info.phy_addr = dmaBuf->pAddr;
  ioctl(RiscvAllocToFd(pAllocator), CODEC_DMA_FREE, &info);
  Rtos_Free(hBuf);

  return true;
}

static AL_VADDR RiscvDmaGetVirtualAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  dmaBuf* dmaBuf = hBuf;
  void* vAddr = NULL;

  if(dmaBuf->vAddr)
    return dmaBuf->vAddr;

  vAddr = AL_RiscvCmaMap(RiscvAllocToFd(pAllocator), dmaBuf->zSize, dmaBuf->offset);
  dmaBuf->vAddr = vAddr;

  return vAddr;
}

static AL_PADDR RiscvDmaGetPhysicalAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  dmaBuf* dmaBuf = hBuf;

  (void)pAllocator;
  return dmaBuf->pAddr;
}

static const AL_AllocatorVtable s_RiscvDmaAllocatorVtable =
{
  .pfnDestroy = RiscvDmaDestroy,
  .pfnAlloc = RiscvDmaAlloc,
  .pfnFree = RiscvDmaFree,
  .pfnGetVirtualAddr = RiscvDmaGetVirtualAddr,
  .pfnGetPhysicalAddr = RiscvDmaGetPhysicalAddr,
  .pfnAllocNamed = RiscvDmaAllocNamed,
};

AL_TAllocator* AL_RiscvGetDmaAllocator(int fd)
{
  AL_TRiscvAllocator* pAllocator;

  pAllocator = Rtos_Malloc(sizeof(*pAllocator));

  if(!pAllocator)
    return NULL;

  pAllocator->dmaAllocator.vtable = &s_RiscvDmaAllocatorVtable;
  pAllocator->fd = fd;

  return &pAllocator->dmaAllocator;
}

void* AL_RiscvCmaMap(int fd, uint64_t uSize, uint64_t uOffset)
{
  void* vAddr = NULL;

  if(!uSize)
    return NULL;

  vAddr = mmap(NULL, uSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, uOffset);

  if(vAddr == MAP_FAILED)
    return NULL;

  return vAddr;
}

void AL_RiscvCmaUnmap(void* pAddr, uint64_t uSize)
{
  if(pAddr)
    munmap(pAddr, uSize);
}

void AL_RiscvCmaFree(int fd, uint64_t phyAddr)
{
  struct codec_dma_info info;

  info.phy_addr = phyAddr;
  ioctl(fd, CODEC_DMA_FREE_MCU, &info);
}
