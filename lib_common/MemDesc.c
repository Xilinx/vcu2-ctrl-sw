// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/******************************************************************************
   \addtogroup lib_base
   !@{
   \file
 *****************************************************************************/
#include "lib_common/MemDesc.h"

/****************************************************************************/
void AL_MemDesc_Init(AL_TMemDesc* pMD)
{
  if(pMD)
  {
    pMD->pVirtualAddr = NULL;
    pMD->uSize = 0;
    pMD->uPhysicalAddr = 0;
    pMD->pAllocator = NULL;
    pMD->hAllocBuf = NULL;
  }
}

/****************************************************************************/
bool AL_MemDesc_Alloc(AL_TMemDesc* pMD, AL_TAllocator* pAllocator, size_t zSize)
{
  return AL_MemDesc_AllocNamed(pMD, pAllocator, zSize, "unknown");
}

bool AL_MemDesc_AllocNamed(AL_TMemDesc* pMD, AL_TAllocator* pAllocator, size_t zSize, char const* name)
{
  bool bRet = false;

  if(pMD && pAllocator)
  {
    AL_HANDLE hBuf = AL_Allocator_AllocNamed(pAllocator, zSize, name);

    if(hBuf)
    {
      pMD->pAllocator = pAllocator;
      pMD->hAllocBuf = hBuf;
      pMD->uSize = zSize;
      pMD->pVirtualAddr = AL_Allocator_GetVirtualAddr(pAllocator, hBuf);
      pMD->uPhysicalAddr = AL_Allocator_GetPhysicalAddr(pAllocator, hBuf);
      bRet = true;
    }
  }
  return bRet;
}

/****************************************************************************/
bool AL_MemDesc_Free(AL_TMemDesc* pMD)
{
  if(pMD && pMD->pAllocator && pMD->hAllocBuf)
  {
    AL_Allocator_Free(pMD->pAllocator, pMD->hAllocBuf);
    AL_MemDesc_Init(pMD);
    return true;
  }
  else
    return false;
}

/*****************************************************************************/
/*!@}*/
