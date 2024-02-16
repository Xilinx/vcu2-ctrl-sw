// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <functional>

extern "C" {
#include "lib_common/BufferAPI.h"
#include "lib_common/FourCC.h"
}

void YV12_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void YV12_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void YV12_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void YV12_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void YV12_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void YV12_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void I420_To_YV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I420_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I420_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I420_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I420_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I420_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I420_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void I422_To_NV16(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I422_To_P210(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void I444_To_NV24(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I444_To_P410(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I444_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void IYUV_To_YV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void IYUV_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void IYUV_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void IYUV_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void IYUV_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void NV12_To_YV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void NV12_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void NV12_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void NV12_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void NV12_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void NV12_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void NV16_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void NV16_To_I2AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void NV16_To_P210(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void NV24_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void NV24_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void NV24_To_P410(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void Y800_To_YV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y800_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y800_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y800_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y800_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y800_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y800_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y012_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y012_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void P010_To_YV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P010_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P010_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P010_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P010_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P012_To_Y012(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P010_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P010_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P012_To_I0CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P212_To_I2CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P012_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P212_To_I2AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I4CL_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0CL_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0CL_To_Y012(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P012_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P212_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I4CL_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void P210_To_I2AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P210_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void I0AL_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0AL_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0AL_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0AL_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0AL_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0AL_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void I2AL_To_NV16(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I2AL_To_P210(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void I4AL_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I4AL_To_NV24(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I4AL_To_P410(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void I0CL_To_P012(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I2CL_To_P212(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I4CL_To_P412(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void T6m8_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void T608_To_YV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T608_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T608_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T608_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T608_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T608_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T608_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T608_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void T60A_To_YV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T60A_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T60A_To_IYUV(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T60A_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T60A_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T60A_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T60A_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T60A_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void T60C_To_Y012(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T60C_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T60C_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T60C_To_I0CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T60C_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T60C_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void T628_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T628_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T628_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T628_To_NV16(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T628_To_I2AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T628_To_P210(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void T62A_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T62A_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T62A_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T62A_To_NV16(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T62A_To_I2AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T62A_To_P210(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void T62C_To_I2AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T62C_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T62C_To_Y012(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T62C_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T62C_To_I2CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T62C_To_P212(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void T648_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T648_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void T64A_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T64A_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void T64C_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T64C_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void T64C_To_I4CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void Y800_To_T6m8(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I420_To_T6m8(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y010_To_T6mA(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0AL_To_T6mA(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y012_To_T6mC(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0CL_To_T6mC(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void Y010_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y010_To_T64C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y010_To_T6mA(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y012_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P010_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y800_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void NV12_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0AL_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0CL_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I420_To_T6m8(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y800_To_T6m8(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I420_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void IYUV_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void YV12_To_T608(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I420_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I420_To_T60C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void IYUV_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void YV12_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0AL_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0CL_To_T60C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0AL_To_T60C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y800_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y800_To_T60C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y010_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y010_To_T60C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y012_To_T60C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void NV12_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P010_To_T60A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y800_To_T62A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y800_To_T62C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y012_To_T62C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y012_To_T6mC(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y010_To_T62A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I2AL_To_T62A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I2CL_To_T62C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I2AL_To_T62C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I422_To_T62C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I422_To_T62A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void NV16_To_T62A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P210_To_T62A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P212_To_T62C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I444_To_T648(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I444_To_T64A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I4AL_To_T648(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I4AL_To_T64A(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I4CL_To_T64C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I4AL_To_T64C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I444_To_T64C(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y800_To_T628(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y010_To_T628(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I422_To_T628(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void NV16_To_T628(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I2AL_To_T628(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I2CL_To_T628(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P210_To_T628(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void Y016_To_Y800(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y016_To_Y010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y016_To_Y012(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P016_To_I420(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P016_To_NV12(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P016_To_I0AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P016_To_I0CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P016_To_P010(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P016_To_P012(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P216_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P216_To_NV16(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P216_To_I2AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P216_To_I2CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P216_To_P210(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P216_To_P212(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y416_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y416_To_I4CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0AL_To_P016(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I0CL_To_P016(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P010_To_P016(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P012_To_P016(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I2AL_To_P216(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I2CL_To_P216(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P210_To_P216(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P212_To_P216(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I4AL_To_Y416(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void I4CL_To_Y416(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P410_To_Y416(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void P412_To_Y416(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

void AYUV_To_I444(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void AYUV_To_NV24(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y410_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y4AL_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y4AM_To_I4AL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y4CL_To_I4CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void Y4CM_To_I4CL(AL_TBuffer const* pSrc, AL_TBuffer* pDst);
void UYVY_To_I422(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

/**************************************************************************//*!
   \brief Copy pixels from a source to a destination buffer having both
   the same FourCC. Format must not be 10bit-packed, tiled, or
   compressed.
   \param[in] pSrc Source buffer to copy
   \param[in] pDst Destination buffer with data copied from pSrc
   \return false in case of error, true on success.
******************************************************************************/
bool CopyPixMapBuffer(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

/**************************************************************************//*!
   \brief Convert data from a buffer to another.
   \param[in] pSrc Source buffer to convert
   \param[in] pDst Destination buffer with data converted from pSrc
   \return 1 in case of error, 0 on success.
******************************************************************************/
int ConvertPixMapBuffer(AL_TBuffer const* pSrc, AL_TBuffer* pDst);

typedef std::function<void (AL_TBuffer const*, AL_TBuffer*)> tConvFourCCFunc;

tConvFourCCFunc GetConvFourCCFunc(TFourCC tInFourCC, TFourCC tOutFourCC);
