// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include <fstream>
#include <string>
#include <regex>
#include <stdexcept>

#include "lib_app/CompFrameReader.h"

extern "C"
{
#include "lib_common/PixMapBuffer.h"
#include "lib_common/PixMapBufferInternal.h"
}

using namespace std;

const string CompFrameReader::ErrorMessageVersion = "Your software can't open compressed YUV file with version <version>, please update it.";
const string CompFrameReader::ErrorMessageCorrupted = "Error reading compressed YUV. File is corrupted.";
const string CompFrameReader::ErrorMessagePictureNumber = "Can't go to frame <frame-idx>, compressed YUV contains less frames.";
const string CompFrameReader::ErrorMessageBufferTooSmall = "Buffer provided to read compressed YUV is too small.";
const string CompFrameReader::ChromaModeNotHandled = "Given chroma mode is not handled.";
const string CompFrameReader::InvalidResolution = "Resolution of the compressed YUV file differs from what we want to read.";
const string CompFrameReader::InvalidChromaMode = "Chroma-mode of the compressed YUV file differs from what we want to read.";
const string CompFrameReader::InvalidBitDepth = "Bitdepth of the compressed YUV file differs from what we want to read.";
const string CompFrameReader::InvalidStorageMode = "Storage-mode (64x4/32x4) of the compressed YUV file differs from what we want to read.";

CompFrameReader::CompFrameReader(std::ifstream& sRecFileName, std::ifstream& sMapFileName, bool bLoopFrames) : FrameReader(sRecFileName, bLoopFrames),
  m_mapFile(sMapFileName), m_uCurrentResIdx(-1), m_uCurrentResFrameIdx(-1), m_readResult(NEW_RESOLUTION_FRAME_RED)
{
  if(!m_recFile.is_open())
    throw runtime_error("Invalid input file");

  if(!m_mapFile.is_open())
    throw runtime_error("Invalid map file");

  ParseVersion();

  ParseHeader();

  ParseResolutions();
}

void CompFrameReader::ParseVersion(void)
{
  ParseValue(m_mapFile, m_uVersion);

  if(m_uVersion > CurrentCompFileVersion)
    throw runtime_error(std::regex_replace(ErrorMessageVersion, std::regex("<version>"), to_string(m_uVersion)));
}

AL_TPicFormat CompFrameReader::ParsePicFormat(void)
{
  TFourCC tFourCC;
  ParseValue(m_mapFile, tFourCC);
  AL_TPicFormat tPicFormat;

  if(!AL_GetPicFormat(tFourCC, &tPicFormat))
    throw runtime_error("Invalid input file");

  return tPicFormat;
}

void CompFrameReader::ParseHeader(void)
{
  if(m_uVersion < 3)
    m_tCompFrameHeader.tPicFormat = ParsePicFormat();

  ParseValue(m_mapFile, m_tCompFrameHeader.eTileMode);
  ParseValue(m_mapFile, m_tCompFrameHeader.uCompMode);
}

void CompFrameReader::ParseResolutions(void)
{
  TResolutionInfos tResInfo;

  do
  {
    ParseResolution(tResInfo);

    if(tResInfo.uResFrameCnt != 0)
    {
      m_vResolutions.push_back(tResInfo);
      m_uTotalFrameCnt += tResInfo.uResFrameCnt;
    }
  }
  while(!tResInfo.bLastResolution);

  GoTo(0);
}

void CompFrameReader::ParseResolution(TResolutionInfos& tResInfo)
{
  if(m_uVersion >= 3)
  {
    tResInfo.tHead.eTileMode = m_tCompFrameHeader.eTileMode;
    tResInfo.tHead.uCompMode = m_tCompFrameHeader.uCompMode;
    tResInfo.tHead.tPicFormat = ParsePicFormat();
  }
  else
    tResInfo.tHead = m_tCompFrameHeader;

  ParseValue(m_mapFile, tResInfo.tRes.uCroppedWidth);
  ParseValue(m_mapFile, tResInfo.tRes.uCroppedHeight);

  if(m_uVersion >= 2)
  {
    ParseValue(m_mapFile, tResInfo.tRes.uCropOffsetHrz);
    ParseValue(m_mapFile, tResInfo.tRes.uCropOffsetVrt);
  }
  else
  {
    uint8_t uCropOffsetHrz, uCropOffsetVrt;
    ParseValue(m_mapFile, uCropOffsetHrz);
    ParseValue(m_mapFile, uCropOffsetVrt);
    tResInfo.tRes.uCropOffsetHrz = uCropOffsetHrz;
    tResInfo.tRes.uCropOffsetVrt = uCropOffsetVrt;
  }

  tResInfo.tRes.uWidth = tResInfo.tRes.uCroppedWidth + tResInfo.tRes.uCropOffsetHrz;
  tResInfo.tRes.uHeight = tResInfo.tRes.uCroppedHeight + tResInfo.tRes.uCropOffsetVrt;

  if(m_uVersion >= 2)
  {
    ParseValue(m_mapFile, tResInfo.tRes.uPitch);
    ParseValue(m_mapFile, tResInfo.tRes.uPitchMap);
  }
  else
  {
    uint16_t uPitch, uPitchMap;
    ParseValue(m_mapFile, uPitch);
    ParseValue(m_mapFile, uPitchMap);
    tResInfo.tRes.uPitch = uPitch;
    tResInfo.tRes.uPitchMap = uPitchMap;
  }

  ParseValue(m_mapFile, tResInfo.tRes.uHeightInTilesY);

  if(m_uVersion >= 2)
    ParseValue(m_mapFile, tResInfo.tRes.uHeightInMapTilesY);
  else
    tResInfo.tRes.uHeightInMapTilesY = tResInfo.tRes.uHeightInTilesY;

  ComputeBufferSizes(tResInfo);

  tResInfo.uResFrameCnt = 0;

  if(m_uVersion >= 1)
    ParseValue(m_mapFile, tResInfo.uResFrameCnt);

  tResInfo.tMapStart = m_mapFile.tellg();
  tResInfo.tRecStart = m_recFile.tellg();

  uint32_t uSizePict = GetSizePicRec(tResInfo);

  if(tResInfo.uResFrameCnt == 0)
  {
    m_recFile.seekg(0, ios_base::end);
    tResInfo.tRecEnd = m_recFile.tellg();

    m_mapFile.seekg(0, ios_base::end);
    tResInfo.tMapEnd = m_mapFile.tellg();

    tResInfo.uResFrameCnt = static_cast<uint32_t>(AL_64U(tResInfo.tRecEnd - tResInfo.tRecStart) / uSizePict);
    tResInfo.bLastResolution = true;
  }
  else
  {
    uint32_t uSizePictMap = GetSizePicMap(tResInfo);
    tResInfo.tRecEnd = tResInfo.tRecStart + streampos(uSizePict) * streampos(tResInfo.uResFrameCnt);
    tResInfo.tMapEnd = tResInfo.tMapStart + streampos(uSizePictMap) * streampos(tResInfo.uResFrameCnt);
    tResInfo.bLastResolution = false;

    m_recFile.seekg(tResInfo.tRecEnd);
    m_mapFile.seekg(tResInfo.tMapEnd);
  }
}

void CompFrameReader::ComputeBufferSizes(TResolutionInfos& tResInfo)
{
  switch(tResInfo.tHead.tPicFormat.eChromaMode)
  {
  case AL_CHROMA_4_4_4:
  case AL_CHROMA_4_2_2:
    tResInfo.tRes.uHeightInTilesC = tResInfo.tRes.uHeightInTilesY;
    tResInfo.tRes.uHeightInMapTilesC = tResInfo.tRes.uHeightInMapTilesY;
    break;
  case AL_CHROMA_4_2_0:
    tResInfo.tRes.uHeightInTilesC = (1 + tResInfo.tRes.uHeightInTilesY) / 2; // Interlace might need rounding
    tResInfo.tRes.uHeightInMapTilesC = (1 + tResInfo.tRes.uHeightInMapTilesY) / 2;
    break;
  case AL_CHROMA_4_0_0:
    tResInfo.tRes.uHeightInTilesC = 0;
    tResInfo.tRes.uHeightInMapTilesC = 0;
    break;
  default:
    throw runtime_error(ChromaModeNotHandled);
    break;
  }

  tResInfo.uBufSizeY = tResInfo.tRes.uPitch * tResInfo.tRes.uHeightInTilesY;
  tResInfo.uBufSizeMapY = tResInfo.tRes.uPitchMap * tResInfo.tRes.uHeightInMapTilesY;
  tResInfo.uBufSizeC = tResInfo.tRes.uPitch * tResInfo.tRes.uHeightInTilesC;
  tResInfo.uBufSizeMapC = tResInfo.tRes.uPitchMap * tResInfo.tRes.uHeightInMapTilesC;
}

CompFrameReader::CompFrameReadResult CompFrameReader::GoTo(uint32_t uFrameIdx)
{
  uint32_t uResIdx = 0;
  uint32_t uResFirstFrameIdx = 0;

  auto resIt = m_vResolutions.begin();

  while(resIt != m_vResolutions.end() && uFrameIdx > (uResFirstFrameIdx + resIt->uResFrameCnt - 1))
  {
    uResFirstFrameIdx += resIt->uResFrameCnt;
    uResIdx++;
    resIt++;
  }

  return GoTo(uResIdx, uFrameIdx - uResFirstFrameIdx);
}

CompFrameReader::CompFrameReadResult CompFrameReader::GoTo(uint32_t uResIdx, uint32_t uResFrameIdx)
{
  if(uResIdx < m_vResolutions.size() && uResFrameIdx < m_vResolutions[uResIdx].uResFrameCnt)
  {
    auto& res = m_vResolutions[uResIdx];

    m_recFile.seekg(res.tRecStart + streampos(GetSizePicRec(res) * uResFrameIdx));
    m_mapFile.seekg(res.tMapStart + streampos(GetSizePicMap(res) * uResFrameIdx));

    m_readResult = uResIdx != m_uCurrentResIdx ? NEW_RESOLUTION_FRAME_RED : FRAME_RED;
  }
  else
  {
    // seek to EOF to prevent potential following read.
    m_recFile.seekg(0, m_recFile.end);
    m_mapFile.seekg(0, m_mapFile.end);
    m_readResult = END_OF_FILE;
  }

  m_uCurrentResIdx = uResIdx;
  m_uCurrentResFrameIdx = uResFrameIdx;

  return m_readResult;
}

uint32_t CompFrameReader::GetCurrentFrameIdx(void)
{
  uint32_t uFrameCnt = m_uCurrentResFrameIdx;

  for(int i = m_uCurrentResIdx - 1; i >= 0; --i)
    uFrameCnt += m_vResolutions[m_uCurrentResIdx].uResFrameCnt;

  return uFrameCnt;
}

AL_EChromaMode CompFrameReader::GetCurrentChromaMode() const
{
  return GetCurrentHeader().tPicFormat.eChromaMode;
}

uint8_t CompFrameReader::GetCurrentBitDepth() const
{
  return GetCurrentHeader().tPicFormat.uBitDepth;
}

uint8_t CompFrameReader::GetCurrentStorageMode() const
{
  return GetCurrentHeader().tPicFormat.eStorageMode;
}

void CompFrameReader::ParseBuffer(std::ifstream& m_stream, uint8_t* pBuf, size_t bufSize, uint32_t uReadSize)
{
  if(uReadSize > bufSize)
    throw std::runtime_error(ErrorMessageBufferTooSmall);

  if(!m_stream.read(reinterpret_cast<char*>(pBuf), uReadSize))
    throw std::runtime_error(ErrorMessageCorrupted);
}

CompFrameReader::CompFrameReadResult CompFrameReader::GetNextStatus(void)
{
  return m_readResult;
}

bool CompFrameReader::ReadFrame(uint8_t* pBufY, size_t bufYSize, uint8_t* pBufC1, size_t bufC1Size, uint8_t* pBufC2, size_t bufC2Size, uint8_t* pBufMapY, size_t bufMapYSize, uint8_t* pBufMapC1, size_t bufMapC1Size, uint8_t* pBufMapC2, size_t bufMapC2Size)
{
  if(m_uTotalFrameCnt == 0)
    return false;

  if((m_recFile.peek() == EOF) && !m_bLoopFile)
    return false;

  if(m_recFile.peek() == EOF)
  {
    m_recFile.clear();
    m_mapFile.clear();
    GoTo(0);
  }

  ReadComponent(pBufY, bufYSize, pBufMapY, bufMapYSize, false);

  auto& res = m_vResolutions[m_uCurrentResIdx];

  if(AL_CHROMA_MONO != res.tHead.tPicFormat.eChromaMode)
  {
    ReadComponent(pBufC1, bufC1Size, pBufMapC1, bufMapC1Size, true);

    if(AL_PLANE_MODE_PLANAR == res.tHead.tPicFormat.ePlaneMode)
      ReadComponent(pBufC2, bufC2Size, pBufMapC2, bufMapC2Size, true);
  }

  ++m_uCurrentResFrameIdx;

  if(m_uCurrentResFrameIdx >= m_vResolutions[m_uCurrentResIdx].uResFrameCnt)
    GoTo(m_uCurrentResIdx + 1, 0);
  else
    m_readResult = FRAME_RED;

  return true;
}

void CompFrameReader::ReadComponent(uint8_t* pBuf, size_t bufSize, uint8_t* pBufMap, size_t bufMapSize, bool bChroma)
{
  auto& res = m_vResolutions[m_uCurrentResIdx];
  ParseBuffer(m_recFile, pBuf, bufSize, bChroma ? res.uBufSizeC : res.uBufSizeY);
  ParseBuffer(m_mapFile, pBufMap, bufMapSize, bChroma ? res.uBufSizeMapC : res.uBufSizeMapY);
}

uint32_t CompFrameReader::GetNumChromaPlane(TResolutionInfos const& tResInfo) const
{
  if(AL_CHROMA_MONO == tResInfo.tHead.tPicFormat.eChromaMode)
    return 0;

  if(AL_PLANE_MODE_SEMIPLANAR == tResInfo.tHead.tPicFormat.ePlaneMode)
    return 1;

  return 2;
}

bool CompFrameReader::ReadFrame(AL_TBuffer* pBuffer)
{
  uint8_t* pY = AL_PixMapBuffer_GetPlaneAddress(pBuffer, AL_PLANE_Y);
  uint8_t* pMapY = AL_PixMapBuffer_GetPlaneAddress(pBuffer, AL_PLANE_MAP_Y);

  uint8_t* pC1 = nullptr;
  uint8_t* pMapC1 = nullptr;
  uint8_t* pC2 = nullptr;
  uint8_t* pMapC2 = nullptr;

  AL_TPicFormat tPicFormat;
  AL_GetPicFormat(AL_PixMapBuffer_GetFourCC(pBuffer), &tPicFormat);

  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pBuffer);
  TCompFrameResolution compRes = GetCurrentResolution();

  if(compRes.uWidth != tDim.iWidth || compRes.uHeight != tDim.iHeight)
    throw runtime_error(InvalidResolution);

  if(GetCurrentChromaMode() != tPicFormat.eChromaMode)
    throw runtime_error(InvalidChromaMode);

  if(GetCurrentBitDepth() != tPicFormat.uBitDepth)
    throw runtime_error(InvalidBitDepth);

  if(GetCurrentStorageMode() != tPicFormat.eStorageMode)
    throw runtime_error(InvalidStorageMode);

  if(AL_PLANE_MODE_PLANAR == tPicFormat.ePlaneMode)
  {
    pC1 = AL_PixMapBuffer_GetPlaneAddress(pBuffer, AL_PLANE_U);
    pMapC1 = AL_PixMapBuffer_GetPlaneAddress(pBuffer, AL_PLANE_MAP_U);
    pC2 = AL_PixMapBuffer_GetPlaneAddress(pBuffer, AL_PLANE_V);
    pMapC2 = AL_PixMapBuffer_GetPlaneAddress(pBuffer, AL_PLANE_MAP_V);
  }
  else if(AL_PLANE_MODE_SEMIPLANAR == tPicFormat.ePlaneMode)
  {
    pC1 = AL_PixMapBuffer_GetPlaneAddress(pBuffer, AL_PLANE_UV);
    pMapC1 = AL_PixMapBuffer_GetPlaneAddress(pBuffer, AL_PLANE_MAP_UV);
  }
  auto& res = m_vResolutions[m_uCurrentResIdx];

  size_t const uPitchYuv = AL_PixMapBuffer_GetPlanePitch(pBuffer, AL_PLANE_Y);
  size_t const uPitchMap = AL_PixMapBuffer_GetPlanePitch(pBuffer, AL_PLANE_MAP_Y);

  if(uPitchYuv != res.tRes.uPitch)
    throw runtime_error("uPitchYuv should be equal to res.tRes.uPitch");

  if(uPitchMap != res.tRes.uPitchMap)
    throw runtime_error("uPitchMap should be equal to res.tRes.uPitchMap");

  return ReadFrame(pY, res.uBufSizeY, pC1, res.uBufSizeC, pC2, res.uBufSizeC,
                   pMapY, res.uBufSizeMapY, pMapC1, res.uBufSizeMapC, pMapC2, res.uBufSizeMapC);
}

void CompFrameReader::SeekA(uint32_t uFrameIdx)
{
  GoTo(uFrameIdx);
}

void CompFrameReader::SeekR(int iFrameDlt)
{
  int iFrameIdx = int(GetCurrentFrameIdx()) + iFrameDlt;

  if(iFrameIdx < 0)
    iFrameIdx = 0;

  GoTo(iFrameIdx);
}
