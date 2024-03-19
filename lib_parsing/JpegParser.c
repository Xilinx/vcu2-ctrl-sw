// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "JpegParser.h"

#define HUFFMAN_DC_OFFSET 0
#define HUFFMAN_DC_SIZE 16
#define HUFFMAN_AC_OFFSET 16
#define HUFFMAN_AC_SIZE 240

#define HUFFMAN_TABLE_SIZE (HUFFMAN_DC_SIZE + HUFFMAN_AC_SIZE)

#define VALPTR_OFFSET 256

/*****************************************************************************/
static bool IsSliceData(EJpeg_Marker eMarker)
{
  return eMarker == SOS_MARKER;
}

/*****************************************************************************/
static bool IsFrameHeader(EJpeg_Marker eMarker)
{
  return (eMarker >= SOF0_MARKER && eMarker <= SOF3_MARKER) || (eMarker >= SOF9_MARKER && eMarker <= SOF11_MARKER);
}

/*****************************************************************************/
static bool IsBitdepthSupported(AL_TDecJpegParam* pJP)
{
  if(pJP->bitdepth == 8)
    return true;

  if(pJP->bitdepth == 10 && pJP->lossless)
    return true;

  if(pJP->bitdepth == 12)
    return true;

  return false;
}

/*****************************************************************************/
static bool ParseFrameHeader(AL_TDecJpegParam* pJP, AL_TRbspParser* pRP)
{
  pJP->bitdepth = u(pRP, 8);

  if(!IsBitdepthSupported(pJP))
    return false;

  pJP->picture_height = u(pRP, 16);
  pJP->picture_width = u(pRP, 16);

  int num_comp = u(pRP, 8);

  if(num_comp != 1 && num_comp != 3)
    return false;

  pJP->iID[0] = u(pRP, 8); // skip component identifier
  pJP->luma_hi = u(pRP, 4);
  pJP->luma_vi = u(pRP, 4);
  pJP->quant_tab_selectY = u(pRP, 8);

  for(int i = 1; i < num_comp; ++i)
  {
    pJP->iID[i] = u(pRP, 8); // skip component identifier
    pJP->chroma_hi = u(pRP, 4);
    pJP->chroma_vi = u(pRP, 4);
    pJP->quant_tab_selectC[i - 1] = u(pRP, 8);
  }

  if(num_comp == 1)
    pJP->chroma_mode = AL_CHROMA_MONO;
  else if((pJP->luma_vi == 2 * pJP->chroma_vi) && (pJP->luma_hi == 2 * pJP->chroma_hi))
    pJP->chroma_mode = AL_CHROMA_4_2_0;
  else if((pJP->luma_vi == pJP->chroma_vi) && (pJP->luma_hi == 2 * pJP->chroma_hi))
    pJP->chroma_mode = AL_CHROMA_4_2_2;
  else if((pJP->luma_vi == pJP->chroma_vi) && (pJP->luma_hi == pJP->chroma_hi))
    pJP->chroma_mode = AL_CHROMA_4_4_4;
  else
    return false;

  pJP->loadTable = 1;
  return true;
}

/*****************************************************************************/
static bool ParseScanHeader(AL_TDecJpegParam* pJP, AL_TRbspParser* pRP)
{
  int num_comp = u(pRP, 8);

  for(int i = 0; i < num_comp; ++i)
  {
    int iID = u(pRP, 8);

    if(iID == pJP->iID[0])
    {
      pJP->huffman_tab_select_dc_Y = u(pRP, 4);
      pJP->huffman_tab_select_ac_Y = u(pRP, 4);
    }
    else if(iID == pJP->iID[1])
    {
      pJP->huffman_tab_select_dc_U = u(pRP, 4);
      pJP->huffman_tab_select_ac_U = u(pRP, 4);
    }
    else if(iID == pJP->iID[2])
    {
      pJP->huffman_tab_select_dc_V = u(pRP, 4);
      pJP->huffman_tab_select_ac_V = u(pRP, 4);
    }
    else
      return false;
  }

  skip(pRP, 24); // skip ss, se, ah, al
  return true;
}

/*****************************************************************************/
static bool ParseQuantTable(AL_TRbspParser* pRP, TBuffer* pQuant, int segment_length)
{
  int iCurOffset = offset(pRP) >> 3;
  int iEndOffset = iCurOffset + segment_length;

  while(iCurOffset < iEndOffset)
  {
    int precision_flag = u(pRP, 4);

    if(precision_flag > 1)
      return false;

    quant_jpeg_t* pBuf = (quant_jpeg_t*)pQuant->tMD.pVirtualAddr;
    int iID = u(pRP, 4);
    pBuf += iID * AL_JPEG_NUM_QUANT_COEFF;

    Rtos_Memset(pBuf, 0, AL_JPEG_NUM_QUANT_COEFF);

    for(int i = 0; i < AL_JPEG_NUM_QUANT_COEFF; ++i)
      pBuf[i] = u(pRP, 8 << precision_flag);

    iCurOffset = offset(pRP) >> 3;
  }

  return true;
}

/*****************************************************************************/
static void ParseHuffmanTable(AL_TDecJpegParam* pJP, AL_TRbspParser* pRP, TBuffer* pHuff, int segment_length)
{
  int iCurOffset = offset(pRP) >> 3;
  int iEndOffset = iCurOffset + segment_length;

  while(iCurOffset < iEndOffset)
  {
    int IsACTable = u(pRP, 4);
    uint8_t* pBuf = pHuff->tMD.pVirtualAddr + (IsACTable ? HUFFMAN_AC_OFFSET : HUFFMAN_DC_OFFSET);

    int iID = u(pRP, 4);
    pBuf += iID * HUFFMAN_TABLE_SIZE;

    Rtos_Memset(pBuf, 0, IsACTable ? HUFFMAN_AC_SIZE : HUFFMAN_DC_SIZE);
    int iNumOffset = iID * 2 + IsACTable;

    for(int i = 0; i < 16; ++i)
      pJP->iNumHuff[iNumOffset][i] = u(pRP, 8);

    for(int i = 0; i < 16; ++i)
    {
      for(int j = 0; j < pJP->iNumHuff[iNumOffset][i]; ++j)
        *pBuf++ = u(pRP, 8);
    }

    iCurOffset = offset(pRP) >> 3;
  }
}

/*****************************************************************************/
static void BuildMinMaxTable(AL_TDecJpegParam* pJP, TBuffer* pMinMaxVal)
{
  uint16_t* pBufOutCode = (uint16_t*)pMinMaxVal->tMD.pVirtualAddr;
  uint8_t* pBufOutValPtr = pMinMaxVal->tMD.pVirtualAddr + VALPTR_OFFSET;

  for(int iTab = 0; iTab < 2; ++iTab)
  {
    for(int IsAC = 0; IsAC < 2; ++IsAC)
    {
      int iNumOffset = iTab * 2 + IsAC;
      int* pBITS = pJP->iNumHuff[iNumOffset];

      /* Figure C.1: make table of Huffman code length for each symbol */
      int p = 0;
      char huffsize[257];
      unsigned int huffcode[257];
      unsigned int code;

      for(int l = 1; l <= 16; l++)
      {
        int i = (int)pBITS[l - 1];

        while(i--)
          huffsize[p++] = (char)l;
      }

      huffsize[p] = 0;

      /* Figure C.2: generate the codes themselves */
      code = 0;
      int si = huffsize[0];
      p = 0;

      while(huffsize[p])
      {
        while(((int)huffsize[p]) == si)
        {
          huffcode[p++] = code;
          code++;
        }

        code <<= 1;
        si++;
      }

      int j = 0;

      for(int i = 0; i < 16; ++i)
      {
        if(pBITS[i] > 0)
        {
          *pBufOutValPtr++ = j;
          *pBufOutCode++ = huffcode[j];
          j += pBITS[i];
          *pBufOutCode++ = huffcode[j - 1];
        }
        else
        {
          *pBufOutValPtr++ = 0;
          *pBufOutCode++ = 0;
          *pBufOutCode++ = 0xFFFF;
        }
      }
    }
  }
}

static void ResetQuantTable(uint8_t* pBuf)
{
  uint32_t* pTmp = (uint32_t*)pBuf;
  uint32_t uSize = AL_JPEG_QUANT_BUF_SIZE / sizeof(uint32_t);

  while(uSize--)
    *pTmp++ = 0xBAADF00D;
}

/*****************************************************************************/
bool AL_JPEG_ParseHeaders(AL_TDecJpegParam* pJP, AL_TRbspParser* pRP, TBuffer* pQuant, TBuffer* pHuff, TBuffer* pMinMaxVal)
{
  EJpeg_Marker eMarker = UNKNOWN_MARKER;
  (void)pQuant;
  (void)pHuff;
  (void)pMinMaxVal;

  ResetQuantTable(pQuant->tMD.pVirtualAddr);

  while(!IsSliceData(eMarker) && get_avail_size(pRP) >= 32)
  {
    eMarker = u(pRP, 16);
    int segment_length = u(pRP, 16) - 2;
    switch(eMarker)
    {
    case SOS_MARKER:

      if(!ParseScanHeader(pJP, pRP))
        return false;
      break;

    case DQT_MARKER:

      if(!ParseQuantTable(pRP, pQuant, segment_length))
        return false;
      break;

    case DHT_MARKER:
      ParseHuffmanTable(pJP, pRP, pHuff, segment_length);
      break;

    case DRI_MARKER:
      pJP->restart_interval = u(pRP, 16);
      break;

    case DNL_MARKER:
      pJP->picture_height = u(pRP, 16);
      break;

    case SOF3_MARKER:
      pJP->lossless = true;
    // fallthrough

    default:

      if(IsFrameHeader(eMarker))
      {
        if(!ParseFrameHeader(pJP, pRP))
          return false;
      }
      else
        skip(pRP, segment_length * 8);
      break;
    }
  }

  BuildMinMaxTable(pJP, pMinMaxVal);
  return true;
}

