// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/****************************************************************************
   -----------------------------------------------------------------------------
 **************************************************************************//*!
   \addtogroup lib_base
   @{
   \file
 *****************************************************************************/
// Fourcc.org is not complete for the format definition of yuv
// - For planar format and 10-12 bits precision : the reference used is
// https://github.com/videolan/vlc/blob/master/src/misc/fourcc_list.h
// - For semi-planar format and 10-12 bits precision : the reference used is
// https://docs.microsoft.com/en-us/windows/win32/medfound/10-bit-and-16-bit-yuv-video-formats

#include <stdexcept>
#include <cstring>
#include <string>
#include <algorithm>
#include "lib_app/convert.h"

extern "C" {
#include "lib_common/PixMapBuffer.h"
#include "lib_common/Utils.h"
}

static inline uint16_t CONV_8B_TO_10B(uint8_t val)
{
  return ((uint16_t)val) << 2;
}

static inline uint16_t CONV_8B_TO_12B(uint8_t val)
{
  return ((uint16_t)val) << 4;
}

static inline uint8_t RND_10B_TO_8B(uint16_t val)
{
  return (uint8_t)((val >= 0x3FC) ? 0xFF : ((val + 2) >> 2));
}

static inline uint8_t RND_12B_TO_8B(uint16_t val)
{
  return (uint8_t)((val >= 0xFF0) ? 0xFF : ((val + 8) >> 4));
}

static inline uint16_t RND_12B_TO_10B(uint16_t val)
{
  return (uint16_t)((val >= 0xFFC) ? 0x3FF : ((val + 2) >> 2));
}

static inline uint8_t RND_16B_TO_8B(uint16_t val)
{
  return (uint8_t)((val >= 0xFF00) ? 0xFF : ((val + 128) >> 8));
}

static inline uint16_t RND_16B_TO_10B(uint16_t val)
{
  return (uint16_t)((val >= 0xFFC0) ? 0x3FF : ((val + 32) >> 6));
}

static inline uint16_t RND_16B_TO_12B(uint16_t val)
{
  return (uint16_t)((val >= 0xFFF0) ? 0xFFF : ((val + 8) >> 4));
}

static inline uint16_t LSB_10B_TO_MSB_10B(uint16_t val)
{
  return (uint16_t)(val << 6);
}

static inline uint16_t LSB_12B_TO_MSB_12B(uint16_t val)
{
  return (uint16_t)(val << 4);
}

static inline uint16_t COPY(uint16_t val)
{
  return val;
}

/****************************************************************************/
void CopyPixMapPlane(AL_TBuffer const* pSrc, AL_TBuffer* pDst, AL_EPlaneId ePlaneType, int iWidth, int iHeight, uint8_t uBitDepth)
{
  int iPitchSrc = AL_PixMapBuffer_GetPlanePitch(pSrc, ePlaneType);
  int iPitchDst = AL_PixMapBuffer_GetPlanePitch(pDst, ePlaneType);
  uint8_t* pSrcData = AL_PixMapBuffer_GetPlaneAddress(pSrc, ePlaneType);
  uint8_t* pDstData = AL_PixMapBuffer_GetPlaneAddress(pDst, ePlaneType);
  TFourCC tFourCC = AL_PixMapBuffer_GetFourCC(pSrc);

  AL_TPicFormat tPicFormat;
  AL_GetPicFormat(tFourCC, &tPicFormat);

  int iByteWidth = iWidth * (uBitDepth >= 10 ? 2 : 1);

  if(tPicFormat.ePlaneMode == AL_PLANE_MODE_INTERLEAVED && tPicFormat.eChromaMode != AL_CHROMA_4_0_0)
  {
    int iPixSize = sizeof(uint32_t);
    int iHorizontalScale = (tPicFormat.eChromaMode == AL_CHROMA_4_4_4) ? 1 : 2;

    bool bHasAlpha = tPicFormat.eAlphaMode == AL_ALPHA_MODE_BEFORE || tPicFormat.eAlphaMode == AL_ALPHA_MODE_AFTER;

    if((bHasAlpha && tPicFormat.uBitDepth == 8)
       || (tPicFormat.eSamplePackMode == AL_SAMPLE_PACK_MODE_PACKED && tPicFormat.uBitDepth == 10))
      iPixSize = sizeof(uint32_t);

    if(tPicFormat.eSamplePackMode == AL_SAMPLE_PACK_MODE_BYTE && (tPicFormat.uBitDepth == 12 || tPicFormat.uBitDepth == 10))
      iPixSize = sizeof(uint64_t);
    iByteWidth = iWidth * iPixSize / iHorizontalScale;
  }
  else if(AL_SAMPLE_PACK_MODE_PACKED_XV == tPicFormat.eSamplePackMode)
    iByteWidth = (iWidth + 2) / 3 * sizeof(uint32_t);

  for(int iH = 0; iH < iHeight; iH++)
  {
    std::memcpy(pDstData, pSrcData, iByteWidth);
    pSrcData += iPitchSrc;
    pDstData += iPitchDst;
  }
}

/****************************************************************************/
template<typename TSrc, typename TDst>
void ConvertPixMapPlane(AL_TBuffer const* pSrc, AL_TBuffer* pDst, AL_EPlaneId ePlaneType, int iWidth, int iHeight, TDst (* CONV_FUNC)(TSrc))
{
  int iPitchSrc = AL_PixMapBuffer_GetPlanePitch(pSrc, ePlaneType) / sizeof(TSrc);
  int iPitchDst = AL_PixMapBuffer_GetPlanePitch(pDst, ePlaneType) / sizeof(TDst);
  auto pSrcData = (TSrc*)AL_PixMapBuffer_GetPlaneAddress(pSrc, ePlaneType);
  auto pDstData = (TDst*)AL_PixMapBuffer_GetPlaneAddress(pDst, ePlaneType);

  for(int iH = 0; iH < iHeight; iH++)
  {
    for(int iW = 0; iW < iWidth; iW++)
      pDstData[iW] = (*CONV_FUNC)(pSrcData[iW]);

    pSrcData += iPitchSrc;
    pDstData += iPitchDst;
  }
}

/****************************************************************************/
template<typename T>
void SetPixMapPlane(AL_TBuffer* pDst, AL_EPlaneId ePlaneType, int iWidth, int iHeight, T uVal)
{
  int iPitchDst = AL_PixMapBuffer_GetPlanePitch(pDst, ePlaneType) / sizeof(T);
  auto pDstData = (T*)AL_PixMapBuffer_GetPlaneAddress(pDst, ePlaneType);

  for(int iH = 0; iH < iHeight; iH++)
  {
    for(int iW = 0; iW < iWidth; iW++)
      *pDstData++ = uVal;

    pDstData += iPitchDst - iWidth;
  }
}

/****************************************************************************/
void I420_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  CopyPixMapBuffer(pSrc, pDst);
}

/****************************************************************************/
void I420_To_YV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  CopyPixMapBuffer(pSrc, pDst);
}

/****************************************************************************/
void I420_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  AL_PixMapBuffer_SetDimension(pDst, tDim);

  CopyPixMapPlane(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, 8);
}

/****************************************************************************/
void I420_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  AL_PixMapBuffer_SetDimension(pDst, tDim);

  ConvertPixMapPlane<uint8_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, CONV_8B_TO_10B);
}

/****************************************************************************/
void I420_To_Y012(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  AL_PixMapBuffer_SetDimension(pDst, tDim);

  ConvertPixMapPlane<uint8_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, CONV_8B_TO_12B);
}

/****************************************************************************/
static void I4XX_To_IXAL(AL_TBuffer const* pSrc, AL_TBuffer* pDst, int iHScale, int iVScale)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  AL_PixMapBuffer_SetDimension(pDst, tDim);

  // Luma
  ConvertPixMapPlane<uint8_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, CONV_8B_TO_10B);

  // Chroma
  int iWidthChroma = (tDim.iWidth + iHScale - 1) / iHScale;
  int iHeightChroma = (tDim.iHeight + iVScale - 1) / iVScale;
  ConvertPixMapPlane<uint8_t, uint16_t>(pSrc, pDst, AL_PLANE_U, iWidthChroma, iHeightChroma, CONV_8B_TO_10B);
  ConvertPixMapPlane<uint8_t, uint16_t>(pSrc, pDst, AL_PLANE_V, iWidthChroma, iHeightChroma, CONV_8B_TO_10B);
}

/****************************************************************************/
void I420_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I4XX_To_IXAL(pSrc, pDst, 2, 2);
}

/****************************************************************************/
void I444_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I4XX_To_IXAL(pSrc, pDst, 1, 1);
}

/****************************************************************************/
void IYUV_To_420(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  CopyPixMapBuffer(pSrc, pDst);
}

/****************************************************************************/
void IYUV_To_YV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I420_To_YV12(pSrc, pDst);
}

/****************************************************************************/
void IYUV_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I420_To_Y800(pSrc, pDst);
}

/****************************************************************************/
void IYUV_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I420_To_I0AL(pSrc, pDst);
}

/****************************************************************************/
void YV12_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  CopyPixMapBuffer(pSrc, pDst);
}

/****************************************************************************/
void YV12_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  CopyPixMapBuffer(pSrc, pDst);
}

/****************************************************************************/
void YV12_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I420_To_Y800(pSrc, pDst);
}

/****************************************************************************/
void YV12_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I420_To_I0AL(pSrc, pDst);
}

/****************************************************************************/
void NV12_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  AL_PixMapBuffer_SetDimension(pDst, tDim);

  CopyPixMapPlane(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, 8);
}

/****************************************************************************/
void Y800_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  AL_PixMapBuffer_SetDimension(pDst, tDim);

  CopyPixMapPlane(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, 8);

  int iWidthChroma = (tDim.iWidth + 1) >> 1;
  int iHeightChroma = (tDim.iHeight + 1) >> 1;
  SetPixMapPlane<uint8_t>(pDst, AL_PLANE_U, iWidthChroma, iHeightChroma, 0x80);
  SetPixMapPlane<uint8_t>(pDst, AL_PLANE_V, iWidthChroma, iHeightChroma, 0x80);
}

/****************************************************************************/
void Y800_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  Y800_To_I420(pSrc, pDst);
}

/****************************************************************************/
void Y800_To_YV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  Y800_To_I420(pSrc, pDst);
}

/****************************************************************************/
void Y800_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  AL_PixMapBuffer_SetDimension(pDst, tDim);

  CopyPixMapPlane(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, 8);

  int iWidthChroma = ((tDim.iWidth + 1) >> 1) << 1;
  int iHeightChroma = (tDim.iHeight + 1) >> 1;
  SetPixMapPlane<uint8_t>(pDst, AL_PLANE_UV, iWidthChroma, iHeightChroma, 0x80);
}

/****************************************************************************/
void Y800_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  AL_PixMapBuffer_SetDimension(pDst, tDim);

  ConvertPixMapPlane<uint8_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, CONV_8B_TO_10B);

  int iWidthChroma = ((tDim.iWidth + 1) >> 1) << 1;
  int iHeightChroma = (tDim.iHeight + 1) >> 1;
  SetPixMapPlane<uint16_t>(pDst, AL_PLANE_UV, iWidthChroma, iHeightChroma, 0x0200);
}

/****************************************************************************/
void Y800_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  AL_PixMapBuffer_SetDimension(pDst, tDim);

  ConvertPixMapPlane<uint8_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, CONV_8B_TO_10B);

  int iWidthChroma = (tDim.iWidth + 1) >> 1;
  int iHeightChroma = (tDim.iHeight + 1) >> 1;
  SetPixMapPlane<uint16_t>(pDst, AL_PLANE_U, iWidthChroma, iHeightChroma >> 1, 0x0200);
  SetPixMapPlane<uint16_t>(pDst, AL_PLANE_V, iWidthChroma, iHeightChroma >> 1, 0x0200);
}

/****************************************************************************/
void Y800_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  AL_PixMapBuffer_SetDimension(pDst, tDim);

  ConvertPixMapPlane<uint8_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, CONV_8B_TO_10B);
}

/****************************************************************************/
static void SemiPlanarToPlanar_1XTo8b(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uHrzCScale, uint8_t uVrtCScale, uint8_t (* RND_FUNC)(uint16_t))
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  // Luma
  ConvertPixMapPlane<uint16_t, uint8_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_FUNC);

  // Chroma
  {
    uint32_t uPitchSrc = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_UV) / sizeof(uint16_t);
    uint32_t uPitchDstU = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_U);
    uint32_t uPitchDstV = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_V);

    int iWidth = (tDim.iWidth + uHrzCScale - 1) / uHrzCScale;
    int iHeight = (tDim.iHeight + uVrtCScale - 1) / uVrtCScale;

    auto pBufInC = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_UV);
    auto pBufOutU = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_U);
    auto pBufOutV = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_V);

    for(int iH = 0; iH < iHeight; ++iH)
    {
      for(int iW = 0; iW < iWidth; ++iW)
      {
        pBufOutU[iW] = RND_FUNC(pBufInC[iW << 1]);
        pBufOutV[iW] = RND_FUNC(pBufInC[(iW << 1) + 1]);
      }

      pBufInC += uPitchSrc;
      pBufOutU += uPitchDstU;
      pBufOutV += uPitchDstV;
    }
  }
}

/****************************************************************************/
static void SemiPlanarToPlanar_1XTo1X(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uHrzCScale, uint8_t uVrtCScale, uint16_t (* RND_FUNC)(uint16_t))
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  // Luma
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_FUNC);

  // Chroma
  {
    uint32_t uPitchSrc = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_UV) / sizeof(uint16_t);
    uint32_t uPitchDstU = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_U) / sizeof(uint16_t);
    uint32_t uPitchDstV = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_V) / sizeof(uint16_t);

    int iWidth = (tDim.iWidth + uHrzCScale - 1) / uHrzCScale;
    int iHeight = (tDim.iHeight + uVrtCScale - 1) / uVrtCScale;

    auto pBufInC = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_UV);
    auto pBufOutU = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_U);
    auto pBufOutV = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_V);

    for(int iH = 0; iH < iHeight; ++iH)
    {
      for(int iW = 0; iW < iWidth; ++iW)
      {
        pBufOutU[iW] = RND_FUNC(pBufInC[iW << 1]);
        pBufOutV[iW] = RND_FUNC(pBufInC[(iW << 1) + 1]);
      }

      pBufInC += uPitchSrc;
      pBufOutU += uPitchDstU;
      pBufOutV += uPitchDstV;
    }
  }
}

/****************************************************************************/
static void PX1X_To_NVXX(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uHrzCScale, uint8_t uVrtCScale, uint8_t (* RND_FUNC)(uint16_t))
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  AL_PixMapBuffer_SetDimension(pDst, tDim);

  ConvertPixMapPlane<uint16_t, uint8_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_FUNC);

  int iChromaWidth = ((tDim.iWidth + uHrzCScale - 1) / uHrzCScale) * uHrzCScale;
  int iChromaHeight = (tDim.iHeight + uVrtCScale - 1) / uVrtCScale;
  ConvertPixMapPlane<uint16_t, uint8_t>(pSrc, pDst, AL_PLANE_UV, iChromaWidth, iChromaHeight, RND_FUNC);
}

/****************************************************************************/
static void PX1X_To_PX1X(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uHrzCScale, uint8_t uVrtCScale, uint16_t (* RND_FUNC)(uint16_t))
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_FUNC);

  int iChromaWidth = ((tDim.iWidth + uHrzCScale - 1) / uHrzCScale) * uHrzCScale;
  int iChromaHeight = (tDim.iHeight + uVrtCScale - 1) / uVrtCScale;
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_UV, iChromaWidth, iChromaHeight, RND_FUNC);
}

/****************************************************************************/
static void IXYL_To_I4XX(AL_TBuffer const* pSrc, AL_TBuffer* pDst, int iHScale, int iVScale, uint8_t (* RND_FUNC)(uint16_t))
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  AL_PixMapBuffer_SetDimension(pDst, tDim);

  // Luma
  ConvertPixMapPlane<uint16_t, uint8_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_FUNC);

  // Chroma
  int iChromaWidth = (tDim.iWidth + iHScale - 1) / iHScale;
  int iChromaHeight = (tDim.iHeight + iVScale - 1) / iVScale;
  ConvertPixMapPlane<uint16_t, uint8_t>(pSrc, pDst, AL_PLANE_U, iChromaWidth, iChromaHeight, RND_FUNC);
  ConvertPixMapPlane<uint16_t, uint8_t>(pSrc, pDst, AL_PLANE_V, iChromaWidth, iChromaHeight, RND_FUNC);
}

/****************************************************************************/
static void IXYL_To_IXYL(AL_TBuffer const* pSrc, AL_TBuffer* pDst, int iHScale, int iVScale, uint16_t (* RND_FUNC)(uint16_t))
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  AL_PixMapBuffer_SetDimension(pDst, tDim);

  // Luma
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_FUNC);

  // Chroma
  const int iChromaWidth = (tDim.iWidth + iHScale - 1) / iHScale;
  const int iChromaHeight = (tDim.iHeight + iVScale - 1) / iVScale;
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_U, iChromaWidth, iChromaHeight, RND_FUNC);
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_V, iChromaWidth, iChromaHeight, RND_FUNC);
}

/****************************************************************************/
void P010_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo8b(pSrc, pDst, 2, 2, RND_10B_TO_8B);
}

/****************************************************************************/
void P210_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo8b(pSrc, pDst, 2, 1, RND_10B_TO_8B);
}

/****************************************************************************/
void P210_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo8b(pSrc, pDst, 1, 1, RND_10B_TO_8B);
}

/****************************************************************************/
void P010_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  P010_To_I420(pSrc, pDst);
}

/****************************************************************************/
void P010_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo1X(pSrc, pDst, 2, 2, COPY);
}

/****************************************************************************/
void P210_To_I2AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo1X(pSrc, pDst, 2, 1, COPY);
}

/****************************************************************************/
void P012_To_I0CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo1X(pSrc, pDst, 2, 2, COPY);
}

/****************************************************************************/
void P212_To_I2CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo1X(pSrc, pDst, 2, 1, COPY);
}

/****************************************************************************/
void P012_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo8b(pSrc, pDst, 2, 2, RND_12B_TO_8B);
}

/****************************************************************************/
void P212_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo8b(pSrc, pDst, 2, 1, RND_12B_TO_8B);
}

/****************************************************************************/
void P010_To_YV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  P010_To_I420(pSrc, pDst);
}

/****************************************************************************/
void P010_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  PX1X_To_NVXX(pSrc, pDst, 2, 2, RND_10B_TO_8B);
}

/****************************************************************************/
void P010_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I0AL_To_Y800(pSrc, pDst);
}

/****************************************************************************/
static void IXAL_To_I4XX(AL_TBuffer const* pSrc, AL_TBuffer* pDst, int iHScale, int iVScale)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  AL_PixMapBuffer_SetDimension(pDst, tDim);

  // Luma
  I0AL_To_Y800(pSrc, pDst);

  // Chroma
  int iChromaWidth = (tDim.iWidth + iHScale - 1) / iHScale;
  int iChromaHeight = (tDim.iHeight + iVScale - 1) / iVScale;
  ConvertPixMapPlane<uint16_t, uint8_t>(pSrc, pDst, AL_PLANE_U, iChromaWidth, iChromaHeight, RND_10B_TO_8B);
  ConvertPixMapPlane<uint16_t, uint8_t>(pSrc, pDst, AL_PLANE_V, iChromaWidth, iChromaHeight, RND_10B_TO_8B);
}

/****************************************************************************/
void I0AL_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXAL_To_I4XX(pSrc, pDst, 2, 2);
}

/****************************************************************************/
void I4AL_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXAL_To_I4XX(pSrc, pDst, 1, 1);
}

/****************************************************************************/
void I0AL_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I0AL_To_I420(pSrc, pDst);
}

/****************************************************************************/
void I0AL_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  AL_PixMapBuffer_SetDimension(pDst, tDim);
  ConvertPixMapPlane<uint16_t, uint8_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_10B_TO_8B);
}

/****************************************************************************/
void I0CL_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  AL_PixMapBuffer_SetDimension(pDst, tDim);
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_12B_TO_10B);
}

/****************************************************************************/
void I0CL_To_Y012(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  AL_PixMapBuffer_SetDimension(pDst, tDim);
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, COPY);
}

/****************************************************************************/
static void I0XL_To_Y01X(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint16_t (* RND_FUNC)(uint16_t))
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  AL_PixMapBuffer_SetDimension(pDst, tDim);

  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_FUNC);
}

/****************************************************************************/
void P010_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I0XL_To_Y01X(pSrc, pDst, COPY);
}

/****************************************************************************/
void P012_To_Y012(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I0XL_To_Y01X(pSrc, pDst, COPY);
}

/****************************************************************************/
void I0AL_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I0XL_To_Y01X(pSrc, pDst, COPY);
}

/****************************************************************************/
static void I4XX_To_NVXX(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uHrzCScale, uint8_t uVrtCScale)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  AL_PixMapBuffer_SetDimension(pDst, tDim);

  // Luma
  CopyPixMapPlane(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, 8);

  // Chroma
  const int iPitchSrcU = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_U);
  const int iPitchSrcV = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_V);
  const int iPitchDst = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_UV);
  AL_VADDR pBufInU = AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_U);
  AL_VADDR pBufInV = AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_V);
  AL_VADDR pBufOut = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_UV);

  int iWidthC = (tDim.iWidth + uHrzCScale - 1) / uHrzCScale;
  int iHeightC = (tDim.iHeight + uVrtCScale - 1) / uVrtCScale;

  for(int iH = 0; iH < iHeightC; ++iH)
  {
    for(int iW = 0; iW < iWidthC; ++iW)
    {
      pBufOut[iW * 2] = pBufInU[iW];
      pBufOut[iW * 2 + 1] = pBufInV[iW];
    }

    pBufOut += iPitchDst;
    pBufInU += iPitchSrcU;
    pBufInV += iPitchSrcV;
  }
}

/****************************************************************************/
void YV12_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I420_To_NV12(pSrc, pDst);
}

/****************************************************************************/
void I420_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I4XX_To_NVXX(pSrc, pDst, 2, 2);
}

/****************************************************************************/
void IYUV_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I4XX_To_NVXX(pSrc, pDst, 2, 2);
}

/****************************************************************************/
void I422_To_NV16(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I4XX_To_NVXX(pSrc, pDst, 2, 1);
}

/****************************************************************************/
void I444_To_NV24(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I4XX_To_NVXX(pSrc, pDst, 1, 1);
}

/****************************************************************************/
static void I4XX_To_PX10(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uHrzCScale, uint8_t uVrtCScale)
{
  // Luma
  I420_To_Y010(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  int iPitchSrcU = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_U);
  int iPitchSrcV = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_V);
  int iPitchDst = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_UV) / sizeof(uint16_t);

  int iWidthC = (tDim.iWidth + uHrzCScale - 1) / uHrzCScale;
  int iHeightC = (tDim.iHeight + uVrtCScale - 1) / uVrtCScale;

  auto pBufInU = AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_U);
  auto pBufInV = AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_V);
  auto pBufOut = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_UV);

  for(int iH = 0; iH < iHeightC; ++iH)
  {
    for(int iW = 0; iW < iWidthC; ++iW)
    {
      *pBufOut++ = ((uint16_t)*pBufInU++) << 2;
      *pBufOut++ = ((uint16_t)*pBufInV++) << 2;
    }

    pBufInU += iPitchSrcU - iWidthC;
    pBufInV += iPitchSrcV - iWidthC;
    pBufOut += iPitchDst - (2 * iWidthC);
  }
}

/****************************************************************************/
static void I4XX_To_PX12(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uHrzCScale, uint8_t uVrtCScale)
{
  // Luma
  I420_To_Y012(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  int iPitchSrcU = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_U);
  int iPitchSrcV = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_V);
  int iPitchDst = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_UV) / sizeof(uint16_t);

  int iWidthC = (tDim.iWidth + uHrzCScale - 1) / uHrzCScale;
  int iHeightC = (tDim.iHeight + uVrtCScale - 1) / uVrtCScale;

  auto pBufInU = AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_U);
  auto pBufInV = AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_V);
  auto pBufOut = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_UV);

  for(int iH = 0; iH < iHeightC; ++iH)
  {
    for(int iW = 0; iW < iWidthC; ++iW)
    {
      *pBufOut++ = ((uint16_t)*pBufInU++) << 4;
      *pBufOut++ = ((uint16_t)*pBufInV++) << 4;
    }

    pBufInU += iPitchSrcU - iWidthC;
    pBufInV += iPitchSrcV - iWidthC;
    pBufOut += iPitchDst - (2 * iWidthC);
  }
}

/****************************************************************************/
void YV12_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I420_To_P010(pSrc, pDst);
}

/****************************************************************************/
void I420_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I4XX_To_PX10(pSrc, pDst, 2, 2);
}

/****************************************************************************/
void IYUV_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I4XX_To_PX10(pSrc, pDst, 2, 2);
}

/****************************************************************************/
void I422_To_P210(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I4XX_To_PX10(pSrc, pDst, 2, 1);
}

/****************************************************************************/
void I444_To_P410(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I4XX_To_PX10(pSrc, pDst, 1, 1);
}

/****************************************************************************/
void I420_To_P012(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I4XX_To_PX12(pSrc, pDst, 2, 2);
}

/****************************************************************************/
void I422_To_P212(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I4XX_To_PX12(pSrc, pDst, 2, 1);
}

/****************************************************************************/
void I444_To_P412(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I4XX_To_PX12(pSrc, pDst, 1, 1);
}

/****************************************************************************/
void Y012_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_12B_TO_10B);
}

/****************************************************************************/
void Y012_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  ConvertPixMapPlane<uint16_t, uint8_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_12B_TO_8B);
}

/****************************************************************************/
void P012_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo1X(pSrc, pDst, 2, 2, RND_12B_TO_10B);
}

/****************************************************************************/
void P212_To_I2AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo1X(pSrc, pDst, 2, 1, RND_12B_TO_10B);
}

/****************************************************************************/
void I4CL_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXYL_To_IXYL(pSrc, pDst, 1, 1, RND_12B_TO_10B);
}

/****************************************************************************/
void I4CL_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXYL_To_I4XX(pSrc, pDst, 1, 1, RND_12B_TO_8B);
}

/****************************************************************************/
static void IXAL_To_NVXX(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uHrzCScale, uint8_t uVrtCScale)
{
  // luma
  I0AL_To_Y800(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  int iHeightC = (tDim.iHeight + uVrtCScale - 1) / uVrtCScale;
  int iWidthC = (tDim.iWidth + uHrzCScale - 1) / uHrzCScale;
  uint32_t uPitchSrcU = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_U) / sizeof(uint16_t);
  uint32_t uPitchSrcV = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_V) / sizeof(uint16_t);
  uint32_t uPitchDst = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_UV);

  auto pBufInU = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_U);
  auto pBufInV = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_V);
  auto pBufOut = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_UV);

  for(int iH = 0; iH < iHeightC; ++iH)
  {
    for(int iW = 0; iW < iWidthC; ++iW)
    {
      *pBufOut++ = RND_10B_TO_8B(*pBufInU++);
      *pBufOut++ = RND_10B_TO_8B(*pBufInV++);
    }

    pBufOut += uPitchDst - tDim.iWidth;
    pBufInU += uPitchSrcU - iWidthC;
    pBufInV += uPitchSrcV - iWidthC;
  }
}

/****************************************************************************/
void I0AL_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXAL_To_NVXX(pSrc, pDst, 2, 2);
}

/****************************************************************************/
void I2AL_To_NV16(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXAL_To_NVXX(pSrc, pDst, 2, 1);
}

/****************************************************************************/
void I4AL_To_NV24(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXAL_To_NVXX(pSrc, pDst, 1, 1);
}

/****************************************************************************/
static void IXYL_To_PX1Y(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uHrzCScale, uint8_t uVrtCScale, uint16_t (* RND_FUNC)(uint16_t))
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  AL_PixMapBuffer_SetDimension(pDst, tDim);

  // Luma
  I0XL_To_Y01X(pSrc, pDst, RND_FUNC);

  // Chroma
  int iHeightC = (tDim.iHeight + uVrtCScale - 1) / uVrtCScale;
  int iWidthC = (tDim.iWidth + uHrzCScale - 1) / uHrzCScale;
  uint32_t uPitchSrcU = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_U) / sizeof(uint16_t);
  uint32_t uPitchSrcV = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_V) / sizeof(uint16_t);
  uint32_t uPitchDst = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_UV) / sizeof(uint16_t);

  auto pBufInU = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_U);
  auto pBufInV = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_V);
  auto pBufOut = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_UV);

  for(int iH = 0; iH < iHeightC; ++iH)
  {
    for(int iW = 0; iW < iWidthC; ++iW)
    {
      pBufOut[2 * iW] = RND_FUNC(pBufInU[iW]);
      pBufOut[2 * iW + 1] = RND_FUNC(pBufInV[iW]);
    }

    pBufInU += uPitchSrcU;
    pBufInV += uPitchSrcV;
    pBufOut += uPitchDst;
  }
}

/****************************************************************************/
void I0AL_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXYL_To_PX1Y(pSrc, pDst, 2, 2, COPY);
}

/****************************************************************************/
void I2AL_To_P210(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXYL_To_PX1Y(pSrc, pDst, 2, 1, COPY);
}

/****************************************************************************/
void I4AL_To_P410(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXYL_To_PX1Y(pSrc, pDst, 1, 1, COPY);
}

/****************************************************************************/
void I0CL_To_P012(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXYL_To_PX1Y(pSrc, pDst, 2, 2, COPY);
}

/****************************************************************************/
void I2CL_To_P212(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXYL_To_PX1Y(pSrc, pDst, 2, 1, COPY);
}

/****************************************************************************/
void I4CL_To_P412(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXYL_To_PX1Y(pSrc, pDst, 1, 1, COPY);
}

static void ALX8_To_I4XX(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uHrzCScale, uint8_t uVrtCScale)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  const int iTileW = 64;
  const int iTileH = 4;

  uint32_t uPitchSrc = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_UV);
  uint8_t* pSrcData = AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_UV);

  uint32_t uPitchDstU = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_U);
  uint32_t uPitchDstV = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_V);
  uint8_t* pDstDataU = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_U);
  uint8_t* pDstDataV = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_V);

  int iWidthC = (tDim.iWidth + uHrzCScale - 1) / uHrzCScale * 2;
  int iHeightC = (tDim.iHeight + uVrtCScale - 1) / uVrtCScale;

  for(int H = 0; H < iHeightC; H += iTileH)
  {
    uint8_t* pInC = pSrcData + (H / iTileH) * uPitchSrc;

    int iCropH = (H + iTileH) - iHeightC;

    if(iCropH < 4)
      iCropH = 0;

    for(int W = 0; W < iWidthC; W += iTileW)
    {
      int iCropW = (W + iTileW) - iWidthC;

      if(iCropW < 8 / uHrzCScale)
        iCropW = 0;

      for(int h = 0; h < iTileH - iCropH; h += 4)
      {
        for(int w = 0; w < iTileW - iCropW; w += 4)
        {
          uint8_t* pOutU = pDstDataU + (H + h) * uPitchDstU + (W + w) / uHrzCScale;
          uint8_t* pOutV = pDstDataV + (H + h) * uPitchDstV + (W + w) / uHrzCScale;

          for(int p = 0; p < (8 / uHrzCScale); p++)
            ((p % 2 == 0) ? pOutU[(p % (8 / uHrzCScale)) / 2] : pOutV[(p % (8 / uHrzCScale)) / 2]) = pInC[p];

          pOutU += uPitchDstU;
          pOutV += uPitchDstV;

          for(int p = (1 * (8 / uHrzCScale)); p < (1 * (8 / uHrzCScale)) + (8 / uHrzCScale); p++)
            ((p % 2 == 0) ? pOutU[(p % (8 / uHrzCScale)) / 2] : pOutV[(p % (8 / uHrzCScale)) / 2]) = pInC[p];

          if(H + h + 3 <= iHeightC)
          {
            pOutU += uPitchDstU;
            pOutV += uPitchDstV;

            for(int p = (2 * (8 / uHrzCScale)); p < (2 * (8 / uHrzCScale)) + (8 / uHrzCScale); p++)
              ((p % 2 == 0) ? pOutU[(p % (8 / uHrzCScale)) / 2] : pOutV[(p % (8 / uHrzCScale)) / 2]) = pInC[p];
          }

          if(H + h + 4 <= iHeightC)
          {
            pOutU += uPitchDstU;
            pOutV += uPitchDstV;

            for(int p = (3 * (8 / uHrzCScale)); p < (3 * (8 / uHrzCScale)) + (8 / uHrzCScale); p++)
              ((p % 2 == 0) ? pOutU[(p % (8 / uHrzCScale)) / 2] : pOutV[(p % (8 / uHrzCScale)) / 2]) = pInC[p];
          }
          pInC += ((4 * 8) / uHrzCScale);
        }

        pInC += (8 / uHrzCScale) * iCropW;
      }

      pInC += iCropH * iTileW;
    }
  }
}

/****************************************************************************/
void T608_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T608_To_Y800(pSrc, pDst);

  // Chroma
  ALX8_To_I4XX(pSrc, pDst, 2, 2);
}

/****************************************************************************/
void T608_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T608_To_I420(pSrc, pDst);
}

/****************************************************************************/
void T608_To_YV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T608_To_Y800(pSrc, pDst);

  // Chroma
  ALX8_To_I4XX(pSrc, pDst, 2, 2);
}

/****************************************************************************/
template<typename TUntiled, typename FConvert>
static void Untile4x4Block8b(uint8_t* pTiled4x4, TUntiled* pUntiled, int iUntiledPitch, FConvert convert)
{
  pUntiled[0] = convert(pTiled4x4[0]);
  pUntiled[1] = convert(pTiled4x4[1]);
  pUntiled[2] = convert(pTiled4x4[2]);
  pUntiled[3] = convert(pTiled4x4[3]);
  pUntiled += iUntiledPitch;
  pUntiled[0] = convert(pTiled4x4[4]);
  pUntiled[1] = convert(pTiled4x4[5]);
  pUntiled[2] = convert(pTiled4x4[6]);
  pUntiled[3] = convert(pTiled4x4[7]);
  pUntiled += iUntiledPitch;
  pUntiled[0] = convert(pTiled4x4[8]);
  pUntiled[1] = convert(pTiled4x4[9]);
  pUntiled[2] = convert(pTiled4x4[10]);
  pUntiled[3] = convert(pTiled4x4[11]);
  pUntiled += iUntiledPitch;
  pUntiled[0] = convert(pTiled4x4[12]);
  pUntiled[1] = convert(pTiled4x4[13]);
  pUntiled[2] = convert(pTiled4x4[14]);
  pUntiled[3] = convert(pTiled4x4[15]);
}

/****************************************************************************/
static void Untile4x4Block8bTo8b(void* pTiled4x4, void* pUntiled, int iUntiledPitch)
{
  Untile4x4Block8b<uint8_t>((uint8_t*)pTiled4x4, (uint8_t*)pUntiled, iUntiledPitch, [](uint8_t u8) { return u8; });
}

/****************************************************************************/
static void Untile4x4Block8bTo10b(void* pTiled4x4, void* pUntiled, int iUntiledPitch)
{
  Untile4x4Block8b<uint16_t>((uint8_t*)pTiled4x4, (uint16_t*)pUntiled, iUntiledPitch, [](uint8_t u8) { return uint16_t(u8) << 2; });
}

/****************************************************************************/
static void Untile4x4Block8bTo12b(void* pTiled4x4, void* pUntiled, int iUntiledPitch)
{
  Untile4x4Block8b<uint16_t>((uint8_t*)pTiled4x4, (uint16_t*)pUntiled, iUntiledPitch, [](uint8_t u8) { return uint16_t(u8) << 4; });
}

/****************************************************************************/
template<typename TUntiled, typename FConvert>
static void Untile4x4Block10b(uint16_t* pTiled4x4, TUntiled* pUntiled, int iUntiledPitch, FConvert convert)
{
  pUntiled[0] = convert(pTiled4x4[0] & 0x3FF);
  pUntiled[1] = convert(((pTiled4x4[0] >> 10) | (pTiled4x4[1] << 6)) & 0x3FF);
  pUntiled[2] = convert((pTiled4x4[1] >> 4) & 0x3FF);
  pUntiled[3] = convert(((pTiled4x4[1] >> 14) | (pTiled4x4[2] << 2)) & 0x3FF);
  pUntiled += iUntiledPitch;
  pUntiled[0] = convert(((pTiled4x4[2] >> 8) | (pTiled4x4[3] << 8)) & 0x3FF);
  pUntiled[1] = convert((pTiled4x4[3] >> 2) & 0x3FF);
  pUntiled[2] = convert(((pTiled4x4[3] >> 12) | (pTiled4x4[4] << 4)) & 0x3FF);
  pUntiled[3] = convert(pTiled4x4[4] >> 6);
  pUntiled += iUntiledPitch;
  pUntiled[0] = convert(pTiled4x4[5] & 0x3FF);
  pUntiled[1] = convert(((pTiled4x4[5] >> 10) | (pTiled4x4[6] << 6)) & 0x3FF);
  pUntiled[2] = convert((pTiled4x4[6] >> 4) & 0x3FF);
  pUntiled[3] = convert(((pTiled4x4[6] >> 14) | (pTiled4x4[7] << 2)) & 0x3FF);
  pUntiled += iUntiledPitch;
  pUntiled[0] = convert(((pTiled4x4[7] >> 8) | (pTiled4x4[8] << 8)) & 0x3FF);
  pUntiled[1] = convert((pTiled4x4[8] >> 2) & 0x3FF);
  pUntiled[2] = convert(((pTiled4x4[8] >> 12) | (pTiled4x4[9] << 4)) & 0x3FF);
  pUntiled[3] = convert(pTiled4x4[9] >> 6);
}

/****************************************************************************/
template<typename TUntiled, typename FConvert>
static void Untile4x4Block12b(uint16_t* pTiled4x4, TUntiled* pUntiled, int iUntiledPitch, FConvert convert)
{
  for(int row = 0; row < 4; row++)
  {
    int off = row * 3;
    pUntiled[0] = convert(pTiled4x4[0 + off] & 0xFFF);
    pUntiled[1] = convert(((pTiled4x4[0 + off] >> 12) & 0xF) | ((pTiled4x4[1 + off] & 0xFF) << 4));
    pUntiled[2] = convert(((pTiled4x4[1 + off] >> 8) & 0xFF) | ((pTiled4x4[2 + off] & 0xF) << 8));
    pUntiled[3] = convert((pTiled4x4[2 + off] >> 4) & 0xFFF);
    pUntiled += iUntiledPitch;
  }
}

/****************************************************************************/
static void Untile4x4Block10bTo8b(void* pTiled4x4, void* pUntiled, int iUntiledPitch)
{
  Untile4x4Block10b<uint8_t>((uint16_t*)pTiled4x4, (uint8_t*)pUntiled, iUntiledPitch, RND_10B_TO_8B);
}

/****************************************************************************/
static void Untile4x4Block10bTo10b(void* pTiled4x4, void* pUntiled, int iUntiledPitch)
{
  Untile4x4Block10b<uint16_t>((uint16_t*)pTiled4x4, (uint16_t*)pUntiled, iUntiledPitch, [](uint16_t u16) { return u16; });
}

/****************************************************************************/
static void Untile4x4Block10bTo12b(void* pTiled4x4, void* pUntiled, int iUntiledPitch)
{
  Untile4x4Block10b<uint16_t>((uint16_t*)pTiled4x4, (uint16_t*)pUntiled, iUntiledPitch, [](uint16_t u16) { return u16 << 2; });
}

/****************************************************************************/
static void Untile4x4Block12bTo8b(void* pTiled4x4, void* pUntiled, int iUntiledPitch)
{
  Untile4x4Block12b<uint8_t>((uint16_t*)pTiled4x4, (uint8_t*)pUntiled, iUntiledPitch, RND_12B_TO_8B);
}

/****************************************************************************/
static void Untile4x4Block12bTo10b(void* pTiled4x4, void* pUntiled, int iUntiledPitch)
{
  Untile4x4Block12b<uint16_t>((uint16_t*)pTiled4x4, (uint16_t*)pUntiled, iUntiledPitch, RND_12B_TO_10B);
}

/****************************************************************************/
static void Untile4x4Block12bTo12b(void* pTiled4x4, void* pUntiled, int iUntiledPitch)
{
  Untile4x4Block12b<uint16_t>((uint16_t*)pTiled4x4, (uint16_t*)pUntiled, iUntiledPitch, [](uint16_t u16) { return u16; });
}

/****************************************************************************/
template<typename TUntiled, typename FConvert>
static void Untile4x4ChromaBlock12bToPlanar(uint16_t* pTiled4x4, TUntiled* pUntiledU, TUntiled* pUntiledV, int iPitchU, int iPitchV, FConvert convert)
{
  for(int row = 0; row < 4; row++)
  {
    int off = row * 3;
    pUntiledU[0] = convert(pTiled4x4[0 + off] & 0xFFF);
    pUntiledV[0] = convert(((pTiled4x4[0 + off] >> 12) & 0xF) | ((pTiled4x4[1 + off] & 0xFF) << 4));
    pUntiledU[1] = convert(((pTiled4x4[1 + off] >> 8) & 0xFF) | ((pTiled4x4[2 + off] & 0xF) << 8));
    pUntiledV[1] = convert((pTiled4x4[2 + off] >> 4) & 0xFFF);
    pUntiledU += iPitchU;
    pUntiledV += iPitchV;
  }
}

/****************************************************************************/
template<typename TUntiled, typename FConvert>
static void Untile4x4ChromaBlock10bToPlanar(uint16_t* pTiled4x4, TUntiled* pUntiledU, TUntiled* pUntiledV, int iPitchU, int iPitchV, FConvert convert)
{
  pUntiledU[0] = convert(pTiled4x4[0] & 0x3FF);
  pUntiledV[0] = convert(((pTiled4x4[0] >> 10) | (pTiled4x4[1] << 6)) & 0x3FF);
  pUntiledU[1] = convert((pTiled4x4[1] >> 4) & 0x3FF);
  pUntiledV[1] = convert(((pTiled4x4[1] >> 14) | (pTiled4x4[2] << 2)) & 0x3FF);
  pUntiledU += iPitchU;
  pUntiledV += iPitchV;
  pUntiledU[0] = convert(((pTiled4x4[2] >> 8) | (pTiled4x4[3] << 8)) & 0x3FF);
  pUntiledV[0] = convert((pTiled4x4[3] >> 2) & 0x3FF);
  pUntiledU[1] = convert(((pTiled4x4[3] >> 12) | (pTiled4x4[4] << 4)) & 0x3FF);
  pUntiledV[1] = convert(pTiled4x4[4] >> 6);
  pUntiledU += iPitchU;
  pUntiledV += iPitchV;
  pUntiledU[0] = convert(pTiled4x4[5] & 0x3FF);
  pUntiledV[0] = convert(((pTiled4x4[5] >> 10) | (pTiled4x4[6] << 6)) & 0x3FF);
  pUntiledU[1] = convert((pTiled4x4[6] >> 4) & 0x3FF);
  pUntiledV[1] = convert(((pTiled4x4[6] >> 14) | (pTiled4x4[7] << 2)) & 0x3FF);
  pUntiledU += iPitchU;
  pUntiledV += iPitchV;
  pUntiledU[0] = convert(((pTiled4x4[7] >> 8) | (pTiled4x4[8] << 8)) & 0x3FF);
  pUntiledV[0] = convert((pTiled4x4[8] >> 2) & 0x3FF);
  pUntiledU[1] = convert(((pTiled4x4[8] >> 12) | (pTiled4x4[9] << 4)) & 0x3FF);
  pUntiledV[1] = convert(pTiled4x4[9] >> 6);
}

/****************************************************************************/
static void Untile4x4ChromaBlock10bToPlanar8b(uint16_t* pTiled4x4, uint8_t* pUntiledU, uint8_t* pUntiledV, int iPitchU, int iPitchV)
{
  Untile4x4ChromaBlock10bToPlanar<uint8_t>(pTiled4x4, pUntiledU, pUntiledV, iPitchU, iPitchV, RND_10B_TO_8B);
}

/****************************************************************************/
static void Untile4x4ChromaBlock10bToPlanar10b(uint16_t* pTiled4x4, uint16_t* pUntiledU, uint16_t* pUntiledV, int iPitchU, int iPitchV)
{
  Untile4x4ChromaBlock10bToPlanar<uint16_t>(pTiled4x4, pUntiledU, pUntiledV, iPitchU, iPitchV, [](uint16_t u16) { return u16; });
}

/****************************************************************************/
static void Untile4x4ChromaBlock12bToPlanar8b(uint16_t* pTiled4x4, uint8_t* pUntiledU, uint8_t* pUntiledV, int iPitchU, int iPitchV)
{
  Untile4x4ChromaBlock12bToPlanar<uint8_t>(pTiled4x4, pUntiledU, pUntiledV, iPitchU, iPitchV, RND_12B_TO_8B);
}

/****************************************************************************/
static void Untile4x4ChromaBlock12bToPlanar10b(uint16_t* pTiled4x4, uint16_t* pUntiledU, uint16_t* pUntiledV, int iPitchU, int iPitchV)
{
  Untile4x4ChromaBlock12bToPlanar<uint16_t>(pTiled4x4, pUntiledU, pUntiledV, iPitchU, iPitchV, RND_12B_TO_10B);
}

/****************************************************************************/
static void Untile4x4ChromaBlock12bToPlanar12b(uint16_t* pTiled4x4, uint16_t* pUntiledU, uint16_t* pUntiledV, int iPitchU, int iPitchV)
{
  Untile4x4ChromaBlock12bToPlanar<uint16_t>(pTiled4x4, pUntiledU, pUntiledV, iPitchU, iPitchV, [](uint16_t u16) { return u16; });
}

/****************************************************************************/
template<typename SrcType, typename DstType>
static void T64_Untile_Plane(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t bdIn, uint8_t bdOut, AL_EPlaneId ePlaneId, AL_TDimension tPlaneDim)
{
  const int iTileW = 64;
  const int iTileH = 4;

  void (* Untile4x4Block) (void*, void*, int);

  if(bdIn == 12)
  {
    if(bdOut == 12)
      Untile4x4Block = Untile4x4Block12bTo12b;
    else if(bdOut == 10)
      Untile4x4Block = Untile4x4Block12bTo10b;
    else
      Untile4x4Block = Untile4x4Block12bTo8b;
  }
  else if(bdIn == 10)
  {
    if(bdOut == 12)
      Untile4x4Block = Untile4x4Block10bTo12b;
    else if(bdOut == 10)
      Untile4x4Block = Untile4x4Block10bTo10b;
    else
      Untile4x4Block = Untile4x4Block10bTo8b;
  }
  else
  {
    if(bdOut == 12)
      Untile4x4Block = Untile4x4Block8bTo12b;
    else if(bdOut == 10)
      Untile4x4Block = Untile4x4Block8bTo10b;
    else
      Untile4x4Block = Untile4x4Block8bTo8b;
  }

  auto pSrcData = (SrcType*)AL_PixMapBuffer_GetPlaneAddress(pSrc, ePlaneId);
  auto pDstData = (DstType*)AL_PixMapBuffer_GetPlaneAddress(pDst, ePlaneId);
  int iPitchSrc = AL_PixMapBuffer_GetPlanePitch(pSrc, ePlaneId) / sizeof(SrcType);
  int iPitchDst = AL_PixMapBuffer_GetPlanePitch(pDst, ePlaneId) / sizeof(DstType);

  /* Src increment = (16 * bdIn) / (8 * sizeof(SrcType)) */
  const int iSrcIncr4x4 = (bdIn << 1) / sizeof(SrcType);

  for(int H = 0; H < tPlaneDim.iHeight; H += iTileH)
  {
    SrcType* pIn = pSrcData + (H / iTileH) * iPitchSrc;

    int iCropH = (H + iTileH) - tPlaneDim.iHeight;

    if(iCropH < 0)
      iCropH = 0;

    for(int W = 0; W < tPlaneDim.iWidth; W += iTileW)
    {
      int iCropW = (W + iTileW) - tPlaneDim.iWidth;

      if(iCropW < 0)
        iCropW = 0;

      for(int h = 0; h < iTileH - iCropH; h += 4)
      {
        for(int w = 0; w < iTileW - iCropW; w += 4)
        {
          DstType* pOut = pDstData + (H + h) * iPitchDst + (W + w);
          Untile4x4Block(pIn, pOut, iPitchDst);
          pIn += iSrcIncr4x4;
        }

        pIn += iSrcIncr4x4 * (iCropW >> 2);
      }

      pIn += iSrcIncr4x4 * (iTileW >> 2) * (iCropH >> 2);
    }
  }
}

/****************************************************************************/
void T608_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  T64_Untile_Plane<uint8_t, uint8_t>(pSrc, pDst, 8, 8, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void T608_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T608_To_Y800(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  tDim.iHeight = (tDim.iHeight + 1) >> 1;
  T64_Untile_Plane<uint8_t, uint8_t>(pSrc, pDst, 8, 8, AL_PLANE_UV, tDim);
}

/****************************************************************************/
void T608_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  T64_Untile_Plane<uint8_t, uint16_t>(pSrc, pDst, 8, 10, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void T608_To_Y012(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  T64_Untile_Plane<uint8_t, uint16_t>(pSrc, pDst, 8, 12, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void T608_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T608_To_Y010(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  tDim.iHeight = (tDim.iHeight + 1) >> 1;
  T64_Untile_Plane<uint8_t, uint16_t>(pSrc, pDst, 8, 10, AL_PLANE_UV, tDim);
}

/****************************************************************************/
void T608_To_P012(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T608_To_Y012(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  tDim.iHeight = (tDim.iHeight + 1) >> 1;
  T64_Untile_Plane<uint8_t, uint16_t>(pSrc, pDst, 8, 12, AL_PLANE_UV, tDim);
}

/****************************************************************************/
static void Chroma_T608_To_I0XL(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uBitDepth)
{
  if(uBitDepth != 10 && uBitDepth != 12)
    throw std::runtime_error("uBitDepth(" + std::to_string(uBitDepth) + ") must be equal to 10 or 12");

  int iPitchSrc = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_UV);
  int iPitchDstU = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_U) / sizeof(uint16_t);
  int iPitchDstV = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_V) / sizeof(uint16_t);

  auto pSrcData = AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_UV);
  auto pDstDataU = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_U);
  auto pDstDataV = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_V);

  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  tDim.iHeight = (tDim.iHeight + 1) >> 1;

  const int iTileW = 64;
  const int iTileH = 4;

  int iShift = uBitDepth == 10 ? 2 : 4;

  for(int H = 0; H < tDim.iHeight; H += iTileH)
  {
    uint8_t* pInC = pSrcData + (H / iTileH) * iPitchSrc;

    int iCropH = (H + iTileH) - tDim.iHeight;

    if(iCropH < 0)
      iCropH = 0;

    for(int W = 0; W < tDim.iWidth; W += iTileW)
    {
      int iCropW = (W + iTileW) - tDim.iWidth;

      if(iCropW < 0)
        iCropW = 0;

      for(int h = 0; h < iTileH - iCropH; h += 4)
      {
        for(int w = 0; w < iTileW - iCropW; w += 4)
        {
          uint16_t* pOutU = pDstDataU + (H + h) * iPitchDstU + (W + w) / 2;
          uint16_t* pOutV = pDstDataV + (H + h) * iPitchDstV + (W + w) / 2;

          pOutU[0] = ((uint16_t)pInC[0]) << iShift;
          pOutV[0] = ((uint16_t)pInC[1]) << iShift;
          pOutU[1] = ((uint16_t)pInC[2]) << iShift;
          pOutV[1] = ((uint16_t)pInC[3]) << iShift;
          pOutU += iPitchDstU;
          pOutV += iPitchDstV;
          pOutU[0] = ((uint16_t)pInC[4]) << iShift;
          pOutV[0] = ((uint16_t)pInC[5]) << iShift;
          pOutU[1] = ((uint16_t)pInC[6]) << iShift;
          pOutV[1] = ((uint16_t)pInC[7]) << iShift;
          pOutU += iPitchDstU;
          pOutV += iPitchDstV;
          pOutU[0] = ((uint16_t)pInC[8]) << iShift;
          pOutV[0] = ((uint16_t)pInC[9]) << iShift;
          pOutU[1] = ((uint16_t)pInC[10]) << iShift;
          pOutV[1] = ((uint16_t)pInC[11]) << iShift;
          pOutU += iPitchDstU;
          pOutV += iPitchDstV;
          pOutU[0] = ((uint16_t)pInC[12]) << iShift;
          pOutV[0] = ((uint16_t)pInC[13]) << iShift;
          pOutU[1] = ((uint16_t)pInC[14]) << iShift;
          pOutV[1] = ((uint16_t)pInC[15]) << iShift;
          pInC += 16;
        }

        pInC += 16 * (iCropW >> 2);
      }

      pInC += 16 * (iTileW >> 2) * (iCropH >> 2);
    }
  }
}

/****************************************************************************/
void T608_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T608_To_Y010(pSrc, pDst);

  // Chroma
  Chroma_T608_To_I0XL(pSrc, pDst, 10);
}

/****************************************************************************/
void T608_To_I0CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T608_To_Y012(pSrc, pDst);

  // Chroma
  Chroma_T608_To_I0XL(pSrc, pDst, 12);
}

/****************************************************************************/
void T6m8_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T608_To_Y800(pSrc, pDst);
}

/****************************************************************************/
void T628_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T608_To_Y800(pSrc, pDst);
}

/****************************************************************************/
void T628_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T608_To_Y010(pSrc, pDst);
}

/****************************************************************************/
void T628_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T608_To_Y800(pSrc, pDst);

  // Chroma
  ALX8_To_I4XX(pSrc, pDst, 2, 1);
}

/****************************************************************************/
void T628_To_NV16(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T608_To_Y800(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  T64_Untile_Plane<uint8_t, uint8_t>(pSrc, pDst, 8, 8, AL_PLANE_UV, tDim);
}

/****************************************************************************/
static void Chroma_T628_To_I2XL(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uBitDepth)
{
  if(uBitDepth != 10 && uBitDepth != 12)
    throw std::runtime_error("uBitDepth(" + std::to_string(uBitDepth) + ") must be equal to 10 or 12");

  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;

  int iPitchSrc = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_UV);
  int iPitchDstU = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_U) / sizeof(uint16_t);
  int iPitchDstV = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_V) / sizeof(uint16_t);

  auto pSrcDataC = AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_UV);
  auto pDstDataU = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_U);
  auto pDstDataV = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_V);

  int iShift = uBitDepth == 10 ? 2 : 4;

  for(int h = 0; h < tDim.iHeight; h += 4)
  {
    uint8_t* pInC = pSrcDataC + (h >> 2) * iPitchSrc;

    for(int w = 0; w < tDim.iWidth; w += 4)
    {
      uint16_t* pOutU = pDstDataU + h * iPitchDstU + w / 2;
      uint16_t* pOutV = pDstDataV + h * iPitchDstV + w / 2;

      pOutU[0] = ((uint16_t)pInC[0]) << iShift;
      pOutV[0] = ((uint16_t)pInC[1]) << iShift;
      pOutU[1] = ((uint16_t)pInC[2]) << iShift;
      pOutV[1] = ((uint16_t)pInC[3]) << iShift;
      pOutU += iPitchDstU;
      pOutV += iPitchDstV;
      pOutU[0] = ((uint16_t)pInC[4]) << iShift;
      pOutV[0] = ((uint16_t)pInC[5]) << iShift;
      pOutU[1] = ((uint16_t)pInC[6]) << iShift;
      pOutV[1] = ((uint16_t)pInC[7]) << iShift;
      pOutU += iPitchDstU;
      pOutV += iPitchDstV;
      pOutU[0] = ((uint16_t)pInC[8]) << iShift;
      pOutV[0] = ((uint16_t)pInC[9]) << iShift;
      pOutU[1] = ((uint16_t)pInC[10]) << iShift;
      pOutV[1] = ((uint16_t)pInC[11]) << iShift;
      pOutU += iPitchDstU;
      pOutV += iPitchDstV;
      pOutU[0] = ((uint16_t)pInC[12]) << iShift;
      pOutV[0] = ((uint16_t)pInC[13]) << iShift;
      pOutU[1] = ((uint16_t)pInC[14]) << iShift;
      pOutV[1] = ((uint16_t)pInC[15]) << iShift;
      pInC += 16;
    }
  }
}

/****************************************************************************/
void T628_To_I2AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T608_To_Y010(pSrc, pDst);

  // Chroma
  Chroma_T628_To_I2XL(pSrc, pDst, 10);
}

/****************************************************************************/
void T628_To_I2CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T608_To_Y012(pSrc, pDst);

  // Chroma
  Chroma_T628_To_I2XL(pSrc, pDst, 12);
}

/****************************************************************************/
void T628_To_P210(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T608_To_Y010(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  T64_Untile_Plane<uint8_t, uint16_t>(pSrc, pDst, 8, 10, AL_PLANE_UV, tDim);
}

/****************************************************************************/
void T60A_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  T64_Untile_Plane<uint16_t, uint8_t>(pSrc, pDst, 10, 8, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void T60C_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  T64_Untile_Plane<uint16_t, uint8_t>(pSrc, pDst, 12, 8, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void T60A_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  T64_Untile_Plane<uint16_t, uint16_t>(pSrc, pDst, 10, 10, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void T60C_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  T64_Untile_Plane<uint16_t, uint16_t>(pSrc, pDst, 12, 10, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void T60C_To_Y012(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  T64_Untile_Plane<uint16_t, uint16_t>(pSrc, pDst, 12, 12, AL_PLANE_Y, tDim);
}

/****************************************************************************/
template<typename DstType>
static void T6XX_To_4XX(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t bdIn, uint8_t bdOut, int iHScale, int iVScale)
{
  // Luma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  T64_Untile_Plane<uint16_t, DstType>(pSrc, pDst, bdIn, bdOut, AL_PLANE_Y, tDim);

  // Chroma
  int iWidthC = 2 * ((tDim.iWidth + iHScale - 1) / iHScale);
  int iHeightC = (tDim.iHeight + iVScale - 1) / iVScale;

  int iPitchSrc = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_UV) / sizeof(uint16_t);
  int iPitchDstU = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_U) / sizeof(DstType);
  int iPitchDstV = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_V) / sizeof(DstType);

  auto pSrcData = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_UV);
  auto pDstDataU = (DstType*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_U);
  auto pDstDataV = (DstType*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_V);

  for(int h = 0; h < iHeightC; h += 4)
  {
    uint16_t* pInC = pSrcData + (h >> 2) * iPitchSrc;

    for(int w = 0; w < iWidthC; w += 4)
    {
      DstType* pOutU = pDstDataU + h * iPitchDstU + w / 2;
      DstType* pOutV = pDstDataV + h * iPitchDstV + w / 2;

      if(bdIn == 12)
      {
        if(bdOut == 12)
        {
          Untile4x4ChromaBlock12bToPlanar12b(pInC, (uint16_t*)pOutU, (uint16_t*)pOutV, iPitchDstU, iPitchDstV);
        }
        else if(bdOut == 10)
        {
          Untile4x4ChromaBlock12bToPlanar10b(pInC, (uint16_t*)pOutU, (uint16_t*)pOutV, iPitchDstU, iPitchDstV);
        }
        else
        {
          Untile4x4ChromaBlock12bToPlanar8b(pInC, (uint8_t*)pOutU, (uint8_t*)pOutV, iPitchDstU, iPitchDstV);
        }
      }
      else // bdIn 10 bit
      {
        bdOut == 10 ?
        Untile4x4ChromaBlock10bToPlanar10b(pInC, (uint16_t*)pOutU, (uint16_t*)pOutV, iPitchDstU, iPitchDstV) :
        Untile4x4ChromaBlock10bToPlanar8b(pInC, (uint8_t*)pOutU, (uint8_t*)pOutV, iPitchDstU, iPitchDstV);
      }
      pInC += bdIn;
    }
  }
}

/****************************************************************************/
void T60A_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T6XX_To_4XX<uint8_t>(pSrc, pDst, 10, 8, 2, 2);
}

/****************************************************************************/
void T60C_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T6XX_To_4XX<uint8_t>(pSrc, pDst, 12, 8, 2, 2);
}

/****************************************************************************/
void T60A_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T60A_To_I420(pSrc, pDst);
}

/****************************************************************************/
void T60C_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T60A_To_I420(pSrc, pDst);
}

/****************************************************************************/
void T60A_To_YV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T6XX_To_4XX<uint8_t>(pSrc, pDst, 10, 8, 2, 2);
}

/****************************************************************************/
void T60C_To_YV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T6XX_To_4XX<uint8_t>(pSrc, pDst, 12, 8, 2, 2);
}

/****************************************************************************/
void T60A_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T6XX_To_4XX<uint16_t>(pSrc, pDst, 10, 10, 2, 2);
}

/****************************************************************************/
void T60C_To_I0CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T6XX_To_4XX<uint16_t>(pSrc, pDst, 12, 12, 2, 2);
}

/****************************************************************************/
void T60C_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T6XX_To_4XX<uint16_t>(pSrc, pDst, 12, 10, 2, 2);
}

/****************************************************************************/
void T60A_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T60A_To_Y800(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  tDim.iHeight = (tDim.iHeight + 1) >> 1;
  T64_Untile_Plane<uint16_t, uint8_t>(pSrc, pDst, 10, 8, AL_PLANE_UV, tDim);
}

/****************************************************************************/
void T60A_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T60A_To_Y010(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  tDim.iHeight = (tDim.iHeight + 1) >> 1;
  T64_Untile_Plane<uint16_t, uint16_t>(pSrc, pDst, 10, 10, AL_PLANE_UV, tDim);
}

/****************************************************************************/
void T62A_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T60A_To_Y800(pSrc, pDst);
}

/****************************************************************************/
void T62C_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T60C_To_Y800(pSrc, pDst);
}

/****************************************************************************/
void T62C_To_Y012(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T60C_To_Y012(pSrc, pDst);
}

/****************************************************************************/
void T62A_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T60A_To_Y010(pSrc, pDst);
}

/****************************************************************************/
void T62A_To_I2AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T6XX_To_4XX<uint16_t>(pSrc, pDst, 10, 10, 2, 1);
}

/****************************************************************************/
void T62C_To_I2CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T6XX_To_4XX<uint16_t>(pSrc, pDst, 12, 12, 2, 1);
}

/****************************************************************************/
void T62C_To_I2AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T6XX_To_4XX<uint16_t>(pSrc, pDst, 12, 10, 2, 1);
}

/****************************************************************************/
void T62C_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T6XX_To_4XX<uint8_t>(pSrc, pDst, 12, 8, 2, 1);
}

/****************************************************************************/
void T62A_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T6XX_To_4XX<uint8_t>(pSrc, pDst, 10, 8, 2, 1);
}

/****************************************************************************/
void T62A_To_NV16(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  T60A_To_Y800(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  T64_Untile_Plane<uint16_t, uint8_t>(pSrc, pDst, 10, 8, AL_PLANE_UV, tDim);
}

/****************************************************************************/
void T62X_To_P21X(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uBd)
{
  // Luma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  T64_Untile_Plane<uint16_t, uint16_t>(pSrc, pDst, uBd, uBd, AL_PLANE_Y, tDim);

  // Chroma
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  T64_Untile_Plane<uint16_t, uint16_t>(pSrc, pDst, uBd, uBd, AL_PLANE_UV, tDim);
}

/****************************************************************************/
void T62A_To_P210(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T62X_To_P21X(pSrc, pDst, 10);
}

/****************************************************************************/
void T62C_To_P212(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  T62X_To_P21X(pSrc, pDst, 12);
}

/****************************************************************************/
void T648_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  T64_Untile_Plane<uint8_t, uint8_t>(pSrc, pDst, 8, 8, AL_PLANE_Y, tDim);
  T64_Untile_Plane<uint8_t, uint8_t>(pSrc, pDst, 8, 8, AL_PLANE_U, tDim);
  T64_Untile_Plane<uint8_t, uint8_t>(pSrc, pDst, 8, 8, AL_PLANE_V, tDim);
}

/****************************************************************************/
void T64A_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  T64_Untile_Plane<uint16_t, uint8_t>(pSrc, pDst, 10, 8, AL_PLANE_Y, tDim);
  T64_Untile_Plane<uint16_t, uint8_t>(pSrc, pDst, 10, 8, AL_PLANE_U, tDim);
  T64_Untile_Plane<uint16_t, uint8_t>(pSrc, pDst, 10, 8, AL_PLANE_V, tDim);
}

/****************************************************************************/
void T648_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  T64_Untile_Plane<uint8_t, uint16_t>(pSrc, pDst, 8, 10, AL_PLANE_Y, tDim);
  T64_Untile_Plane<uint8_t, uint16_t>(pSrc, pDst, 8, 10, AL_PLANE_U, tDim);
  T64_Untile_Plane<uint8_t, uint16_t>(pSrc, pDst, 8, 10, AL_PLANE_V, tDim);
}

/****************************************************************************/
void T64A_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  T64_Untile_Plane<uint16_t, uint16_t>(pSrc, pDst, 10, 10, AL_PLANE_Y, tDim);
  T64_Untile_Plane<uint16_t, uint16_t>(pSrc, pDst, 10, 10, AL_PLANE_U, tDim);
  T64_Untile_Plane<uint16_t, uint16_t>(pSrc, pDst, 10, 10, AL_PLANE_V, tDim);
}

/****************************************************************************/
void T64C_To_I4CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  T64_Untile_Plane<uint16_t, uint16_t>(pSrc, pDst, 12, 12, AL_PLANE_Y, tDim);
  T64_Untile_Plane<uint16_t, uint16_t>(pSrc, pDst, 12, 12, AL_PLANE_U, tDim);
  T64_Untile_Plane<uint16_t, uint16_t>(pSrc, pDst, 12, 12, AL_PLANE_V, tDim);
}

/****************************************************************************/
void T64C_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  T64_Untile_Plane<uint16_t, uint16_t>(pSrc, pDst, 12, 10, AL_PLANE_Y, tDim);
  T64_Untile_Plane<uint16_t, uint16_t>(pSrc, pDst, 12, 10, AL_PLANE_U, tDim);
  T64_Untile_Plane<uint16_t, uint16_t>(pSrc, pDst, 12, 10, AL_PLANE_V, tDim);
}

/****************************************************************************/
void T64C_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  T64_Untile_Plane<uint16_t, uint8_t>(pSrc, pDst, 12, 8, AL_PLANE_Y, tDim);
  T64_Untile_Plane<uint16_t, uint8_t>(pSrc, pDst, 12, 8, AL_PLANE_U, tDim);
  T64_Untile_Plane<uint16_t, uint8_t>(pSrc, pDst, 12, 8, AL_PLANE_V, tDim);
}

/****************************************************************************/
template<typename TUntiled, typename FConvert>
static void Tile4x4Block8b(TUntiled* pUntiled, int iUntiledPitch, uint8_t* pTiled4x4, FConvert convert)
{
  pTiled4x4[0] = convert(pUntiled[0]);
  pTiled4x4[1] = convert(pUntiled[1]);
  pTiled4x4[2] = convert(pUntiled[2]);
  pTiled4x4[3] = convert(pUntiled[3]);
  pUntiled += iUntiledPitch;

  pTiled4x4[4] = convert(pUntiled[0]);
  pTiled4x4[5] = convert(pUntiled[1]);
  pTiled4x4[6] = convert(pUntiled[2]);
  pTiled4x4[7] = convert(pUntiled[3]);
  pUntiled += iUntiledPitch;

  pTiled4x4[8] = convert(pUntiled[0]);
  pTiled4x4[9] = convert(pUntiled[1]);
  pTiled4x4[10] = convert(pUntiled[2]);
  pTiled4x4[11] = convert(pUntiled[3]);
  pUntiled += iUntiledPitch;

  pTiled4x4[12] = convert(pUntiled[0]);
  pTiled4x4[13] = convert(pUntiled[1]);
  pTiled4x4[14] = convert(pUntiled[2]);
  pTiled4x4[15] = convert(pUntiled[3]);
}

/****************************************************************************/
template<typename TUntiled, typename FConvert>
static void Tile4x4Block10b(TUntiled* pUntiled, int iUntiledPitch, uint16_t* pTiled4x4, FConvert convert)
{
  pTiled4x4[0] = convert(
    ((pUntiled[1] & 0x3F) << 10) |
    (pUntiled[0] & 0x3FF));
  pTiled4x4[1] = convert(
    ((pUntiled[3] & 0x3) << 14) |
    ((pUntiled[2] & 0x3FF) << 4) |
    ((pUntiled[1] >> 6) & 0xF));
  pTiled4x4[2] = convert(
    ((pUntiled[iUntiledPitch + 0] & 0xFF) << 8) |
    ((pUntiled[3] >> 2) & 0xFF));
  pUntiled += iUntiledPitch;
  pTiled4x4[3] = convert(
    ((pUntiled[2] & 0xF) << 12) |
    ((pUntiled[1] & 0x3FF) << 2) |
    ((pUntiled[0] >> 8) & 0x3));
  pTiled4x4[4] = convert(
    ((pUntiled[3] & 0x3FF) << 6) |
    ((pUntiled[2] >> 4) & 0x3F));
  pUntiled += iUntiledPitch;

  pTiled4x4[5] = convert(
    ((pUntiled[1] & 0x3F) << 10) |
    (pUntiled[0] & 0x3FF));
  pTiled4x4[6] = convert(
    ((pUntiled[3] & 0x3) << 14) |
    ((pUntiled[2] & 0x3FF) << 4) |
    ((pUntiled[1] >> 6) & 0xF));
  pTiled4x4[7] = convert(
    ((pUntiled[iUntiledPitch + 0] & 0xFF) << 8) |
    ((pUntiled[3] >> 2) & 0xFF));
  pUntiled += iUntiledPitch;
  pTiled4x4[8] = convert(
    ((pUntiled[2] & 0xF) << 12) |
    ((pUntiled[1] & 0x3FF) << 2) |
    ((pUntiled[0] >> 8) & 0x3));
  pTiled4x4[9] = convert(
    ((pUntiled[3] & 0x3FF) << 6) |
    ((pUntiled[2] >> 4) & 0x3F));
}

/****************************************************************************/
template<typename TUntiled, typename FConvert>
static void Tile4x4Block12b(TUntiled* pUntiled, int iUntiledPitch, uint16_t* pTiled4x4, FConvert convert)
{
  for(int row = 0; row < 4; row++)
  {
    int off = row * 3;

    pTiled4x4[0 + off] = convert(((pUntiled[1] & 0xF) << 12) | (pUntiled[0] & 0xFFF));
    pTiled4x4[1 + off] = convert(((pUntiled[2] & 0xFF) << 8) | ((pUntiled[1] >> 4) & 0xFF));
    pTiled4x4[2 + off] = convert(((pUntiled[3] & 0xFFF) << 4) | ((pUntiled[2] >> 8) & 0xF));
    pUntiled += iUntiledPitch;
  }
}

/****************************************************************************/
static void Tile4x4Block8bTo8b(void* pUntiled, int iUntiledPitch, void* pTiled4x4)
{
  Tile4x4Block8b<uint8_t>((uint8_t*)pUntiled, iUntiledPitch, (uint8_t*)pTiled4x4, [](uint8_t u8) { return u8; });
}

/****************************************************************************/
static void Tile4x4Block8bTo10b(void* pUntiled, int iUntiledPitch, void* pTiled4x4)
{
  Tile4x4Block8b<uint16_t>((uint16_t*)pUntiled, iUntiledPitch, (uint8_t*)pTiled4x4, [](uint8_t u8) { return uint16_t(u8) << 2; });
}

/****************************************************************************/
static void Tile4x4Block8bTo12b(void* pUntiled, int iUntiledPitch, void* pTiled4x4)
{
  Tile4x4Block8b<uint16_t>((uint16_t*)pUntiled, iUntiledPitch, (uint8_t*)pTiled4x4, [](uint8_t u8) { return uint16_t(u8) << 4; });
}

/****************************************************************************/
static void Tile4x4Block10bTo8b(void* pUntiled, int iUntiledPitch, void* pTiled4x4)
{
  Tile4x4Block10b<uint8_t>((uint8_t*)pUntiled, iUntiledPitch, (uint16_t*)pTiled4x4, RND_10B_TO_8B);
}

/****************************************************************************/
static void Tile4x4Block10bTo10b(void* pUntiled, int iUntiledPitch, void* pTiled4x4)
{
  Tile4x4Block10b<uint16_t>((uint16_t*)pUntiled, iUntiledPitch, (uint16_t*)pTiled4x4, [](uint16_t u16) { return u16; });
}

/****************************************************************************/
static void Tile4x4Block10bTo12b(void* pUntiled, int iUntiledPitch, void* pTiled4x4)
{
  Tile4x4Block10b<uint16_t>((uint16_t*)pUntiled, iUntiledPitch, (uint16_t*)pTiled4x4, [](uint16_t u16) { return u16 << 2; });
}

/****************************************************************************/
static void Tile4x4Block12bTo8b(void* pUntiled, int iUntiledPitch, void* pTiled4x4)
{
  Tile4x4Block12b<uint8_t>((uint8_t*)pUntiled, iUntiledPitch, (uint16_t*)pTiled4x4, RND_12B_TO_8B);
}

/****************************************************************************/
static void Tile4x4Block12bTo10b(void* pUntiled, int iUntiledPitch, void* pTiled4x4)
{
  Tile4x4Block12b<uint16_t>((uint16_t*)pUntiled, iUntiledPitch, (uint16_t*)pTiled4x4, RND_12B_TO_10B);
}

/****************************************************************************/
static void Tile4x4Block12bTo12b(void* pUntiled, int iUntiledPitch, void* pTiled4x4)
{
  Tile4x4Block12b<uint16_t>((uint16_t*)pUntiled, iUntiledPitch, (uint16_t*)pTiled4x4, [](uint16_t u16) { return u16; });
}

/****************************************************************************/
template<typename SrcType, typename DstType>
static void Plane_Tile_T64(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t bdIn, uint8_t bdOut, AL_EPlaneId ePlaneId, AL_TDimension tPlaneDim)
{
  const int iTileW = 64;
  const int iTileH = 4;

  void (* Tile4x4Block) (void*, int, void*) = nullptr;

  if(bdIn == 12)
  {
    if(bdOut == 12)
      Tile4x4Block = Tile4x4Block12bTo12b;
    else if(bdOut == 10)
      Tile4x4Block = Tile4x4Block12bTo10b;
    else
      Tile4x4Block = Tile4x4Block12bTo8b;
  }
  else if(bdIn == 10)
  {
    if(bdOut == 12)
      Tile4x4Block = Tile4x4Block10bTo12b;
    else if(bdOut == 10)
      Tile4x4Block = Tile4x4Block10bTo10b;
    else
      Tile4x4Block = Tile4x4Block10bTo8b;
  }
  else
  {
    if(bdOut == 12)
      Tile4x4Block = Tile4x4Block8bTo12b;
    else if(bdOut == 10)
      Tile4x4Block = Tile4x4Block8bTo10b;
    else
      Tile4x4Block = Tile4x4Block8bTo8b;
  }

  auto pSrcData = (SrcType*)AL_PixMapBuffer_GetPlaneAddress(pSrc, ePlaneId);
  auto pDstData = (DstType*)AL_PixMapBuffer_GetPlaneAddress(pDst, ePlaneId);
  int iPitchSrc = AL_PixMapBuffer_GetPlanePitch(pSrc, ePlaneId) / sizeof(SrcType);
  int iPitchDst = AL_PixMapBuffer_GetPlanePitch(pDst, ePlaneId) / sizeof(DstType);

  /* Src increment = (16 * bdIn) / (8 * sizeof(SrcType)) */
  const int iSrcIncr4x4 = (bdIn << 1) / sizeof(SrcType);

  for(int H = 0; H < tPlaneDim.iHeight; H += iTileH)
  {
    DstType* pOut = pDstData + (H / iTileH) * iPitchDst;

    int iCropH = (H + iTileH) - tPlaneDim.iHeight;

    if(iCropH < 0)
      iCropH = 0;

    for(int W = 0; W < tPlaneDim.iWidth; W += iTileW)
    {
      int iCropW = (W + iTileW) - tPlaneDim.iWidth;

      if(iCropW < 0)
        iCropW = 0;

      for(int h = 0; h < iTileH - iCropH; h += 4)
      {
        for(int w = 0; w < iTileW - iCropW; w += 4)
        {
          SrcType* pIn = pSrcData + (H + h) * iPitchSrc + (W + w);
          Tile4x4Block(pIn, iPitchSrc, pOut);
          pOut += iSrcIncr4x4;
        }

        pOut += iSrcIncr4x4 * (iCropW >> 2);
      }

      pOut += iSrcIncr4x4 * (iTileW >> 2) * (iCropH >> 2);
    }
  }
}

/****************************************************************************/
static void Chroma_I0XL_To_T608(AL_TBuffer const* pDst, AL_TBuffer* pSrc, uint8_t uBitDepth)
{
  if(uBitDepth != 10 && uBitDepth != 12)
    throw std::runtime_error("uBitDepth(" + std::to_string(uBitDepth) + ") must be equal to 10 or 12");

  int iPitchDst = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_UV);
  int iPitchSrcU = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_U) / sizeof(uint16_t);
  int iPitchSrcV = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_V) / sizeof(uint16_t);
  auto pDstData = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_UV);
  auto pSrcDataU = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_U);
  auto pSrcDataV = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_V);

  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  tDim.iHeight = (tDim.iHeight + 1) >> 1;

  const int iTileW = 64;
  const int iTileH = 4;

  int iShift = uBitDepth == 10 ? 2 : 4;

  for(int H = 0; H < tDim.iHeight; H += iTileH)
  {
    uint8_t* pOutC = pDstData + (H / iTileH) * iPitchDst;

    int iCropH = (H + iTileH) - tDim.iHeight;

    if(iCropH < 0)
      iCropH = 0;

    for(int W = 0; W < tDim.iWidth; W += iTileW)
    {
      int iCropW = (W + iTileW) - tDim.iWidth;

      if(iCropW < 0)
        iCropW = 0;

      for(int h = 0; h < iTileH - iCropH; h += 4)
      {
        for(int w = 0; w < iTileW - iCropW; w += 4)
        {
          uint16_t* pInU = pSrcDataU + (H + h) * iPitchSrcU + (W + w) / 2;
          uint16_t* pInV = pSrcDataV + (H + h) * iPitchSrcV + (W + w) / 2;

          pOutC[0] = (uint8_t)(pInU[0] >> iShift);
          pOutC[1] = (uint8_t)(pInV[0] >> iShift);
          pOutC[2] = (uint8_t)(pInU[1] >> iShift);
          pOutC[3] = (uint8_t)(pInV[1] >> iShift);
          pInU += iPitchSrcU;
          pInV += iPitchSrcV;
          pOutC[4] = (uint8_t)(pInU[0] >> iShift);
          pOutC[5] = (uint8_t)(pInV[0] >> iShift);
          pOutC[6] = (uint8_t)(pInU[1] >> iShift);
          pOutC[7] = (uint8_t)(pInV[1] >> iShift);
          pInU += iPitchSrcU;
          pInV += iPitchSrcV;
          pOutC[8] = (uint8_t)(pInU[0] >> iShift);
          pOutC[9] = (uint8_t)(pInV[0] >> iShift);
          pOutC[10] = (uint8_t)(pInU[1] >> iShift);
          pOutC[11] = (uint8_t)(pInV[1] >> iShift);
          pInU += iPitchSrcU;
          pInV += iPitchSrcV;
          pOutC[12] = (uint8_t)(pInU[0] >> iShift);
          pOutC[13] = (uint8_t)(pInV[0] >> iShift);
          pOutC[14] = (uint8_t)(pInU[1] >> iShift);
          pOutC[15] = (uint8_t)(pInV[1] >> iShift);
          pOutC += 16;
        }

        pOutC += 16 * (iCropW >> 2);
      }

      pOutC += 16 * (iTileW >> 2) * (iCropH >> 2);
    }
  }
}

/****************************************************************************/
static void I4XX_To_ALX8(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uHrzCScale, uint8_t uVrtCScale)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);

  const int iTileW = 64;
  const int iTileH = 4;

  uint32_t uPitchDst = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_UV);
  uint8_t* pDstData = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_UV);

  uint32_t uPitchSrcU = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_U);
  uint32_t uPitchSrcV = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_V);
  uint8_t* pSrcDataU = AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_U);
  uint8_t* pSrcDataV = AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_V);

  int iWidthC = (tDim.iWidth + uHrzCScale - 1) / uHrzCScale * 2;
  int iHeightC = (tDim.iHeight + uVrtCScale - 1) / uVrtCScale;

  for(int H = 0; H < iHeightC; H += iTileH)
  {
    uint8_t* pOutC = pDstData + (H / iTileH) * uPitchDst;

    int iCropH = (H + iTileH) - iHeightC;

    if(iCropH < 4)
      iCropH = 0;

    for(int W = 0; W < iWidthC; W += iTileW)
    {
      int iCropW = (W + iTileW) - iWidthC;

      if(iCropW < 8 / uHrzCScale)
        iCropW = 0;

      for(int h = 0; h < iTileH - iCropH; h += 4)
      {
        for(int w = 0; w < iTileW - iCropW; w += 4)
        {
          uint8_t* pInU = pSrcDataU + (H + h) * uPitchSrcU + (W + w) / uHrzCScale;
          uint8_t* pInV = pSrcDataV + (H + h) * uPitchSrcV + (W + w) / uHrzCScale;

          for(int p = 0; p < (8 / uHrzCScale); p++)
            pOutC[p] = ((p % 2 == 0) ? pInU[(p % (8 / uHrzCScale)) / 2] : pInV[(p % (8 / uHrzCScale)) / 2]);

          pInU += uPitchSrcU;
          pInV += uPitchSrcV;

          for(int p = (1 * (8 / uHrzCScale)); p < (1 * (8 / uHrzCScale)) + (8 / uHrzCScale); p++)
            pOutC[p] = ((p % 2 == 0) ? pInU[(p % (8 / uHrzCScale)) / 2] : pInV[(p % (8 / uHrzCScale)) / 2]);

          if(H + h + 3 <= iHeightC)
          {
            pInU += uPitchSrcU;
            pInV += uPitchSrcV;

            for(int p = (2 * (8 / uHrzCScale)); p < (2 * (8 / uHrzCScale)) + (8 / uHrzCScale); p++)
              pOutC[p] = ((p % 2 == 0) ? pInU[(p % (8 / uHrzCScale)) / 2] : pInV[(p % (8 / uHrzCScale)) / 2]);
          }

          if(H + h + 4 <= iHeightC)
          {
            pInU += uPitchSrcU;
            pInV += uPitchSrcV;

            for(int p = (3 * (8 / uHrzCScale)); p < (3 * (8 / uHrzCScale)) + (8 / uHrzCScale); p++)
              pOutC[p] = ((p % 2 == 0) ? pInU[(p % (8 / uHrzCScale)) / 2] : pInV[(p % (8 / uHrzCScale)) / 2]);
          }
          pOutC += ((4 * 8) / uHrzCScale);
        }

        pOutC += (8 / uHrzCScale) * iCropW;
      }

      pOutC += iCropH * iTileW;
    }
  }
}

/****************************************************************************/
void Y800_To_T6m8(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  Plane_Tile_T64<uint8_t, uint8_t>(pSrc, pDst, 8, 8, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void I420_To_T6m8(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  Y800_To_T6m8(pSrc, pDst);
}

/****************************************************************************/
void Y010_To_T6mA(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, 10, 10, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void I0AL_To_T6mA(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  Y010_To_T6mA(pSrc, pDst);
}

/****************************************************************************/
void Y012_To_T6mC(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, 12, 12, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void I0CL_To_T6mC(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  Y012_To_T6mC(pSrc, pDst);
}

/****************************************************************************/
void Y010_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  Plane_Tile_T64<uint16_t, uint8_t>(pSrc, pDst, 10, 8, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void Y010_To_T64C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  Plane_Tile_T64<uint16_t, uint8_t>(pSrc, pDst, 10, 12, AL_PLANE_Y, tDim);

  AL_PixMapBuffer_SetFourCC(pDst, FOURCC(T64C));
}

/****************************************************************************/
void Y012_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  Plane_Tile_T64<uint16_t, uint8_t>(pSrc, pDst, 12, 8, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void P010_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y010_To_T608(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  tDim.iHeight = (tDim.iHeight + 1) >> 1;
  Plane_Tile_T64<uint16_t, uint8_t>(pSrc, pDst, 10, 8, AL_PLANE_UV, tDim);
}

/****************************************************************************/
void NV12_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y800_To_T608(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  tDim.iHeight = (tDim.iHeight + 1) >> 1;
  Plane_Tile_T64<uint8_t, uint8_t>(pSrc, pDst, 8, 8, AL_PLANE_UV, tDim);
}

/****************************************************************************/
void I0AL_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y010_To_T608(pSrc, pDst);

  // Chroma
  Chroma_I0XL_To_T608(pSrc, pDst, 10);
}

/****************************************************************************/
void I0CL_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y012_To_T608(pSrc, pDst);

  // Chroma
  Chroma_I0XL_To_T608(pSrc, pDst, 12);
}

/****************************************************************************/
void I420_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y800_To_T608(pSrc, pDst);

  // Chroma
  I4XX_To_ALX8(pSrc, pDst, 2, 2);
}

/****************************************************************************/
void IYUV_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I420_To_T608(pSrc, pDst);
}

/****************************************************************************/
void YV12_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y800_To_T608(pSrc, pDst);

  // Chroma
  I4XX_To_ALX8(pSrc, pDst, 2, 2);
}

/****************************************************************************/
template<typename TTiled, typename FConvert>
static void PlanarToTile4x4ChromaBlock10b(TTiled* pUntiledU, TTiled* pUntiledV, int iTiledPitchU, int iTiledPitchV, uint16_t* pTiled4x4, FConvert convert)
{
  pTiled4x4[0] = convert(
    ((pUntiledV[0] & 0x3F) << 10) |
    (pUntiledU[0] & 0x3FF));
  pTiled4x4[1] = convert(
    ((pUntiledV[1] & 0x3) << 14) |
    ((pUntiledU[1] & 0x3FF) << 4) |
    ((pUntiledV[0] >> 6) & 0xF));
  pTiled4x4[2] = convert(
    ((pUntiledU[iTiledPitchU + 0] & 0xFF) << 8) |
    ((pUntiledV[1] >> 2) & 0xFF));
  pUntiledU += iTiledPitchU;
  pUntiledV += iTiledPitchV;
  pTiled4x4[3] = convert(
    ((pUntiledU[1] & 0xF) << 12) |
    ((pUntiledV[0] & 0x3FF) << 2) |
    ((pUntiledU[0] >> 8) & 0x3));
  pTiled4x4[4] = convert(
    ((pUntiledV[1] & 0x3FF) << 6) |
    ((pUntiledU[1] >> 4) & 0x3F));
  pUntiledU += iTiledPitchU;
  pUntiledV += iTiledPitchV;

  pTiled4x4[5] = convert(
    ((pUntiledV[0] & 0x3F) << 10) |
    (pUntiledU[0] & 0x3FF));
  pTiled4x4[6] = convert(
    ((pUntiledV[1] & 0x3) << 14) |
    ((pUntiledU[1] & 0x3FF) << 4) |
    ((pUntiledV[0] >> 6) & 0xF));
  pTiled4x4[7] = convert(
    ((pUntiledU[iTiledPitchU + 0] & 0xFF) << 8) |
    ((pUntiledV[1] >> 2) & 0xFF));
  pUntiledU += iTiledPitchU;
  pUntiledV += iTiledPitchV;
  pTiled4x4[8] = convert(
    ((pUntiledU[1] & 0xF) << 12) |
    ((pUntiledV[0] & 0x3FF) << 2) |
    ((pUntiledU[0] >> 8) & 0x3));
  pTiled4x4[9] = convert(
    ((pUntiledV[1] & 0x3FF) << 6) |
    ((pUntiledU[1] >> 4) & 0x3F));
}

/****************************************************************************/
template<typename TTiled, typename FConvert>
static void PlanarToTile4x4ChromaBlock12b(TTiled* pUntiledU, TTiled* pUntiledV, int iTiledPitchU, int iTiledPitchV, uint16_t* pTiled4x4, FConvert convert)
{
  for(int row = 0; row < 4; row++)
  {
    int off = row * 3;

    pTiled4x4[0 + off] = convert(((pUntiledV[0] & 0xF) << 12) | (pUntiledU[0] & 0xFFF));
    pTiled4x4[1 + off] = convert(((pUntiledU[1] & 0xFF) << 8) | ((pUntiledV[0] >> 4) & 0xFF));
    pTiled4x4[2 + off] = convert(((pUntiledV[1] & 0xFFF) << 4) | ((pUntiledU[1] >> 8) & 0xF));
    pUntiledU += iTiledPitchU;
    pUntiledV += iTiledPitchV;
  }
}

/****************************************************************************/
static void Planar8bToTile4x4ChromaBlock10b(uint8_t* pUntiledU, uint8_t* pUntiledV, int iPitchU, int iPitchV, uint16_t* pTiled4x4)
{
  PlanarToTile4x4ChromaBlock10b<uint8_t>(pUntiledU, pUntiledV, iPitchU, iPitchV, pTiled4x4, RND_10B_TO_8B);
}

/****************************************************************************/
static void Planar10bToTile4x4ChromaBlock10b(uint16_t* pUntiledU, uint16_t* pUntiledV, int iPitchU, int iPitchV, uint16_t* pTiled4x4)
{
  PlanarToTile4x4ChromaBlock10b<uint16_t>(pUntiledU, pUntiledV, iPitchU, iPitchV, pTiled4x4, [](uint16_t u16) { return u16; });
}

/****************************************************************************/
static void Planar8bToTile4x4ChromaBlock12b(uint8_t* pUntiledU, uint8_t* pUntiledV, int iPitchU, int iPitchV, uint16_t* pTiled4x4)
{
  PlanarToTile4x4ChromaBlock12b<uint8_t>(pUntiledU, pUntiledV, iPitchU, iPitchV, pTiled4x4, RND_12B_TO_8B);
}

/****************************************************************************/
static void Planar10bToTile4x4ChromaBlock12b(uint16_t* pUntiledU, uint16_t* pUntiledV, int iPitchU, int iPitchV, uint16_t* pTiled4x4)
{
  PlanarToTile4x4ChromaBlock12b<uint16_t>(pUntiledU, pUntiledV, iPitchU, iPitchV, pTiled4x4, RND_12B_TO_10B);
}

/****************************************************************************/
static void Planar12bToTile4x4ChromaBlock12b(uint16_t* pUntiledU, uint16_t* pUntiledV, int iPitchU, int iPitchV, uint16_t* pTiled4x4)
{
  PlanarToTile4x4ChromaBlock12b<uint16_t>(pUntiledU, pUntiledV, iPitchU, iPitchV, pTiled4x4, [](uint16_t u16) { return u16; });
}

/****************************************************************************/
template<typename SrcType>
static void From_4XX_To_T6XX(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t bdIn, uint8_t bdOut, int iHScale, int iVScale)
{
  // Luma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  Plane_Tile_T64<SrcType, uint16_t>(pSrc, pDst, bdIn, bdOut, AL_PLANE_Y, tDim);

  // Chroma
  int iWidthC = 2 * ((tDim.iWidth + iHScale - 1) / iHScale);
  int iHeightC = (tDim.iHeight + iVScale - 1) / iVScale;

  int iPitchDst = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_UV) / sizeof(uint16_t);
  int iPitchSrcU = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_U) / sizeof(SrcType);
  int iPitchSrcV = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_V) / sizeof(SrcType);

  auto pDstData = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_UV);
  auto pSrcDataU = (SrcType*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_U);
  auto pSrcDataV = (SrcType*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_V);

  for(int h = 0; h < iHeightC; h += 4)
  {
    uint16_t* pInC = pDstData + (h >> 2) * iPitchDst;

    for(int w = 0; w < iWidthC; w += 4)
    {
      SrcType* pOutU = pSrcDataU + h * iPitchSrcU + w / 2;
      SrcType* pOutV = pSrcDataV + h * iPitchSrcV + w / 2;

      if(bdIn == 12)
      {
        if(bdOut == 12)
        {
          Planar12bToTile4x4ChromaBlock12b((uint16_t*)pOutU, (uint16_t*)pOutV, iPitchSrcU, iPitchSrcV, pInC);
        }
        else if(bdOut == 10)
        {
          Planar10bToTile4x4ChromaBlock12b((uint16_t*)pOutU, (uint16_t*)pOutV, iPitchSrcU, iPitchSrcV, pInC);
        }
        else
        {
          Planar8bToTile4x4ChromaBlock12b((uint8_t*)pOutU, (uint8_t*)pOutV, iPitchSrcU, iPitchSrcV, pInC);
        }
      }
      else // bdIn 10 bit
      {
        bdOut == 10 ?
        Planar10bToTile4x4ChromaBlock10b((uint16_t*)pOutU, (uint16_t*)pOutV, iPitchSrcU, iPitchSrcV, pInC) :
        Planar8bToTile4x4ChromaBlock10b((uint8_t*)pOutU, (uint8_t*)pOutV, iPitchSrcU, iPitchSrcV, pInC);
      }
      pInC += bdIn;
    }
  }
}

/****************************************************************************/
void I420_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  From_4XX_To_T6XX<uint16_t>(pSrc, pDst, 8, 10, 2, 2);
}

/****************************************************************************/
void I420_To_T60C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  From_4XX_To_T6XX<uint16_t>(pSrc, pDst, 8, 12, 2, 2);
}

/****************************************************************************/
void IYUV_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  I420_To_T60A(pSrc, pDst);
}

/****************************************************************************/
void YV12_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  From_4XX_To_T6XX<uint8_t>(pSrc, pDst, 8, 10, 2, 2);
}

/****************************************************************************/
void I0AL_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  From_4XX_To_T6XX<uint16_t>(pSrc, pDst, 10, 10, 2, 2);
}

/****************************************************************************/
void I0CL_To_T60C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  From_4XX_To_T6XX<uint16_t>(pSrc, pDst, 12, 12, 2, 2);
}

/****************************************************************************/
void I0AL_To_T60C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  From_4XX_To_T6XX<uint16_t>(pSrc, pDst, 10, 12, 2, 2);
}

/****************************************************************************/
void Y800_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  Plane_Tile_T64<uint8_t, uint16_t>(pSrc, pDst, 8, 10, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void Y800_To_T60C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  Plane_Tile_T64<uint16_t, uint8_t>(pSrc, pDst, 8, 12, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void Y010_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, 10, 10, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void Y010_To_T60C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, 10, 12, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void Y012_To_T60C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, 12, 12, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void NV12_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y800_To_T60A(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  tDim.iHeight = (tDim.iHeight + 1) >> 1;
  Plane_Tile_T64<uint8_t, uint16_t>(pSrc, pDst, 8, 10, AL_PLANE_UV, tDim);
}

/****************************************************************************/
void P010_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y010_To_T60A(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  tDim.iHeight = (tDim.iHeight + 1) >> 1;
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, 10, 10, AL_PLANE_UV, tDim);
}

/****************************************************************************/
void Y800_To_T62A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y800_To_T60A(pSrc, pDst);
}

/****************************************************************************/
void Y800_To_T62C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y800_To_T60C(pSrc, pDst);
}

/****************************************************************************/
void Y012_To_T62C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y012_To_T60C(pSrc, pDst);
}

/****************************************************************************/
void Y010_To_T62A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y010_To_T60A(pSrc, pDst);
}

/****************************************************************************/
void I2AL_To_T62A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  From_4XX_To_T6XX<uint16_t>(pSrc, pDst, 10, 10, 2, 1);
}

/****************************************************************************/
void I2CL_To_T62C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  From_4XX_To_T6XX<uint16_t>(pSrc, pDst, 12, 12, 2, 1);
}

/****************************************************************************/
void I2AL_To_T62C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  From_4XX_To_T6XX<uint16_t>(pSrc, pDst, 10, 12, 2, 1);
}

/****************************************************************************/
void I422_To_T62C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  From_4XX_To_T6XX<uint16_t>(pSrc, pDst, 8, 12, 2, 1);
}

/****************************************************************************/
void I422_To_T62A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  From_4XX_To_T6XX<uint16_t>(pSrc, pDst, 8, 10, 2, 1);
}

/****************************************************************************/
void NV16_To_T62A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y800_To_T60A(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  Plane_Tile_T64<uint8_t, uint16_t>(pSrc, pDst, 8, 10, AL_PLANE_UV, tDim);
}

/****************************************************************************/
void P21X_To_T62X(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uBd)
{
  // Luma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, uBd, uBd, AL_PLANE_Y, tDim);

  // Chroma
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, uBd, uBd, AL_PLANE_UV, tDim);
}

/****************************************************************************/
void P210_To_T62A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  P21X_To_T62X(pSrc, pDst, 10);
}

/****************************************************************************/
void P212_To_T62C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  P21X_To_T62X(pSrc, pDst, 12);
}

/****************************************************************************/
void I444_To_T648(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  Plane_Tile_T64<uint8_t, uint8_t>(pSrc, pDst, 8, 8, AL_PLANE_Y, tDim);
  Plane_Tile_T64<uint8_t, uint8_t>(pSrc, pDst, 8, 8, AL_PLANE_U, tDim);
  Plane_Tile_T64<uint8_t, uint8_t>(pSrc, pDst, 8, 8, AL_PLANE_V, tDim);
}

/****************************************************************************/
void I444_To_T64A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  Plane_Tile_T64<uint8_t, uint16_t>(pSrc, pDst, 8, 10, AL_PLANE_Y, tDim);
  Plane_Tile_T64<uint8_t, uint16_t>(pSrc, pDst, 8, 10, AL_PLANE_U, tDim);
  Plane_Tile_T64<uint8_t, uint16_t>(pSrc, pDst, 8, 10, AL_PLANE_V, tDim);
}

/****************************************************************************/
void I4AL_To_T648(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  Plane_Tile_T64<uint16_t, uint8_t>(pSrc, pDst, 10, 8, AL_PLANE_Y, tDim);
  Plane_Tile_T64<uint16_t, uint8_t>(pSrc, pDst, 10, 8, AL_PLANE_U, tDim);
  Plane_Tile_T64<uint16_t, uint8_t>(pSrc, pDst, 10, 8, AL_PLANE_V, tDim);
}

/****************************************************************************/
void I4AL_To_T64A(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, 10, 10, AL_PLANE_Y, tDim);
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, 10, 10, AL_PLANE_U, tDim);
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, 10, 10, AL_PLANE_V, tDim);
}

/****************************************************************************/
void I4CL_To_T64C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, 12, 12, AL_PLANE_Y, tDim);
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, 12, 12, AL_PLANE_U, tDim);
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, 12, 12, AL_PLANE_V, tDim);
}

/****************************************************************************/
void I4AL_To_T64C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, 10, 12, AL_PLANE_Y, tDim);
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, 10, 12, AL_PLANE_U, tDim);
  Plane_Tile_T64<uint16_t, uint16_t>(pSrc, pDst, 10, 12, AL_PLANE_V, tDim);
}

/****************************************************************************/
void I444_To_T64C(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  Plane_Tile_T64<uint8_t, uint16_t>(pSrc, pDst, 8, 12, AL_PLANE_Y, tDim);
  Plane_Tile_T64<uint8_t, uint16_t>(pSrc, pDst, 8, 12, AL_PLANE_U, tDim);
  Plane_Tile_T64<uint8_t, uint16_t>(pSrc, pDst, 8, 12, AL_PLANE_V, tDim);
}

/****************************************************************************/
void Y800_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  Plane_Tile_T64<uint8_t, uint8_t>(pSrc, pDst, 8, 8, AL_PLANE_Y, tDim);
}

/****************************************************************************/
void Y800_To_T628(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y800_To_T608(pSrc, pDst);
}

/****************************************************************************/
void Y010_To_T628(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y010_To_T608(pSrc, pDst);
}

/****************************************************************************/
void I422_To_T628(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y800_To_T608(pSrc, pDst);

  // Chroma
  I4XX_To_ALX8(pSrc, pDst, 2, 1);
}

/****************************************************************************/
void NV16_To_T628(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y800_To_T608(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  Plane_Tile_T64<uint8_t, uint8_t>(pSrc, pDst, 8, 8, AL_PLANE_UV, tDim);
}

/****************************************************************************/
static void Chroma_I2XL_To_T628(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uBitDepth)
{
  if(uBitDepth != 10 && uBitDepth != 12)
    throw std::runtime_error("uBitDepth(" + std::to_string(uBitDepth) + ") must be equal to 10 or 12");

  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pDst);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;

  int iPitchDst = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_UV);
  int iPitchSrcU = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_U) / sizeof(uint16_t);
  int iPitchSrcV = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_V) / sizeof(uint16_t);

  auto pDstDataC = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_UV);
  auto pSrcDataU = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_U);
  auto pSrcDataV = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_V);

  int iShift = uBitDepth == 10 ? 2 : 4;

  for(int h = 0; h < tDim.iHeight; h += 4)
  {
    uint8_t* pOutC = pDstDataC + (h >> 2) * iPitchDst;

    for(int w = 0; w < tDim.iWidth; w += 4)
    {
      uint16_t* pInU = pSrcDataU + h * iPitchSrcU + w / 2;
      uint16_t* pInV = pSrcDataV + h * iPitchSrcV + w / 2;

      pOutC[0] = (uint8_t)(pInU[0] >> iShift);
      pOutC[1] = (uint8_t)(pInV[0] >> iShift);
      pOutC[2] = (uint8_t)(pInU[1] >> iShift);
      pOutC[3] = (uint8_t)(pInV[1] >> iShift);
      pInU += iPitchSrcU;
      pInV += iPitchSrcV;
      pOutC[4] = (uint8_t)(pInU[0] >> iShift);
      pOutC[5] = (uint8_t)(pInV[0] >> iShift);
      pOutC[6] = (uint8_t)(pInU[1] >> iShift);
      pOutC[7] = (uint8_t)(pInV[1] >> iShift);
      pInU += iPitchSrcU;
      pInV += iPitchSrcV;
      pOutC[8] = (uint8_t)(pInU[0] >> iShift);
      pOutC[9] = (uint8_t)(pInV[0] >> iShift);
      pOutC[10] = (uint8_t)(pInU[1] >> iShift);
      pOutC[11] = (uint8_t)(pInV[1] >> iShift);
      pInU += iPitchSrcU;
      pInV += iPitchSrcV;
      pOutC[12] = (uint8_t)(pInU[0] >> iShift);
      pOutC[13] = (uint8_t)(pInV[0] >> iShift);
      pOutC[14] = (uint8_t)(pInU[1] >> iShift);
      pOutC[15] = (uint8_t)(pInV[1] >> iShift);
      pOutC += 16;
    }
  }
}

/****************************************************************************/
void I2AL_To_T628(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y010_To_T608(pSrc, pDst);

  // Chroma
  Chroma_I2XL_To_T628(pSrc, pDst, 10);
}

/****************************************************************************/
void I2CL_To_T628(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y012_To_T608(pSrc, pDst);

  // Chroma
  Chroma_I2XL_To_T628(pSrc, pDst, 12);
}

/****************************************************************************/
void P210_To_T628(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // Luma
  Y010_To_T608(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  tDim.iWidth = ((tDim.iWidth + 1) >> 1) << 1;
  Plane_Tile_T64<uint16_t, uint8_t>(pSrc, pDst, 10, 8, AL_PLANE_UV, tDim);
}

/****************************************************************************/
static void NVXX_To_I4XX(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uHrzCScale, uint8_t uVrtCScale)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  // Luma
  CopyPixMapPlane(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, 8);

  // Chroma
  auto const iPitchSrc = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_UV);
  auto const iPitchDstU = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_U);
  auto const iPitchDstV = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_V);
  uint8_t* pBufInC = AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_UV);
  uint8_t* pBufOutU = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_U);
  uint8_t* pBufOutV = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_V);

  int iWidthC = (tDim.iWidth + uHrzCScale - 1) / uHrzCScale;
  int iHeightC = (tDim.iHeight + uVrtCScale - 1) / uVrtCScale;

  for(int iH = 0; iH < iHeightC; ++iH)
  {
    for(int iW = 0; iW < iWidthC; ++iW)
    {
      pBufOutU[iW] = pBufInC[iW << 1];
      pBufOutV[iW] = pBufInC[(iW << 1) + 1];
    }

    pBufInC += iPitchSrc;
    pBufOutU += iPitchDstU;
    pBufOutV += iPitchDstV;
  }
}

/****************************************************************************/
void NV12_To_YV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  NV12_To_I420(pSrc, pDst);
}

/****************************************************************************/
void NV12_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  NVXX_To_I4XX(pSrc, pDst, 2, 2);
}

/****************************************************************************/
void NV16_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  NVXX_To_I4XX(pSrc, pDst, 2, 1);
}

/****************************************************************************/
void NV24_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  NVXX_To_I4XX(pSrc, pDst, 1, 1);
}

/****************************************************************************/
void NV12_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  NVXX_To_I4XX(pSrc, pDst, 2, 2);
}

/****************************************************************************/
static void NVXX_To_IXAL(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uHrzCScale, uint8_t uVrtCScale)
{
  // Luma
  Y800_To_Y010(pSrc, pDst);

  // Chroma
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  int iWidthC = (tDim.iWidth + uHrzCScale - 1) / uHrzCScale;
  int iHeightC = (tDim.iHeight + uVrtCScale - 1) / uVrtCScale;

  int iPitchSrc = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_UV);
  int iPitchDstU = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_U) / sizeof(uint16_t);
  int iPitchDstV = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_V) / sizeof(uint16_t);

  auto pBufIn = AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_UV);
  auto pBufOutU = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_U);
  auto pBufOutV = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_V);

  for(int iH = 0; iH < iHeightC; ++iH)
  {
    for(int iW = 0; iW < iWidthC; ++iW)
    {
      pBufOutU[iW] = ((uint16_t)pBufIn[iW << 1]) << 2;
      pBufOutV[iW] = ((uint16_t)pBufIn[(iW << 1) + 1]) << 2;
    }

    pBufIn += iPitchSrc;
    pBufOutU += iPitchDstU;
    pBufOutV += iPitchDstV;
  }
}

/****************************************************************************/
void NV12_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  NVXX_To_IXAL(pSrc, pDst, 2, 2);
}

/****************************************************************************/
void NV16_To_I2AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  NVXX_To_IXAL(pSrc, pDst, 2, 1);
}

/****************************************************************************/
void NV24_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  NVXX_To_IXAL(pSrc, pDst, 1, 1);
}

/****************************************************************************/
static void NVXX_To_PX10(AL_TBuffer const* pSrc, AL_TBuffer* pDst, uint8_t uHrzCScale, uint8_t uVrtCScale)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  AL_PixMapBuffer_SetDimension(pDst, tDim);

  // Luma
  I420_To_Y010(pSrc, pDst);

  // Chroma
  auto pBufIn = AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_UV);
  auto pBufOut = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_UV);

  int iPitchSrc = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_UV);
  int iPitchDst = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_UV) / sizeof(uint16_t);

  int iWidthC = 2 * (tDim.iWidth + uHrzCScale - 1) / uHrzCScale;
  int iHeightC = (tDim.iHeight + uVrtCScale - 1) / uVrtCScale;

  for(int iH = 0; iH < iHeightC; ++iH)
  {
    for(int iW = 0; iW < iWidthC; ++iW)
      pBufOut[iW] = ((uint16_t)pBufIn[iW]) << 2;

    pBufIn += iPitchSrc;
    pBufOut += iPitchDst;
  }
}

/****************************************************************************/
void NV12_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  NVXX_To_PX10(pSrc, pDst, 2, 2);
}

/****************************************************************************/
void NV16_To_P210(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  NVXX_To_PX10(pSrc, pDst, 2, 1);
}

/****************************************************************************/
void NV24_To_P410(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  NVXX_To_PX10(pSrc, pDst, 1, 1);
}

/****************************************************************************/
void Y016_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  // Luma
  ConvertPixMapPlane<uint16_t, uint8_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_16B_TO_8B);
}

/****************************************************************************/
void Y016_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  // Luma
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_16B_TO_10B);
}

/****************************************************************************/
void Y016_To_Y012(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  // Luma
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_16B_TO_12B);
}

/****************************************************************************/
void P016_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo8b(pSrc, pDst, 2, 2, RND_16B_TO_8B);
}

/****************************************************************************/
void P016_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  PX1X_To_NVXX(pSrc, pDst, 2, 2, RND_16B_TO_8B);
}

/****************************************************************************/
void P016_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo1X(pSrc, pDst, 2, 2, RND_16B_TO_10B);
}

/****************************************************************************/
void P016_To_I0CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo1X(pSrc, pDst, 2, 2, RND_16B_TO_12B);
}

/****************************************************************************/
void P016_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  PX1X_To_PX1X(pSrc, pDst, 2, 2, RND_16B_TO_10B);
}

/****************************************************************************/
void P016_To_P210(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  PX1X_To_PX1X(pSrc, pDst, 2, 2, RND_16B_TO_10B);
}

/****************************************************************************/
void P216_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo8b(pSrc, pDst, 2, 1, RND_16B_TO_8B);
}

/****************************************************************************/
void P216_To_NV16(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  PX1X_To_NVXX(pSrc, pDst, 2, 1, RND_16B_TO_8B);
}

/****************************************************************************/
void P216_To_I2AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo1X(pSrc, pDst, 2, 1, RND_16B_TO_10B);
}

/****************************************************************************/
void P216_To_I2CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo1X(pSrc, pDst, 2, 1, RND_16B_TO_12B);
}

/****************************************************************************/
void P216_To_P210(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  PX1X_To_PX1X(pSrc, pDst, 2, 1, RND_16B_TO_10B);
}

/****************************************************************************/
void P216_To_P212(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  PX1X_To_PX1X(pSrc, pDst, 2, 1, RND_16B_TO_12B);
}

/****************************************************************************/
void Y416_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_16B_TO_10B);
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_U, tDim.iWidth, tDim.iHeight, RND_16B_TO_10B);
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_V, tDim.iWidth, tDim.iHeight, RND_16B_TO_10B);
}

/****************************************************************************/
void Y416_To_I4CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, RND_16B_TO_12B);
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_U, tDim.iWidth, tDim.iHeight, RND_16B_TO_12B);
  ConvertPixMapPlane<uint16_t, uint16_t>(pSrc, pDst, AL_PLANE_V, tDim.iWidth, tDim.iHeight, RND_16B_TO_12B);
}

void I0AL_To_P016(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXYL_To_PX1Y(pSrc, pDst, 2, 2, LSB_10B_TO_MSB_10B);
}

void I0CL_To_P016(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXYL_To_PX1Y(pSrc, pDst, 2, 2, LSB_12B_TO_MSB_12B);
}

void P010_To_P016(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  PX1X_To_PX1X(pSrc, pDst, 2, 2, LSB_10B_TO_MSB_10B);
}

void P012_To_P016(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  PX1X_To_PX1X(pSrc, pDst, 2, 2, LSB_12B_TO_MSB_12B);
}

void I2AL_To_P216(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXYL_To_PX1Y(pSrc, pDst, 2, 1, LSB_10B_TO_MSB_10B);
}

void I2CL_To_P216(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXYL_To_PX1Y(pSrc, pDst, 2, 1, LSB_12B_TO_MSB_12B);
}

void P210_To_P216(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  PX1X_To_PX1X(pSrc, pDst, 2, 1, LSB_10B_TO_MSB_10B);
}

void P212_To_P216(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  PX1X_To_PX1X(pSrc, pDst, 2, 1, LSB_12B_TO_MSB_12B);
}

void I4AL_To_Y416(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXYL_To_IXYL(pSrc, pDst, 1, 1, LSB_10B_TO_MSB_10B);
}

void I4CL_To_Y416(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  IXYL_To_IXYL(pSrc, pDst, 1, 1, LSB_12B_TO_MSB_12B);
}

void P410_To_Y416(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo1X(pSrc, pDst, 1, 1, LSB_10B_TO_MSB_10B);
}

void P412_To_Y416(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  SemiPlanarToPlanar_1XTo1X(pSrc, pDst, 1, 1, LSB_12B_TO_MSB_12B);
}

/****************************************************************************/
// Copy buffer without any planar conversion (semi-planar to semi_planar,
// planar to planar)
// Manage correctly the different chroma mode
bool CopyPixMapBuffer(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  TFourCC tFourCC = AL_PixMapBuffer_GetFourCC(pSrc);
  AL_TDimension tDim = AL_PixMapBuffer_GetDimension(pSrc);

  AL_TPicFormat tPicFormat;
  bool const bSuccess = AL_GetPicFormat(tFourCC, &tPicFormat);

  if(!bSuccess || tPicFormat.bCompressed)
    return false;

  AL_PixMapBuffer_SetDimension(pDst, tDim);

  if(tPicFormat.ePlaneMode == AL_PLANE_MODE_INTERLEAVED)
  {
    CopyPixMapPlane(pSrc, pDst, AL_PLANE_YUV, tDim.iWidth, tDim.iHeight, tPicFormat.uBitDepth);
    return true;
  }

  // Luma
  CopyPixMapPlane(pSrc, pDst, AL_PLANE_Y, tDim.iWidth, tDim.iHeight, tPicFormat.uBitDepth);

  // Chroma
  if(tPicFormat.eChromaMode == AL_CHROMA_MONO)
    return true;

  int iChromaWidth = tDim.iWidth;
  int iChromaHeight = tPicFormat.eChromaMode == AL_CHROMA_4_2_0 ? (tDim.iHeight + 1) / 2 : tDim.iHeight;

  if(tPicFormat.ePlaneMode == AL_PLANE_MODE_SEMIPLANAR)
  {
    if(tPicFormat.eChromaMode == AL_CHROMA_4_4_4)
      iChromaWidth *= 2;
    else
      iChromaWidth = ((iChromaWidth + 1) / 2) * 2;

    CopyPixMapPlane(pSrc, pDst, AL_PLANE_UV, iChromaWidth, iChromaHeight, tPicFormat.uBitDepth);
    return true;
  }

  if(tPicFormat.eChromaMode != AL_CHROMA_4_4_4)
    iChromaWidth = (iChromaWidth + 1) / 2;

  CopyPixMapPlane(pSrc, pDst, AL_PLANE_U, iChromaWidth, iChromaHeight, tPicFormat.uBitDepth);
  CopyPixMapPlane(pSrc, pDst, AL_PLANE_V, iChromaWidth, iChromaHeight, tPicFormat.uBitDepth);
  return true;
}

void AYUV_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // The AYUV format defined by microsoft is actually VUYA
  AL_TDimension dim = AL_PixMapBuffer_GetDimension(pSrc);
  uint32_t* pSrcWord = (uint32_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_YUV);
  int iSrcPitch = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_YUV) / sizeof(uint32_t);
  uint8_t* pDstY = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_Y);
  int iDstYPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_Y);
  uint8_t* pDstU = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_U);
  int iDstUPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_U);
  uint8_t* pDstV = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_V);
  int iDstVPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_V);

  for(int H = 0; H < dim.iHeight; H++)
  {
    for(int W = 0; W < dim.iWidth; W++)
    {
      uint32_t currentWord = pSrcWord[H * iSrcPitch + W];
      pDstY[H * iDstYPitch + W] = (currentWord >> 16) & 0xFF;
      pDstU[H * iDstUPitch + W] = (currentWord >> 8) & 0xFF;
      pDstV[H * iDstVPitch + W] = currentWord & 0xFF;
    }
  }
}

void AYUV_To_NV24(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  // The AYUV format defined by microsoft is actually VUYA
  AL_TDimension dim = AL_PixMapBuffer_GetDimension(pSrc);
  uint32_t* pSrcWord = (uint32_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_YUV);
  int iSrcPitch = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_YUV) / sizeof(uint32_t);
  uint8_t* pDstY = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_Y);
  int iDstYPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_Y);
  uint8_t* pDstUV = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_UV);
  int iDstUVPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_UV);

  for(int H = 0; H < dim.iHeight; H++)
  {
    for(int W = 0; W < dim.iWidth; W++)
    {
      uint32_t currentWord = pSrcWord[H * iSrcPitch + W];
      pDstY[H * iDstYPitch + W] = (currentWord >> 16) & 0xFF;
      pDstUV[H * iDstUVPitch + 2 * W] = (currentWord >> 8) & 0xFF;
      pDstUV[H * iDstUVPitch + 2 * W + 1] = currentWord & 0xFF;
    }
  }
}

void Y410_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension dim = AL_PixMapBuffer_GetDimension(pSrc);
  uint32_t* pSrcWord = (uint32_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_YUV);
  int iSrcPitch = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_YUV) / sizeof(uint32_t);
  uint16_t* pDstY = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_Y);
  int iDstYPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_Y) / sizeof(uint16_t);
  uint16_t* pDstU = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_U);
  int iDstUPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_U) / sizeof(uint16_t);
  uint16_t* pDstV = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_V);
  int iDstVPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_V) / sizeof(uint16_t);

  for(int H = 0; H < dim.iHeight; H++)
  {
    for(int W = 0; W < dim.iWidth; W++)
    {
      uint32_t currentWord = pSrcWord[H * iSrcPitch + W];
      pDstY[H * iDstYPitch + W] = (currentWord >> 10) & 0x3FF;
      pDstU[H * iDstUPitch + W] = currentWord & 0x3FF;
      pDstV[H * iDstVPitch + W] = (currentWord >> 20) & 0x3FF;
    }
  }
}

void Y4XX_To_I4XL(AL_TBuffer const* pSrc, AL_TBuffer* pDst, int iBitDepth, bool bIsMsb)
{
  AL_TDimension dim = AL_PixMapBuffer_GetDimension(pSrc);
  uint64_t* pSrcWord = (uint64_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_YUV);
  int iSrcPitch = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_YUV) / sizeof(uint64_t);
  uint16_t* pDstY = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_Y);
  int iDstYPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_Y) / sizeof(uint16_t);
  uint16_t* pDstU = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_U);
  int iDstUPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_U) / sizeof(uint16_t);
  uint16_t* pDstV = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_V);
  int iDstVPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_V) / sizeof(uint16_t);
  int iShift = 0;

  if(bIsMsb)
    iShift = 16 - iBitDepth;

  for(int H = 0; H < dim.iHeight; H++)
  {
    for(int W = 0; W < dim.iWidth; W++)
    {
      uint16_t* currentWord = (uint16_t*)&pSrcWord[H * iSrcPitch + W];
      pDstY[H * iDstYPitch + W] = currentWord[1] >> iShift;
      pDstU[H * iDstUPitch + W] = currentWord[0] >> iShift;
      pDstV[H * iDstVPitch + W] = currentWord[2] >> iShift;
    }
  }
}

void Y4AL_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  Y4XX_To_I4XL(pSrc, pDst, 10, false);
}

void Y4AM_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  Y4XX_To_I4XL(pSrc, pDst, 10, true);
}

void Y4CL_To_I4CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  Y4XX_To_I4XL(pSrc, pDst, 12, false);
}

void Y4CM_To_I4CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  Y4XX_To_I4XL(pSrc, pDst, 12, true);
}

void RGB3_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  CopyPixMapBuffer(pSrc, pDst);
}

void ARGB_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AYUV_To_I444(pSrc, pDst);
}

void AB30_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension dim = AL_PixMapBuffer_GetDimension(pSrc);
  uint32_t* pSrcWord = (uint32_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_YUV);
  int iSrcPitch = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_YUV) / sizeof(uint32_t);
  uint16_t* pDstY = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_Y);
  int iDstYPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_Y) / sizeof(uint16_t);
  uint16_t* pDstU = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_U);
  int iDstUPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_U) / sizeof(uint16_t);
  uint16_t* pDstV = (uint16_t*)AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_V);
  int iDstVPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_V) / sizeof(uint16_t);

  for(int H = 0; H < dim.iHeight; H++)
  {
    for(int W = 0; W < dim.iWidth; W++)
    {
      uint32_t currentWord = pSrcWord[H * iSrcPitch + W];
      pDstY[H * iDstYPitch + W] = currentWord & 0x3FF;
      pDstU[H * iDstUPitch + W] = (currentWord >> 10) & 0x3FF;
      pDstV[H * iDstVPitch + W] = (currentWord >> 20) & 0x3FF;
    }
  }
}

void UYVY_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  AL_TDimension dim = AL_PixMapBuffer_GetDimension(pSrc);
  uint32_t* pSrcWord = (uint32_t*)AL_PixMapBuffer_GetPlaneAddress(pSrc, AL_PLANE_YUV);
  int iSrcPitch = AL_PixMapBuffer_GetPlanePitch(pSrc, AL_PLANE_YUV) / sizeof(uint32_t);
  uint8_t* pDstY = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_Y);
  int iDstYPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_Y);
  uint8_t* pDstU = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_U);
  int iDstUPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_U);
  uint8_t* pDstV = AL_PixMapBuffer_GetPlaneAddress(pDst, AL_PLANE_V);
  int iDstVPitch = AL_PixMapBuffer_GetPlanePitch(pDst, AL_PLANE_V);

  for(int H = 0; H < dim.iHeight; H++)
  {
    for(int W = 0; W < dim.iWidth / 2; W++)
    {
      uint8_t* currentWord = (uint8_t*)&pSrcWord[H * iSrcPitch + W];
      pDstU[H * iDstUPitch + W] = currentWord[0];
      pDstY[H * iDstYPitch + 2 * W] = currentWord[1];
      pDstV[H * iDstVPitch + W] = currentWord[2];
      pDstY[H * iDstYPitch + 2 * W + 1] = currentWord[3];
    }
  }
}

struct sFourCCToConvFunc
{
  TFourCC tOutFourCC;
  tConvFourCCFunc tFunc;
};

static const sFourCCToConvFunc ConversionI0ALFuncArray[] =
{
  {
    FOURCC(I420), I0AL_To_I420
  },
  {
    FOURCC(IYUV), I0AL_To_IYUV
  },
  {
    FOURCC(NV12), I0AL_To_NV12
  },
  {
    FOURCC(P010), I0AL_To_P010
  },
  {
    FOURCC(Y010), I0AL_To_Y010
  },
  {
    FOURCC(Y800), I0AL_To_Y800
  },
  {
    FOURCC(T608), I0AL_To_T608
  },
  {
    FOURCC(T60A), I0AL_To_T60A
  },
  {
    FOURCC(T6mA), I0AL_To_T6mA
  },
  {
    FOURCC(T60C), I0AL_To_T60C
  },
};

static const sFourCCToConvFunc ConversionI0CLFuncArray[] =
{
  {
    FOURCC(P012), I0CL_To_P012
  },
  {
    FOURCC(Y012), I0CL_To_Y012
  },
  {
    FOURCC(T608), I0CL_To_T608
  },
  {
    FOURCC(T60C), I0CL_To_T60C
  },
  {
    FOURCC(T6mC), I0CL_To_T6mC
  },
};

static const sFourCCToConvFunc ConversionI2ALFuncArray[] =
{
  {
    FOURCC(NV16), I2AL_To_NV16
  },
  {
    FOURCC(P210), I2AL_To_P210
  },
  {
    FOURCC(T628), I2AL_To_T628
  },
  {
    FOURCC(T62A), I2AL_To_T62A
  },
  {
    FOURCC(T62C), I2AL_To_T62C
  },
};

static const sFourCCToConvFunc ConversionI2CLFuncArray[] =
{
  {
    FOURCC(P212), I2CL_To_P212
  },
  {
    FOURCC(T628), I2CL_To_T628
  },
  {
    FOURCC(T62C), I2CL_To_T62C
  },
};

static const sFourCCToConvFunc ConversionI420FuncArray[] =
{
  {
    FOURCC(I0AL), I420_To_I0AL
  },
  {
    FOURCC(IYUV), I420_To_IYUV
  },
  {
    FOURCC(NV12), I420_To_NV12
  },
  {
    FOURCC(P010), I420_To_P010
  },
  {
    FOURCC(P010), I420_To_P012
  },
  {
    FOURCC(Y010), I420_To_Y010
  },
  {
    FOURCC(Y800), I420_To_Y800
  },
  {
    FOURCC(YV12), I420_To_YV12
  },
  {
    FOURCC(T608), I420_To_T608
  },
  {
    FOURCC(T60A), I420_To_T60A
  },
  {
    FOURCC(T60C), I420_To_T60C
  },
  {
    FOURCC(T6m8), I420_To_T6m8
  },
};

static const sFourCCToConvFunc ConversionI422FuncArray[] =
{
  {
    FOURCC(NV16), I422_To_NV16
  },
  {
    FOURCC(P210), I422_To_P210
  },
  {
    FOURCC(P212), I422_To_P212
  },
  {
    FOURCC(T628), I422_To_T628
  },
  {
    FOURCC(T62A), I422_To_T62A
  },
  {
    FOURCC(T62C), I422_To_T62C
  },
};

static const sFourCCToConvFunc ConversionI444FuncArray[] =
{
  {
    FOURCC(I4AL), I444_To_I4AL
  },
  {
    FOURCC(NV24), I444_To_NV24
  },
  {
    FOURCC(P410), I444_To_P410
  },
  {
    FOURCC(P412), I444_To_P412
  },
  {
    FOURCC(T648), I444_To_T648
  },
  {
    FOURCC(T64A), I444_To_T64A
  },
  {
    FOURCC(T64C), I444_To_T64C
  },
};

static const sFourCCToConvFunc ConversionI4ALFuncArray[] =
{
  {
    FOURCC(I444), I4AL_To_I444
  },
  {
    FOURCC(NV24), I4AL_To_NV24
  },
  {
    FOURCC(P410), I4AL_To_P410
  },
  {
    FOURCC(T648), I4AL_To_T648
  },
  {
    FOURCC(T64A), I4AL_To_T64A
  },
  {
    FOURCC(T64C), I4AL_To_T64C
  },
};

static const sFourCCToConvFunc ConversionI4CLFuncArray[] =
{
  {
    FOURCC(I444), I4CL_To_I444
  },
  {
    FOURCC(I4AL), I4CL_To_I4AL
  },
  {
    FOURCC(P412), I4CL_To_P412
  },
  {
    FOURCC(T64C), I4CL_To_T64C
  },
};

static const sFourCCToConvFunc ConversionIYUVFuncArray[] =
{
  {
    FOURCC(I0AL), IYUV_To_I0AL
  },
  {
    FOURCC(NV12), IYUV_To_NV12
  },
  {
    FOURCC(P010), IYUV_To_P010
  },
  {
    FOURCC(Y800), IYUV_To_Y800
  },
  {
    FOURCC(YV12), IYUV_To_YV12
  },
  {
    FOURCC(T608), IYUV_To_T608
  },
  {
    FOURCC(T60A), IYUV_To_T60A
  },
};

static const sFourCCToConvFunc ConversionNV12FuncArray[] =
{
  {
    FOURCC(I0AL), NV12_To_I0AL
  },
  {
    FOURCC(I420), NV12_To_I420
  },
  {
    FOURCC(IYUV), NV12_To_IYUV
  },
  {
    FOURCC(P010), NV12_To_P010
  },
  {
    FOURCC(Y800), NV12_To_Y800
  },
  {
    FOURCC(YV12), NV12_To_YV12
  },
  {
    FOURCC(T608), NV12_To_T608
  },
  {
    FOURCC(T60A), NV12_To_T60A
  },
};

static const sFourCCToConvFunc ConversionNV16FuncArray[] =
{
  {
    FOURCC(I2AL), NV16_To_I2AL
  },
  {
    FOURCC(I422), NV16_To_I422
  },
  {
    FOURCC(P210), NV16_To_P210
  },
  {
    FOURCC(T628), NV16_To_T628
  },
  {
    FOURCC(T62A), NV16_To_T62A
  },
};

static const sFourCCToConvFunc ConversionNV24FuncArray[] =
{
  {
    FOURCC(I444), NV24_To_I444
  },
  {
    FOURCC(I4AL), NV24_To_I4AL
  },
  {
    FOURCC(P410), NV24_To_P410
  },
};

static const sFourCCToConvFunc ConversionP010FuncArray[] =
{
  {
    FOURCC(I0AL), P010_To_I0AL
  },
  {
    FOURCC(I420), P010_To_I420
  },
  {
    FOURCC(IYUV), P010_To_IYUV
  },
  {
    FOURCC(NV12), P010_To_NV12
  },
  {
    FOURCC(Y010), P010_To_Y010
  },
  {
    FOURCC(Y800), P010_To_Y800
  },
  {
    FOURCC(YV12), P010_To_YV12
  },
  {
    FOURCC(T608), P010_To_T608
  },
  {
    FOURCC(T60A), P010_To_T60A
  },
};

static const sFourCCToConvFunc ConversionP012FuncArray[] =
{
  {
    FOURCC(I0AL), P012_To_I0AL
  },
  {
    FOURCC(I0CL), P012_To_I0CL
  },
  {
    FOURCC(I420), P012_To_I420
  },
  {
    FOURCC(Y012), P012_To_Y012
  },
};

static const sFourCCToConvFunc ConversionP210FuncArray[] =
{
  {
    FOURCC(I2AL), P210_To_I2AL
  },
  {
    FOURCC(I422), P210_To_I422
  },
  {
    FOURCC(T628), P210_To_T628
  },
  {
    FOURCC(T62A), P210_To_T62A
  },
};

static const sFourCCToConvFunc ConversionP212FuncArray[] =
{
  {
    FOURCC(I2AL), P212_To_I2AL
  },
  {
    FOURCC(I2CL), P212_To_I2CL
  },
  {
    FOURCC(I422), P212_To_I422
  },
  {
    FOURCC(T62C), P212_To_T62C
  },
};

static const sFourCCToConvFunc ConversionT608FuncArray[] =
{
  {
    FOURCC(I0AL), T608_To_I0AL
  },
  {
    FOURCC(I0CL), T608_To_I0CL
  },
  {
    FOURCC(I420), T608_To_I420
  },
  {
    FOURCC(IYUV), T608_To_IYUV
  },
  {
    FOURCC(NV12), T608_To_NV12
  },
  {
    FOURCC(P010), T608_To_P010
  },
  {
    FOURCC(Y010), T608_To_Y010
  },
  {
    FOURCC(Y800), T608_To_Y800
  },
  {
    FOURCC(YV12), T608_To_YV12
  },
};

static const sFourCCToConvFunc ConversionT60AFuncArray[] =
{
  {
    FOURCC(I0AL), T60A_To_I0AL
  },
  {
    FOURCC(I420), T60A_To_I420
  },
  {
    FOURCC(IYUV), T60A_To_IYUV
  },
  {
    FOURCC(NV12), T60A_To_NV12
  },
  {
    FOURCC(P010), T60A_To_P010
  },
  {
    FOURCC(Y010), T60A_To_Y010
  },
  {
    FOURCC(Y800), T60A_To_Y800
  },
  {
    FOURCC(YV12), T60A_To_YV12
  },
};

static const sFourCCToConvFunc ConversionT60CFuncArray[] =
{
  {
    FOURCC(I0AL), T60C_To_I0AL
  },
  {
    FOURCC(I0CL), T60C_To_I0CL
  },
  {
    FOURCC(I420), T60C_To_I420
  },
  {
    FOURCC(Y010), T60C_To_Y010
  },
  {
    FOURCC(Y012), T60C_To_Y012
  },
  {
    FOURCC(Y800), T60C_To_Y800
  },
};

static const sFourCCToConvFunc ConversionT628FuncArray[] =
{
  {
    FOURCC(I2AL), T628_To_I2AL
  },
  {
    FOURCC(I2CL), T628_To_I2CL
  },
  {
    FOURCC(I422), T628_To_I422
  },
  {
    FOURCC(NV16), T628_To_NV16
  },
  {
    FOURCC(P210), T628_To_P210
  },
  {
    FOURCC(Y010), T628_To_Y010
  },
  {
    FOURCC(Y800), T628_To_Y800
  },
};

static const sFourCCToConvFunc ConversionT62AFuncArray[] =
{
  {
    FOURCC(I2AL), T62A_To_I2AL
  },
  {
    FOURCC(I422), T62A_To_I422
  },
  {
    FOURCC(NV16), T62A_To_NV16
  },
  {
    FOURCC(P210), T62A_To_P210
  },
  {
    FOURCC(Y010), T62A_To_Y010
  },
  {
    FOURCC(Y800), T62A_To_Y800
  },
};

static const sFourCCToConvFunc ConversionT62CFuncArray[] =
{
  {
    FOURCC(I2AL), T62C_To_I2AL
  },
  {
    FOURCC(I2CL), T62C_To_I2CL
  },
  {
    FOURCC(I422), T62C_To_I422
  },
  {
    FOURCC(P212), T62C_To_P212
  },
  {
    FOURCC(Y012), T62C_To_Y012
  },
  {
    FOURCC(Y800), T62C_To_Y800
  },
};

static const sFourCCToConvFunc ConversionT648FuncArray[] =
{
  {
    FOURCC(I444), T648_To_I444
  },
  {
    FOURCC(I4AL), T648_To_I4AL
  },
};

static const sFourCCToConvFunc ConversionT64AFuncArray[] =
{
  {
    FOURCC(I444), T64A_To_I444
  },
  {
    FOURCC(I4AL), T64A_To_I4AL
  },
};

static const sFourCCToConvFunc ConversionT64CFuncArray[] =
{
  {
    FOURCC(I444), T64C_To_I444
  },
  {
    FOURCC(I4AL), T64C_To_I4AL
  },
  {
    FOURCC(I4CL), T64C_To_I4CL
  },
};

static const sFourCCToConvFunc ConversionY010FuncArray[] =
{
  {
    FOURCC(T608), Y010_To_T608
  },
  {
    FOURCC(T6mA), Y010_To_T6mA
  },
  {
    FOURCC(T60A), Y010_To_T60A
  },
  {
    FOURCC(T60C), Y010_To_T60C
  },
  {
    FOURCC(T628), Y010_To_T628
  },
  {
    FOURCC(T62A), Y010_To_T62A
  },
};

static const sFourCCToConvFunc ConversionY012FuncArray[] =
{
  {
    FOURCC(Y010), Y012_To_Y010
  },
  {
    FOURCC(Y800), Y012_To_Y800
  },
  {
    FOURCC(T608), Y012_To_T608
  },
  {
    FOURCC(T6mC), Y012_To_T6mC
  },
  {
    FOURCC(T60C), Y012_To_T60C
  },
  {
    FOURCC(T62C), Y012_To_T62C
  },
  {
    FOURCC(T6mC), Y012_To_T6mC
  },
};

static const sFourCCToConvFunc ConversionY800FuncArray[] =
{
  {
    FOURCC(I0AL), Y800_To_I0AL
  },
  {
    FOURCC(I420), Y800_To_I420
  },
  {
    FOURCC(IYUV), Y800_To_IYUV
  },
  {
    FOURCC(NV12), Y800_To_NV12
  },
  {
    FOURCC(P010), Y800_To_P010
  },
  {
    FOURCC(Y010), Y800_To_Y010
  },
  {
    FOURCC(YV12), Y800_To_YV12
  },
  {
    FOURCC(T6m8), Y800_To_T6m8
  },
  {
    FOURCC(T608), Y800_To_T608
  },
  {
    FOURCC(T60A), Y800_To_T60A
  },
  {
    FOURCC(T60C), Y800_To_T60C
  },
  {
    FOURCC(T628), Y800_To_T628
  },
  {
    FOURCC(T62A), Y800_To_T62A
  },
  {
    FOURCC(T62C), Y800_To_T62C
  },
};

static const sFourCCToConvFunc ConversionYV12FuncArray[] =
{
  {
    FOURCC(I0AL), YV12_To_I0AL
  },
  {
    FOURCC(I420), YV12_To_I420
  },
  {
    FOURCC(IYUV), YV12_To_IYUV
  },
  {
    FOURCC(NV12), YV12_To_NV12
  },
  {
    FOURCC(P010), YV12_To_P010
  },
  {
    FOURCC(Y800), YV12_To_Y800
  },
  {
    FOURCC(T608), YV12_To_T608
  },
  {
    FOURCC(T60A), YV12_To_T60A
  },
};

static const sFourCCToConvFunc ConversionT6m8FuncArray[] =
{
  {
    FOURCC(Y800), T608_To_Y800
  },
  {
    FOURCC(Y010), T608_To_Y010
  },
  {
    FOURCC(Y012), T608_To_Y012
  },
  {
    FOURCC(I420), T6m8_To_I420
  },
};

static const sFourCCToConvFunc ConversionT6mAFuncArray[] =
{
  {
    FOURCC(Y800), T60A_To_Y800
  },
  {
    FOURCC(Y010), T60A_To_Y010
  },
};

static const sFourCCToConvFunc ConversionT6mCFuncArray[] =
{
  {
    FOURCC(Y012), T60C_To_Y012
  },
};

static const sFourCCToConvFunc ConversionY016FuncArray[] =
{
  {
    FOURCC(Y800), Y016_To_Y800
  },
  {
    FOURCC(Y010), Y016_To_Y010
  },
  {
    FOURCC(Y012), Y016_To_Y012
  },
};

static const sFourCCToConvFunc ConversionP016FuncArray[] =
{
  {
    FOURCC(Y800), Y016_To_Y800
  },
  {
    FOURCC(Y010), Y016_To_Y010
  },
  {
    FOURCC(Y012), Y016_To_Y012
  },
  {
    FOURCC(I420), P016_To_I420
  },
  {
    FOURCC(I0AL), P016_To_I0AL
  },
  {
    FOURCC(I0CL), P016_To_I0CL
  },
  {
    FOURCC(NV12), P016_To_NV12
  },
};
static const sFourCCToConvFunc ConversionP216FuncArray[] =
{
  {
    FOURCC(I422), P216_To_I422
  },
  {
    FOURCC(I2AL), P216_To_I2AL
  },
  {
    FOURCC(I2CL), P216_To_I2CL
  },
  {
    FOURCC(NV16), P216_To_NV16
  },
};

static const sFourCCToConvFunc ConversionY416FuncArray[] =
{
  {
    FOURCC(I4AL), Y416_To_I4AL
  },
  {
    FOURCC(I4CL), Y416_To_I4CL
  },
};

static const sFourCCToConvFunc ConversionAYUVFuncArray[] =
{
  {
    FOURCC(I444), AYUV_To_I444
  },
  {
    FOURCC(NV24), AYUV_To_NV24
  },
};

static const sFourCCToConvFunc ConversionY410FuncArray[] =
{
  {
    FOURCC(I4AL), Y410_To_I4AL
  },
};

static const sFourCCToConvFunc ConversionY4ALFuncArray[] =
{
  {
    FOURCC(I4AL), Y4AL_To_I4AL
  },
};

static const sFourCCToConvFunc ConversionY4AMFuncArray[] =
{
  {
    FOURCC(I4AL), Y4AM_To_I4AL
  },
};

static const sFourCCToConvFunc ConversionY4CLFuncArray[] =
{
  {
    FOURCC(I4CL), Y4CL_To_I4CL
  },
};

static const sFourCCToConvFunc ConversionY4CMFuncArray[] =
{
  {
    FOURCC(I4CL), Y4CM_To_I4CL
  },
};

static const sFourCCToConvFunc ConversionRGB3FuncArray[] =
{
  {
    FOURCC(I444), RGB3_To_I444
  },
};

static const sFourCCToConvFunc ConversionARGBFuncArray[] =
{
  {
    FOURCC(I444), ARGB_To_I444
  },
};

static const sFourCCToConvFunc ConversionAB30FuncArray[] =
{
  {
    FOURCC(I4AL), AB30_To_I4AL
  },
};

static const sFourCCToConvFunc ConversionUYVYFuncArray[] =
{
  {
    FOURCC(I422), UYVY_To_I422
  },
};

#define CONV_FOURCC_ARRAY(array) array, ARRAY_SIZE(array)

struct sConvFourCCArray
{
  TFourCC tInFourCC;
  const sFourCCToConvFunc* array;
  unsigned int array_size;
};

static const sConvFourCCArray ConvMatchArray[] =
{
  { FOURCC(I0AL), CONV_FOURCC_ARRAY(ConversionI0ALFuncArray) },
  { FOURCC(I0CL), CONV_FOURCC_ARRAY(ConversionI0CLFuncArray) },
  { FOURCC(I2AL), CONV_FOURCC_ARRAY(ConversionI2ALFuncArray) },
  { FOURCC(I2CL), CONV_FOURCC_ARRAY(ConversionI2CLFuncArray) },
  { FOURCC(I420), CONV_FOURCC_ARRAY(ConversionI420FuncArray) },
  { FOURCC(I422), CONV_FOURCC_ARRAY(ConversionI422FuncArray) },
  { FOURCC(I444), CONV_FOURCC_ARRAY(ConversionI444FuncArray) },
  { FOURCC(I4AL), CONV_FOURCC_ARRAY(ConversionI4ALFuncArray) },
  { FOURCC(I4CL), CONV_FOURCC_ARRAY(ConversionI4CLFuncArray) },
  { FOURCC(IYUV), CONV_FOURCC_ARRAY(ConversionIYUVFuncArray) },
  { FOURCC(NV12), CONV_FOURCC_ARRAY(ConversionNV12FuncArray) },
  { FOURCC(NV16), CONV_FOURCC_ARRAY(ConversionNV16FuncArray) },
  { FOURCC(NV24), CONV_FOURCC_ARRAY(ConversionNV24FuncArray) },
  { FOURCC(P010), CONV_FOURCC_ARRAY(ConversionP010FuncArray) },
  { FOURCC(P012), CONV_FOURCC_ARRAY(ConversionP012FuncArray) },
  { FOURCC(P210), CONV_FOURCC_ARRAY(ConversionP210FuncArray) },
  { FOURCC(P212), CONV_FOURCC_ARRAY(ConversionP212FuncArray) },
  { FOURCC(T608), CONV_FOURCC_ARRAY(ConversionT608FuncArray) },
  { FOURCC(T60A), CONV_FOURCC_ARRAY(ConversionT60AFuncArray) },
  { FOURCC(T60C), CONV_FOURCC_ARRAY(ConversionT60CFuncArray) },
  { FOURCC(T628), CONV_FOURCC_ARRAY(ConversionT628FuncArray) },
  { FOURCC(T62A), CONV_FOURCC_ARRAY(ConversionT62AFuncArray) },
  { FOURCC(T62C), CONV_FOURCC_ARRAY(ConversionT62CFuncArray) },
  { FOURCC(T648), CONV_FOURCC_ARRAY(ConversionT648FuncArray) },
  { FOURCC(T64A), CONV_FOURCC_ARRAY(ConversionT64AFuncArray) },
  { FOURCC(T64C), CONV_FOURCC_ARRAY(ConversionT64CFuncArray) },
  { FOURCC(Y012), CONV_FOURCC_ARRAY(ConversionY012FuncArray) },
  { FOURCC(Y800), CONV_FOURCC_ARRAY(ConversionY800FuncArray) },
  { FOURCC(YV12), CONV_FOURCC_ARRAY(ConversionYV12FuncArray) },
  { FOURCC(T6m8), CONV_FOURCC_ARRAY(ConversionT6m8FuncArray) },
  { FOURCC(T6mA), CONV_FOURCC_ARRAY(ConversionT6mAFuncArray) },
  { FOURCC(T6mC), CONV_FOURCC_ARRAY(ConversionT6mCFuncArray) },
  { FOURCC(Y010), CONV_FOURCC_ARRAY(ConversionY010FuncArray) },
  { FOURCC(Y016), CONV_FOURCC_ARRAY(ConversionY016FuncArray) },
  { FOURCC(P016), CONV_FOURCC_ARRAY(ConversionP016FuncArray) },
  { FOURCC(P216), CONV_FOURCC_ARRAY(ConversionP216FuncArray) },
  { FOURCC(Y416), CONV_FOURCC_ARRAY(ConversionY416FuncArray) },
  { FOURCC(AYUV), CONV_FOURCC_ARRAY(ConversionAYUVFuncArray) },
  { FOURCC(Y410), CONV_FOURCC_ARRAY(ConversionY410FuncArray) },
  { FOURCC(Y4AL), CONV_FOURCC_ARRAY(ConversionY4ALFuncArray) },
  { FOURCC(Y4AM), CONV_FOURCC_ARRAY(ConversionY4AMFuncArray) },
  { FOURCC(Y4CL), CONV_FOURCC_ARRAY(ConversionY4CLFuncArray) },
  { FOURCC(Y4CM), CONV_FOURCC_ARRAY(ConversionY4CMFuncArray) },
  { FOURCC(UYVY), CONV_FOURCC_ARRAY(ConversionUYVYFuncArray) },
};

typedef union
{
  uint32_t uFourCC;
  struct
  {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
  }Value;
}tUnionFourCC;

static tConvFourCCFunc GetConversionOutFunction(sConvFourCCArray const* pMatchArray, TFourCC tOutFourCC)
{
  sFourCCToConvFunc const* pFourCCConv;

  for(unsigned int i = 0; i < pMatchArray->array_size; i++)
  {
    pFourCCConv = &pMatchArray->array[i];

    if(pFourCCConv->tOutFourCC == tOutFourCC)
      return pFourCCConv->tFunc;
  }

  return nullptr;
}

tConvFourCCFunc GetConvFourCCFunc(TFourCC tInFourCC, TFourCC tOutFourCC)
{
  sConvFourCCArray const* pMatchArray;

  if(tInFourCC == tOutFourCC)
  {
    AL_TPicFormat tPicFormat;
    bool bSuccess = AL_GetPicFormat(tInFourCC, &tPicFormat);

    if(!bSuccess || tPicFormat.bCompressed)
      return nullptr;

    if(AL_IsTiled(tInFourCC))
      return nullptr;

    return CopyPixMapBuffer;
  }

  auto const AdjustTileFourCC = [](TFourCC& tFourCC)
                                {
                                  tUnionFourCC sF;
                                  sF.uFourCC = tFourCC;

                                  /* T5XX FourCC are handled by T6XX function */
                                  if(sF.Value.a == 'T' && sF.Value.b == '5')
                                  {
                                    sF.Value.b = '6';
                                    tFourCC = sF.uFourCC;
                                  }
                                };

  AdjustTileFourCC(tInFourCC);
  AdjustTileFourCC(tOutFourCC);

  for(unsigned int i = 0; i < ARRAY_SIZE(ConvMatchArray); i++)
  {
    pMatchArray = &ConvMatchArray[i];

    if(pMatchArray->tInFourCC == tInFourCC)
      return GetConversionOutFunction(pMatchArray, tOutFourCC);
  }

  return nullptr;
}

int ConvertPixMapBuffer(AL_TBuffer const* pSrc, AL_TBuffer* pDst)
{
  TFourCC tInFourCC = AL_PixMapBuffer_GetFourCC(pSrc);
  TFourCC tOutFourCC = AL_PixMapBuffer_GetFourCC(pDst);
  tConvFourCCFunc tFunc;

  tFunc = GetConvFourCCFunc(tInFourCC, tOutFourCC);

  if(!tFunc)
    return 1;

  tFunc(pSrc, pDst);

  return 0;
}

/*@}*/
