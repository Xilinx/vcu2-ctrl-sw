// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <vector>

#include "FrameReader.h"
#include "lib_app/CompFrameCommon.h"

extern "C"
{
#include "lib_common/FourCC.h"
#include "lib_common/PicFormat.h"
#include "lib_common/PixMapBuffer.h"
}

class CompFrameReader : public FrameReader
{
public:
  struct TCompFrameHeader
  {
    AL_TPicFormat tPicFormat;
    ETileMode eTileMode;
    uint8_t uCompMode; // 0 is lossless, 1 to 6 (or 8/10 in 10/12bpc) is lossy, 50 is lossy 50%
  };

  struct TCompFrameResolution
  {
    uint16_t uWidth;
    uint16_t uHeight;
    uint16_t uCroppedWidth;
    uint16_t uCroppedHeight;
    uint16_t uCropOffsetHrz;
    uint16_t uCropOffsetVrt;

    uint32_t uPitch;
    uint32_t uPitchMap;

    uint16_t uHeightInTilesY;
    uint16_t uHeightInTilesC;
    uint16_t uHeightInMapTilesY;
    uint16_t uHeightInMapTilesC;
  };

  enum CompFrameReadResult
  {
    FRAME_RED,
    NEW_RESOLUTION_FRAME_RED,
    END_OF_FILE
  };

  CompFrameReader(std::ifstream& iRecFile, std::ifstream& iMapFile, bool bLoopFrames);

  TCompFrameHeader const& GetCurrentHeader() const;
  TCompFrameResolution const& GetCurrentResolution() const;

  CompFrameReadResult GetNextStatus();
  CompFrameReadResult GoTo(uint32_t uFrameIdx);
  bool ReadFrame(uint8_t* pBufY, size_t bufYSize, uint8_t* pBufC1, size_t bufC1Size, uint8_t* pBufC2, size_t bufC2Size, uint8_t* pBufMapY, size_t bufMapYSize, uint8_t* pBufMapC1, size_t bufMapC1Size, uint8_t* pBufMapC2, size_t bufMapC2Size);
  bool ReadFrame(AL_TBuffer* pFrameBuffer);
  void ReadComponent(uint8_t* pBuf, size_t bufSize, uint8_t* pBufMap, size_t bufMapSize, bool bChroma);

  void SeekA(uint32_t uFrameIdx); // seek to Absolution position from the beginning
  void SeekR(int iFrameDlt);      // seek to Relative position from the current position (both direction allowed)

private:
  struct TResolutionInfos
  {
    std::streampos tMapStart;
    std::streampos tMapEnd;
    std::streampos tRecStart;
    std::streampos tRecEnd;

    uint32_t uResFrameCnt;
    bool bLastResolution;

    TCompFrameResolution tRes;
    TCompFrameHeader tHead;

    uint32_t uBufSizeY;
    uint32_t uBufSizeC;
    uint32_t uBufSizeMapY;
    uint32_t uBufSizeMapC;
  };

  std::ifstream& m_mapFile;
  uint8_t m_uVersion;
  TCompFrameHeader m_tCompFrameHeader;

  std::vector<TResolutionInfos> m_vResolutions;

  uint32_t m_uCurrentResIdx;
  uint32_t m_uCurrentResFrameIdx;
  CompFrameReadResult m_readResult;

  void ParseVersion();
  AL_TPicFormat ParsePicFormat();
  void ParseHeader();
  void ParseResolutions();

  void ParseResolution(TResolutionInfos& tResInfo);
  void ComputeBufferSizes(TResolutionInfos& tResInfo);

  CompFrameReadResult GoTo(uint32_t uResIdx, uint32_t uResFrameIdx);
  uint32_t GetCurrentFrameIdx();
  AL_EChromaMode GetCurrentChromaMode() const;
  uint8_t GetCurrentBitDepth() const;
  uint8_t GetCurrentStorageMode() const;

  uint32_t GetNumChromaPlane(TResolutionInfos const &) const;
  uint32_t GetSizePicRec(const TResolutionInfos& tResInfo) const;
  uint32_t GetSizePicMap(const TResolutionInfos& tResInfo) const;

  template<typename T>
  void ParseValue(std::ifstream& m_stream, T& val);
  void ParseBuffer(std::ifstream& m_stream, uint8_t* pBuf, size_t bufSize, uint32_t uReadSize);

  static const std::string ErrorMessageVersion;
  static const std::string ErrorMessageCorrupted;
  static const std::string ErrorMessagePictureNumber;
  static const std::string ErrorMessageBufferTooSmall;
  static const std::string ChromaModeNotHandled;
  static const std::string InvalidResolution;
  static const std::string InvalidChromaMode;
  static const std::string InvalidBitDepth;
  static const std::string InvalidStorageMode;
};

inline CompFrameReader::TCompFrameResolution const & CompFrameReader::GetCurrentResolution() const
{
  return m_vResolutions[m_uCurrentResIdx].tRes;
}

inline CompFrameReader::TCompFrameHeader const & CompFrameReader::GetCurrentHeader() const
{
  return m_vResolutions[m_uCurrentResIdx].tHead;
}

inline uint32_t CompFrameReader::GetSizePicRec(const TResolutionInfos& tResInfo) const
{
  return tResInfo.uBufSizeY + tResInfo.uBufSizeC * GetNumChromaPlane(tResInfo);
}

inline uint32_t CompFrameReader::GetSizePicMap(const TResolutionInfos& tResInfo) const
{
  return tResInfo.uBufSizeMapY + tResInfo.uBufSizeMapC * GetNumChromaPlane(tResInfo);
}

template<typename T>
void CompFrameReader::ParseValue(std::ifstream& m_stream, T& val)
{
  if(!m_stream.read((char*)&val, sizeof(T)))
    throw std::runtime_error(ErrorMessageCorrupted);
}
