// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_rtos/lib_rtos.h"
#include "lib_common/BufferPixMapMeta.h"
#include "lib_common/BufCommon.h"

static bool SrcMeta_Destroy(AL_TMetaData* pMeta)
{
  Rtos_Free(pMeta);
  return true;
}

AL_TPixMapMetaData* AL_PixMapMetaData_Clone(AL_TPixMapMetaData* pMeta)
{
  if(!pMeta)
    return NULL;

  AL_TPixMapMetaData* pClone = AL_PixMapMetaData_CreateEmpty(pMeta->tFourCC);

  if(!pClone)
    return NULL;

  pClone->tDim = pMeta->tDim;

  for(int iPlane = 0; iPlane < AL_PLANE_MAX_ENUM; iPlane++)
    pClone->tPlanes[iPlane] = pMeta->tPlanes[iPlane];

  return pClone;
}

static AL_TMetaData* SrcMeta_Clone(AL_TMetaData* pMeta)
{
  return (AL_TMetaData*)AL_PixMapMetaData_Clone((AL_TPixMapMetaData*)pMeta);
}

bool AL_PixMapMetaData_AddPlane(AL_TPixMapMetaData* pMeta, AL_TPlane tPlane, AL_EPlaneId ePlaneId)
{
  AL_TPicFormat tPicFormat;
  bool const bSuccess = AL_GetPicFormat(pMeta->tFourCC, &tPicFormat);

  if(!bSuccess)
    return false;

  pMeta->tPlanes[ePlaneId] = tPlane;

  return true;
}

AL_TPixMapMetaData* AL_PixMapMetaData_CreateEmpty(TFourCC tFourCC)
{
  AL_TPixMapMetaData* pMeta = (AL_TPixMapMetaData*)Rtos_Malloc(sizeof(*pMeta));

  if(!pMeta)
    return NULL;

  pMeta->tMeta.eType = AL_META_TYPE_PIXMAP;
  pMeta->tMeta.MetaDestroy = SrcMeta_Destroy;
  pMeta->tMeta.MetaClone = SrcMeta_Clone;

  pMeta->tDim.iWidth = 0;
  pMeta->tDim.iHeight = 0;

  AL_TPlane tEmptyPlane = { -1, 0, 0 };

  for(int iPlane = 0; iPlane < AL_PLANE_MAX_ENUM; iPlane++)
    pMeta->tPlanes[iPlane] = tEmptyPlane;

  pMeta->tFourCC = tFourCC;

  return pMeta;
}

AL_TPixMapMetaData* AL_PixMapMetaData_Create(AL_TDimension tDim, AL_TPlane tYPlane, AL_TPlane tUVPlane, TFourCC tFourCC)
{
  AL_TPixMapMetaData* pMeta = AL_PixMapMetaData_CreateEmpty(tFourCC);

  if(!pMeta)
    return NULL;

  pMeta->tDim = tDim;

  if(!AL_PixMapMetaData_AddPlane(pMeta, tYPlane, AL_PLANE_Y) ||
     !AL_PixMapMetaData_AddPlane(pMeta, tUVPlane, AL_PLANE_UV))
  {
    AL_MetaData_Destroy((AL_TMetaData*)pMeta);
    return NULL;
  }

  return pMeta;
}

int AL_PixMapMetaData_GetOffset(AL_TPixMapMetaData* pMeta, AL_EPlaneId ePlaneId)
{
  return pMeta->tPlanes[ePlaneId].iOffset;
}

int AL_PixMapMetaData_GetOffsetY(AL_TPixMapMetaData* pMeta)
{
  return AL_PixMapMetaData_GetOffset(pMeta, AL_PLANE_Y);
}

int AL_PixMapMetaData_GetOffsetUV(AL_TPixMapMetaData* pMeta)
{
  return AL_PixMapMetaData_GetOffset(pMeta, AL_PLANE_UV);
}

int AL_PixMapMetaData_GetLumaSize(AL_TPixMapMetaData* pMeta)
{
  if(AL_IsTiled(pMeta->tFourCC))
    return pMeta->tPlanes[AL_PLANE_Y].iPitch * pMeta->tDim.iHeight / 4;
  return pMeta->tPlanes[AL_PLANE_Y].iPitch * pMeta->tDim.iHeight;
}

int AL_PixMapMetaData_GetChromaSize(AL_TPixMapMetaData* pMeta)
{
  AL_EChromaMode eCMode = AL_GetChromaMode(pMeta->tFourCC);

  if(eCMode == AL_CHROMA_MONO)
    return 0;

  int const iHeightC = AL_GetChromaHeight(pMeta->tFourCC, pMeta->tDim.iHeight);

  if(AL_IsTiled(pMeta->tFourCC))
    return pMeta->tPlanes[AL_PLANE_UV].iPitch * iHeightC / 4;

  if(AL_IsSemiPlanar(pMeta->tFourCC))
    return pMeta->tPlanes[AL_PLANE_UV].iPitch * iHeightC;

  return pMeta->tPlanes[AL_PLANE_UV].iPitch * iHeightC * 2;
}
