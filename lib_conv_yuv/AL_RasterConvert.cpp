// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_conv_yuv/AL_RasterConvert.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#include "lib_app/convert.h"

extern "C"
{
#include "lib_common/PixMapBuffer.h"
#include "lib_common_enc/IpEncFourCC.h"
}

using namespace std;

/*****************************************************************************/
CYuvSrcConv::CYuvSrcConv(TFrameInfo const& FrameInfo) :
  m_FrameInfo(FrameInfo)
{
}

/*****************************************************************************/
static string FourCCToString(TFourCC tFourCC)
{
  stringstream ss;
  ss << static_cast<char>(tFourCC & 0xFF) << static_cast<char>((tFourCC & 0xFF00) >> 8) << static_cast<char>((tFourCC & 0xFF0000) >> 16) << static_cast<char>((tFourCC & 0xFF000000) >> 24);
  return ss.str();
}

/*****************************************************************************/
static void NoConversionFound(TFourCC tInFourCC, TFourCC tOutFourCC)
{
  cout << "No conversion known from " << FourCCToString(tInFourCC) << " to " << FourCCToString(tOutFourCC) << endl;
  assert(0);
}

/*****************************************************************************/
static void convertToY010(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I0AL):
  case FOURCC(I2AL):
  case FOURCC(I4AL):
  case FOURCC(P010):
  case FOURCC(P210):
  case FOURCC(P410):
    return I0AL_To_Y010(pSrcIn, pSrcOut);
  case FOURCC(I420):
  case FOURCC(I422):
  case FOURCC(I444):
  case FOURCC(NV12):
  case FOURCC(NV16):
  case FOURCC(Y800):
    return Y800_To_Y010(pSrcIn, pSrcOut);
  default: return NoConversionFound(inFourCC, FOURCC(Y010));
  }
}

/*****************************************************************************/
static void convertToY012(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I0CL):
  case FOURCC(I2CL):
  case FOURCC(I4CL):
    return I0CL_To_Y012(pSrcIn, pSrcOut);
  default: return NoConversionFound(inFourCC, FOURCC(Y012));
  }
}

/*****************************************************************************/
static void convertToY800(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I0AL): return I0AL_To_Y800(pSrcIn, pSrcOut);
  case FOURCC(I420):
  case FOURCC(I422):
  case FOURCC(I444):
    return I420_To_Y800(pSrcIn, pSrcOut);
  default: return NoConversionFound(inFourCC, FOURCC(Y800));
  }
}

/*****************************************************************************/
static void convertToNV12(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(Y800): return Y800_To_NV12(pSrcIn, pSrcOut);
  case FOURCC(I420): return I420_To_NV12(pSrcIn, pSrcOut);
  case FOURCC(IYUV): return IYUV_To_NV12(pSrcIn, pSrcOut);
  case FOURCC(YV12): return YV12_To_NV12(pSrcIn, pSrcOut);
  case FOURCC(NV12): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  case FOURCC(P010): return P010_To_NV12(pSrcIn, pSrcOut);
  case FOURCC(I0AL): return I0AL_To_NV12(pSrcIn, pSrcOut);
  default: return NoConversionFound(inFourCC, FOURCC(NV12));
  }
}

/*****************************************************************************/
static void convertToNV16(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I422): return I422_To_NV16(pSrcIn, pSrcOut);
  case FOURCC(YV16): return I422_To_NV16(pSrcIn, pSrcOut);
  case FOURCC(NV16): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  case FOURCC(I2AL): return I2AL_To_NV16(pSrcIn, pSrcOut);
  default: return NoConversionFound(inFourCC, FOURCC(NV16));
  }
}

/*****************************************************************************/
static void convertToNV24(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I444): return I444_To_NV24(pSrcIn, pSrcOut);
  case FOURCC(I4AL): return I4AL_To_NV24(pSrcIn, pSrcOut);
  case FOURCC(NV24): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(NV24));
  }
}

/*****************************************************************************/
static void convertToP010(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(Y800): return Y800_To_P010(pSrcIn, pSrcOut);
  case FOURCC(I420): return I420_To_P010(pSrcIn, pSrcOut);
  case FOURCC(IYUV): return IYUV_To_P010(pSrcIn, pSrcOut);
  case FOURCC(YV12): return YV12_To_P010(pSrcIn, pSrcOut);
  case FOURCC(NV12): return NV12_To_P010(pSrcIn, pSrcOut);
  case FOURCC(P010): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  case FOURCC(I0AL): return I0AL_To_P010(pSrcIn, pSrcOut);
  default: return NoConversionFound(inFourCC, FOURCC(P010));
  }
}

/*****************************************************************************/
static void convertToP012(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(P012): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  case FOURCC(I0CL): return I0CL_To_P012(pSrcIn, pSrcOut);
  default: return NoConversionFound(inFourCC, FOURCC(P012));
  }
}

/*****************************************************************************/
static void convertToP210(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I422): return I422_To_P210(pSrcIn, pSrcOut);
  case FOURCC(YV16): return I422_To_P210(pSrcIn, pSrcOut);
  case FOURCC(P210): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  case FOURCC(I2AL): return I2AL_To_P210(pSrcIn, pSrcOut);
  case FOURCC(NV16): return NV16_To_P210(pSrcIn, pSrcOut);
  default: return NoConversionFound(inFourCC, FOURCC(P210));
  }
}

/*****************************************************************************/
static void convertToP212(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I2CL): return I2CL_To_P212(pSrcIn, pSrcOut);
  case FOURCC(P212): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(P212));
  }
}

/*****************************************************************************/
static void convertToP410(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(NV24): return NV24_To_P410(pSrcIn, pSrcOut);
  case FOURCC(I444): return I444_To_P410(pSrcIn, pSrcOut);
  case FOURCC(I4AL): return I4AL_To_P410(pSrcIn, pSrcOut);
  case FOURCC(P410): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(P410));
  }
}

/*****************************************************************************/
static void convertToP016(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I0AL): return I0AL_To_P016(pSrcIn, pSrcOut);
  case FOURCC(I0CL): return I0CL_To_P016(pSrcIn, pSrcOut);
  case FOURCC(P010): return P010_To_P016(pSrcIn, pSrcOut);
  case FOURCC(P012): return P012_To_P016(pSrcIn, pSrcOut);
  case FOURCC(P016): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(P016));
  }
}

/*****************************************************************************/
static void convertToP216(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I2AL): return I2AL_To_P216(pSrcIn, pSrcOut);
  case FOURCC(I2CL): return I2CL_To_P216(pSrcIn, pSrcOut);
  case FOURCC(P210): return P210_To_P216(pSrcIn, pSrcOut);
  case FOURCC(P212): return P212_To_P216(pSrcIn, pSrcOut);
  case FOURCC(P216): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(P216));
  }
}

/*****************************************************************************/
static void convertToY416(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I4AL): return I4AL_To_Y416(pSrcIn, pSrcOut);
  case FOURCC(I4CL): return I4CL_To_Y416(pSrcIn, pSrcOut);
  case FOURCC(P410): return P410_To_Y416(pSrcIn, pSrcOut);
  case FOURCC(P412): return P412_To_Y416(pSrcIn, pSrcOut);
  case FOURCC(Y416): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(Y416));
  }
}

/*****************************************************************************/
static void convertToT608(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I0AL): return I0AL_To_T608(pSrcIn, pSrcOut);
  case FOURCC(I0CL): return I0CL_To_T608(pSrcIn, pSrcOut);
  case FOURCC(I420): return I420_To_T608(pSrcIn, pSrcOut);
  case FOURCC(IYUV): return IYUV_To_T608(pSrcIn, pSrcOut);
  case FOURCC(NV12): return NV12_To_T608(pSrcIn, pSrcOut);
  case FOURCC(P010): return P010_To_T608(pSrcIn, pSrcOut);
  case FOURCC(Y010): return Y010_To_T608(pSrcIn, pSrcOut);
  case FOURCC(Y012): return Y012_To_T608(pSrcIn, pSrcOut);
  case FOURCC(Y800): return Y800_To_T608(pSrcIn, pSrcOut);
  case FOURCC(YV12): return YV12_To_T608(pSrcIn, pSrcOut);

  case FOURCC(T608): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(T608));
  }
}

/*****************************************************************************/
static void convertToT60A(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I0AL): return I0AL_To_T60A(pSrcIn, pSrcOut);
  case FOURCC(I420): return I420_To_T60A(pSrcIn, pSrcOut);
  case FOURCC(IYUV): return IYUV_To_T60A(pSrcIn, pSrcOut);
  case FOURCC(NV12): return NV12_To_T60A(pSrcIn, pSrcOut);
  case FOURCC(P010): return P010_To_T60A(pSrcIn, pSrcOut);
  case FOURCC(Y010): return Y010_To_T60A(pSrcIn, pSrcOut);
  case FOURCC(Y800): return Y800_To_T60A(pSrcIn, pSrcOut);
  case FOURCC(YV12): return YV12_To_T60A(pSrcIn, pSrcOut);

  case FOURCC(T60A): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(T60A));
  }
}

/*****************************************************************************/
static void convertToT60C(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I0AL): return I0AL_To_T60C(pSrcIn, pSrcOut);
  case FOURCC(I0CL): return I0CL_To_T60C(pSrcIn, pSrcOut);
  case FOURCC(I420): return I420_To_T60C(pSrcIn, pSrcOut);
  case FOURCC(Y010): return Y010_To_T60C(pSrcIn, pSrcOut);
  case FOURCC(Y012): return Y012_To_T60C(pSrcIn, pSrcOut);
  case FOURCC(Y800): return Y800_To_T60C(pSrcIn, pSrcOut);

  case FOURCC(T60C): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(T60C));
  }
}

/*****************************************************************************/
static void convertToT628(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I2AL): return I2AL_To_T628(pSrcIn, pSrcOut);
  case FOURCC(I2CL): return I2CL_To_T628(pSrcIn, pSrcOut);
  case FOURCC(I422): return I422_To_T628(pSrcIn, pSrcOut);
  case FOURCC(NV16): return NV16_To_T628(pSrcIn, pSrcOut);
  case FOURCC(P210): return P210_To_T628(pSrcIn, pSrcOut);
  case FOURCC(Y010): return Y010_To_T628(pSrcIn, pSrcOut);
  case FOURCC(Y800): return Y800_To_T628(pSrcIn, pSrcOut);

  case FOURCC(T628): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(T628));
  }
}

/*****************************************************************************/
static void convertToT62A(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I2AL): return I2AL_To_T62A(pSrcIn, pSrcOut);
  case FOURCC(I422): return I422_To_T62A(pSrcIn, pSrcOut);
  case FOURCC(NV16): return NV16_To_T62A(pSrcIn, pSrcOut);
  case FOURCC(P210): return P210_To_T62A(pSrcIn, pSrcOut);
  case FOURCC(Y010): return Y010_To_T62A(pSrcIn, pSrcOut);
  case FOURCC(Y800): return Y800_To_T62A(pSrcIn, pSrcOut);

  case FOURCC(T62A): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(T62A));
  }
}

/*****************************************************************************/
static void convertToT62C(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I2AL): return I2AL_To_T62C(pSrcIn, pSrcOut);
  case FOURCC(I2CL): return I2CL_To_T62C(pSrcIn, pSrcOut);
  case FOURCC(I422): return I422_To_T62C(pSrcIn, pSrcOut);
  case FOURCC(P212): return P212_To_T62C(pSrcIn, pSrcOut);
  case FOURCC(Y012): return Y012_To_T62C(pSrcIn, pSrcOut);
  case FOURCC(Y800): return Y800_To_T62C(pSrcIn, pSrcOut);

  case FOURCC(T62C): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(T62C));
  }
}

/*****************************************************************************/
static void convertToT648(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I444): return I444_To_T648(pSrcIn, pSrcOut);
  case FOURCC(I4AL): return I4AL_To_T648(pSrcIn, pSrcOut);

  case FOURCC(T648): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(T648));
  }
}

/*****************************************************************************/
static void convertToT64A(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I444): return I444_To_T64A(pSrcIn, pSrcOut);
  case FOURCC(I4AL): return I4AL_To_T64A(pSrcIn, pSrcOut);

  case FOURCC(T64A): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(T64A));
  }
}

/*****************************************************************************/
static void convertToT64C(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(I444): return I444_To_T64C(pSrcIn, pSrcOut);
  case FOURCC(I4AL): return I4AL_To_T64C(pSrcIn, pSrcOut);
  case FOURCC(I4CL): return I4CL_To_T64C(pSrcIn, pSrcOut);
  case FOURCC(Y010): return Y010_To_T64C(pSrcIn, pSrcOut);

  case FOURCC(T64C): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(T64C));
  }
}

/*****************************************************************************/
static void convertToT6m8(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(Y800):
  case FOURCC(I420):
  case FOURCC(I422):
  case FOURCC(I444):
    return Y800_To_T6m8(pSrcIn, pSrcOut);
  case FOURCC(T6m8): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(T6m8));
  }
}

/*****************************************************************************/
static void convertToT6mA(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(Y010):
  case FOURCC(I0AL):
  case FOURCC(I2AL):
  case FOURCC(I4AL):
    return Y010_To_T6mA(pSrcIn, pSrcOut);
  case FOURCC(T6mA): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(T6mA));
  }
}

/*****************************************************************************/
static void convertToT6mC(AL_TBuffer const* pSrcIn, TFourCC inFourCC, AL_TBuffer* pSrcOut)
{
  switch(inFourCC)
  {
  case FOURCC(Y012):
  case FOURCC(I0CL):
  case FOURCC(I2CL):
  case FOURCC(I4CL): return I0CL_To_T6mC(pSrcIn, pSrcOut);
  case FOURCC(T6mC): CopyPixMapBuffer(pSrcIn, pSrcOut);
    return;
  default: return NoConversionFound(inFourCC, FOURCC(T6mC));
  }
}

/*****************************************************************************/
void CYuvSrcConv::ConvertSrcBuf(uint8_t uBitDepth, AL_TBuffer const* pSrcIn, AL_TBuffer* pSrcOut)
{
  (void)uBitDepth;
  TFourCC tFourCCIn = AL_PixMapBuffer_GetFourCC(pSrcIn);
  TFourCC tSrcOutFourCC = AL_PixMapBuffer_GetFourCC(pSrcOut);
  switch(tSrcOutFourCC)
  {
  case FOURCC(Y800): return convertToY800(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(Y010): return convertToY010(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(Y012): return convertToY012(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(NV12): return convertToNV12(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(NV16): return convertToNV16(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(NV24): return convertToNV24(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(P010): return convertToP010(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(P012): return convertToP012(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(P210): return convertToP210(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(P212): return convertToP212(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(P410): return convertToP410(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(P016): return convertToP016(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(P216): return convertToP216(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(Y416): return convertToY416(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T608): return convertToT608(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T60A): return convertToT60A(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T60C): return convertToT60C(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T628): return convertToT628(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T62A): return convertToT62A(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T62C): return convertToT62C(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T648): return convertToT648(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T64A): return convertToT64A(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T64C): return convertToT64C(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T6m8): return convertToT6m8(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T6mA): return convertToT6mA(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T6mC): return convertToT6mC(pSrcIn, tFourCCIn, pSrcOut);

  case FOURCC(T508): return convertToT608(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T50A): return convertToT60A(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T50C): return convertToT60C(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T528): return convertToT628(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T52A): return convertToT62A(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T52C): return convertToT62C(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T548): return convertToT648(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T54A): return convertToT64A(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T54C): return convertToT64C(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T5m8): return convertToT6m8(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T5mA): return convertToT6mA(pSrcIn, tFourCCIn, pSrcOut);
  case FOURCC(T5mC): return convertToT6mC(pSrcIn, tFourCCIn, pSrcOut);

  default: return NoConversionFound(tFourCCIn, tSrcOutFourCC);
  }
}
