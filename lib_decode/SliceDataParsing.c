// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/****************************************************************************
   -----------------------------------------------------------------------------
 **************************************************************************//*!
   \addtogroup lib_decode_hls
   @{
   \file
 *****************************************************************************/

#include "SliceDataParsing.h"
#include "I_DecoderCtx.h"
#include "NalUnitParser.h"

#include "lib_decode/lib_decode.h"
#include "lib_decode/I_DecScheduler.h"

#include "lib_common/PixMapBufferInternal.h"
#include "lib_common/BufferHandleMeta.h"
#include "lib_common/BufferAPIInternal.h"

#include "lib_common_dec/RbspParser.h"

#include "lib_parsing/Avc_PictMngr.h"
#include "lib_decode/AvcHwBufInitialization.h"
#include "lib_parsing/Hevc_PictMngr.h"
#include "lib_decode/HevcHwBufInitialization.h"

#include "lib_assert/al_assert.h"

/******************************************************************************/
static void setBufferHandle(const TBuffer* in, TBuffer* out)
{
  out->tMD.uPhysicalAddr = in->tMD.uPhysicalAddr;
  out->tMD.pVirtualAddr = in->tMD.pVirtualAddr;
  out->tMD.uSize = in->tMD.uSize;
}

/******************************************************************************/
static void AL_sGetToggleBuffers(const AL_TDecCtx* pCtx, AL_TDecPicBuffers* pBufs)
{
  const int toggle = pCtx->uToggle;
  setBufferHandle(&pCtx->PoolListRefAddr[toggle], &pBufs->tListRef);
  setBufferHandle(&pCtx->PoolVirtRefAddr[toggle], &pBufs->tListVirtRef);
  setBufferHandle(&pCtx->PoolCompData[toggle], &pBufs->tCompData);
  setBufferHandle(&pCtx->PoolCompMap[toggle], &pBufs->tCompMap);
  setBufferHandle(&pCtx->PoolSclLst[toggle], &pBufs->tScl);
  setBufferHandle(&pCtx->PoolWP[toggle], &pBufs->tWP);
}

/******************************************************************************/
static void pushCommandParameters(AL_TDecCtx* pCtx, AL_TDecSliceParam* pSP, bool bIsLastAUNal)
{
  pSP->bIsLastSlice = bIsLastAUNal;

  /* update circular buffer */
  pSP->uStrAvailSize = pCtx->NalStream.iAvailSize;
  pSP->uStrOffset = pCtx->NalStream.iOffset;
}

/******************************************************************************/
static void AL_sSaveCommandBlk2(AL_TDecCtx* pCtx, AL_TDecPicParam const* pPP, AL_TDecPicBuffers* pBufs)
{
  (void)pPP;

  AL_TStreamSettings const* pStreamSettings = &pCtx->tInitialStreamSettings;
  int const iMaxBitDepth = pStreamSettings->iBitDepth;
  AL_TBuffer* pRec = pCtx->pRecs.pFrame;

  uint32_t uPitch = AL_PixMapBuffer_GetPlanePitch(pRec, AL_PLANE_Y);
  AL_Assert(uPitch != 0);

  // The first version supported only 8 or 10 bit with a flag at pos 31.
  // For backward compatibility, the bit 30 is used to set 12 bits output picture bitdepth
  uint32_t uPictureBitDepth = (iMaxBitDepth - 8);
  int iDec2RecBitDepthOffset = 28;

  uPictureBitDepth <<= iDec2RecBitDepthOffset;
  pBufs->uPitch = uPitch | uPictureBitDepth;

  TFourCC tFourCC = AL_PixMapBuffer_GetFourCC(pRec);
  AL_EPlaneMode ePlaneMode = AL_GetPlaneMode(tFourCC);

  AL_EPlaneId eFirstCPlane = AL_PLANE_MODE_PLANAR == ePlaneMode ? AL_PLANE_U : AL_PLANE_UV;
  pBufs->tRecY.tMD.uPhysicalAddr = AL_PixMapBuffer_GetPlanePhysicalAddress(pRec, AL_PLANE_Y);
  pBufs->tRecY.tMD.pVirtualAddr = AL_PixMapBuffer_GetPlaneAddress(pRec, AL_PLANE_Y);
  pBufs->tRecC1.tMD.uPhysicalAddr = AL_PixMapBuffer_GetPlanePhysicalAddress(pRec, eFirstCPlane);
  pBufs->tRecC1.tMD.pVirtualAddr = AL_PixMapBuffer_GetPlaneAddress(pRec, eFirstCPlane);

  pBufs->tRecC2.tMD.uPhysicalAddr = AL_PixMapBuffer_GetPlanePhysicalAddress(pRec, AL_PLANE_V);
  pBufs->tRecC2.tMD.pVirtualAddr = AL_PixMapBuffer_GetPlaneAddress(pRec, AL_PLANE_V);

  uint32_t uOffset = AL_PixMapBuffer_GetPositionOffset(pRec, pCtx->tOutputPosition, AL_PLANE_Y);
  pBufs->tRecY.tMD.uPhysicalAddr += uOffset;
  pBufs->tRecY.tMD.pVirtualAddr += uOffset;
  uOffset = AL_PixMapBuffer_GetPositionOffset(pRec, pCtx->tOutputPosition, eFirstCPlane);
  pBufs->tRecC1.tMD.uPhysicalAddr += uOffset;
  pBufs->tRecC1.tMD.pVirtualAddr += uOffset;
  uOffset = AL_PixMapBuffer_GetPositionOffset(pRec, pCtx->tOutputPosition, AL_PLANE_V);
  pBufs->tRecC2.tMD.uPhysicalAddr += uOffset;
  pBufs->tRecC2.tMD.pVirtualAddr += uOffset;

  if(pCtx->pChanParam->tOutputSettings.bCustomFormat)
  {
    bool bForceRasterInDec2 = false;

    pRec = pCtx->pRecs.pSecondOutputFrame;

    TFourCC tFourCCSecondOutput = AL_PixMapBuffer_GetFourCC(pRec);
    AL_EPlaneMode ePlaneModeSecondOutput = AL_GetPlaneMode(tFourCCSecondOutput);

    AL_EPlaneId eFirstPlaneSecondOutput = ePlaneModeSecondOutput == AL_PLANE_MODE_INTERLEAVED ? AL_PLANE_YUV : AL_PLANE_Y;
    AL_EPlaneId eChromaPlaneSecondOutput = ePlaneModeSecondOutput == AL_PLANE_MODE_PLANAR ? AL_PLANE_U : AL_PLANE_UV;

    if(bForceRasterInDec2)
    {
      AL_TPicFormat tPicFormat;
      Rtos_Memset(&tPicFormat, 0, sizeof(tPicFormat));
      tPicFormat.uBitDepth = uPictureBitDepth;
      tPicFormat.eStorageMode = AL_FB_RASTER;
      uPitch = AL_Decoder_GetMinPitch(pStreamSettings->tDim.iWidth, &tPicFormat);
    }
    else
      uPitch = AL_PixMapBuffer_GetPlanePitch(pRec, eFirstPlaneSecondOutput);
    AL_Assert(uPitch != 0);

    pBufs->uPitchSecondOutput = uPitch | uPictureBitDepth;

    pBufs->tRecSecondOutputY.tMD.uPhysicalAddr = AL_PixMapBuffer_GetPlanePhysicalAddress(pRec, eFirstPlaneSecondOutput);
    pBufs->tRecSecondOutputY.tMD.pVirtualAddr = AL_PixMapBuffer_GetPlaneAddress(pRec, eFirstPlaneSecondOutput);
    pBufs->tRecSecondOutputC1.tMD.uPhysicalAddr = AL_PixMapBuffer_GetPlanePhysicalAddress(pRec, eChromaPlaneSecondOutput);
    pBufs->tRecSecondOutputC1.tMD.pVirtualAddr = AL_PixMapBuffer_GetPlaneAddress(pRec, eChromaPlaneSecondOutput);
    pBufs->tRecSecondOutputC2.tMD.uPhysicalAddr = AL_PixMapBuffer_GetPlanePhysicalAddress(pRec, AL_PLANE_V);
    pBufs->tRecSecondOutputC2.tMD.pVirtualAddr = AL_PixMapBuffer_GetPlaneAddress(pRec, AL_PLANE_V);
  }

  pBufs->tPoc.tMD.uPhysicalAddr = pCtx->POC.tMD.uPhysicalAddr;
  pBufs->tPoc.tMD.pVirtualAddr = pCtx->POC.tMD.pVirtualAddr;
  pBufs->tPoc.tMD.uSize = pCtx->POC.tMD.uSize;

  pBufs->tMV.tMD.uPhysicalAddr = pCtx->MV.tMD.uPhysicalAddr;
  pBufs->tMV.tMD.pVirtualAddr = pCtx->MV.tMD.pVirtualAddr;
  pBufs->tMV.tMD.uSize = pCtx->MV.tMD.uSize;

}

/*****************************************************************************/
static void AL_sSaveNalStreamBlk1(AL_TDecCtx* pCtx, AL_TDecSliceParam* pSP)
{
  (void)pSP;
  pCtx->NalStream = pCtx->Stream;
}

/*****************************************************************************/
static void AL_FlushBuffers(AL_TDecCtx* pCtx)
{
  AL_TDecPicBuffers* pPictBuffers = &pCtx->PoolPB[pCtx->uToggle];

  Rtos_FlushCacheMemory(pPictBuffers->tListRef.tMD.pVirtualAddr, pPictBuffers->tListRef.tMD.uSize);
  Rtos_FlushCacheMemory(pPictBuffers->tPoc.tMD.pVirtualAddr, pPictBuffers->tPoc.tMD.uSize);
  Rtos_FlushCacheMemory(pPictBuffers->tScl.tMD.pVirtualAddr, pPictBuffers->tScl.tMD.uSize);
  Rtos_FlushCacheMemory(pPictBuffers->tWP.tMD.pVirtualAddr, pPictBuffers->tWP.tMD.uSize);

  // Stream buffer was already flushed for start-code detection.
}

/*****************************************************************************/
static void AL_SetBufferAddrs(AL_TDecCtx* pCtx, AL_TDecPicBufferAddrs* pBufAddrs)
{
  AL_TDecPicBuffers* pPictBuffers = &pCtx->PoolPB[pCtx->uToggle];
  pBufAddrs->pCompData = pPictBuffers->tCompData.tMD.uPhysicalAddr;
  pBufAddrs->pCompMap = pPictBuffers->tCompMap.tMD.uPhysicalAddr;
  pBufAddrs->pListRef = pPictBuffers->tListRef.tMD.uPhysicalAddr;
  pBufAddrs->pMV = pPictBuffers->tMV.tMD.uPhysicalAddr;
  pBufAddrs->pPoc = pPictBuffers->tPoc.tMD.uPhysicalAddr;
  pBufAddrs->pRecY = pPictBuffers->tRecY.tMD.uPhysicalAddr;
  pBufAddrs->pRecC1 = pPictBuffers->tRecC1.tMD.uPhysicalAddr;
  pBufAddrs->pRecFbcMapY = pCtx->pChanParam->bFrameBufferCompression ? pPictBuffers->tRecFbcMapY.tMD.uPhysicalAddr : 0;
  pBufAddrs->pRecFbcMapC1 = pCtx->pChanParam->bFrameBufferCompression ? pPictBuffers->tRecFbcMapC1.tMD.uPhysicalAddr : 0;
  pBufAddrs->pRecC2 = pPictBuffers->tRecC2.tMD.uPhysicalAddr;
  pBufAddrs->pRecFbcMapC2 = pCtx->pChanParam->bFrameBufferCompression ? pPictBuffers->tRecFbcMapC2.tMD.uPhysicalAddr : 0;
  pBufAddrs->pScl = pPictBuffers->tScl.tMD.uPhysicalAddr;
  pBufAddrs->pWP = pPictBuffers->tWP.tMD.uPhysicalAddr;
  pBufAddrs->pStream = pPictBuffers->tStream.tMD.uPhysicalAddr;

  AL_Assert(pPictBuffers->tStream.tMD.uSize > 0);
  pBufAddrs->uStreamSize = pPictBuffers->tStream.tMD.uSize;
  pBufAddrs->uPitch = pPictBuffers->uPitch;

  if(pCtx->pChanParam->tOutputSettings.bCustomFormat)
  {
    pBufAddrs->pRecSecondOutputY = pPictBuffers->tRecSecondOutputY.tMD.uPhysicalAddr;
    pBufAddrs->pRecSecondOutputC1 = pPictBuffers->tRecSecondOutputC1.tMD.uPhysicalAddr;
    pBufAddrs->uPitchSecondOutput = pPictBuffers->uPitchSecondOutput;
    pBufAddrs->pRecSecondOutputC2 = pPictBuffers->tRecSecondOutputC2.tMD.uPhysicalAddr;
  }
  else
  {
    pBufAddrs->pRecSecondOutputY = 0;
    pBufAddrs->pRecSecondOutputC1 = 0;
    pBufAddrs->uPitchSecondOutput = 0;
    pBufAddrs->pRecSecondOutputC2 = 0;
  }

}

static void SetBufferHandleMetaData(AL_TDecCtx* pCtx)
{
  if(!pCtx->pInputBuffer)
    return;

  if(pCtx->pInputBuffer == pCtx->eosBuffer)
    return;

  AL_TBuffer* pFrame = pCtx->pRecs.pFrame;

  if(pCtx->pRecs.pSecondOutputFrame)
    pFrame = pCtx->pRecs.pSecondOutputFrame;

  AL_THandleMetaData* pMeta = (AL_THandleMetaData*)AL_Buffer_GetMetaData(pFrame, AL_META_TYPE_HANDLE);

  if(!pMeta)
  {
    pMeta = AL_HandleMetaData_Create(AL_MAX_SLICES_SUBFRAME, sizeof(AL_TDecMetaHandle));
    AL_Buffer_AddMetaData(pFrame, (AL_TMetaData*)pMeta);
  }

  AL_TDecMetaHandle handle = { AL_DEC_HANDLE_STATE_PROCESSING, pCtx->pInputBuffer };
  AL_HandleMetaData_AddHandle(pMeta, &handle);
}

/***************************************************************************/
/*                          P U B L I C   f u n c t i o n s                */
/***************************************************************************/

static void UpdateStreamOffset(AL_TDecCtx* pCtx)
{
  Rtos_GetMutex(pCtx->DecMutex);
  pCtx->iStreamOffset[pCtx->iNumFrmBlk1 % pCtx->iStackSize] = (pCtx->Stream.iOffset + pCtx->Stream.iAvailSize) % pCtx->Stream.tMD.uSize;
  Rtos_ReleaseMutex(pCtx->DecMutex);
}

static void decodeOneSlice(AL_TDecCtx* pCtx, uint16_t uSliceID, AL_TDecPicBufferAddrs* pBufAddrs)
{
  AL_TDecSliceParam* pSP_v = &(((AL_TDecSliceParam*)pCtx->PoolSP[pCtx->uToggle].tMD.pVirtualAddr)[uSliceID]);
  AL_PADDR pSP_p = (AL_PADDR)(uintptr_t)&(((AL_TDecSliceParam*)(uintptr_t)pCtx->PoolSP[pCtx->uToggle].tMD.uPhysicalAddr)[uSliceID]);
  TMemDesc SliceParam;
  SliceParam.pVirtualAddr = (AL_VADDR)pSP_v;
  SliceParam.uPhysicalAddr = pSP_p;
  // The HandleMetaData handle order should be the same as the slice order
  // as we add them each time we send one.
  pSP_v->uParsingId = uSliceID;
  AL_IDecScheduler_DecodeOneSlice(pCtx->pScheduler, pCtx->hChannel, &pCtx->PoolPP[pCtx->uToggle], pBufAddrs, &SliceParam);
}

/*****************************************************************************/

/*****************************************************************************/
void AL_LaunchSliceDecoding(AL_TDecCtx* pCtx, bool bIsLastAUNal, bool hasPreviousSlice)
{
  uint16_t uSliceID = pCtx->tCurrentFrameCtx.uNumSlice - 1;
  AL_TDecSliceParam* pPrevSP = NULL;

  UpdateStreamOffset(pCtx);

  if(hasPreviousSlice && uSliceID)
  {
    pPrevSP = &(((AL_TDecSliceParam*)pCtx->PoolSP[pCtx->uToggle].tMD.pVirtualAddr)[uSliceID - 1]);

    if(pPrevSP->eSliceType == AL_SLICE_CONCEAL && uSliceID == 1)
    {
      AL_FlushBuffers(pCtx);
      AL_SetBufferAddrs(pCtx, &pCtx->BufAddrs);
      SetBufferHandleMetaData(pCtx);
    }
    decodeOneSlice(pCtx, uSliceID - 1, &pCtx->BufAddrs);
  }

  AL_FlushBuffers(pCtx);
  AL_SetBufferAddrs(pCtx, &pCtx->BufAddrs);
  SetBufferHandleMetaData(pCtx);

  if(!bIsLastAUNal)
    return;

  if(pPrevSP == NULL || !pPrevSP->bIsLastSlice)
    decodeOneSlice(pCtx, uSliceID, &pCtx->BufAddrs);

  pCtx->tCurrentFrameCtx.uCurTileID = 0;

  Rtos_GetMutex(pCtx->DecMutex);
  ++pCtx->iNumFrmBlk1;
  pCtx->uToggle = (pCtx->iNumFrmBlk1 % pCtx->iStackSize);
  Rtos_ReleaseMutex(pCtx->DecMutex);
}

/*****************************************************************************/
void AL_LaunchFrameDecoding(AL_TDecCtx* pCtx)
{
  AL_FlushBuffers(pCtx);

  AL_TDecPicBufferAddrs BufAddrs;
  AL_SetBufferAddrs(pCtx, &BufAddrs);
  SetBufferHandleMetaData(pCtx);

  UpdateStreamOffset(pCtx);
  AL_TDecSliceParam* pSP = (AL_TDecSliceParam*)pCtx->PoolSP[pCtx->uToggle].tMD.pVirtualAddr;
  pSP->uParsingId = 0;

  AL_IDecScheduler_DecodeOneFrame(pCtx->pScheduler, pCtx->hChannel, &pCtx->PoolPP[pCtx->uToggle], &BufAddrs, &pCtx->PoolSP[pCtx->uToggle].tMD);

  pCtx->tCurrentFrameCtx.uCurTileID = 0;

  Rtos_GetMutex(pCtx->DecMutex);
  ++pCtx->iNumFrmBlk1;
  pCtx->uToggle = (pCtx->iNumFrmBlk1 % pCtx->iStackSize);
  Rtos_ReleaseMutex(pCtx->DecMutex);
}

/*****************************************************************************/
static void AL_InitRefBuffers(AL_TDecCtx* pCtx, AL_TDecPicBuffers* pBufs)
{
  int iOffset = pCtx->iNumFrmBlk1 % AL_DEC_SW_MAX_STACK_SIZE;
  pCtx->uNumRef[iOffset] = 0;

  uint8_t uNode = 0;

  while(uNode < MAX_DPB_SIZE && pCtx->uNumRef[iOffset] < MAX_REF)
  {
    AL_EMarkingRef eMarkingRef = AL_Dpb_GetMarkingFlag(&pCtx->PictMngr.DPB, uNode);
    uint8_t uFrameId = AL_Dpb_GetFrmID_FromNode(&pCtx->PictMngr.DPB, uNode);
    uint8_t uMvID = AL_Dpb_GetMvID_FromNode(&pCtx->PictMngr.DPB, uNode);

    if((uFrameId != uEndOfList) && (uMvID != uEndOfList) && (eMarkingRef != UNUSED_FOR_REF) && (eMarkingRef != NON_EXISTING_REF))
    {
      pCtx->uFrameIDRefList[iOffset][pCtx->uNumRef[iOffset]] = uFrameId;
      pCtx->uMvIDRefList[iOffset][pCtx->uNumRef[iOffset]] = uMvID;
      ++pCtx->uNumRef[iOffset];
    }

    ++uNode;
  }

  AL_PictMngr_LockRefID(&pCtx->PictMngr, pCtx->uNumRef[iOffset], pCtx->uFrameIDRefList[iOffset], pCtx->uMvIDRefList[iOffset]);

  // prepare buffers
  AL_sGetToggleBuffers(pCtx, pBufs);
  {
    AL_CleanupMemory(pBufs->tCompData.tMD.pVirtualAddr, pBufs->tCompData.tMD.uSize);
    AL_CleanupMemory(pBufs->tCompMap.tMD.pVirtualAddr, pBufs->tCompMap.tMD.uSize);
  }
}

/*****************************************************************************/
bool AL_InitFrameBuffers(AL_TDecCtx* pCtx, AL_TDecPicBuffers* pBufs, bool bStartsNewCVS, AL_TDimension tDim, AL_EChromaMode eDecodedChromaMode, AL_TDecPicParam* pPP)
{
  Rtos_GetSemaphore(pCtx->Sem, AL_WAIT_FOREVER);

  if(!AL_PictMngr_BeginFrame(&pCtx->PictMngr, bStartsNewCVS, tDim, eDecodedChromaMode))
  {
    pCtx->eChanState = CHAN_DESTROYING;
    Rtos_ReleaseSemaphore(pCtx->Sem);
    return false;
  }
  pPP->tBufIDs.FrmID = AL_PictMngr_GetCurrentFrmID(&pCtx->PictMngr);
  pPP->tBufIDs.MvID = AL_PictMngr_GetCurrentMvID(&pCtx->PictMngr);

  AL_InitRefBuffers(pCtx, pBufs);
  return true;
}

/*****************************************************************************/
void AL_CancelFrameBuffers(AL_TDecCtx* pCtx)
{
  AL_PictMngr_CancelFrame(&pCtx->PictMngr);

  int iOffset = pCtx->iNumFrmBlk1 % AL_DEC_SW_MAX_STACK_SIZE;
  AL_PictMngr_UnlockRefID(&pCtx->PictMngr, pCtx->uNumRef[iOffset], pCtx->uFrameIDRefList[iOffset], pCtx->uMvIDRefList[iOffset]);
  UpdateContextAtEndOfFrame(pCtx);
  Rtos_ReleaseSemaphore(pCtx->Sem);
}

/*****************************************************************************/
static void AL_TerminateCurrentCommand(AL_TDecCtx* pCtx, AL_TDecPicParam const* pPP, AL_TDecSliceParam* pSP)
{
  AL_TDecPicBuffers* pBufs = &pCtx->PoolPB[pCtx->uToggle];

  pSP->NextSliceSegment = pPP->LcuPicWidth * pPP->LcuPicHeight;
  pSP->NextIsDependent = false;

  AL_sSaveCommandBlk2(pCtx, pPP, pBufs);
  pushCommandParameters(pCtx, pSP, true);
}

/*****************************************************************************/
void AL_SetConcealParameters(AL_TDecCtx* pCtx, AL_TDecSliceParam* pSP)
{
  pSP->ConcealPicID = AL_PictMngr_GetLastPicID(&pCtx->PictMngr);
  pSP->ValidConceal = (pSP->ConcealPicID == uEndOfList) ? false : true;
}

/*****************************************************************************/
void AL_TerminatePreviousCommand(AL_TDecCtx* pCtx, AL_TDecPicParam const* pPP, AL_TDecSliceParam* pSP, AL_TDecPicBuffers* pBufs, bool bIsLastVclNalInAU, bool bNextIsDependent)
{
  AL_sSaveCommandBlk2(pCtx, pPP, pBufs);

  if(pCtx->tCurrentFrameCtx.uNumSlice == 0)
    return;

  AL_TDecSliceParam* pPrevSP = &(((AL_TDecSliceParam*)pCtx->PoolSP[pCtx->uToggle].tMD.pVirtualAddr)[pCtx->tCurrentFrameCtx.uNumSlice - 1]);

  if(bIsLastVclNalInAU)
    pPrevSP->NextSliceSegment = pPP->LcuPicWidth * pPP->LcuPicHeight;
  else
    pPrevSP->NextSliceSegment = pSP->FirstLcuSliceSegment;

  pPrevSP->NextIsDependent = bNextIsDependent;

  if(!pCtx->tConceal.bValidFrame)
  {
    pPrevSP->eSliceType = AL_SLICE_CONCEAL;
    pPrevSP->SliceFirstLCU = 0;
  }
  pushCommandParameters(pCtx, pPrevSP, bIsLastVclNalInAU);
}

/*****************************************************************************/
void AL_AVC_InitHWCommandBuffers(AL_TDecCtx* pCtx, AL_TDecSliceParam const* pSP, AL_TAvcSliceHdr const* pSlice, AL_TScl const* pSclLst, AL_EChromaMode eChromaMode, AL_TDecPicBuffers* pBufs)
{
  if(pCtx->tCurrentFrameCtx.eBufStatus == DEC_FRAME_BUF_RESERVED)
  {
    AL_AVC_PictMngr_GetBuffers(&pCtx->PictMngr, pSP, &pBufs->tListVirtRef, &pBufs->tListRef, &pCtx->POC, &pCtx->MV, &pCtx->pRecs);
    AL_AVC_InitHWFrameBuffers(pSclLst, eChromaMode, pBufs);
    pCtx->tCurrentFrameCtx.eBufStatus |= DEC_FRAME_BUF_FILLED;
  }

  AL_AVC_InitHWSliceBuffers(pCtx->tCurrentFrameCtx.uNumSlice, pSlice, pBufs);
}

/*****************************************************************************/
void AL_AVC_PrepareCommand(AL_TDecCtx* pCtx, AL_TScl* pSCL, AL_TDecPicParam* pPP, AL_TDecPicBuffers* pBufs, AL_TDecSliceParam* pSP, AL_TAvcSliceHdr* pSlice, bool bIsLastVclNalInAU, bool bIsValid)
{
  // fast access
  uint16_t uSliceID = pCtx->tCurrentFrameCtx.uNumSlice;

  AL_TDecSliceParam* pPrevSP = uSliceID ? &(((AL_TDecSliceParam*)pCtx->PoolSP[pCtx->uToggle].tMD.pVirtualAddr)[uSliceID - 1]) : NULL;

  pPP->iFrmNum = pCtx->iNumFrmBlk1;
  pPP->UserParam = pCtx->uToggle;

  AL_AVC_InitHWCommandBuffers(pCtx, pSP, pSlice, (AL_TScl const*)pSCL, pPP->ChromaMode, pBufs);

  if(pPrevSP && !bIsValid && bIsLastVclNalInAU)
  {
    AL_TerminatePreviousCommand(pCtx, pPP, pSP, pBufs, bIsLastVclNalInAU, true);
    return;
  }

  // copy collocated info
  if(pSP->FirstLcuSliceSegment && pSP->eSliceType == AL_SLICE_I)
    pSP->ColocPicID = pPrevSP->ColocPicID;

  // stock command registers in memory
  AL_TerminatePreviousCommand(pCtx, pPP, pSP, pBufs, false, true);

  if(pSP->SliceFirstLCU)
    pSP->FirstLcuTileID = pSP->DependentSlice ? pPrevSP->FirstLcuTileID : pCtx->tCurrentFrameCtx.uCurTileID;

  AL_sSaveNalStreamBlk1(pCtx, pSP);

  if(bIsLastVclNalInAU)
    AL_TerminateCurrentCommand(pCtx, pPP, pSP);
}

// static int dumbCounter = 0;
/*****************************************************************************/
void AL_HEVC_InitHWCommandBuffers(AL_TDecCtx* pCtx, AL_TDecSliceParam const* pSP, AL_THevcSliceHdr const* pSlice, AL_TScl const* pSclLst, AL_TDecPicBuffers* pBufs)
{
  if(pCtx->tCurrentFrameCtx.eBufStatus == DEC_FRAME_BUF_RESERVED)
  {
    AL_HEVC_PictMngr_GetBuffers(&pCtx->PictMngr, pSP, &pBufs->tListVirtRef, &pBufs->tListRef, &pCtx->POC, &pCtx->MV, &pCtx->pRecs);

    if(pSlice->first_slice_segment_in_pic_flag)
      AL_HEVC_InitHWFrameBuffers(pSclLst, pBufs);

    pCtx->tCurrentFrameCtx.eBufStatus |= DEC_FRAME_BUF_FILLED;
  }

  AL_HEVC_InitHWSliceBuffers(pCtx->tCurrentFrameCtx.uNumSlice, pSlice, pBufs);
}

/*****************************************************************************/
void AL_HEVC_PrepareCommand(AL_TDecCtx* pCtx, AL_TScl* pSCL, AL_TDecPicParam* pPP, AL_TDecPicBuffers* pBufs, AL_TDecSliceParam* pSP, AL_THevcSliceHdr* pSlice, bool bIsLastVclNalInAU, bool bIsValid)
{
  // fast access
  uint16_t uSliceID = pCtx->tCurrentFrameCtx.uNumSlice;
  AL_TDecSliceParam* pPrevSP = uSliceID ? &(((AL_TDecSliceParam*)pCtx->PoolSP[pCtx->uToggle].tMD.pVirtualAddr)[uSliceID - 1]) : NULL;

  pPP->iFrmNum = pCtx->iNumFrmBlk1;
  pPP->UserParam = pCtx->uToggle;

  AL_HEVC_InitHWCommandBuffers(pCtx, pSP, pSlice, (AL_TScl const*)pSCL, pBufs);

  if(pPrevSP && !bIsValid && bIsLastVclNalInAU)
  {
    AL_TerminatePreviousCommand(pCtx, pPP, pSP, pBufs, bIsLastVclNalInAU, true);
    return;
  }

  // copy collocated info
  if(pSP->FirstLcuSliceSegment && pSP->eSliceType == AL_SLICE_I)
    pSP->ColocPicID = pPrevSP->ColocPicID;

  // stock command registers in memory
  AL_TerminatePreviousCommand(pCtx, pPP, pSP, pBufs, false, pSP->DependentSlice);

  if(pSP->FirstLcuSliceSegment)
  {
    pSP->FirstLcuSlice = pSP->DependentSlice ? pPrevSP->FirstLcuSlice : pSP->FirstLcuSlice;
    pSP->FirstLcuTileID = pSP->DependentSlice ? pPrevSP->FirstLcuTileID : pCtx->tCurrentFrameCtx.uCurTileID;
  }

  AL_sSaveNalStreamBlk1(pCtx, pSP);

  if(bIsLastVclNalInAU)
    AL_TerminateCurrentCommand(pCtx, pPP, pSP);
}

/*@}*/
