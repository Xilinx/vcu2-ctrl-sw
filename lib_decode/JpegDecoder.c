// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_common/Error.h"

#include "DefaultDecoder.h"
#include "I_DecoderCtx.h"
#include "lib_assert/al_assert.h"
#include "lib_common/PixMapBufferInternal.h"
#include "lib_common/BufferHandleMeta.h"
#include "lib_common_dec/DecHardwareConfig.h"
#include "lib_decode/I_DecSchedulerInfo.h"
#include "lib_parsing/JpegParser.h"

/*****************************************************************************/
static void Jpeg_EndDecoding(void* pUserParam, AL_TDecPicStatus const* pStatus)
{
  AL_TDecCtx* pCtx = (AL_TDecCtx*)pUserParam;

  AL_PictMngr_Flush(&pCtx->PictMngr);

  AL_Default_Decoder_EndDecoding(pCtx, pStatus);
}

/******************************************************************************/
static bool initChannel(AL_TDecCtx* pCtx)
{
  AL_TDecChanParam* pChan = pCtx->pChanParam;
  AL_TStreamSettings const* pStreamSettings = &pCtx->tCurrentStreamSettings;
  pChan->iWidth = pStreamSettings->tDim.iWidth;
  pChan->iHeight = pStreamSettings->tDim.iHeight;
  pChan->eMaxChromaMode = pStreamSettings->eChroma;

  return AL_Default_Decoder_CreateChannel(pCtx, NULL, Jpeg_EndDecoding);
}

/*****************************************************************************/
static bool DecodeHeader(AL_TDecCtx* pCtx, TCircBuffer* pBufStream, AL_TDecJpegParam* pJP)
{
  AL_TRbspParser rp;
  InitRbspParser(pBufStream, NULL, 0, false, &rp);

  uint8_t uByte = u(&rp, 8);

  if(uByte != 0xFF)
    return false;

  while(uByte == 0xFF && get_avail_size(&rp) >= 8)
    uByte = u(&rp, 8);

  EJpeg_Marker eMarker = UNKNOWN_MARKER | uByte;

  if(eMarker != SOI_MARKER)
    return false;

  int iOffset = pCtx->iNumFrmBlk1 % AL_DEC_SW_MAX_STACK_SIZE;
  bool bRet = AL_JPEG_ParseHeaders(pJP, &rp, &pCtx->QuantBuffer[iOffset], &pCtx->HuffmanBuffer[iOffset], &pCtx->MinMaxBuf[iOffset]);

  if(bRet)
  {
    int iCurOffset = (offset(&rp) >> 3);
    pBufStream->iOffset += iCurOffset;
    pBufStream->iAvailSize -= iCurOffset;
  }
  return bRet;
}

/*****************************************************************************/
static AL_TStreamSettings extractStreamSettings(AL_TDecJpegParam* pJP)
{
  AL_TStreamSettings tStreamSettings;
  tStreamSettings.eChroma = pJP->chroma_mode;
  tStreamSettings.iBitDepth = pJP->bitdepth;
  tStreamSettings.tDim.iWidth = pJP->picture_width;
  tStreamSettings.tDim.iHeight = pJP->picture_height;
  tStreamSettings.eProfile = AL_PROFILE_JPEG;
  tStreamSettings.eSequenceMode = AL_SM_PROGRESSIVE;
  tStreamSettings.iLevel = 0;
  tStreamSettings.bDecodeIntraOnly = false;
  return tStreamSettings;
}

/*****************************************************************************/
static void GetRecAddr(AL_TDecCtx* pCtx, AL_TJpegBufferAddrs* pAddr)
{
  AL_TRecBuffers* pRecs = &pCtx->pRecs;
  AL_PictMngr_GetBuffers(&pCtx->PictMngr, NULL, NULL, NULL, NULL, NULL, pRecs);
  AL_TStreamSettings const* pStreamSettings = &pCtx->tCurrentStreamSettings;

  TFourCC tOutputFourCC = AL_PixMapBuffer_GetFourCC(pRecs->pFrame);
  AL_TPicFormat tOutputPicFormat;
  AL_GetPicFormat(tOutputFourCC, &tOutputPicFormat);

  AL_EPlaneId eFirstPlane = tOutputPicFormat.ePlaneMode == AL_PLANE_MODE_INTERLEAVED ? AL_PLANE_YUV : AL_PLANE_Y;
  AL_EPlaneId eFirstChromaPlane = tOutputPicFormat.ePlaneMode == AL_PLANE_MODE_PLANAR ? AL_PLANE_U : AL_PLANE_UV;

  pAddr->uPitch = AL_PixMapBuffer_GetPlanePitch(pRecs->pFrame, eFirstPlane);
  AL_Assert(pAddr->uPitch != 0);

  pAddr->pRecY = AL_PixMapBuffer_GetPlanePhysicalAddress(pRecs->pFrame, eFirstPlane);
  pAddr->pRecC1 = 0;
  pAddr->pRecC2 = 0;

  if(pStreamSettings->eChroma != AL_CHROMA_MONO)
    pAddr->pRecC1 = AL_PixMapBuffer_GetPlanePhysicalAddress(pRecs->pFrame, eFirstChromaPlane);

  if(pStreamSettings->eChroma == AL_CHROMA_4_4_4)
    pAddr->pRecC2 = AL_PixMapBuffer_GetPlanePhysicalAddress(pRecs->pFrame, AL_PLANE_V);

}

/*****************************************************************************/
static void FillAddrs(AL_TDecCtx* pCtx, AL_TJpegBufferAddrs* pAddr)
{
  TCircBuffer* pBufStream = &pCtx->Stream;
  pAddr->uOffset = pBufStream->iOffset;
  pAddr->uAvailSize = pBufStream->iAvailSize;
  pAddr->pStream = pBufStream->tMD.uPhysicalAddr;
  pAddr->uStreamSize = pBufStream->tMD.uSize;
  int iOffset = pCtx->iNumFrmBlk1 % AL_DEC_SW_MAX_STACK_SIZE;
  pAddr->pHuff = pCtx->HuffmanBuffer[iOffset].tMD.uPhysicalAddr;
  pAddr->pQuantTab = pCtx->QuantBuffer[iOffset].tMD.uPhysicalAddr;
  pAddr->pMinMaxTab = pCtx->MinMaxBuf[iOffset].tMD.uPhysicalAddr;

  Rtos_FlushCacheMemory(pCtx->HuffmanBuffer[iOffset].tMD.pVirtualAddr, pCtx->HuffmanBuffer[iOffset].tMD.uSize);
  Rtos_FlushCacheMemory(pCtx->QuantBuffer[iOffset].tMD.pVirtualAddr, pCtx->QuantBuffer[iOffset].tMD.uSize);
  Rtos_FlushCacheMemory(pCtx->MinMaxBuf[iOffset].tMD.pVirtualAddr, pCtx->MinMaxBuf[iOffset].tMD.uSize);

  GetRecAddr(pCtx, pAddr);
}

/*****************************************************************************/
static bool isHeaderParamsCompatibleWithStreamSettings(AL_TDecCtx* pCtx, AL_TDecJpegParam* tJpegParam)
{
  AL_TStreamSettings const* pStreamSettings = &pCtx->tCurrentStreamSettings;

  if(tJpegParam->chroma_mode > AL_HWConfig_Dec_GetJpegSupportedChromaMode())
    return false;

  if(pStreamSettings->iBitDepth > 0 && pStreamSettings->iBitDepth < tJpegParam->bitdepth)
    return false;

  if(tJpegParam->bitdepth > AL_HWConfig_Dec_GetJpegSupportedBitDepth())
    return false;

  if(pStreamSettings->tDim.iWidth > 0 && pStreamSettings->tDim.iWidth < tJpegParam->picture_width)
    return false;

  if(pStreamSettings->tDim.iHeight > 0 && pStreamSettings->tDim.iHeight < tJpegParam->picture_height)
    return false;

  return true;
}

/*****************************************************************************/
bool AL_JPEG_DecodeOneNAL(AL_TDecCtx* pCtx)
{
  TCircBuffer* pBufStream = &pCtx->Stream;
  AL_TDecJpegParam tJpegParam;
  Rtos_Memset(&tJpegParam, 0, sizeof(tJpegParam));

  tJpegParam.bitdepth = 8;

  if(!DecodeHeader(pCtx, pBufStream, &tJpegParam))
  {
    AL_Default_Decoder_SetError(pCtx, AL_ERR_INVALID_OR_UNSUPPORTED_FILE_FORMAT, -1, true);
    return false;
  }

  if(!isHeaderParamsCompatibleWithStreamSettings(pCtx, &tJpegParam))
  {
    Rtos_Log(AL_LOG_ERROR, "Cannot decode using the current allocated buffers\n");
    AL_Default_Decoder_SetError(pCtx, AL_WARN_SPS_NOT_COMPATIBLE_WITH_CHANNEL_SETTINGS, -1, true);
    return false;
  }

  AL_TStreamSettings tCurStreamSettings = extractStreamSettings(&tJpegParam);

  if(!pCtx->bIsFirstSPSChecked)
  {
    pCtx->bIsFirstSPSChecked = true;

    if(!pCtx->bAreBuffersAllocated)
    {
      pCtx->tCurrentStreamSettings = tCurStreamSettings;
      pCtx->tInitialStreamSettings = tCurStreamSettings;
    }

    pCtx->bIsFirstSPSChecked = true;

    if(!initChannel(pCtx))
      return false;

    if(!pCtx->bAreBuffersAllocated)
    {
      AL_TPictMngrParam tPictMngrParam =
      {
        pCtx->pChanParam->uNumCore,
        pCtx->eDpbMode,
        pCtx->pChanParam->eFBStorageMode,
        pCtx->iStackSize,
        0,
        pCtx->pChanParam->bUseEarlyCallback,
        { 0, 0 },
      };

      if(!AL_PictMngr_BasicInit(&pCtx->PictMngr, &tPictMngrParam))
      {
        Rtos_Log(AL_LOG_ERROR, "Cannot initialize picture manager");
        AL_Default_Decoder_SetError(pCtx, AL_ERR_NO_MEMORY, -1, true);
        return false;
      }
    }
  }

  AL_TCropInfo const tCropInfo = { false, 0, 0, 0, 0 }; // XXX
  AL_ERR error = pCtx->tDecCB.resolutionFoundCB.func(pCtx->pChanParam->uNumCore * AL_DEC_NUM_JPEG_PER_CORE, &tCurStreamSettings, &tCropInfo, pCtx->tDecCB.resolutionFoundCB.userParam);

  // In the case of mjpeg, it needs to wait only the first time
  if(!AL_PictMngr_IsInitComplete(&pCtx->PictMngr))
    Rtos_WaitEvent(pCtx->hDecOutSettingsConfiguredEvt, AL_WAIT_FOREVER);

  tJpegParam.tOutPicFormat = pCtx->pChanParam->tOutputSettings.tPicFormat;

  if(AL_IS_ERROR_CODE(error))
  {
    AL_Default_Decoder_SetError(pCtx, error, -1, true);
    return false;
  }

  pCtx->bAreBuffersAllocated = true;

  Rtos_GetSemaphore(pCtx->Sem, AL_WAIT_FOREVER);

  AL_EChromaMode eDecodedChromaMode = tCurStreamSettings.eChroma;
  AL_PictMngr_BeginFrame(&pCtx->PictMngr, false, tCurStreamSettings.tDim, eDecodedChromaMode);
  tJpegParam.FrmID = AL_PictMngr_GetCurrentFrmID(&pCtx->PictMngr);
  tJpegParam.MvID = AL_PictMngr_GetCurrentMvID(&pCtx->PictMngr);
  tJpegParam.FrmNum = pCtx->iNumFrmBlk1;
  tJpegParam.UserParam = pCtx->uToggle;

  AL_TJpegBufferAddrs tPicBufAddrs;
  FillAddrs(pCtx, &tPicBufAddrs);

  if(pCtx->pInputBuffer)
  {
    AL_THandleMetaData* pMeta = (AL_THandleMetaData*)AL_Buffer_GetMetaData(pCtx->pRecs.pFrame, AL_META_TYPE_HANDLE);

    if(!pMeta)
    {
      pMeta = AL_HandleMetaData_Create(AL_MAX_SLICES_SUBFRAME, sizeof(AL_TDecMetaHandle));
      AL_Buffer_AddMetaData(pCtx->pRecs.pFrame, (AL_TMetaData*)pMeta);
    }

    AL_TDecMetaHandle handle = { AL_DEC_HANDLE_STATE_PROCESSING, pCtx->pInputBuffer };
    AL_HandleMetaData_AddHandle(pMeta, &handle);
  }

  Rtos_GetMutex(pCtx->DecMutex);
  pCtx->iStreamOffset[pCtx->iNumFrmBlk1 % pCtx->iStackSize] = (pCtx->Stream.iOffset + pCtx->Stream.iAvailSize) % pCtx->Stream.tMD.uSize;
  Rtos_ReleaseMutex(pCtx->DecMutex);

  AL_PictMngr_Insert(&pCtx->PictMngr, 0, 0, 0, tJpegParam.FrmID, tJpegParam.MvID, 1, SHORT_TERM_REF, 0, 0, 0);
  AL_IDecScheduler_DecodeJpeg(pCtx->pScheduler, pCtx->hChannel, &tJpegParam, &tPicBufAddrs);
  pCtx->iNumFrmBlk1++;
  pCtx->uToggle = (pCtx->iNumFrmBlk1 % pCtx->iStackSize);

  return true;
}

/*****************************************************************************/
AL_ERR CreateJpegDecoder(AL_TDecoder** hDec, AL_IDecScheduler* pScheduler, AL_TAllocator* pAllocator, AL_TDecSettings* pSettings, AL_TDecCallBacks* pCB)
{
  return AL_CreateDefaultDecoder((AL_TDecoder**)hDec, pScheduler, pAllocator, pSettings, pCB);
}

