// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "lib_common/SliceConsts.h"
#include "lib_common/Utils.h"
#include "Reordering.h"

#define AL_MAX_NUM_FOLLOW_REF 8

/*************************************************************************//*!
   \brief Reference Picture information
*****************************************************************************/
typedef struct
{
  uint32_t eType; // ESliceType
  AL_EMarkingRef eRefMode; /*!< Freame reference mode */
  int32_t iPOC; /*!< Picture Order Count */
  int32_t iRefAPOC;
  int32_t iRefBPOC;
  uint8_t uRefIdx;
  AL_EPicStruct ePicStruct;
}AL_TRefParam;

typedef struct
{
  AL_TRefParam RefA; /*!< Specifies the picture reference mode used for reference A */
  AL_TRefParam RefB; /*!< Specifies the picture reference mode used for reference B */
  AL_TRefParam RefColoc; /*!< Specifies the picture reference mode used for the colocated reference */
  AL_TRefParam RefF[AL_MAX_NUM_FOLLOW_REF]; /*!< Specifies the picture reference mode used for the eventual following picture */

  uint8_t uNumRefIdxL0;
  uint8_t uNumRefIdxL1;

  bool bMergeLTL0; /*!< RefIdx0 L0 Picture Marking */
  bool bMergeLTL1; /*!< RefIdx0 L1 Picture Marking */

  int32_t iMMCORemovePicNum;
  bool bRmLT;

  bool bColocFromL0;
  bool bNoBackwardPredFlag;
  bool bRefColocL0Flag;
  bool bRefColocL0LTFlag;
  bool bRefColocL1LTFlag;
  AL_TReorder tReorder;
}AL_TRefInfo;

/*************************************************************************//*!
   \brief Available reference information
*****************************************************************************/
typedef struct AL_TRpsInfo
{
  // RPS
  int iNumShortTerm;                   /*!< Number of short term picture(s) in the DPB */
  int32_t pShortTermPOCs[AL_MAX_NUM_REF];  /*!< array of POC. on POC per the short term pictures in the DPB */

  int iNumFollow;                   /*!< Number of short term following picture(s) in the DPB */
  int32_t pFollowPOCs[AL_MAX_NUM_REF];  /*!< array of POC. on POC per the short term following pictures in the DPB */

  int iNumLongTerm;                    /*!< Number of long term picture(s) in the DPB */
  int32_t pLongTermPOCs[AL_MAX_NUM_REF];   /*!< array of POC. on POC per the long term pictures in the DPB */

}AL_TRpsInfo;

/*************************************************************************//*!
   \brief Available reference information
*****************************************************************************/
typedef struct AL_TAvailRef
{
  int iNumStRefPOCs; /*!< Number of Short Term Reference pictures available */
  int iNumLtRefPOCs; /*!< Number of Long Term Reference pictures available */
  int32_t pRefPOCs[2 * AL_MAX_NUM_REF]; /*!< POC list of the available reference picture(s) */
  AL_EMarkingRef eMarkingRef[2 * AL_MAX_NUM_REF]; /*!< Marking list of the available reference picture(s) */
  int32_t pType[2 * AL_MAX_NUM_REF]; /*!< Slice type of the available reference picture(s) */
}AL_TAvailRef;

