// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "lib_common/BufCommonInternal.h"
#include "lib_common_enc/EncRecBuffer.h"
#include "lib_common/BufferAPI.h"
#include "EncEPBuffer.h"

/*****************************************************************************
   \brief Slice Buffers: Set of buffers needed to encode a slice
*****************************************************************************/
typedef struct t_Span
{
  uint8_t* pBuf;
  uint32_t uSize;
}TSpan;

typedef struct t_SliceBuffersEnc
{
  AL_TBuffer* pSrc; /*!< Pointer to Source frame buffer. */

  TSpan RefA[AL_PLANE_MAX_ENUM]; /*!< Pointer to frame buffers used as first reference picture.
                                    (Required only for P Slice encoding; Can be set to
                                    NULL for I Slice encoding) */
  TSpan RefB[AL_PLANE_MAX_ENUM]; /*!< Pointer to frame buffers used as second reference picture.
                                    (Required only for B slice or P Slice with 2 reference
                                    pictures. Can be set to NULL if not used) */
  TSpan Rec[AL_PLANE_MAX_ENUM]; /*!< Pointer to frame buffers that receives reconstructed slice. */
  TBufferMV Coloc; /*!< Pointer to co-located buffer. */
  TBufferMV MV; /*!< Pointer to MV buffer that contains valid POC List section
                   and that receives Motion Vectors of the encoded slice. */

  TBuffer CompData; /*!< Pointer to the intermediate compressed buffer */
  TBuffer CompMap; /*!< Pointer to the intermediate compressed mapping */

  TBuffer* pWPP; /*!< Pointer to Wavefront size buffer */
  TBufferEP* pEP1; /*!< Pointer to the lambdas & SclMtx buffer */
  TBufferEP* pEP2; /*!< Pointer to the QP table buffer */

  TBufferEP Hwrc[AL_ENC_NUM_CORES]; /*!< Pointer to the HwRcCtx buffers for each core */

  AL_TCircBuffer Stream;
}TSliceBuffersEnc;
