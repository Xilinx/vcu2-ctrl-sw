// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_common_dec/IpDecFourCC.h"
#include "lib_rtos/lib_rtos.h"

TFourCC AL_GetDecFourCC(AL_TPicFormat const picFmt)
{
  if(AL_FB_RASTER == picFmt.eStorageMode)
  {
    Rtos_Assert(picFmt.eChromaMode == AL_CHROMA_MONO || picFmt.eChromaMode == AL_CHROMA_4_4_4 || picFmt.ePlaneMode == AL_PLANE_MODE_SEMIPLANAR);
  }
  else if(picFmt.bMSB)
  {
    Rtos_Assert(picFmt.uBitDepth > 8);
  }

  return AL_GetFourCC(picFmt);
}

AL_EPlaneMode AL_ChromaModeToPlaneMode(AL_EChromaMode eChromaMode)
{
  return GetInternalBufPlaneMode(eChromaMode);
}

AL_TPicFormat AL_GetDecPicFormat(AL_EChromaMode eChromaMode, uint8_t uBitDepth, AL_EFbStorageMode eStorageMode, bool bIsCompressed, AL_EPlaneMode ePlaneMode)
{
  AL_EPlaneMode eAdjustedPlaneMode = (AL_PLANE_MODE_MAX_ENUM == ePlaneMode) ? GetInternalBufPlaneMode(eChromaMode) : ePlaneMode;
  AL_ESamplePackMode eSamplePackMode = AL_SAMPLE_PACK_MODE_BYTE;

  if(eStorageMode == AL_FB_TILE_32x4 || eStorageMode == AL_FB_TILE_64x4)
    eSamplePackMode = AL_SAMPLE_PACK_MODE_PACKED;

  AL_TPicFormat picFormat =
  {
    eChromaMode,
    AL_ALPHA_MODE_DISABLED,
    uBitDepth,
    eStorageMode,
    eAdjustedPlaneMode,
    AL_COMPONENT_ORDER_YUV,
    eSamplePackMode,
    bIsCompressed,
    false
  };
  return picFormat;
}
