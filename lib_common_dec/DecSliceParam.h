// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/******************************************************************************
   \addtogroup lib_base
   !@{
   \file
 *****************************************************************************/
#pragma once

#include "lib_common/SliceConsts.h"
#include "lib_common_dec/DecBuffersInternal.h"

/*****************************************************************************
   \brief Slice Parameters : Mimics structure for IP registers
*****************************************************************************/
typedef struct AL_TDecSliceParam
{
  uint8_t MaxMergeCand;
  uint8_t CabacInitIdc;
  uint8_t ColocFromL0;
  uint8_t mvd_l1_zero_flag;
  uint16_t SliceId;
  uint8_t NumRefIdxL1Minus1;
  uint8_t NumRefIdxL0Minus1;
  uint8_t WeightedPred;
  uint8_t WeightedBiPred;
  bool ValidConceal;
  uint8_t SliceHeaderLength;
  uint8_t TileNgbA;
  uint8_t TileNgbB;
  uint8_t TileNgbC;
  uint8_t TileNgbD;
  uint8_t TileNgbE;
  uint8_t TileNgbH;
  uint8_t TileNgbI;
  uint16_t NumEntryPoint;
  uint8_t PicIDL0[MAX_REF];
  uint8_t PicIDL1[MAX_REF];
  uint8_t ColocPicID;
  uint8_t ConcealPicID;

  int8_t CbQpOffset;
  int8_t CrQpOffset;
  int8_t SliceQP;
  int8_t tc_offset_div2;
  int8_t beta_offset_div2;

  uint16_t TileWidth;
  uint16_t TileHeight;
  uint16_t FirstTileLCU;
  uint16_t FirstLcuTileID;
  uint16_t LcuTileWidth;
  uint16_t LcuTileHeight;

  uint32_t SliceFirstLCU;
  uint32_t SliceNumLCU;

  uint32_t NextSliceSegment;
  uint32_t FirstLcuSliceSegment;
  uint32_t FirstLcuSlice;

  union
  {
    bool DirectSpatial;
    bool TemporalMVP;
  };
  bool bIsLastSlice;
  bool DependentSlice;
  bool SAOFilterChroma;
  bool SAOFilterLuma;
  bool DisableLoopFilter;
  bool XSliceLoopFilter;
  bool CuChromaQpOffset;
  bool NextIsDependent;
  bool Tile;

  AL_ESliceType eSliceType;
  uint32_t uStrAvailSize;
  uint32_t uCompOffset;
  uint32_t uStrOffset;
  uint32_t uParsingId;

  /* Keep this at last position of structure since it allows to copy only
   * necessary entry_point_offset content.
   */
  uint32_t entry_point_offset[AL_MAX_ENTRY_POINT + 1];
}AL_TDecSliceParam;

typedef struct AL_TDecJpegParam
{
  int picture_width;
  int picture_height;
  int8_t luma_hi;
  int8_t luma_vi;
  int8_t chroma_hi;
  int8_t chroma_vi;
  int8_t quant_tab_selectY;
  int8_t quant_tab_selectC[2];
  int8_t huffman_tab_select_dc_Y;
  int8_t huffman_tab_select_ac_Y;
  int8_t huffman_tab_select_dc_U;
  int8_t huffman_tab_select_ac_U;
  int8_t huffman_tab_select_dc_V;
  int8_t huffman_tab_select_ac_V;
  int iNumHuff[4][16];
  bool loadTable;
  int restart_interval;
  AL_EChromaMode chroma_mode;
  AL_TPicFormat tOutPicFormat;
  bool lossless;

  int iID[3];

  AL_64U UserParam;
  uint32_t FrmNum;
  uint32_t FrmID;
  uint8_t MvID;
  uint8_t bitdepth;
}AL_TDecJpegParam;

/*!@}*/
