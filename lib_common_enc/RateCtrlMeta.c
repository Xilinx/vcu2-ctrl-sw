// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_common_enc/RateCtrlMeta.h"
#include "lib_rtos/lib_rtos.h"
#include "lib_common_enc/EncBuffersInternal.h"

static bool destroy(AL_TMetaData* pBaseMeta)
{
  AL_TRateCtrlMetaData* pMeta = (AL_TRateCtrlMetaData*)pBaseMeta;
  AL_Buffer_Unref(pMeta->pMVBuf);
  Rtos_Free(pMeta);
  return true;
}

static AL_TRateCtrlMetaData* create(AL_TAllocator* pAllocator, uint32_t uBufMVSize);

static AL_TMetaData* clone(AL_TMetaData* pBaseMeta)
{
  AL_TRateCtrlMetaData* pMeta = (AL_TRateCtrlMetaData*)pBaseMeta;
  AL_TRateCtrlMetaData* pNewMeta = create(pMeta->pMVBuf->pAllocator, AL_Buffer_GetSize(pMeta->pMVBuf));

  if(!pNewMeta)
    return false;

  pNewMeta->tRateCtrlStats = pMeta->tRateCtrlStats;

  Rtos_Memcpy(AL_Buffer_GetData(pNewMeta->pMVBuf), AL_Buffer_GetData(pMeta->pMVBuf), AL_Buffer_GetSize(pMeta->pMVBuf));

  return (AL_TMetaData*)pNewMeta;
}

static AL_TRateCtrlMetaData* create_with_buf(AL_TBuffer* pMVBuf)
{
  AL_TRateCtrlMetaData* pMeta = Rtos_Malloc(sizeof(AL_TRateCtrlMetaData));

  if(!pMeta)
    return NULL;

  pMeta->pMVBuf = pMVBuf;

  AL_Buffer_Ref(pMeta->pMVBuf);

  pMeta->tMeta.eType = AL_META_TYPE_RATECTRL;
  pMeta->tMeta.MetaDestroy = destroy;
  pMeta->tMeta.MetaClone = clone;

  pMeta->bFilled = false;

  return pMeta;
}

static AL_TRateCtrlMetaData* create(AL_TAllocator* pAllocator, uint32_t uBufMVSize)
{
  AL_TRateCtrlMetaData* pMeta;
  AL_TBuffer* pMVBuf;

  pMVBuf = AL_Buffer_Create_And_Allocate(pAllocator, uBufMVSize, &AL_Buffer_Destroy);

  if(!pMVBuf)
    return NULL;

  pMeta = create_with_buf(pMVBuf);

  if(!pMeta)
    AL_Buffer_Destroy(pMVBuf);

  return pMeta;
}

AL_TRateCtrlMetaData* AL_RateCtrlMetaData_Create(AL_TAllocator* pAllocator, AL_TDimension tDim, uint8_t uLog2MaxCuSize, AL_ECodec eCodec)
{
  uint32_t uSizeMV = AL_GetAllocSize_MV(tDim, uLog2MaxCuSize, eCodec) - MVBUFF_MV_OFFSET;
  return create(pAllocator, uSizeMV);
}

AL_TRateCtrlMetaData* AL_RateCtrlMetaData_Create_WithBuffer(AL_TBuffer* pMVBuf)
{
  return create_with_buf(pMVBuf);
}
