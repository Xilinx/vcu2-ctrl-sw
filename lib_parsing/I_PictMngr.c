// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "I_PictMngr.h"

#include <limits.h>
#include "lib_common/PicFormat.h"
#include "lib_common_dec/DecOutputSettingsInternal.h"
#include "lib_common/Error.h"
#include "lib_common/PixMapBufferInternal.h"
#include "lib_common/BufferStreamMeta.h"
#include "lib_common_dec/IpDecFourCC.h"
#include "lib_common/DisplayInfoMeta.h"
#include "lib_decode/lib_decode.h"
#include "lib_rtos/lib_rtos.h"

/*************************************************************************/
static AL_TBuffer* sRecBuffers_GetDisplayBuffer(AL_TRecBuffers const* tRecBuffers, AL_TFrmBufPool const* pPool)
{
  (void)pPool;

  if(pPool->bHasSecondOutputFrame)
    return tRecBuffers->pSecondOutputFrame;

  return tRecBuffers->pFrame;
}

/*************************************************************************/
static bool sRecBuffers_AreNull(AL_TRecBuffers const* tRecBuffers)
{
  bool bNull = NULL == tRecBuffers->pFrame;

  bNull = bNull && (NULL == tRecBuffers->pSecondOutputFrame);

  return bNull;
}

/*************************************************************************/
static bool sRecBuffers_AreNotNull(AL_TRecBuffers const* tRecBuffers, AL_TFrmBufPool const* pPool)
{
  (void)pPool;
  bool bNotNull = tRecBuffers->pFrame;

  if(pPool->bHasSecondOutputFrame)
    bNotNull = bNotNull && tRecBuffers->pSecondOutputFrame;

  return bNotNull;
}

/*************************************************************************/
static void sRecBuffers_Reset(AL_TRecBuffers* tRecBuffers)
{
  tRecBuffers->pFrame = NULL;
  tRecBuffers->pSecondOutputFrame = NULL;
}

/*************************************************************************/
static void sRecBuffers_CleanUp(AL_TRecBuffers* tRecBuffers, AL_TFrmBufPool const* pPool)
{
  (void)pPool;

  AL_Buffer_Cleanup(tRecBuffers->pFrame);

  if(pPool->bHasSecondOutputFrame)
    AL_Buffer_Cleanup(tRecBuffers->pSecondOutputFrame);
}

/*************************************************************************/
static void sRecBuffers_Release(AL_TRecBuffers* tRecBuffers, AL_TFrmBufPool const* pPool)
{
  (void)pPool;

  if(pPool->bHasSecondOutputFrame)
  {
    AL_Buffer_Unref(tRecBuffers->pSecondOutputFrame);
    AL_DecFramePool_Release(&pPool->tSecondOutputPool, tRecBuffers->pFrame);
  }
  else
  AL_Buffer_Unref(tRecBuffers->pFrame);
}

/*************************************************************************/
static bool sRecBuffers_HasBuf(AL_TRecBuffers const* tRecBuffers, AL_TBuffer const* pBuf, AL_TFrmBufPool const* pPool)
{
  (void)pPool;
  bool bHasBuf = tRecBuffers->pFrame == pBuf;

  if(pPool->bHasSecondOutputFrame)
  {
    bHasBuf |= tRecBuffers->pSecondOutputFrame == pBuf;
  }

  return bHasBuf;
}

/*************************************************************************/
static int sFrmBufPool_GetFrameIDFromBuf(AL_TFrmBufPool const* pPool, AL_TBuffer const* pBuf)
{
  Rtos_GetMutex(pPool->Mutex);

  for(int i = 0; i < FRM_BUF_POOL_SIZE; i++)
  {
    if(sRecBuffers_HasBuf(&pPool->array[i].tRecBuffers, pBuf, pPool))
    {
      Rtos_ReleaseMutex(pPool->Mutex);
      return i;
    }
  }

  Rtos_ReleaseMutex(pPool->Mutex);
  return -1;
}

/*************************************************************************/
static int sFrmBufPool_GetFrameIDFromDisplay(AL_TFrmBufPool const* pPool, AL_TBuffer const* pDisplayBuf)
{
  Rtos_GetMutex(pPool->Mutex);

  for(int i = 0; i < FRM_BUF_POOL_SIZE; i++)
  {
    if(sRecBuffers_GetDisplayBuffer(&pPool->array[i].tRecBuffers, pPool) == pDisplayBuf)
    {
      Rtos_ReleaseMutex(pPool->Mutex);
      return i;
    }
  }

  Rtos_ReleaseMutex(pPool->Mutex);
  return -1;
}

/*************************************************************************/
static bool sFrmBufPoolFifo_IsInFifo(AL_TFrmBufPool const* pPool, AL_TBuffer const* pDisplayBuf)
{
  Rtos_GetMutex(pPool->Mutex);

  for(int iCur = pPool->iFifoHead; iCur != -1; iCur = pPool->array[iCur].iNext)
  {
    if(sRecBuffers_GetDisplayBuffer(&pPool->array[iCur].tRecBuffers, pPool) == pDisplayBuf)
    {
      Rtos_ReleaseMutex(pPool->Mutex);
      return true;
    }
  }

  Rtos_ReleaseMutex(pPool->Mutex);
  return false;
}

/*************************************************************************/
static void AddBufferToFifo(AL_TFrmBufPool* pPool, int iFrameID, AL_TRecBuffers const* pRecBuffers)
{
  Rtos_Memcpy(&pPool->array[iFrameID].tRecBuffers, pRecBuffers, sizeof(AL_TRecBuffers));

  if(pPool->iFifoTail == -1 && pPool->iFifoHead == -1)
    pPool->iFifoHead = iFrameID;
  else
    pPool->array[pPool->iFifoTail].iNext = iFrameID;

  pPool->iFifoTail = iFrameID;

  pPool->array[iFrameID].iAccessCnt = 0;
  pPool->array[iFrameID].bWillBeOutputted = false;

  ++pPool->iBufNumber;
}

/*************************************************************************/
static bool sFrmBufPoolFifo_PushBack(AL_TFrmBufPool* pPool, AL_TRecBuffers const* pRecBuffers)
{
  bool const bRecNotNull = sRecBuffers_AreNotNull(pRecBuffers, pPool);
  (void)bRecNotNull;
  Rtos_Assert(bRecNotNull);

  Rtos_GetMutex(pPool->Mutex);

  int iPoolIdx = 0;

  while(iPoolIdx < FRM_BUF_POOL_SIZE && (!sRecBuffers_AreNull(&pPool->array[iPoolIdx].tRecBuffers) ||
                                         (pPool->array[iPoolIdx].iNext != -1) ||
                                         (pPool->array[iPoolIdx].iAccessCnt != -1) ||
                                         pPool->array[iPoolIdx].bWillBeOutputted
                                         ))
    iPoolIdx++;

  if(iPoolIdx < FRM_BUF_POOL_SIZE)
  {
    AddBufferToFifo(pPool, iPoolIdx, pRecBuffers);
    Rtos_ReleaseSemaphore(pPool->Semaphore);
  }

  Rtos_ReleaseMutex(pPool->Mutex);
  return iPoolIdx < FRM_BUF_POOL_SIZE;
}

/*************************************************************************/
static int RemoveBufferFromFifo(AL_TFrmBufPool* pPool)
{
  int const iFrameID = pPool->iFifoHead;
  --pPool->iBufNumber;

  pPool->iFifoHead = pPool->array[pPool->iFifoHead].iNext;

  pPool->array[iFrameID].iNext = -1;
  pPool->array[iFrameID].iAccessCnt = 1;

  if(pPool->iFifoHead == -1)
    pPool->iFifoTail = pPool->iFifoHead;
  return iFrameID;
}

/*************************************************************************/
static int sFrmBufPoolFifo_Pop(AL_TFrmBufPool* pPool)
{
  Rtos_GetSemaphore(pPool->Semaphore, AL_WAIT_FOREVER);

  Rtos_GetMutex(pPool->Mutex);

  if(pPool->isDecommited)
  {
    Rtos_ReleaseSemaphore(pPool->Semaphore);
    Rtos_ReleaseMutex(pPool->Mutex);
    return UndefID;
  }

  Rtos_Assert(pPool->iBufNumber > 0);
  Rtos_Assert(pPool->iFifoHead != -1);
  bool const bRecNotNull = sRecBuffers_AreNotNull(&pPool->array[pPool->iFifoHead].tRecBuffers, pPool);
  (void)bRecNotNull;
  Rtos_Assert(bRecNotNull);
  Rtos_Assert(pPool->array[pPool->iFifoHead].iAccessCnt == 0);
  Rtos_Assert(pPool->array[pPool->iFifoHead].bWillBeOutputted == false);

  sRecBuffers_CleanUp(&pPool->array[pPool->iFifoHead].tRecBuffers, pPool);
  pPool->array[pPool->iFifoHead].eError = AL_SUCCESS;

  int const iFrameID = RemoveBufferFromFifo(pPool);

  Rtos_ReleaseMutex(pPool->Mutex);
  return iFrameID;
}

/*************************************************************************/
static void sFrmBufPoolFifo_Decommit(AL_TFrmBufPool* pPool)
{
  Rtos_GetMutex(pPool->Mutex);
  pPool->isDecommited = true;
  Rtos_ReleaseSemaphore(pPool->Semaphore);
  Rtos_ReleaseMutex(pPool->Mutex);
}

/*************************************************************************/
static void sFrmBufPool_RemoveID(AL_TFrmBufPool* pPool, int iFrameID)
{
  Rtos_GetMutex(pPool->Mutex);
  Rtos_Assert(iFrameID >= 0 && iFrameID < FRM_BUF_POOL_SIZE);
  AL_TFrameFifo* pFrame = &pPool->array[iFrameID];
  bool const bRecNotNull = sRecBuffers_AreNotNull(&pFrame->tRecBuffers, pPool);
  (void)bRecNotNull;
  Rtos_Assert(bRecNotNull);
  Rtos_Assert(pFrame->iNext == -1);
  Rtos_Assert(pFrame->iAccessCnt == 0);

  sRecBuffers_Reset(&pFrame->tRecBuffers);
  pFrame->iAccessCnt = -1;
  pFrame->bWillBeOutputted = false;
  pFrame->iNext = -1;

  Rtos_ReleaseMutex(pPool->Mutex);
}

/*************************************************************************/
static AL_TRecBuffers* sFrmBufPool_GetBufferFromID(AL_TFrmBufPool* pPool, int iFrameID)
{
  Rtos_Assert(iFrameID >= 0 && iFrameID < FRM_BUF_POOL_SIZE);
  bool const bRecNotNull = sRecBuffers_AreNotNull(&pPool->array[iFrameID].tRecBuffers, pPool);
  (void)bRecNotNull;
  Rtos_Assert(bRecNotNull);
  return &pPool->array[iFrameID].tRecBuffers;
}

/*************************************************************************/
static void sFrmBufPoolFifo_Init(AL_TFrmBufPool* pPool)
{
  for(int i = 0; i < FRM_BUF_POOL_SIZE; i++)
  {
    sRecBuffers_Reset(&pPool->array[i].tRecBuffers);
    pPool->array[i].iNext = -1;
    pPool->array[i].iAccessCnt = -1;
    pPool->array[i].bWillBeOutputted = false;
  }

  pPool->iFifoHead = -1;
  pPool->iFifoTail = -1;
}

/*************************************************************************/
static bool sFrmBufPool_Init(AL_TFrmBufPool* pPool, AL_TAllocator* pAllocator, bool bHasSecondOutputFrame)
{
  (void)pAllocator;
  (void)bHasSecondOutputFrame;

  pPool->Mutex = Rtos_CreateMutex();

  if(!pPool->Mutex)
    goto fail_alloc_mutex;

  pPool->Semaphore = Rtos_CreateSemaphore(0);

  if(!pPool->Semaphore)
    goto fail_alloc_sem_free;

  pPool->iBufNumber = 0;
  sFrmBufPoolFifo_Init(pPool);

  pPool->bHasSecondOutputFrame = bHasSecondOutputFrame;
  pPool->pSecondOutputAllocator = pAllocator;
  AL_DecFramePool_Init(&pPool->tSecondOutputPool);

  return true;
  fail_alloc_sem_free:
  Rtos_DeleteMutex(pPool->Mutex);
  fail_alloc_mutex:
  return false;
}

/*************************************************************************/
static void sEnsureRecBufferAreRemoved(AL_TFrmBufPool* pPool)
{
  for(int i = 0; i < FRM_BUF_POOL_SIZE; i++)
  {
    if(pPool->array[i].iAccessCnt == 0)
    {
      AL_TRecBuffers tBuffers;
      Rtos_Memcpy(&tBuffers, sFrmBufPool_GetBufferFromID(pPool, i), sizeof(tBuffers));
      sFrmBufPool_RemoveID(pPool, i);
      sRecBuffers_Release(&tBuffers, pPool);
    }

    Rtos_Assert(pPool->array[i].iAccessCnt == -1);
  }
}

/*************************************************************************/
static void sFrmBufPool_Deinit(AL_TFrmBufPool* pPool)
{
  Rtos_Assert(pPool->iFifoHead == -1);
  Rtos_Assert(pPool->iFifoTail == -1);

  sEnsureRecBufferAreRemoved(pPool);

  AL_DecFramePool_Deinit(&pPool->tSecondOutputPool);

  Rtos_DeleteSemaphore(pPool->Semaphore);
  Rtos_DeleteMutex(pPool->Mutex);
}

/*************************************************************************/
static void sFrmBufPool_DecrementBufID(AL_TFrmBufPool* pPool, int iFrameID, bool bForceOutput)
{
  Rtos_GetMutex(pPool->Mutex);
  Rtos_Assert(iFrameID >= 0 && iFrameID < FRM_BUF_POOL_SIZE);
  AL_TFrameFifo* pFrame = &pPool->array[iFrameID];
  Rtos_Assert(pFrame->iAccessCnt >= 1);
  pFrame->iAccessCnt--;

  if(pFrame->iAccessCnt == 0 && !pFrame->bOutEarly)
  {
    bool bWillBeOutputted = pFrame->bWillBeOutputted;
    AL_TRecBuffers tBuffers;
    Rtos_Memcpy(&tBuffers, sFrmBufPool_GetBufferFromID(pPool, iFrameID), sizeof(tBuffers));
    sFrmBufPool_RemoveID(pPool, iFrameID);

    if((!bWillBeOutputted) || bForceOutput)
    {
      bool const bNotInFifo = sFrmBufPoolFifo_IsInFifo(pPool, sRecBuffers_GetDisplayBuffer(&tBuffers, pPool)) == false;
      (void)bNotInFifo;
      Rtos_Assert(bNotInFifo);
      sFrmBufPoolFifo_PushBack(pPool, &tBuffers);
    }
    else
      sRecBuffers_Release(&tBuffers, pPool);
  }

  Rtos_ReleaseMutex(pPool->Mutex);
}

/*************************************************************************/
static void sFrmBufPool_OutputBufID(AL_TFrmBufPool* pPool, int iFrameID)
{
  Rtos_GetMutex(pPool->Mutex);
  Rtos_Assert(iFrameID >= 0 && iFrameID < FRM_BUF_POOL_SIZE);
  AL_TFrameFifo* pFrame = &pPool->array[iFrameID];
  Rtos_Assert(pFrame->bWillBeOutputted == false);
  pFrame->bWillBeOutputted = true;
  Rtos_ReleaseMutex(pPool->Mutex);
}

/*************************************************************************/
static void sFrmBufPool_IncrementBufID(AL_TFrmBufPool* pPool, int iFrameID)
{
  Rtos_GetMutex(pPool->Mutex);
  Rtos_Assert(iFrameID >= 0 && iFrameID < FRM_BUF_POOL_SIZE);
  AL_TFrameFifo* pFrame = &pPool->array[iFrameID];
  Rtos_Assert(pFrame->iAccessCnt >= 0);
  pFrame->iAccessCnt++;
  Rtos_ReleaseMutex(pPool->Mutex);
}

/*****************************************************************************/
static void sFrmBufPool_Terminate(AL_TFrmBufPool* pPool)
{
  (void)pPool; // Nothing to do
}

/*************************************************************************/
static bool sMvBufPool_Init(AL_TMvBufPool* pPool, int iMaxBuf)
{
  Rtos_Assert(iMaxBuf <= MAX_DPB_SIZE);

  for(int i = 0; i < iMaxBuf; ++i)
  {
    pPool->pFreeIDs[i] = i;
    pPool->iAccessCnt[i] = 0;
    AL_CleanupMemory(pPool->pMvBufs[i].tMD.pVirtualAddr, pPool->pMvBufs[i].tMD.uSize);
    AL_CleanupMemory(pPool->pPocBufs[i].tMD.pVirtualAddr, pPool->pPocBufs[i].tMD.uSize);
  }

  pPool->iBufCnt = iMaxBuf;

  for(int i = iMaxBuf; i < MAX_DPB_SIZE; ++i)
  {
    pPool->pFreeIDs[i] = UndefID;
    pPool->iAccessCnt[i] = 0;
  }

  pPool->iFreeCnt = iMaxBuf;
  pPool->Mutex = Rtos_CreateMutex();

  if(!pPool->Mutex)
    goto fail_alloc_mutex;

  pPool->Semaphore = Rtos_CreateSemaphore(iMaxBuf);

  if(!pPool->Semaphore)
    goto fail_alloc_sem;

  return true;
  fail_alloc_sem:
  Rtos_DeleteMutex(pPool->Mutex);
  fail_alloc_mutex:
  return false;
}

/*************************************************************************/
static void sMvBufPool_Deinit(AL_TMvBufPool* pPool)
{
  Rtos_DeleteSemaphore(pPool->Semaphore);
  Rtos_DeleteMutex(pPool->Mutex);
}

/*************************************************************************/
static uint8_t sMvBufPool_GetFreeBufID(AL_TMvBufPool* pPool)
{
  Rtos_GetSemaphore(pPool->Semaphore, AL_WAIT_FOREVER);

  Rtos_GetMutex(pPool->Mutex);
  uint8_t uMvID = pPool->pFreeIDs[--pPool->iFreeCnt];
  Rtos_Assert(pPool->iAccessCnt[uMvID] == 0);
  pPool->iAccessCnt[uMvID] = 1;

  AL_CleanupMemory(pPool->pMvBufs[uMvID].tMD.pVirtualAddr, pPool->pMvBufs[uMvID].tMD.uSize);

  Rtos_ReleaseMutex(pPool->Mutex);

  return uMvID;
}

/*************************************************************************/
static void sMvBufPool_DecrementBufID(AL_TMvBufPool* pPool, uint8_t uMvID)
{
  Rtos_Assert(uMvID < MAX_DPB_SIZE);

  Rtos_GetMutex(pPool->Mutex);

  bool bFree = false;

  if(pPool->iAccessCnt[uMvID])
  {
    bFree = (--pPool->iAccessCnt[uMvID] == 0);

    if(bFree)
      pPool->pFreeIDs[pPool->iFreeCnt++] = uMvID;
  }

  Rtos_ReleaseMutex(pPool->Mutex);

  if(bFree)
    Rtos_ReleaseSemaphore(pPool->Semaphore);
}

/*************************************************************************/
static void sMvBufPool_IncrementBufID(AL_TMvBufPool* pPool, int iMvID)
{
  Rtos_Assert(iMvID < FRM_BUF_POOL_SIZE);
  Rtos_GetMutex(pPool->Mutex);
  Rtos_AtomicIncrement(&(pPool->iAccessCnt[iMvID]));
  Rtos_ReleaseMutex(pPool->Mutex);
}

/*****************************************************************************/
static void sMvBufPool_Terminate(AL_TMvBufPool* pPool)
{
  for(int i = 0; i < pPool->iBufCnt; ++i)
    Rtos_GetSemaphore(pPool->Semaphore, AL_WAIT_FOREVER);

  for(int i = 0; i < pPool->iBufCnt; ++i)
    Rtos_ReleaseSemaphore(pPool->Semaphore);
}

/*************************************************************************/
static void sPictMngr_DecrementFrmBuf(void* pUserParam, int iFrameID)
{
  Rtos_Assert(pUserParam);
  AL_TPictMngrCtx* pCtx = (AL_TPictMngrCtx*)pUserParam;
  sFrmBufPool_DecrementBufID(&pCtx->FrmBufPool, iFrameID, pCtx->bForceOutput);
}

/*************************************************************************/
static void sPictMngr_IncrementFrmBuf(void* pUserParam, int iFrameID)
{
  Rtos_Assert(pUserParam);
  AL_TPictMngrCtx* pCtx = (AL_TPictMngrCtx*)pUserParam;
  sFrmBufPool_IncrementBufID(&pCtx->FrmBufPool, iFrameID);
}

/*************************************************************************/
static void sPictMngr_OutputFrmBuf(void* pUserParam, int iFrameID)
{
  Rtos_Assert(pUserParam);
  AL_TPictMngrCtx* pCtx = (AL_TPictMngrCtx*)pUserParam;
  sFrmBufPool_OutputBufID(&pCtx->FrmBufPool, iFrameID);
}

/*************************************************************************/
static void sPictMngr_IncrementMvBuf(void* pUserParam, uint8_t uMvID)
{
  Rtos_Assert(pUserParam);
  AL_TPictMngrCtx* pCtx = (AL_TPictMngrCtx*)pUserParam;
  sMvBufPool_IncrementBufID(&pCtx->MvBufPool, uMvID);
}

/*************************************************************************/
static void sPictMngr_DecrementMvBuf(void* pUserParam, uint8_t uMvID)
{
  Rtos_Assert(pUserParam);
  AL_TPictMngrCtx* pCtx = (AL_TPictMngrCtx*)pUserParam;
  sMvBufPool_DecrementBufID(&pCtx->MvBufPool, uMvID);
}

/*****************************************************************************/
static bool CheckPictMngrInitParameter(AL_TPictMngrParam const* pParam)
{
  if(pParam->iSizeMV < 0)
    return false;

  if(pParam->iNumMV < 0)
    return false;

  if(pParam->iNumDPBRef < 0)
    return false;

  if(pParam->iNumMV < pParam->iNumDPBRef)
    return false;

  if(pParam->eDPBMode >= AL_DPB_MAX_ENUM)
    return false;

  if(pParam->eFbStorageMode >= AL_FB_MAX_ENUM)
    return false;

  return true;
}

/*****************************************************************************/
bool AL_PictMngr_PreInit(AL_TPictMngrCtx* pCtx)
{
  if(!pCtx)
    return false;

  pCtx->FirstInitMutex = Rtos_CreateMutex();

  if(!pCtx->FirstInitMutex)
    return false;

  pCtx->bFirstInit = false;
  pCtx->FrmBufPool.isDecommited = false;

  return true;
}

/*****************************************************************************/
bool AL_PictMngr_BasicInit(AL_TPictMngrCtx* pCtx, AL_TPictMngrParam const* pParam)
{
  if(!pCtx)
    return false;

  if(!CheckPictMngrInitParameter(pParam))
    return false;

  if(!sMvBufPool_Init(&pCtx->MvBufPool, pParam->iNumMV))
    return false;

  AL_TDpbCallback tCallbacks =
  {
    sPictMngr_IncrementFrmBuf,
    sPictMngr_DecrementFrmBuf,
    sPictMngr_OutputFrmBuf,
    sPictMngr_IncrementMvBuf,
    sPictMngr_DecrementMvBuf,
    pCtx,
  };

  if(!AL_Dpb_Init(&pCtx->DPB, pParam->iNumDPBRef, pParam->eDPBMode, tCallbacks))
    return false;

  pCtx->eFbStorageMode = pParam->eFbStorageMode;
  pCtx->iSizeMV = pParam->iSizeMV;
  pCtx->iCurFramePOC = 0;

  pCtx->iPrevPocLSB = 0;
  pCtx->iPrevPocMSB = 0;

  pCtx->uFrameID = UndefID;
  pCtx->uMvID = UndefID;

  pCtx->iPrevFrameNum = -1;
  Rtos_GetMutex(pCtx->FirstInitMutex);
  pCtx->bFirstInit = true;
  Rtos_ReleaseMutex(pCtx->FirstInitMutex);
  pCtx->bForceOutput = pParam->bForceOutput;
  pCtx->bCompleteInit = false;

  pCtx->tOutputPosition = pParam->tOutputPosition;

  return true;
}

bool AL_PictMngr_CompleteInit(AL_TPictMngrCtx* pCtx, AL_TAllocator* pAllocator, bool bEnableSecondOutput)
{
  bool bSuccess = sFrmBufPool_Init(&pCtx->FrmBufPool, pAllocator, bEnableSecondOutput);
  pCtx->bCompleteInit = bSuccess;
  return bSuccess;
}

/*****************************************************************************/

bool AL_PictMngr_IsInitComplete(AL_TPictMngrCtx const* pCtx)
{
  return pCtx->bCompleteInit;
}

/*****************************************************************************/
void AL_PictMngr_Terminate(AL_TPictMngrCtx* pCtx)
{
  if(!pCtx->bFirstInit)
    return;

  AL_Dpb_Terminate(&pCtx->DPB);

  sFrmBufPool_Terminate(&pCtx->FrmBufPool);
  sMvBufPool_Terminate(&pCtx->MvBufPool);
}

/*****************************************************************************/
void AL_PictMngr_Deinit(AL_TPictMngrCtx* pCtx)
{
  Rtos_DeleteMutex(pCtx->FirstInitMutex);

  if(!pCtx->bFirstInit)
    return;

  sMvBufPool_Deinit(&pCtx->MvBufPool);
  sFrmBufPool_Deinit(&pCtx->FrmBufPool);
  AL_Dpb_Deinit(&pCtx->DPB);
}

/*****************************************************************************/
void AL_PictMngr_LockRefID(AL_TPictMngrCtx* pCtx, uint8_t uNumRef, uint8_t* pRefFrameID, uint8_t* pRefMvID)
{
  for(uint8_t uRef = 0; uRef < uNumRef; ++uRef)
  {
    sPictMngr_IncrementFrmBuf(pCtx, pRefFrameID[uRef]);
    sPictMngr_IncrementMvBuf(pCtx, pRefMvID[uRef]);
  }
}

/*****************************************************************************/
void AL_PictMngr_UnlockRefID(AL_TPictMngrCtx* pCtx, uint8_t uNumRef, uint8_t* pRefFrameID, uint8_t* pRefMvID)
{
  for(uint8_t uRef = 0; uRef < uNumRef; ++uRef)
  {
    sPictMngr_DecrementFrmBuf(pCtx, pRefFrameID[uRef]);
    sPictMngr_DecrementMvBuf(pCtx, pRefMvID[uRef]);
  }
}

/*****************************************************************************/
uint8_t AL_PictMngr_GetCurrentFrmID(AL_TPictMngrCtx const* pCtx)
{
  return pCtx->uFrameID;
}

/*****************************************************************************/
uint8_t AL_PictMngr_GetCurrentMvID(AL_TPictMngrCtx const* pCtx)
{
  return pCtx->uMvID;
}

/*****************************************************************************/
int32_t AL_PictMngr_GetCurrentPOC(AL_TPictMngrCtx const* pCtx)
{
  return pCtx->iCurFramePOC;
}

/***************************************************************************/
static void ChangePictChromaMode(AL_TBuffer* pBuf, AL_EChromaMode eChromaMode)
{
  TFourCC tFourCC = AL_PixMapBuffer_GetFourCC(pBuf);
  AL_TPicFormat tPicFmt;
  bool const bSuccess = AL_GetPicFormat(tFourCC, &tPicFmt);
  (void)bSuccess;
  Rtos_Assert(bSuccess);

  if(eChromaMode == tPicFmt.eChromaMode)
    return;
  tPicFmt = AL_GetDecPicFormat(eChromaMode, tPicFmt.uBitDepth, tPicFmt.eStorageMode, tPicFmt.bCompressed, AL_PLANE_MODE_MAX_ENUM);
  tFourCC = AL_GetDecFourCC(tPicFmt);
  AL_PixMapBuffer_SetFourCC(pBuf, tFourCC);
}

/***************************************************************************/
bool AL_PictMngr_BeginFrame(AL_TPictMngrCtx* pCtx, bool bStartsNewCVS, AL_TDimension tDim, AL_EChromaMode eDecodedChromaMode)
{
  pCtx->uFrameID = sFrmBufPoolFifo_Pop(&pCtx->FrmBufPool);

  if(pCtx->uFrameID == UndefID)
    return false;

  pCtx->uMvID = sMvBufPool_GetFreeBufID(&pCtx->MvBufPool);
  Rtos_Assert(pCtx->uMvID != UndefID);

  AL_TRecBuffers* pBuffers = sFrmBufPool_GetBufferFromID(&pCtx->FrmBufPool, pCtx->uFrameID);

  AL_PixMapBuffer_SetDimension(pBuffers->pFrame, tDim);
  ChangePictChromaMode(pBuffers->pFrame, eDecodedChromaMode);

  if(pCtx->FrmBufPool.bHasSecondOutputFrame)
  {
    AL_TDimension outputDim = tDim;
    AL_PixMapBuffer_SetDimension(pBuffers->pSecondOutputFrame, outputDim);

    bool bChangeChromaMode = true;

    if(bChangeChromaMode)
      ChangePictChromaMode(pBuffers->pSecondOutputFrame, eDecodedChromaMode);
  }

  pCtx->FrmBufPool.array[pCtx->uFrameID].bStartsNewCVS = bStartsNewCVS;

  return true;
}

/*****************************************************************************/
static void sFrmBufPool_SignalCallbackReleaseIsDone(AL_TFrmBufPool* pPool, AL_TBuffer* pReleasedFrame)
{
  Rtos_GetMutex(pPool->Mutex);
  int const iFrameID = sFrmBufPool_GetFrameIDFromDisplay(pPool, pReleasedFrame);
  Rtos_Assert(iFrameID >= 0 && iFrameID < FRM_BUF_POOL_SIZE);
  bool const bNotInFifo = sFrmBufPoolFifo_IsInFifo(pPool, pReleasedFrame) == false;
  (void)bNotInFifo;
  Rtos_Assert(bNotInFifo);
  Rtos_Assert(pPool->array[iFrameID].bWillBeOutputted || pPool->array[iFrameID].bOutEarly);
  pPool->array[iFrameID].bWillBeOutputted = false;
  AL_TRecBuffers tBuffers;
  Rtos_Memcpy(&tBuffers, sFrmBufPool_GetBufferFromID(pPool, iFrameID), sizeof(tBuffers));
  sFrmBufPool_RemoveID(pPool, iFrameID);
  sRecBuffers_Release(&tBuffers, pPool);
  Rtos_ReleaseMutex(pPool->Mutex);
}

/***************************************************************************/
void AL_PictMngr_CancelFrame(AL_TPictMngrCtx* pCtx)
{

  if(pCtx->uMvID != UndefID)
  {
    sMvBufPool_DecrementBufID(&pCtx->MvBufPool, pCtx->uMvID);
    pCtx->uMvID = UndefID;
  }

  if(pCtx->uFrameID != UndefID)
  {
    sFrmBufPool_DecrementBufID(&pCtx->FrmBufPool, pCtx->uFrameID, pCtx->bForceOutput);
    pCtx->uFrameID = UndefID;
  }
}

/*************************************************************************/
void AL_PictMngr_Flush(AL_TPictMngrCtx* pCtx)
{
  if(!pCtx->bFirstInit)
    return;

  AL_Dpb_Flush(&pCtx->DPB);
  AL_Dpb_BeginNewSeq(&pCtx->DPB);
}

/*************************************************************************/
void AL_PictMngr_UpdateDPBInfo(AL_TPictMngrCtx* pCtx, uint8_t uMaxRef)
{
  AL_Dpb_SetNumRef(&pCtx->DPB, uMaxRef);
}

/*****************************************************************************/
uint8_t AL_PictMngr_GetLastPicID(AL_TPictMngrCtx const* pCtx)
{
  return AL_Dpb_GetLastPicID(&pCtx->DPB);
}

/*****************************************************************************/
void AL_PictMngr_Insert(AL_TPictMngrCtx* pCtx, int iFramePOC, AL_EPicStruct ePicStruct, uint32_t uPocLsb, int iFrameID, uint8_t uMvID, uint8_t pic_output_flag, AL_EMarkingRef eMarkingFlag, uint8_t uNonExisting, AL_ENut eNUT, uint8_t uSubpicFlag)
{
  uint8_t uNode = AL_Dpb_GetNextFreeNode(&pCtx->DPB);

  if(uNode == uEndOfList)
    return;

  if(!AL_Dpb_NodeIsReset(&pCtx->DPB, uNode))
    AL_Dpb_Remove(&pCtx->DPB, uNode);

  AL_Dpb_Insert(&pCtx->DPB, iFramePOC, ePicStruct, uPocLsb, uNode, iFrameID, uMvID, pic_output_flag, eMarkingFlag, uNonExisting, eNUT, uSubpicFlag);
}

/***************************************************************************/
static void sFrmBufPool_UpdateCRC(AL_TFrmBufPool* pPool, int iFrameID, uint32_t uCRC)
{
  Rtos_Assert(iFrameID >= 0 && iFrameID < FRM_BUF_POOL_SIZE);
  pPool->array[iFrameID].uCRC = uCRC;
}

/***************************************************************************/
static void sFrmBufPool_UpdateCrop(AL_TFrmBufPool* pPool, int iFrameID, AL_TCropInfo const* pCrop)
{
  Rtos_Assert(iFrameID >= 0 && iFrameID < FRM_BUF_POOL_SIZE && pCrop);
  pPool->array[iFrameID].tCrop = *pCrop;
}

/***************************************************************************/
static void sFrmBufPool_UpdatePicStruct(AL_TFrmBufPool* pPool, int iFrameID, AL_EPicStruct ePicStruct)
{
  Rtos_Assert(iFrameID >= 0 && iFrameID < FRM_BUF_POOL_SIZE);
  pPool->array[iFrameID].ePicStruct = ePicStruct;
}

/***************************************************************************/
static void sFrmBufPool_UpdateError(AL_TFrmBufPool* pPool, int iFrameID, AL_ERR error)
{
  Rtos_Assert(iFrameID >= 0 && iFrameID < FRM_BUF_POOL_SIZE);
  pPool->array[iFrameID].eError = error;
}

/***************************************************************************/
void AL_PictMngr_UpdateDisplayBufferCRC(AL_TPictMngrCtx* pCtx, int iFrameID, uint32_t uCRC)
{
  sFrmBufPool_UpdateCRC(&pCtx->FrmBufPool, iFrameID, uCRC);
}

/***************************************************************************/
void AL_PictMngr_UpdateDisplayBufferCrop(AL_TPictMngrCtx* pCtx, int iFrameID, AL_TCropInfo const* pCrop)
{
  sFrmBufPool_UpdateCrop(&pCtx->FrmBufPool, iFrameID, pCrop);
}

/***************************************************************************/
void AL_PictMngr_UpdateDisplayBufferPicStruct(AL_TPictMngrCtx* pCtx, int iFrameID, AL_EPicStruct ePicStruct)
{
  sFrmBufPool_UpdatePicStruct(&pCtx->FrmBufPool, iFrameID, ePicStruct);
}

/***************************************************************************/
void AL_PictMngr_UpdateDisplayBufferError(AL_TPictMngrCtx* pCtx, int iFrameID, AL_ERR eError)
{
  sFrmBufPool_UpdateError(&pCtx->FrmBufPool, iFrameID, eError);
}

/***************************************************************************/
void AL_PictMngr_EndDecoding(AL_TPictMngrCtx* pCtx, int iFrameID)
{
  AL_Dpb_EndDecoding(&pCtx->DPB, iFrameID);
}

/***************************************************************************/
void AL_PictMngr_UnlockID(AL_TPictMngrCtx* pCtx, int iFrameID, int iMotionVectorID)
{
  sFrmBufPool_DecrementBufID(&pCtx->FrmBufPool, iFrameID, pCtx->bForceOutput);
  sMvBufPool_DecrementBufID(&pCtx->MvBufPool, iMotionVectorID);
}

/***************************************************************************/
static void sFrmBufPool_GetInfoDecode(AL_TPictMngrCtx* pCtx, int iFrameID, AL_TInfoDecode* pInfo, bool* pStartsNewCVS, AL_EFbStorageMode eFbStorageMode, bool bDisplayInfo)
{
  Rtos_Assert(pInfo);

  AL_TFrmBufPool* pPool = &pCtx->FrmBufPool;

  AL_TRecBuffers* pBuffers = sFrmBufPool_GetBufferFromID(pPool, iFrameID);
  bool const bRecNotNull = sRecBuffers_AreNotNull(pBuffers, pPool);
  (void)bRecNotNull;
  Rtos_Assert(bRecNotNull);

  AL_TBuffer* pBuf = bDisplayInfo ? sRecBuffers_GetDisplayBuffer(pBuffers, pPool) : pBuffers->pFrame;
  AL_TPixMapMetaData* pMetaSrc = (AL_TPixMapMetaData*)AL_Buffer_GetMetaData(pBuf, AL_META_TYPE_PIXMAP);
  Rtos_Assert(pMetaSrc);

  pInfo->tCrop = pPool->array[iFrameID].tCrop;
  pInfo->uBitDepthY = pInfo->uBitDepthC = AL_GetBitDepth(pMetaSrc->tFourCC);
  pInfo->uCRC = pPool->array[iFrameID].uCRC;
  pInfo->tDim = AL_PixMapBuffer_GetDimension(pBuf);
  pInfo->eFbStorageMode = eFbStorageMode;
  pInfo->ePicStruct = pPool->array[iFrameID].ePicStruct;
  TFourCC tFourCC = AL_PixMapBuffer_GetFourCC(pBuf);
  Rtos_Assert(tFourCC != 0);
  pInfo->eChromaMode = AL_GetChromaMode(tFourCC);
  pInfo->eOutputID = AL_OUTPUT_MAIN;
  pInfo->tPos = pCtx->tOutputPosition;

  if(pStartsNewCVS)
    *pStartsNewCVS = pPool->array[iFrameID].bStartsNewCVS;
}

/***************************************************************************/
static AL_TBuffer* AL_PictMngr_GetDisplayBuffer2(AL_TPictMngrCtx* pCtx, AL_TInfoDecode* pInfo, bool* pStartsNewCVS, int iFrameID)
{
  if(iFrameID == UndefID)
    return NULL;

  AL_EFbStorageMode eOutputStorageMode = pCtx->eFbStorageMode;

  if(pCtx->FrmBufPool.bHasSecondOutputFrame)
  {
    eOutputStorageMode = AL_FB_RASTER;
  }

  if(pInfo)
    sFrmBufPool_GetInfoDecode(pCtx, iFrameID, pInfo, pStartsNewCVS, eOutputStorageMode, true);

  AL_TRecBuffers* pRecBuffers = sFrmBufPool_GetBufferFromID(&pCtx->FrmBufPool, iFrameID);

  AL_TBuffer* displayBuffer = sRecBuffers_GetDisplayBuffer(pRecBuffers, &pCtx->FrmBufPool);

  if(pInfo)
  {
    AL_TDisplayInfoMetaData* pMeta = (AL_TDisplayInfoMetaData*)(AL_Buffer_GetMetaData(displayBuffer, AL_META_TYPE_DISPLAY_INFO));

    if(pMeta)
    {
      pMeta->ePicStruct = pInfo->ePicStruct;
      pMeta->tCrop = pInfo->tCrop;
      pMeta->uCrc = pInfo->uCRC;
      pMeta->uStreamBitDepthY = pInfo->uBitDepthY;
      pMeta->uStreamBitDepthC = pInfo->uBitDepthC;
      pMeta->eOutputID = pInfo->eOutputID;

    }
  }

  return displayBuffer;
}

/***************************************************************************/
AL_TBuffer* AL_PictMngr_ForceDisplayBuffer(AL_TPictMngrCtx* pCtx, AL_TInfoDecode* pInfo, bool* pStartsNewCVS, int iFrameID)
{
  Rtos_Assert(pCtx->bForceOutput);
  AL_TFrmBufPool* pPool = &pCtx->FrmBufPool;
  Rtos_GetMutex(pPool->Mutex);
  AL_TFrameFifo* pFrame = &pPool->array[iFrameID];
  pFrame->bOutEarly = true;
  Rtos_ReleaseMutex(pPool->Mutex);
  return AL_PictMngr_GetDisplayBuffer2(pCtx, pInfo, pStartsNewCVS, iFrameID);
}

/*************************************************************************/
AL_TBuffer* AL_PictMngr_GetDisplayBuffer(AL_TPictMngrCtx* pCtx, AL_TInfoDecode* pInfo, bool* pStartsNewCVS)
{
  if(!pCtx->bFirstInit)
    return NULL;

  return AL_PictMngr_GetDisplayBuffer2(pCtx, pInfo, pStartsNewCVS, AL_Dpb_GetDisplayBuffer(&pCtx->DPB));
}

/*************************************************************************/
static void sPictMngr_ReleaseDisplayBuffer(AL_TFrmBufPool* pPool, int iFrameID)
{
  Rtos_GetMutex(pPool->Mutex);
  Rtos_Assert(iFrameID >= 0 && iFrameID < FRM_BUF_POOL_SIZE);

  AL_TFrameFifo* pFrame = &pPool->array[iFrameID];

  if(pFrame->bOutEarly)
  {
    pFrame->bOutEarly = false;

    if((pFrame->iAccessCnt == 0) && pFrame->bWillBeOutputted)
    {
      pFrame->bWillBeOutputted = false;
      AL_TRecBuffers tBuffers;
      Rtos_Memcpy(&tBuffers, sFrmBufPool_GetBufferFromID(pPool, iFrameID), sizeof(tBuffers));
      sFrmBufPool_RemoveID(pPool, iFrameID);
      bool const bNotInFifo = sFrmBufPoolFifo_IsInFifo(pPool, sRecBuffers_GetDisplayBuffer(&tBuffers, pPool)) == false;
      (void)bNotInFifo;
      Rtos_Assert(bNotInFifo);
      sFrmBufPoolFifo_PushBack(pPool, &tBuffers);
    }

    Rtos_ReleaseMutex(pPool->Mutex);
    return;
  }

  Rtos_Assert(pFrame->bWillBeOutputted == true);

  pFrame->bWillBeOutputted = false;

  if(pFrame->iAccessCnt == 0)
  {
    AL_TRecBuffers tBuffers;
    Rtos_Memcpy(&tBuffers, sFrmBufPool_GetBufferFromID(pPool, iFrameID), sizeof(tBuffers));
    sFrmBufPool_RemoveID(pPool, iFrameID);
    bool const bNotInFifo = sFrmBufPoolFifo_IsInFifo(pPool, sRecBuffers_GetDisplayBuffer(&tBuffers, pPool)) == false;
    (void)bNotInFifo;
    Rtos_Assert(bNotInFifo);
    sFrmBufPoolFifo_PushBack(pPool, &tBuffers);
  }

  Rtos_ReleaseMutex(pPool->Mutex);
}

/*************************************************************************/
AL_TBuffer* AL_PictMngr_GetDisplayBufferFromID(AL_TPictMngrCtx* pCtx, int iFrameID)
{
  Rtos_Assert(pCtx);

  AL_TRecBuffers* pRecBuffers = sFrmBufPool_GetBufferFromID(&pCtx->FrmBufPool, iFrameID);
  return sRecBuffers_GetDisplayBuffer(pRecBuffers, &pCtx->FrmBufPool);
}

/*************************************************************************/
AL_TBuffer* AL_PictMngr_GetRecBufferFromID(AL_TPictMngrCtx* pCtx, int iFrameID)
{
  Rtos_Assert(pCtx);
  return sFrmBufPool_GetBufferFromID(&pCtx->FrmBufPool, iFrameID)->pFrame;
}

/*************************************************************************/
bool AL_PictMngr_GetFrameEncodingError(AL_TPictMngrCtx const* pCtx, AL_TBuffer const* pDisplayBuf, AL_ERR* pError)
{
  if(pDisplayBuf == NULL)
    return false;

  int iFrameID = sFrmBufPool_GetFrameIDFromBuf(&pCtx->FrmBufPool, pDisplayBuf);

  if(pError != NULL && iFrameID != -1)
  {
    *pError = pCtx->FrmBufPool.array[iFrameID].eError;
    return true;
  }

  return false;
}

/*************************************************************************/
static bool sFrmBufPool_FillRecBuffer(AL_TFrmBufPool* pPool, AL_TBuffer* pDisplayBuf, AL_TRecBuffers* pRecBuffers)
{
  (void)pPool;

  if(pPool->bHasSecondOutputFrame)
  {
    pRecBuffers->pFrame = AL_DecFramePool_Get(&pPool->tSecondOutputPool);

    if(!pRecBuffers->pFrame)
      return false;
    pRecBuffers->pSecondOutputFrame = pDisplayBuf;
  }
  else
  {

  pRecBuffers->pFrame = pDisplayBuf;
  pRecBuffers->pSecondOutputFrame = NULL;
}

  AL_Buffer_Ref(pDisplayBuf);

  return true;
}

/*************************************************************************/
static bool sFrmBufPool_PutDisplayBuffer(AL_TFrmBufPool* pPool, AL_TBuffer* pBuf)
{
  Rtos_GetMutex(pPool->Mutex);
  bool bSucceed = false;

  Rtos_Assert(pBuf);

  int const iFrameID = sFrmBufPool_GetFrameIDFromDisplay(pPool, pBuf);

  if(iFrameID == -1)
  {
    AL_TRecBuffers tRecBuffers;

    if(sFrmBufPool_FillRecBuffer(pPool, pBuf, &tRecBuffers))
    {
      if(sFrmBufPoolFifo_PushBack(pPool, &tRecBuffers))
        bSucceed = true;
      else
        sRecBuffers_Release(&tRecBuffers, pPool);
    }
  }
  else
  {
    sPictMngr_ReleaseDisplayBuffer(pPool, iFrameID);
    bSucceed = true;
  }

  Rtos_ReleaseMutex(pPool->Mutex);

  return bSucceed;
}

/*************************************************************************/
bool AL_PictMngr_PutDisplayBuffer(AL_TPictMngrCtx* pCtx, AL_TBuffer* pBuf)
{
  return sFrmBufPool_PutDisplayBuffer(&pCtx->FrmBufPool, pBuf);
}

/*****************************************************************************/
void AL_PictMngr_SignalCallbackDisplayIsDone(AL_TPictMngrCtx* pCtx)
{
  AL_Dpb_ReleaseDisplayBuffer(&pCtx->DPB);
}

/*****************************************************************************/
void AL_PictMngr_SignalCallbackReleaseIsDone(AL_TPictMngrCtx* pCtx, AL_TBuffer* pReleasedFrame)
{
  sFrmBufPool_SignalCallbackReleaseIsDone(&pCtx->FrmBufPool, pReleasedFrame);
}

/*****************************************************************************/
void AL_PictMngr_DecommitPool(AL_TPictMngrCtx* pCtx)
{
  Rtos_GetMutex(pCtx->FirstInitMutex);

  if(!pCtx->bFirstInit)
  {
    pCtx->FrmBufPool.isDecommited = true;
    Rtos_ReleaseMutex(pCtx->FirstInitMutex);
    return;
  }
  Rtos_ReleaseMutex(pCtx->FirstInitMutex);

  if(pCtx->bCompleteInit)
    sFrmBufPoolFifo_Decommit(&pCtx->FrmBufPool);
}

/*****************************************************************************/
static AL_TBuffer* sFrmBufPoolFifo_FlushOneDisplayBuffer(AL_TFrmBufPool* pPool)
{
  Rtos_GetMutex(pPool->Mutex);

  int iFifoHead = pPool->iFifoHead;

  if((iFifoHead == -1) && (pPool->iFifoTail == -1))
  {
    Rtos_ReleaseMutex(pPool->Mutex);
    return NULL;
  }

  Rtos_Assert(iFifoHead != -1);
  AL_TFrameFifo const* pHeadBuf = &pPool->array[iFifoHead];
  (void)pHeadBuf;
  Rtos_Assert(pHeadBuf->iAccessCnt == 0);
  Rtos_Assert((!pHeadBuf->bOutEarly && (pHeadBuf->bWillBeOutputted == false)) || pHeadBuf->bOutEarly);

  int const iFrameID = RemoveBufferFromFifo(pPool);
  AL_TFrameFifo* removedBuf = &pPool->array[iFrameID];
  removedBuf->iAccessCnt = 0;

  if(!removedBuf->bOutEarly)
    removedBuf->bWillBeOutputted = true;
  AL_TRecBuffers* pBuffers = sFrmBufPool_GetBufferFromID(pPool, iFrameID);
  Rtos_ReleaseMutex(pPool->Mutex);

  return sRecBuffers_GetDisplayBuffer(pBuffers, pPool);
}

/*****************************************************************************/
AL_TBuffer* AL_PictMngr_GetUnusedDisplayBuffer(AL_TPictMngrCtx* pCtx)
{
  if(!pCtx->bFirstInit)
    return NULL;

  return sFrmBufPoolFifo_FlushOneDisplayBuffer(&pCtx->FrmBufPool);
}

/*****************************************************************************/
static void FillPocAndLongtermLists(AL_TDpb const* pDpb, TBufferPOC* pPoc, AL_TDecSliceParam const* pSP)
{
  int32_t* pPocList = (int32_t*)(pPoc->tMD.pVirtualAddr);
  uint32_t* pLongTermList = (uint32_t*)(pPoc->tMD.pVirtualAddr + POCBUFF_LONG_TERM_OFFSET);
  uint32_t* pSubpicList = (uint32_t*)(pPoc->tMD.pVirtualAddr + POCBUFF_SUBPIC_OFFSET);

  if(!pSP->FirstLcuSliceSegment)
  {
    *pLongTermList = 0;
    *pSubpicList = 0;

    for(int i = 0; i < MAX_REF; ++i)
      pPocList[i] = UINT32_MAX;
  }

  AL_Dpb_FillList(pDpb, pPocList, pLongTermList, pSubpicList);
}

/*****************************************************************************/
bool AL_PictMngr_GetBuffers(AL_TPictMngrCtx* pCtx, AL_TDecSliceParam const* pSP, TBuffer* pListVirtAddr, TBuffer* pListAddr, TBufferPOC* pPOC, TBufferMV* pMV, AL_TRecBuffers* pRecs)
{
  (void)pListVirtAddr; // only used for traces

  if(pCtx->uFrameID == UndefID)
    return false;

  AL_TRecBuffers* pRecBuffers = sFrmBufPool_GetBufferFromID(&pCtx->FrmBufPool, pCtx->uFrameID);
  pRecs->pFrame = pRecBuffers->pFrame;

  if(pCtx->FrmBufPool.bHasSecondOutputFrame)
    pRecs->pSecondOutputFrame = pRecBuffers->pSecondOutputFrame;

  if(pMV && pPOC)
  {
    if(pCtx->uMvID == UndefID)
      return false;

    pMV->tMD = pCtx->MvBufPool.pMvBufs[pCtx->uMvID].tMD;
    pPOC->tMD = pCtx->MvBufPool.pPocBufs[pCtx->uMvID].tMD;

    FillPocAndLongtermLists(&pCtx->DPB, pPOC, (AL_TDecSliceParam const*)pSP);
  }

  TFourCC tFourCC = AL_PixMapBuffer_GetFourCC(pRecs->pFrame);
  AL_TPicFormat tPicFormat;
  AL_GetPicFormat(tFourCC, &tPicFormat);

  AL_EPlaneId eFirstCPlane = AL_PLANE_MODE_PLANAR == tPicFormat.ePlaneMode ? AL_PLANE_U : AL_PLANE_UV;
  AL_EPlaneId eFirstCMapPlane = AL_PLANE_MODE_PLANAR == tPicFormat.ePlaneMode ? AL_PLANE_MAP_U : AL_PLANE_MAP_UV;

  if(pListAddr && pListAddr->tMD.pVirtualAddr)
  {
    TRefListOffsets tRefListOffsets;
    AL_GetRefListOffsets(&tRefListOffsets, AL_CODEC_INVALID, tPicFormat, sizeof(AL_PADDR));

    AL_PADDR* pAddr = (AL_PADDR*)pListAddr->tMD.pVirtualAddr;
    AL_PADDR* pColocMvList = (AL_PADDR*)(pListAddr->tMD.pVirtualAddr + tRefListOffsets.uColocMVOffset);
    AL_PADDR* pColocPocList = (AL_PADDR*)(pListAddr->tMD.pVirtualAddr + tRefListOffsets.uColocPocOffset);
    AL_PADDR* pFbcList = (AL_PADDR*)(pListAddr->tMD.pVirtualAddr + tRefListOffsets.uMapOffset);

    for(int i = 0; i < PIC_ID_POOL_SIZE; ++i)
    {
      uint8_t uNodeID = AL_Dpb_ConvertPicIDToNodeID(&pCtx->DPB, i);

      if(uNodeID == UndefID)
      {
        if(pSP->ValidConceal && pCtx->DPB.uCountPic)
          uNodeID = AL_Dpb_ConvertPicIDToNodeID(&pCtx->DPB, pSP->ConcealPicID);
      }

      AL_TBuffer const* pRefBuf = NULL;
      TBufferMV const* pRefMV = NULL;
      TBufferPOC const* pRefPOC = NULL;

      if(uNodeID != UndefID)
      {
        int iFrameID = AL_Dpb_GetFrmID_FromNode(&pCtx->DPB, uNodeID);
        uint8_t uMvID = AL_Dpb_GetMvID_FromNode(&pCtx->DPB, uNodeID);
        AL_TRecBuffers* pBufs = sFrmBufPool_GetBufferFromID(&pCtx->FrmBufPool, iFrameID);
        pRefBuf = pBufs->pFrame;
        pRefMV = &pCtx->MvBufPool.pMvBufs[uMvID];
        pRefPOC = &pCtx->MvBufPool.pPocBufs[uMvID];
      }
      else
      {
        // Use current Rec & MV Buffers to avoid non existing ref/coloc
        pRefBuf = pRecs->pFrame;
        pRefMV = pMV;
        pRefPOC = pPOC;
      }

      pAddr[i] = AL_PixMapBuffer_GetPlanePhysicalAddress(pRefBuf, AL_PLANE_Y);
      pAddr[PIC_ID_POOL_SIZE + i] = AL_PixMapBuffer_GetPlanePhysicalAddress(pRefBuf, eFirstCPlane);

      if(AL_PLANE_MODE_PLANAR == tPicFormat.ePlaneMode)
        pAddr[2 * PIC_ID_POOL_SIZE + i] = AL_PixMapBuffer_GetPlanePhysicalAddress(pRefBuf, AL_PLANE_V);
      pAddr[i] += AL_PixMapBuffer_GetPositionOffset(pRefBuf, pCtx->tOutputPosition, AL_PLANE_Y);
      pAddr[PIC_ID_POOL_SIZE + i] += AL_PixMapBuffer_GetPositionOffset(pRefBuf, pCtx->tOutputPosition, eFirstCPlane);

      if(AL_PLANE_MODE_PLANAR == tPicFormat.ePlaneMode)
        pAddr[2 * PIC_ID_POOL_SIZE + i] += AL_PixMapBuffer_GetPositionOffset(pRefBuf, pCtx->tOutputPosition, AL_PLANE_V);

      pFbcList[i] = 0;
      pFbcList[PIC_ID_POOL_SIZE + i] = 0;
      pFbcList[i] = AL_PixMapBuffer_GetPlanePhysicalAddress(pRefBuf, AL_PLANE_MAP_Y);
      pFbcList[PIC_ID_POOL_SIZE + i] = AL_PixMapBuffer_GetPlanePhysicalAddress(pRefBuf, eFirstCMapPlane);

      if(AL_PLANE_MODE_PLANAR == tPicFormat.ePlaneMode && AL_CHROMA_4_0_0 != tPicFormat.eChromaMode)
        pFbcList[2 * PIC_ID_POOL_SIZE + i] = AL_PixMapBuffer_GetPlanePhysicalAddress(pRefBuf, AL_PLANE_MAP_V);

      pColocMvList[i] = pRefMV->tMD.uPhysicalAddr;
      pColocPocList[i] = pRefPOC->tMD.uPhysicalAddr;

    }
  }
  return true;
}

/*************************************************************************/
bool AL_PictMngr_AllocInternalFrameBufs(AL_TPictMngrCtx* pCtx, AL_TDimension tDim, int8_t iBitdepth, AL_EChromaMode eChromaMode, bool bEnableFBC, int iNum)
{
  AL_EPlaneMode ePlaneMode = GetInternalBufPlaneMode(eChromaMode);
  AL_TPicFormat tPicFormat = AL_GetDecPicFormat(eChromaMode, iBitdepth, pCtx->eFbStorageMode, bEnableFBC, ePlaneMode);
  return AL_DecFramePool_Alloc(&pCtx->FrmBufPool.tSecondOutputPool, pCtx->FrmBufPool.pSecondOutputAllocator, tDim, tPicFormat, iNum);
}

/*!@}*/
