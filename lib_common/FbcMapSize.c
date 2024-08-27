// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_common/FbcMapSize.h"
#include "Utils.h"

static AL_TDimension getTileDimension(AL_EFbStorageMode eFBStorageMode, uint8_t uBitdepth)
{
  (void)uBitdepth;
  switch(eFBStorageMode)
  {
  case AL_FB_TILE_32x4:
    return (AL_TDimension) {
             32, 4
    };
  case AL_FB_TILE_64x4:
    return (AL_TDimension) {
             64, 4
    };

  default:
    Rtos_Assert(false);
    return (AL_TDimension) {
             32, 4
    };
  }
}

uint16_t AL_GetFbcMapPitch(uint32_t uWidth, AL_EFbStorageMode eFBStorageMode, uint8_t uBitDepth)
{
  int const NumTilePerMapUnit = 2;

  int MapSize = 1;

  AL_TDimension TileDimension = getTileDimension(eFBStorageMode, uBitDepth);

  uint16_t uMapPitch = MapSize * ((4096 / (NumTilePerMapUnit * TileDimension.iWidth)) * ((uWidth + 4095) >> 12));
  return uMapPitch;
}

uint32_t AL_GetFbcMapPlaneSize(AL_TDimension tDimension, AL_EFbStorageMode eFBStorageMode, uint8_t uBitDepth)
{
  static const uint32_t HW_ENC_MAP_BURST = 16;

  AL_TDimension const TileDimension = getTileDimension(eFBStorageMode, uBitDepth);
  uint32_t uPitch = AL_GetFbcMapPitch(tDimension.iWidth, eFBStorageMode, uBitDepth);
  uint32_t uH = DivideRoundUp(tDimension.iHeight, TileDimension.iHeight); // Ensure that a HW reading burst is reading allocated memory
  uH = RoundUp(uH, HW_ENC_MAP_BURST);
  uint32_t uSize = uH * uPitch;
  return uSize;
}

uint32_t AL_GetFbcMapUVSize(AL_TDimension tDimension, AL_TPicFormat const* pPicFormat)
{
  if(pPicFormat->eChromaMode != AL_CHROMA_4_2_0 && pPicFormat->eChromaMode != AL_CHROMA_4_2_2)
    return 0;

  tDimension.iHeight = (AL_CHROMA_4_2_0 == pPicFormat->eChromaMode) ? tDimension.iHeight / 2 : tDimension.iHeight;
  return AL_GetFbcMapPlaneSize(tDimension, pPicFormat->eStorageMode, pPicFormat->uBitDepth);
}

uint32_t AL_GetFbcMapSize(AL_TDimension tDimension, AL_TPicFormat const* pPicFormat)
{
  uint32_t uSize = AL_GetFbcMapPlaneSize(tDimension, pPicFormat->eStorageMode, pPicFormat->uBitDepth);

  if(AL_CHROMA_MONO == pPicFormat->eChromaMode)
    return uSize;

  if(AL_CHROMA_4_4_4 == pPicFormat->eChromaMode)
    return uSize * 3;

  return uSize + AL_GetFbcMapUVSize(tDimension, pPicFormat);
}
