// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_common/BufferSeiMeta.h"
#include "lib_rtos/lib_rtos.h"

static bool destroy(AL_TMetaData* pMeta)
{
  AL_TSeiMetaData* pSeiMeta = (AL_TSeiMetaData*)pMeta;
  Rtos_Free(pSeiMeta->payload);
  Rtos_Free(pSeiMeta->pBuf);
  Rtos_Free(pSeiMeta);
  return true;
}

AL_TSeiMetaData* AL_SeiMetaData_Clone(AL_TSeiMetaData* pMeta)
{
  if(!pMeta)
    return NULL;

  AL_TSeiMetaData* pSeiMeta = AL_SeiMetaData_Create(pMeta->maxPayload, pMeta->maxBufSize);

  if(!pSeiMeta)
    return NULL;

  return pSeiMeta;
}

static AL_TMetaData* clone(AL_TMetaData* pMeta)
{
  return (AL_TMetaData*)AL_SeiMetaData_Clone((AL_TSeiMetaData*)pMeta);
}

AL_TSeiMetaData* AL_SeiMetaData_Create(uint8_t uMaxPayload, uint32_t uMaxBufSize)
{
  AL_TSeiMetaData* pMeta = (AL_TSeiMetaData*)Rtos_Malloc(sizeof(*pMeta));

  if(!pMeta)
    return NULL;

  pMeta->pBuf = (uint8_t*)Rtos_Malloc(uMaxBufSize * sizeof(*(pMeta->pBuf)));

  if(!pMeta->pBuf)
  {
    Rtos_Free(pMeta);
    return NULL;
  }

  pMeta->payload = (AL_TSeiMessage*)Rtos_Malloc(uMaxPayload * sizeof(*(pMeta->payload)));

  if(!pMeta->payload)
  {
    Rtos_Free(pMeta->pBuf);
    Rtos_Free(pMeta);
    return NULL;
  }

  pMeta->tMeta.eType = AL_META_TYPE_SEI;
  pMeta->tMeta.MetaDestroy = destroy;
  pMeta->tMeta.MetaClone = clone;
  pMeta->maxPayload = uMaxPayload;
  pMeta->maxBufSize = uMaxBufSize;
  AL_SeiMetaData_Reset(pMeta);

  return pMeta;
}

bool AL_SeiMetaData_AddPayload(AL_TSeiMetaData* pMeta, AL_TSeiMessage payload)
{
  if(pMeta->numPayload + 1 > pMeta->maxPayload)
    return false;

  AL_TSeiMessage* pCur = pMeta->payload + pMeta->numPayload;
  *pCur = payload;
  ++pMeta->numPayload;
  return true;
}

uint8_t* AL_SeiMetaData_GetBuffer(AL_TSeiMetaData* pMeta)
{
  if(pMeta->numPayload == 0)
    return pMeta->pBuf;

  AL_TSeiMessage* pLast = pMeta->payload + pMeta->numPayload - 1;
  return pLast->pData + pLast->size;
}

void AL_SeiMetaData_Reset(AL_TSeiMetaData* pMeta)
{
  pMeta->numPayload = 0;
  Rtos_Memset(pMeta->pBuf, 0, pMeta->maxBufSize);
}
