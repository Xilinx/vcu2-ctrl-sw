// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "lib_common_dec/DecSliceParam.h"
#include "lib_common_dec/RbspParser.h"

typedef enum
{
  UNKNOWN_MARKER = 0xFF00,
  SOF0_MARKER = 0xFFC0,
  SOF1_MARKER = 0xFFC1,
  SOF2_MARKER = 0xFFC2,
  SOF3_MARKER = 0xFFC3,
  DHT_MARKER = 0xFFC4,
  SOF5_MARKER = 0xFFC5,
  SOF6_MARKER = 0xFFC6,
  SOF7_MARKER = 0xFFC7,
  JPG_MARKER = 0xFFC8,
  SOF9_MARKER = 0xFFC9,
  SOF10_MARKER = 0xFFCA,
  SOF11_MARKER = 0xFFCB,
  DAC_MARKER = 0xFFCC,
  SOF13_MARKER = 0xFFCD,
  SOF14_MARKER = 0xFFCE,
  SOF15_MARKER = 0xFFCF,
  RST0_MARKER = 0xFFD0,
  RST1_MARKER = 0xFFD1,
  RST2_MARKER = 0xFFD2,
  RST3_MARKER = 0xFFD3,
  RST4_MARKER = 0xFFD4,
  RST5_MARKER = 0xFFD5,
  RST6_MARKER = 0xFFD6,
  RST7_MARKER = 0xFFD7,
  SOI_MARKER = 0xFFD8,
  EOI_MARKER = 0xFFD9,
  SOS_MARKER = 0xFFDA,
  DQT_MARKER = 0xFFDB,
  DNL_MARKER = 0xFFDC,
  DRI_MARKER = 0xFFDD,
  DHP_MARKER = 0xFFDE,
  EXP_MARKER = 0xFFDF,
  APP0_MARKER = 0xFFE0,
  APP1_MARKER = 0xFFE1,
  APP2_MARKER = 0xFFE2,
  APP3_MARKER = 0xFFE3,
  APP4_MARKER = 0xFFE4,
  APP5_MARKER = 0xFFE5,
  APP6_MARKER = 0xFFE6,
  APP7_MARKER = 0xFFE7,
  APP8_MARKER = 0xFFE8,
  APP9_MARKER = 0xFFE9,
  APP10_MARKER = 0xFFEA,
  APP11_MARKER = 0xFFEB,
  APP12_MARKER = 0xFFEC,
  APP13_MARKER = 0xFFED,
  APP14_MARKER = 0xFFEE,
  APP15_MARKER = 0xFFEF,
  JPG0_MARKER = 0xFFF0,
  JPG1_MARKER = 0xFFF1,
  JPG2_MARKER = 0xFFF2,
  JPG3_MARKER = 0xFFF3,
  JPG4_MARKER = 0xFFF4,
  JPG5_MARKER = 0xFFF5,
  JPG6_MARKER = 0xFFF6,
  JPG7_MARKER = 0xFFF7,
  JPG8_MARKER = 0xFFF8,
  JPG9_MARKER = 0xFFF9,
  JPG10_MARKER = 0xFFFA,
  JPG11_MARKER = 0xFFFB,
  JPG12_MARKER = 0xFFFC,
  JPG13_MARKER = 0xFFFD,
  COM_MARKER = 0xFFFE,
}EJpeg_Marker;

/*****************************************************************************/
static inline bool IsAppData(EJpeg_Marker eMarker)
{
  return eMarker >= APP0_MARKER && eMarker <= APP15_MARKER;
}

/*************************************************************************//*!
   \brief This function parses jpeg headers
   \param[out] pJP    Pointer to the header structure that will be filled
   \param[in]  pRP    Pointer to NAL buffer
   \param[out] pQuant Pointer to the buffer receiving the quantification values
   \param[out] pHuff  Pointer to the buffer receiving the huffman values
   \param[out] pMinMaxVal  Pointer to the buffer receiving the min/max huffman values
   \return return true if the current slice header is valid
   false otherwise
*****************************************************************************/
bool AL_JPEG_ParseHeaders(AL_TDecJpegParam* pJP, AL_TRbspParser* pRP, TBuffer* pQuant, TBuffer* pHuff, TBuffer* pMinMaxVal);

