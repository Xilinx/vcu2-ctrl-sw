// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/******************************************************************************
   \addtogroup lib_base
   !@{
   \file
 *****************************************************************************/

#include "lib_common/PicFormat.h"
#include "lib_common_dec/DecBuffersInternal.h"
#include "lib_common/Utils.h"
#include "lib_common/BufferPixMapMeta.h"

#include "lib_common/FbcMapSize.h"

/*****************************************************************************/
int32_t RndPitch(int32_t iWidth, AL_TPicFormat const* pPicFormat)
{
  int const iBurstAlignment = pPicFormat->eStorageMode == AL_FB_RASTER ? AL_DEC_PITCH_ALIGNMENT : HW_IP_BURST_ALIGNMENT;
  int const iRndWidth = RoundUp(iWidth, 64);
  return ComputeRndPitch(iRndWidth, pPicFormat, iBurstAlignment);
}

/******************************************************************************/
int32_t RndHeight(int32_t iHeight, AL_TPicFormat const* pPicFormat)
{
  // Height alignment required by customers to the LCU size
  int const iLcuAlignment = 64;
  return RoundUp(iHeight, iLcuAlignment) / AL_GetNumLinesInPitch(pPicFormat->eStorageMode);
}

/****************************************************************************/
int AL_GetAllocSize_HevcCompData(AL_TDimension tDim, AL_EChromaMode eChromaMode)
{
  int iBlk16x16 = GetSquareBlkNumber(tDim, 64) * 16;
  return HEVC_LCU_CMP_SIZE[eChromaMode] * iBlk16x16;
}

/****************************************************************************/
int AL_GetAllocSize_AvcCompData(AL_TDimension tDim, AL_EChromaMode eChromaMode)
{
  int iBlk16x16 = GetSquareBlkNumber(tDim, 16);
  return AVC_LCU_CMP_SIZE[eChromaMode] * iBlk16x16;
}

/****************************************************************************/
int AL_GetAllocSize_DecCompMap(AL_TDimension tDim)
{
  int iBlk16x16 = GetSquareBlkNumber(tDim, 16);
  return SIZE_LCU_INFO * iBlk16x16;
}

/*****************************************************************************/
int AL_GetAllocSize_HevcMV(AL_TDimension tDim)
{
  int iNumBlk = GetSquareBlkNumber(tDim, 64) * 16;
  return 4 * iNumBlk * sizeof(int32_t);
}

/*****************************************************************************/
int AL_GetAllocSize_AvcMV(AL_TDimension tDim)
{
  int iNumBlk = GetSquareBlkNumber(tDim, 16);
  return 16 * iNumBlk * sizeof(int32_t);
}

/****************************************************************************/
static int GetChromaAllocSize(AL_EChromaMode eChromaMode, int iAllocSizeY)
{
  switch(eChromaMode)
  {
  case AL_CHROMA_MONO:
    return 0;
  case AL_CHROMA_4_2_0:
    return iAllocSizeY >> 1;
  case AL_CHROMA_4_2_2:
    return iAllocSizeY;
  case AL_CHROMA_4_4_4:
    return iAllocSizeY << 1;
  default:
    Rtos_Assert(false);
    break;
  }

  return 0;
}

/*****************************************************************************/
int AL_DecGetAllocSize_Frame_PixPlane(AL_TPicFormat const* pPicFormat, AL_TDimension tDim, int iPitch, AL_EPlaneId ePlaneId)
{
  if(!AL_Plane_Exists(pPicFormat->ePlaneMode, false, ePlaneId))
    return 0;

  int iSize = iPitch * RndHeight(tDim.iHeight, pPicFormat);

  if(ePlaneId == AL_PLANE_UV)
    iSize = GetChromaAllocSize(pPicFormat->eChromaMode, iSize);

  return iSize;
}

/*****************************************************************************/
int AL_DecGetAllocSize_Frame_Y(AL_EFbStorageMode eFbStorage, AL_TDimension tDim, int iPitch)
{
  AL_TPicFormat tPicFormat = GetDefaultPicFormat();
  tPicFormat.eChromaMode = AL_CHROMA_MONO;
  tPicFormat.ePlaneMode = GetInternalBufPlaneMode(AL_CHROMA_MONO);
  tPicFormat.uBitDepth = 8;
  tPicFormat.eStorageMode = eFbStorage;
  tPicFormat.bCompressed = false;
  return AL_DecGetAllocSize_Frame_PixPlane(&tPicFormat, tDim, iPitch, AL_PLANE_Y);
}

/*****************************************************************************/
int AL_DecGetAllocSize_Frame_UV(AL_EFbStorageMode eFbStorage, AL_TDimension tDim, int iPitch, AL_EChromaMode eChromaMode)
{
  AL_TPicFormat tPicFormat = GetDefaultPicFormat();
  tPicFormat.eChromaMode = eChromaMode;
  tPicFormat.ePlaneMode = GetInternalBufPlaneMode(AL_CHROMA_MONO);
  tPicFormat.uBitDepth = 8;
  tPicFormat.eStorageMode = eFbStorage;
  tPicFormat.bCompressed = false;
  return AL_DecGetAllocSize_Frame_PixPlane(&tPicFormat, tDim, iPitch, AL_PLANE_UV);
}

/*****************************************************************************/
int AL_DecGetAllocSize_Frame_MapPlane(AL_TPicFormat const* pPicFormat, AL_TDimension tDim, AL_EPlaneId ePlaneId)
{
  if(!AL_Plane_Exists(pPicFormat->ePlaneMode, pPicFormat->eStorageMode != AL_FB_RASTER && pPicFormat->bCompressed, ePlaneId))
    return 0;

  AL_TDimension rndDim = (AL_TDimension) {
    RoundUp(tDim.iWidth, 64), RoundUp(tDim.iHeight, 64)
  };

  if(ePlaneId == AL_PLANE_MAP_UV)
    return AL_GetFbcMapUVSize(rndDim, pPicFormat);
  else
  {
    AL_TPicFormat tTempPicFormat = *pPicFormat;
    tTempPicFormat.eChromaMode = AL_CHROMA_MONO;
    return AL_GetFbcMapSize(rndDim, &tTempPicFormat);
  }
}

/*****************************************************************************/
int AL_DecGetAllocSize_Frame_MapY(AL_EFbStorageMode eFbStorage, bool bFbCompression, AL_TDimension tDim)
{
  AL_TPicFormat tPicFormat = GetDefaultPicFormat();
  tPicFormat.eChromaMode = AL_CHROMA_MONO;
  tPicFormat.ePlaneMode = GetInternalBufPlaneMode(AL_CHROMA_MONO);
  tPicFormat.uBitDepth = 8;
  tPicFormat.eStorageMode = eFbStorage;
  tPicFormat.bCompressed = bFbCompression;
  return AL_DecGetAllocSize_Frame_MapPlane(&tPicFormat, tDim, AL_PLANE_MAP_Y);
}

/*****************************************************************************/
int AL_DecGetAllocSize_Frame_MapUV(AL_EFbStorageMode eFbStorage, bool bFbCompression, AL_TDimension tDim, AL_EChromaMode eChromaMode)
{
  AL_TPicFormat tPicFormat = GetDefaultPicFormat();
  tPicFormat.eChromaMode = eChromaMode;
  tPicFormat.ePlaneMode = GetInternalBufPlaneMode(AL_CHROMA_MONO);
  tPicFormat.uBitDepth = 8;
  tPicFormat.eStorageMode = eFbStorage;
  tPicFormat.bCompressed = bFbCompression;
  return AL_DecGetAllocSize_Frame_MapPlane(&tPicFormat, tDim, AL_PLANE_MAP_UV);
}

/****************************************************************************/
uint32_t AL_GetRefListOffsets(TRefListOffsets* pOffsets, AL_ECodec eCodec, AL_TPicFormat tPicFormat, uint8_t uAddrSizeInBytes)
{
  AL_EPlaneId usedPlanes[AL_MAX_BUFFER_PLANES];
  const int iNbPixPlanes = Max(2, AL_Plane_GetBufferPixelPlanes(tPicFormat, usedPlanes));
  TRefListOffsets tOffsets;
  (void)eCodec;

  uint32_t uOffset = uAddrSizeInBytes * MAX_REF * iNbPixPlanes; // size of RefList Buff Addrs

  tOffsets.uColocPocOffset = uOffset;
  uOffset += uAddrSizeInBytes * MAX_REF; // size of coloc POCs Buff Addrs

  tOffsets.uColocMVOffset = uOffset;
  uOffset += uAddrSizeInBytes * MAX_REF; // size of coloc MVs Buff Addrs

  tOffsets.uMapOffset = uOffset;
  uOffset += uAddrSizeInBytes * MAX_REF * iNbPixPlanes;  // size of RefList Map Addr

  if(pOffsets)
    *pOffsets = tOffsets;

  return uOffset;
}

/*****************************************************************************/
int AL_DecGetAllocSize_Frame(AL_TDimension tDim, int iPitch, AL_TPicFormat tPicFormat)
{
  uint32_t uSize = 0;

  AL_EPlaneId usedPlanes[AL_MAX_BUFFER_PLANES];
  int iNbPlanes = AL_Plane_GetBufferPlanes(tPicFormat, usedPlanes);

  for(int iPlane = 0; iPlane < iNbPlanes; iPlane++)
  {

    if(AL_Plane_IsMapPlane(usedPlanes[iPlane]))
    {
      tPicFormat.bCompressed = true;
      uSize += AL_DecGetAllocSize_Frame_MapPlane(&tPicFormat, tDim, usedPlanes[iPlane]);
    }
    else
    uSize += AL_DecGetAllocSize_Frame_PixPlane(&tPicFormat, tDim, iPitch, usedPlanes[iPlane]);
  }

  return uSize;
}

/*****************************************************************************/
int AL_GetAllocSize_Frame(AL_TDimension tDim, AL_EChromaMode eChromaMode, uint8_t uBitDepth, bool bFbCompression, AL_EFbStorageMode eFbStorageMode)
{
  AL_TPicFormat tPicFormat = GetDefaultPicFormat();
  tPicFormat.eChromaMode = eChromaMode;
  tPicFormat.ePlaneMode = GetInternalBufPlaneMode(eChromaMode);
  tPicFormat.uBitDepth = uBitDepth;
  tPicFormat.eStorageMode = eFbStorageMode;
  tPicFormat.bCompressed = bFbCompression;
  tPicFormat.eSamplePackMode = GetInternalBufSamplePackMode(eFbStorageMode, uBitDepth);
  int iPitch = RndPitch(tDim.iWidth, &tPicFormat);
  return AL_DecGetAllocSize_Frame(tDim, iPitch, tPicFormat);
}

/*****************************************************************************/
AL_TMetaData* AL_CreateRecBufMetaData(AL_TDimension tDim, int iMinPitch, TFourCC tFourCC)
{
  AL_TPixMapMetaData* pSrcMeta = AL_PixMapMetaData_CreateEmpty(tFourCC);
  pSrcMeta->tDim = tDim;

  AL_TPicFormat tPicFormat;

  bool const bSuccess = AL_GetPicFormat(tFourCC, &tPicFormat);

  if(!bSuccess)
  {
    AL_MetaData_Destroy((AL_TMetaData*)pSrcMeta);
    Rtos_Assert(bSuccess);
    return NULL;
  }

  int iOffset = 0;

  AL_EPlaneId usedPlanes[AL_MAX_BUFFER_PLANES];
  int iNbPlanes = AL_Plane_GetBufferPixelPlanes(tPicFormat, usedPlanes);

  for(int iPlane = 0; iPlane < iNbPlanes; iPlane++)
  {
    int iPitch = usedPlanes[iPlane] == AL_PLANE_Y ? iMinPitch : AL_GetChromaPitch(tFourCC, iMinPitch);
    AL_PixMapMetaData_AddPlane(pSrcMeta, (AL_TPlane) {0, iOffset, iPitch }, usedPlanes[iPlane]);

    if(usedPlanes[iPlane] == AL_PLANE_U)
      AL_PixMapMetaData_AddPlane(pSrcMeta, (AL_TPlane) {0, iOffset, iPitch }, AL_PLANE_UV);

    iOffset += AL_DecGetAllocSize_Frame_PixPlane(&tPicFormat, tDim, iPitch, usedPlanes[iPlane]);
  }

  if(AL_IsCompressed(tFourCC))
  {
    int iMapPitch = AL_GetFbcMapPitch(tDim.iWidth, tPicFormat.eStorageMode, tPicFormat.uBitDepth);

    int iNbPlanes = AL_Plane_GetBufferMapPlanes(tPicFormat, usedPlanes);

    for(int iPlane = 0; iPlane < iNbPlanes; iPlane++)
    {
      int iPitch = usedPlanes[iPlane] == AL_PLANE_MAP_Y ? iMapPitch : AL_GetChromaPitch(tFourCC, iMapPitch);
      AL_PixMapMetaData_AddPlane(pSrcMeta, (AL_TPlane) {0, iOffset, iPitch }, usedPlanes[iPlane]);

      if(usedPlanes[iPlane] == AL_PLANE_MAP_U)
        AL_PixMapMetaData_AddPlane(pSrcMeta, (AL_TPlane) {0, iOffset, iPitch }, AL_PLANE_MAP_UV);

      iOffset += AL_DecGetAllocSize_Frame_MapPlane(&tPicFormat, tDim, usedPlanes[iPlane]);
    }
  }
  return (AL_TMetaData*)pSrcMeta;
}

/*!@}*/
