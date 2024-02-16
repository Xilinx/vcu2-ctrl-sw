// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_app/CompFrameWriter.h"
#include "lib_app/CompFrameCommon.h"

extern "C"
{
#include "lib_common/PixMapBuffer.h"
#include "lib_common/DisplayInfoMeta.h"
}

#include <iostream>
#include <algorithm>

using namespace std;

inline bool AreDimensionsEqual(AL_TDimension tDim1, AL_TDimension tDim2)
{
  return tDim1.iWidth == tDim2.iWidth && tDim1.iHeight == tDim2.iHeight;
}

/****************************************************************************/
CompFrameWriter::CompFrameWriter(std::shared_ptr<std::ostream> recFile, std::shared_ptr<std::ostream> mapFile, AL_EFbStorageMode eStorageMode, uint8_t uCompMode, AL_EOutputType outputID) :
  BaseFrameSink(recFile, eStorageMode, outputID), m_mapFile(mapFile), m_uResolutionFrameCnt(0), m_tResolutionPointerPos(-1), m_uCompMode(uCompMode)
{
  m_bWriteHeader = true;
  m_tCrop = {};
}

/****************************************************************************/
CompFrameWriter::~CompFrameWriter()
{
  m_mapFile->flush();
}

/****************************************************************************/
void CompFrameWriter::WriteHeader(uint8_t uBitDepth)
{
  WriteValue(m_mapFile, CurrentCompFileVersion);
  WriteValue(m_mapFile, EFbStorageModeToETileMode(AL_GetStorageMode(m_tFourCC), uBitDepth));
  WriteValue(m_mapFile, m_uCompMode);
}

/****************************************************************************/
void CompFrameWriter::WriteResolutionChangePointers()
{
  std::streampos tNewResolutionChangePointer = m_mapFile->tellp();

  if(m_uResolutionFrameCnt != 0)
  {
    // Update pointer from previous resolution
    WriteResolutionChangePointer();
    m_uResolutionFrameCnt = 0;
  }

  // Initialize pointer from current resolution
  m_tResolutionPointerPos = tNewResolutionChangePointer;
  WriteResolutionChangePointer();
}

/****************************************************************************/
void CompFrameWriter::WriteResolutionChangePointer()
{
  m_mapFile->seekp(m_tResolutionPointerPos);
  WriteValue(m_mapFile, m_uResolutionFrameCnt);
}

/****************************************************************************/
void CompFrameWriter::DimInTileMapCalculus()
{
  static const uint32_t MIN_HEIGHT_ROUNDING = 8;

  int iMapWidth = GetTileWidth(m_tPicFormat.eStorageMode, m_tPicFormat.uBitDepth);
  int iMapHeight = GetTileHeight(m_tPicFormat.eStorageMode);
  int iMapSize = 1;

  m_uPitchMapFile = AL_RoundUpAndDivide(m_tPicDim.iWidth, 4096, iMapWidth * 2) * iMapSize;
  m_uHeightInMapTileY = AL_RoundUpAndDivide(m_tPicDim.iHeight, std::max(uint32_t(iMapHeight), MIN_HEIGHT_ROUNDING), iMapHeight);

  if(AL_PLANE_MODE_SEMIPLANAR == m_tPicFormat.ePlaneMode)
  {
    m_uHeightInMapTileC = AL_RoundUp(m_uHeightInMapTileY, m_iChromaVertScale) / m_iChromaVertScale;
  }
  else
  {
    m_iChromaVertScale = 0;
    m_uHeightInMapTileC = 0;
  }

  WriteValue(m_mapFile, m_tFourCC);

  WriteValue<uint16_t>(m_mapFile, m_tPicDim.iWidth - m_tCrop.uCropOffsetLeft - m_tCrop.uCropOffsetRight);
  WriteValue<uint16_t>(m_mapFile, m_tPicDim.iHeight - m_tCrop.uCropOffsetTop - m_tCrop.uCropOffsetBottom);
  WriteValue<uint16_t>(m_mapFile, m_tCrop.uCropOffsetLeft);
  WriteValue<uint16_t>(m_mapFile, m_tCrop.uCropOffsetTop);

  WriteValue(m_mapFile, m_uPitchYFile);
  WriteValue(m_mapFile, m_uPitchMapFile);
  WriteValue(m_mapFile, m_uHeightInTileYFile);
  WriteValue(m_mapFile, m_uHeightInMapTileY);

  WriteResolutionChangePointers();
}

/****************************************************************************/
bool CompFrameWriter::MustDoDimInTileCalculus(AL_TDimension const& tPicDim, AL_TPicFormat const& tPicFormat, AL_TCropInfo const& tCrop) const
{
  return !AreDimensionsEqual(tPicDim, m_tPicDim) ||
         tPicFormat.ePlaneMode != m_tPicFormat.ePlaneMode ||
         tPicFormat.eChromaMode != m_tPicFormat.eChromaMode ||
         tCrop.uCropOffsetLeft != m_tCrop.uCropOffsetLeft ||
         tCrop.uCropOffsetRight != m_tCrop.uCropOffsetRight ||
         tCrop.uCropOffsetTop != m_tCrop.uCropOffsetTop ||
         tCrop.uCropOffsetBottom != m_tCrop.uCropOffsetBottom;
}

/****************************************************************************/
void CompFrameWriter::ProcessFrame(AL_TBuffer* pBuf)
{
  AL_TDisplayInfoMetaData* pMeta = reinterpret_cast<AL_TDisplayInfoMetaData*>(AL_Buffer_GetMetaData(pBuf, AL_META_TYPE_DISPLAY_INFO));
  AL_TCropInfo tCrop {};
  AL_EOutputType eOutputID = AL_OUTPUT_MAIN;

  AL_EPicStruct ePicStruct = AL_PS_FRM;

  if(pMeta)
  {
    tCrop = pMeta->tCrop;
    eOutputID = pMeta->eOutputID;
    ePicStruct = pMeta->ePicStruct;
  }

  AL_TPicFormat tPicFormat;
  AL_GetPicFormat(AL_PixMapBuffer_GetFourCC(pBuf), &tPicFormat);
  bool updateCalculus = MustDoDimInTileCalculus(AL_PixMapBuffer_GetDimension(pBuf), tPicFormat, tCrop);

  if(pMeta)
    m_tCrop = pMeta->tCrop;

  m_tFourCC = AL_PixMapBuffer_GetFourCC(pBuf);
  AL_EFbStorageMode currentStorageMode = AL_GetStorageMode(m_tFourCC);
  AL_GetPicFormat(m_tFourCC, &m_tPicFormat);
  m_tPicDim = AL_PixMapBuffer_GetDimension(pBuf);

  if(currentStorageMode != m_eStorageMode || eOutputID != m_iOutputID)
    return;

  // To write header in constructor the fourCC needs to be known which is not the case in decoder prealloc
  if(m_bWriteHeader)
  {
    WriteHeader(tPicFormat.uBitDepth);
    m_bWriteHeader = false;
  }

  // Luma
  const uint8_t* pY = AL_PixMapBuffer_GetPlaneAddress(pBuf, AL_PLANE_Y);
  const uint8_t* pMapY = AL_PixMapBuffer_GetPlaneAddress(pBuf, AL_PLANE_MAP_Y);
  uint32_t uPitchLuma = AL_PixMapBuffer_GetPlanePitch(pBuf, AL_PLANE_Y);
  uint32_t uPitchMap = AL_PixMapBuffer_GetPlanePitch(pBuf, AL_PLANE_MAP_Y);

  // Chroma
  const uint8_t* pC1 = nullptr;
  const uint8_t* pMapC1 = nullptr;
  const uint8_t* pC2 = nullptr;
  const uint8_t* pMapC2 = nullptr;
  uint32_t uPitchChroma = 0;

  if(AL_PLANE_MODE_PLANAR == m_tPicFormat.ePlaneMode)
  {
    pC1 = AL_PixMapBuffer_GetPlaneAddress(pBuf, AL_PLANE_U);
    pMapC1 = AL_PixMapBuffer_GetPlaneAddress(pBuf, AL_PLANE_MAP_U);
    pC2 = AL_PixMapBuffer_GetPlaneAddress(pBuf, AL_PLANE_V);
    pMapC2 = AL_PixMapBuffer_GetPlaneAddress(pBuf, AL_PLANE_MAP_V);
    uPitchChroma = AL_PixMapBuffer_GetPlanePitch(pBuf, AL_PLANE_U);

    if(int(uPitchChroma) != AL_PixMapBuffer_GetPlanePitch(pBuf, AL_PLANE_V))
      throw std::runtime_error(ErrorMessagePitch);
  }
  else if(AL_PLANE_MODE_SEMIPLANAR == m_tPicFormat.ePlaneMode)
  {
    pC1 = AL_PixMapBuffer_GetPlaneAddress(pBuf, AL_PLANE_UV);
    pMapC1 = AL_PixMapBuffer_GetPlaneAddress(pBuf, AL_PLANE_MAP_UV);
    uPitchChroma = AL_PixMapBuffer_GetPlanePitch(pBuf, AL_PLANE_UV);
  }

  if(updateCalculus)
  {
    DimInTileCalculus();
    DimInTileMapCalculus();
  }

  WritePix(pY, uPitchLuma, m_uHeightInTileYFile, m_uPitchYFile);
  WriteMap(pMapY, uPitchMap, m_uHeightInMapTileY, ePicStruct);

  m_uResolutionFrameCnt++;

  if(AL_CHROMA_4_0_0 == m_tPicFormat.eChromaMode)
    return;

  if(AL_PLANE_MODE_PLANAR == m_tPicFormat.ePlaneMode)
  {
    WritePix(pC1, uPitchChroma, m_uHeightInTileYFile, m_uPitchCFile);
    WriteMap(pMapC1, uPitchMap, m_uHeightInMapTileY, ePicStruct);
    WritePix(pC2, uPitchChroma, m_uHeightInTileYFile, m_uPitchCFile);
    WriteMap(pMapC2, uPitchMap, m_uHeightInMapTileY, ePicStruct);
  }
  else if(AL_PLANE_MODE_SEMIPLANAR == m_tPicFormat.ePlaneMode)
  {
    WritePix(pC1, uPitchChroma, m_uHeightInTileCFile, m_uPitchCFile);
    WriteMap(pMapC1, uPitchMap, m_uHeightInMapTileC, ePicStruct);
  }
}

/****************************************************************************/
static const uint8_t* AlignMap(const uint8_t* pMap, uint32_t uPitchInMap, uint16_t uHeightInMap)
{
  const uint32_t uReqAlignment = 256;

  uint32_t uCurAlignment = (uHeightInMap * uPitchInMap) % uReqAlignment;

  if(uCurAlignment)
    pMap += uReqAlignment - uCurAlignment;

  return pMap;
}

/****************************************************************************/
static bool IsInterlacedFrame(AL_EPicStruct ePicStruct)
{
  switch(ePicStruct)
  {
  case AL_PS_TOP_BOT:
  case AL_PS_BOT_TOP:
  case AL_PS_TOP_BOT_TOP:
  case AL_PS_BOT_TOP_BOT:
    return true;
  default:
    break;
  }

  return false;
}

/****************************************************************************/
void CompFrameWriter::WriteMap(const uint8_t* pMap, uint32_t uPitchInMap, uint16_t uHeightInMap, AL_EPicStruct ePicStruct)
{
  CheckNotNull(pMap);

  int iSplit = IsInterlacedFrame(ePicStruct) ? 2 : 1;

  uHeightInMap = (uHeightInMap + iSplit - 1) / iSplit;

  for(int i = 0; i < iSplit; ++i)
  {
    for(int r = 0; r < uHeightInMap; ++r)
    {
      WriteBuffer(m_mapFile, pMap, m_uPitchMapFile);
      pMap += uPitchInMap;
    }

    pMap = AlignMap(pMap, uHeightInMap, uPitchInMap);
  }
}
