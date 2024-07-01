// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "RiscvDmaAllocator.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>

#include <sys/ioctl.h>
#include <sys/mman.h>

#include "lib_fpga/DmaAllocLinux.h"
#include "lib_common/codec_uapi.h"

#define container_of(ptr, type, member) \
  ((type*)((char*)ptr - offsetof(type, member)))

typedef struct
{
  AL_PADDR pAddr;
  AL_VADDR vAddr;
  size_t zSize;
  off_t offset;
  uint32_t fd;
}RiscvDmaBuf;

typedef struct
{
  AL_TLinuxDmaAllocator dmaAllocator;
  int fd;
}AL_TRiscvAllocator;

static int RiscvAllocToFd(AL_TAllocator* pAllocator)
{
  AL_TRiscvAllocator* pRiscvAllocator;

  pRiscvAllocator = container_of(pAllocator, AL_TRiscvAllocator, dmaAllocator);

  return pRiscvAllocator->fd;
}

static void RiscvDmaDestroy(AL_TAllocator* pAllocator)
{
  AL_TRiscvAllocator* pRiscvAllocator;

  pRiscvAllocator = container_of(pAllocator, AL_TRiscvAllocator, dmaAllocator);
  Rtos_Free(pRiscvAllocator);
}

static AL_PADDR RiscvDmaGetPhysicalAddr(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  RiscvDmaBuf* dmaBuf = hBuf;

  (void)pAllocator;
  return dmaBuf->pAddr;
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

static AL_TAllocator* create(int fd, void const* vtable)
{
  AL_TRiscvAllocator* pAllocator;

  pAllocator = Rtos_Malloc(sizeof(*pAllocator));

  if(!pAllocator)
    return NULL;

  pAllocator->dmaAllocator.vtable = (AL_TDmaAllocLinuxVTable const*)vtable;
  pAllocator->fd = fd;

  return (AL_TAllocator*)(&pAllocator->dmaAllocator);
}

static AL_VADDR RiscvDmaGetVirtualAddr_Dmabuf(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  (void)pAllocator;
  RiscvDmaBuf* dmaBuf = hBuf;
  void* vAddr = NULL;

  if(dmaBuf->vAddr)
    return dmaBuf->vAddr;

  vAddr = AL_RiscvCmaMap(dmaBuf->fd, dmaBuf->zSize, 0);
  dmaBuf->vAddr = vAddr;

  return vAddr;
}

static bool RiscvDmaFree_Dmabuf(AL_TAllocator* pAllocator, AL_HANDLE hBuf)
{
  (void)pAllocator;
  RiscvDmaBuf* dmaBuf = hBuf;

  if(!hBuf)
    return false;

  AL_RiscvCmaUnmap(dmaBuf->vAddr, dmaBuf->zSize);

  close(dmaBuf->fd);

  Rtos_Free(hBuf);

  return true;
}

static size_t AlignToPageSize(size_t zSize)
{
  unsigned long pagesize = sysconf(_SC_PAGESIZE);

  if((zSize % pagesize) == 0)
    return zSize;
  return zSize - (zSize % pagesize) + pagesize;
}

static AL_HANDLE RiscvDmaAlloc_Dmabuf(AL_TAllocator* pAllocator, size_t zSize)
{
  struct codec_dma_info info;
  RiscvDmaBuf* dmaBuf;

  dmaBuf = Rtos_Malloc(sizeof(*dmaBuf));

  if(!dmaBuf)
    return NULL;

  size_t zMapSize = AlignToPageSize(zSize);
  info.size = zMapSize;

  if(ioctl(RiscvAllocToFd(pAllocator), CODEC_DMA_ALLOC_WITH_FD, &info))
    goto fail;

  dmaBuf->pAddr = info.phy_addr;
  dmaBuf->vAddr = NULL;
  dmaBuf->zSize = zMapSize;
  dmaBuf->offset = info.offset;
  dmaBuf->fd = info.fd;
  return dmaBuf;
  fail:
  Rtos_Free(dmaBuf);
  return NULL;
}

static AL_HANDLE RiscvDmaAllocNamed_Dmabuf(AL_TAllocator* pAllocator, size_t zSize, char const* pBufName)
{
  (void)pBufName;
  return RiscvDmaAlloc_Dmabuf(pAllocator, zSize);
}

static int RiscvDmaGetFd_Dmabuf(AL_TLinuxDmaAllocator* pAllocator, AL_HANDLE hBuf)
{
  (void)pAllocator;
  RiscvDmaBuf* dmaBuf = hBuf;

  return dmaBuf->fd;
}

static size_t RiscvDmaGetDmabufSize(int fd)
{
  off_t off = lseek(fd, 0, SEEK_END);

  if(off < 0)
  {
    if(errno == ESPIPE)
      perror("dmabuf lseek operation is not supported by your kernel");
    return 0;
  }

  size_t zSize = (size_t)off;

  if(lseek(fd, 0, SEEK_SET) < 0 && errno == ESPIPE)
    perror("dmabuf lseek operation is not supported by your kernel");

  return zSize;
}

static AL_HANDLE RiscvDmaImportFromFd_Dmabuf(AL_TLinuxDmaAllocator* pAllocator, int fd)
{
  struct codec_dma_info info;
  RiscvDmaBuf* dmaBuf = (RiscvDmaBuf*)calloc(1, sizeof(*dmaBuf));

  if(!dmaBuf)
    return NULL;

  info.fd = dup(fd);

  if(ioctl(RiscvAllocToFd((AL_TAllocator*)pAllocator), CODEC_DMA_GET_PHY, &info))
    goto fail;

  dmaBuf->pAddr = info.phy_addr;
  dmaBuf->vAddr = NULL;
  dmaBuf->zSize = AlignToPageSize(RiscvDmaGetDmabufSize(fd));
  dmaBuf->offset = info.offset;
  dmaBuf->fd = info.fd;

  if(dmaBuf->zSize == 0)
    goto fail;

  return dmaBuf;

  fail:
  free(dmaBuf);
  return NULL;
}

static AL_TDmaAllocLinuxVTable const s_RiscvDmaAllocatorVtable =
{
  {
    .pfnDestroy = RiscvDmaDestroy,
    .pfnAlloc = RiscvDmaAlloc_Dmabuf,
    .pfnFree = RiscvDmaFree_Dmabuf,
    .pfnGetVirtualAddr = RiscvDmaGetVirtualAddr_Dmabuf,
    .pfnGetPhysicalAddr = RiscvDmaGetPhysicalAddr,
    .pfnAllocNamed = RiscvDmaAllocNamed_Dmabuf,
  },
  .pfnGetFd = RiscvDmaGetFd_Dmabuf,
  .pfnImportFromFd = RiscvDmaImportFromFd_Dmabuf,
};

AL_TAllocator* AL_RiscvGetDmaAllocator(int fd)
{
  return create(fd, &s_RiscvDmaAllocatorVtable);
}

