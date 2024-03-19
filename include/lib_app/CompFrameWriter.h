// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "lib_app/CompFrameCommon.h"
#include "lib_app/BaseFrameWriter.h"

extern "C"
{
#include "lib_common/FourCC.h"
#include "lib_common/SliceConsts.h"
#include "lib_common/BufferAPI.h"
}

#include <fstream>
#include <stdexcept>

/****************************************************************************/
struct CompFrameWriter final : IFrameWriter, BaseFrameWriter
{
  CompFrameWriter(std::shared_ptr<std::ostream> recFile, std::shared_ptr<std::ostream> mapFile, AL_EFbStorageMode eStorageMode, uint8_t uCompMode);
  ~CompFrameWriter();

  void WriteFrame(AL_TBuffer* pBuf, AL_TCropInfo* pCrop = nullptr, AL_EPicStruct ePicStruct = AL_PS_FRM) override;

private:
  std::shared_ptr<std::ostream> m_mapFile;
  bool m_bWriteHeader;

  uint32_t m_uResolutionFrameCnt;
  std::streampos m_tResolutionPointerPos;
  AL_TCropInfo m_tCrop = {};
  uint8_t m_uCompMode;
  uint32_t m_uPitchMapFile;
  uint16_t m_uHeightInMapTileY;
  uint16_t m_uHeightInMapTileC;

  void WriteHeader(uint8_t uBitDepth);

  void WriteResolutionChangePointers();
  void WriteResolutionChangePointer();

  void WriteMap(const uint8_t* pMap, uint32_t uPitchInMap, uint16_t uHeightInMap, AL_EPicStruct ePicStruct);
  void DimInTileMapCalculus();
  bool MustDoDimInTileCalculus(AL_TDimension const& tPicDim, AL_TPicFormat const& tPicFormat, AL_TCropInfo const& tCrop) const;
};
