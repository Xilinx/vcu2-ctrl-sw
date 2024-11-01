// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_common/BufferStreamMeta.h"
#include "lib_rtos/lib_rtos.h"

static bool StreamMeta_Destroy(AL_TMetaData* pMeta)
{
  AL_TStreamMetaData* pStreamMeta = (AL_TStreamMetaData*)pMeta;
  Rtos_Free(pStreamMeta->pSections);
  Rtos_Free(pMeta);
  return true;
}

AL_TStreamMetaData* AL_StreamMetaData_Clone(AL_TStreamMetaData* pMeta)
{
  if(!pMeta)
    return NULL;

  AL_TStreamMetaData* pNewMeta = AL_StreamMetaData_Create(pMeta->uMaxNumSection);

  if(!pNewMeta)
    return NULL;

  pNewMeta->uTemporalID = pMeta->uTemporalID;
  pNewMeta->uMaxNumSection = pMeta->uMaxNumSection;
  pNewMeta->uNumSection = pMeta->uNumSection;

  for(uint16_t i = 0; i < pMeta->uNumSection; ++i)
    pNewMeta->pSections[i] = pMeta->pSections[i];

  return pNewMeta;
}

AL_TMetaData* StreamMeta_Clone(AL_TMetaData* pMeta)
{
  return (AL_TMetaData*)AL_StreamMetaData_Clone((AL_TStreamMetaData*)pMeta);
}

AL_TStreamMetaData* AL_StreamMetaData_Create(uint16_t uMaxNumSection)
{
  if(uMaxNumSection == 0)
    return NULL;

  AL_TStreamMetaData* pMeta = (AL_TStreamMetaData*)Rtos_Malloc(sizeof(*pMeta));

  if(!pMeta)
    return NULL;

  pMeta->tMeta.eType = AL_META_TYPE_STREAM;
  pMeta->tMeta.MetaDestroy = StreamMeta_Destroy;
  pMeta->tMeta.MetaClone = StreamMeta_Clone;

  pMeta->uTemporalID = 0;
  pMeta->uMaxNumSection = uMaxNumSection;
  pMeta->uNumSection = 0;

  pMeta->pSections = (AL_TStreamSection*)Rtos_Malloc(sizeof(AL_TStreamSection) * uMaxNumSection);

  if(!pMeta->pSections)
    goto fail_alloc_section;

  return pMeta;

  fail_alloc_section:
  Rtos_Free(pMeta);
  return NULL;
}

static void SetSection(AL_TStreamSection* pSections, uint16_t uSectionID, uint32_t uOffset, uint32_t uLength, AL_ESectionFlags eFlags)
{
  pSections[uSectionID].uOffset = uOffset;
  pSections[uSectionID].uLength = uLength;
  pSections[uSectionID].eFlags = eFlags;
}

int AL_StreamMetaData_AddSection(AL_TStreamMetaData* pMetaData, uint32_t uOffset, uint32_t uLength, AL_ESectionFlags eFlags)
{
  if(!pMetaData)
    return AL_INVALID_STREAMSECTION_ID;

  uint16_t uSectionID = pMetaData->uNumSection;

  if(uSectionID >= pMetaData->uMaxNumSection)
    return AL_INVALID_STREAMSECTION_ID;

  SetSection(pMetaData->pSections, uSectionID, uOffset, uLength, eFlags);
  ++pMetaData->uNumSection;

  return uSectionID;
}

/****************************************************************************/
void AL_StreamMetaData_ChangeSection(AL_TStreamMetaData* pMetaData, uint16_t uSectionID, uint32_t uOffset, uint32_t uLength)
{
  Rtos_Assert(pMetaData && uSectionID < pMetaData->uNumSection);

  pMetaData->pSections[uSectionID].uOffset = uOffset;
  pMetaData->pSections[uSectionID].uLength = uLength;
}

/****************************************************************************/
void AL_StreamMetaData_SetSectionFlags(AL_TStreamMetaData* pMetaData, uint16_t uSectionID, AL_ESectionFlags eFlags)
{
  Rtos_Assert(pMetaData && uSectionID < pMetaData->uNumSection);
  pMetaData->pSections[uSectionID].eFlags = eFlags;
}

/****************************************************************************/
void AL_StreamMetaData_ClearAllSections(AL_TStreamMetaData* pMetaData)
{
  Rtos_Assert(pMetaData);
  pMetaData->uNumSection = 0;
}

/****************************************************************************/
int AL_StreamMetaData_GetLastSectionOfFlag(AL_TStreamMetaData* pMetaData, uint32_t flag)
{
  Rtos_Assert(pMetaData);
  AL_TStreamSection* pSections = pMetaData->pSections;
  int flagSectionId = pMetaData->uNumSection - 1;

  while(flagSectionId >= 0)
  {
    if(pSections[flagSectionId].eFlags & flag)
      break;
    --flagSectionId;
  }

  /* flagSectionId == -1 if we didn't find any flag sections */

  return flagSectionId;
}

static int InsertSectionAtId(AL_TStreamMetaData* pMetaData, uint16_t uTargetID, uint32_t uOffset, uint32_t uLength, AL_ESectionFlags eFlags)
{
  if(!pMetaData)
    return AL_INVALID_STREAMSECTION_ID;

  uint16_t uNumSection = pMetaData->uNumSection;
  AL_TStreamSection* pSections = pMetaData->pSections;

  if(uNumSection >= pMetaData->uMaxNumSection)
    return AL_INVALID_STREAMSECTION_ID;

  for(int i = uNumSection - 1; i >= (int)uTargetID; --i)
  {
    AL_TStreamSection* cur = &pSections[i];
    SetSection(pSections, i + 1, cur->uOffset, cur->uLength, cur->eFlags);
  }

  SetSection(pSections, uTargetID, uOffset, uLength, eFlags);
  ++pMetaData->uNumSection;

  return uTargetID;
}

static int AddPrefixSei(AL_TStreamMetaData* pMetaData, uint32_t uOffset, uint32_t uLength)
{
  // the prefix sei needs to be inserted after a config section if it exists
  int iLastSEIPrefixSectionID = AL_StreamMetaData_GetLastSectionOfFlag(pMetaData, AL_SECTION_SEI_PREFIX_FLAG);

  if(iLastSEIPrefixSectionID == -1)
    iLastSEIPrefixSectionID = AL_StreamMetaData_GetLastSectionOfFlag(pMetaData, AL_SECTION_CONFIG_FLAG);

  int iSEIPrefixSectionID = iLastSEIPrefixSectionID + 1;

  return InsertSectionAtId(pMetaData, iSEIPrefixSectionID, uOffset, uLength, AL_SECTION_SEI_PREFIX_FLAG);
}

int AL_StreamMetaData_AddSeiSection(AL_TStreamMetaData* pMetaData, bool isPrefix, uint32_t uOffset, uint32_t uLength)
{
  if(isPrefix)
    return AddPrefixSei(pMetaData, uOffset, uLength);

  return AL_StreamMetaData_AddSection(pMetaData, uOffset, uLength, AL_SECTION_NO_FLAG);
}

uint32_t AL_StreamMetaData_GetUnusedStreamPart(AL_TStreamMetaData* pMetaData)
{
  AL_TStreamSection* pSections = pMetaData->pSections;
  uint16_t uNumSection = pMetaData->uNumSection;

  uint32_t maxOffset = 0;

  for(uint16_t i = 0; i < uNumSection; ++i)
  {
    uint32_t curOffset = pSections[i].uOffset + pSections[i].uLength;

    if(curOffset > maxOffset)
      maxOffset = curOffset;
  }

  return maxOffset;
}
