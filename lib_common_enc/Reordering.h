// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/****************************************************************************
   -----------------------------------------------------------------------------
 **************************************************************************//*!
   \addtogroup lib_base
   @{
   \file
 *****************************************************************************/
#pragma once

/*************************************************************************//*!
   \brief reference list reordering parameters
*****************************************************************************/
typedef struct AL_TReorderInfo
{
  uint16_t uModifIdc;
  uint16_t uAbsDiff;
}AL_TReorderInfo;

typedef AL_TReorderInfo AL_TReorderInfoList[AL_MAX_NUM_REF];

typedef struct
{
  bool bRefPicListModif;
  AL_TReorderInfoList tReorderList;
}AL_TReorder[2];

/****************************************************************************/
/*@}*/
