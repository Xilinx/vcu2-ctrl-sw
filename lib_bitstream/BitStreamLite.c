// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "BitStreamLite.h"
#include "lib_rtos/lib_rtos.h"

/******************************************************************************/

void AL_BitStreamLite_Init(AL_TBitStreamLite* pBS, uint8_t* pBuf, int iMaxSize)
{
  pBS->pData = pBuf;
  pBS->iBitCount = 0;
  pBS->iMaxBits = iMaxSize * 8;
  pBS->isOverflow = false;
}

/******************************************************************************/
void AL_BitStreamLite_Deinit(AL_TBitStreamLite* pBS)
{
  pBS->pData = NULL;
  pBS->iBitCount = 0;
}

/******************************************************************************/
void AL_BitStreamLite_Reset(AL_TBitStreamLite* pBS)
{
  pBS->iBitCount = 0;
}

/******************************************************************************/
uint8_t* AL_BitStreamLite_GetData(AL_TBitStreamLite* pBS)
{
  return pBS->pData;
}

/******************************************************************************/
uint8_t* AL_BitStreamLite_GetCurData(AL_TBitStreamLite* pBS)
{
  return pBS->pData + (pBS->iBitCount / 8);
}

/******************************************************************************/
int AL_BitStreamLite_GetBitsCount(AL_TBitStreamLite* pBS)
{
  return pBS->iBitCount;
}

/******************************************************************************/
void AL_BitStreamLite_PutBit(AL_TBitStreamLite* pBS, uint8_t iBit)
{
  Rtos_Assert((iBit == 0) || (iBit == 1));
  AL_BitStreamLite_PutBits(pBS, 1, iBit);
}

/******************************************************************************/
void AL_BitStreamLite_AlignWithBits(AL_TBitStreamLite* pBS, uint8_t iBit)
{
  while(pBS->iBitCount % 8 != 0)
    AL_BitStreamLite_PutBit(pBS, iBit);
}

/******************************************************************************/
void AL_BitStreamLite_EndOfSEIPayload(AL_TBitStreamLite* pBS)
{
  uint8_t bitOffset = pBS->iBitCount % 8;

  if(bitOffset != 0)
  {
    AL_BitStreamLite_PutBits(pBS, 1, 1);
    AL_BitStreamLite_AlignWithBits(pBS, 0);
  }
}

static inline void writeData(AL_TBitStreamLite* pBS, uint8_t iNumBits, uint32_t uValue)
{
  uint32_t byteNum = pBS->iBitCount >> 3;
  uint8_t byteOffset = pBS->iBitCount & 7;

  Rtos_Assert(byteOffset + iNumBits <= 8);

  if(byteOffset == 0)
  {
    pBS->pData[byteNum] = uValue << (8 - iNumBits);
  }
  else
  {
    uint8_t bitsLeft = 8 - byteOffset;
    pBS->pData[byteNum] += uValue << (bitsLeft - iNumBits);
  }
}

/* Assume that iNumBits will be small enough to fit in current byte */
static void PutInByte(AL_TBitStreamLite* pBS, uint8_t iNumBits, uint32_t uValue)
{
  if(pBS->iBitCount + iNumBits <= pBS->iMaxBits)
    writeData(pBS, iNumBits, uValue);
  else
    pBS->isOverflow = true;
  pBS->iBitCount += iNumBits;
}

/******************************************************************************/
void AL_BitStreamLite_PutBits(AL_TBitStreamLite* pBS, uint8_t iNumBits, uint32_t uValue)
{
  Rtos_Assert(iNumBits == 32 || (uValue >> iNumBits) == 0);

  uint8_t numBitsToWrite = 8 - (pBS->iBitCount & 7);

  while(iNumBits > numBitsToWrite)
  {
    uint8_t byteValue = uValue >> (iNumBits - numBitsToWrite);
    PutInByte(pBS, numBitsToWrite, byteValue);
    uValue &= (0xffffffff >> numBitsToWrite);
    iNumBits -= numBitsToWrite;
    numBitsToWrite = 8 - (pBS->iBitCount & 7);
  }

  PutInByte(pBS, iNumBits, uValue);
}

void AL_BitStreamLite_SkipBits(AL_TBitStreamLite* pBS, int numBits)
{
  pBS->iBitCount += numBits;

  if(pBS->iBitCount > pBS->iMaxBits)
    pBS->isOverflow = true;
}

/******************************************************************************/
void AL_BitStreamLite_PutU(AL_TBitStreamLite* pBS, int iNumBits, uint32_t uValue)
{
  AL_BitStreamLite_PutBits(pBS, iNumBits, uValue);
}

/******************************************************************************/
void AL_BitStreamLite_PutI(AL_TBitStreamLite* pBS, int iNumBits, int32_t iValue)
{
  uint32_t uValue;

  if(iValue >= 0)
    uValue = iValue;
  else
  {
    uValue = -iValue;
    Rtos_Assert(iNumBits == 32 || ((uValue - 1) >> iNumBits) == 0);
    uValue = ~uValue + 1;

    if(iNumBits != 32)
    {
      uint32_t uMask = (1 << iNumBits) - 1;
      uValue &= uMask;
    }
  }

  AL_BitStreamLite_PutBits(pBS, iNumBits, uValue);
}

/******************************************************************************/
static void putVclBits(AL_TBitStreamLite* pBS, uint32_t uCodeLength, uint32_t uValue)
{
  if(uCodeLength == 1)
  {
    AL_BitStreamLite_PutU(pBS, 1, 1);
  }
  else
  {
    uint32_t uInfoLength = (uCodeLength - 1) / 2;
    int32_t iBits = uValue + 1 - (1 << uInfoLength);

    AL_BitStreamLite_PutBits(pBS, uInfoLength, 0);
    AL_BitStreamLite_PutBits(pBS, 1, 1);
    AL_BitStreamLite_PutBits(pBS, uInfoLength, iBits);
  }
}

#if defined(__ICL)
#define bit_scan_reverse _bit_scan_reverse
#elif defined(__GNUC__) || defined(__clang__)
static uint32_t bit_scan_reverse_clz(int32_t NN)
{
  // This function should never be called with a 0 value because __builtin_clz
  // result is undefined.
  Rtos_Assert(NN != 0);

  return 31 - __builtin_clz(NN);
}

#define bit_scan_reverse bit_scan_reverse_clz
#else
static uint32_t bit_scan_reverse_soft(int32_t NN)
{
  int32_t i = -1;

  while(NN)
  {
    NN >>= 1;
    i++;
  }

  return i;
}

#define bit_scan_reverse bit_scan_reverse_soft
#endif

/******************************************************************************/
// Writes one Exp-Golomb code to the bitstream.
// Automatically calculates the required code length.
void AL_BitStreamLite_PutUE(AL_TBitStreamLite* pBS, uint32_t uValue)
{
  // 1 - Compute code length.
  uint32_t uCodeLength = 1 + (bit_scan_reverse(uValue + 1) << 1);

  // 2 - Write code.
  putVclBits(pBS, uCodeLength, uValue);
}

/******************************************************************************/
void AL_BitStreamLite_PutSE(AL_TBitStreamLite* pBS, int32_t iValue)
{
  AL_BitStreamLite_PutUE(pBS, 2 * (iValue > 0 ? iValue : -iValue) - (iValue > 0));
}
