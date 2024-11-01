// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/******************************************************************************
   \addtogroup Buffers
   !@{
   \file
 *****************************************************************************/
#pragma once

#include "lib_common/BufferMeta.h"
#include "lib_common/StreamSection.h"

#define AL_MAX_SECTION (2 * (AL_MAX_ENC_SLICE + 2))
#define AL_INVALID_STREAMSECTION_ID -1

/*****************************************************************************
   \brief Useful section of the buffer containing the bitstream
*****************************************************************************/
typedef struct AL_TStreamMetaData
{
  AL_TMetaData tMeta;
  uint8_t uTemporalID; /*!< Temporal ID */
  AL_TStreamSection* pSections;  /*!< Array of sections */
  uint16_t uNumSection; /*!< number of sections inside the buffer */
  uint16_t uMaxNumSection; /*!< maximum number of sections available */
}AL_TStreamMetaData;

/*****************************************************************************
   \brief Create a stream metadata.
   \param[in] uMaxNumSection maximum number of sections the user is expecting
   inside the stream. The library can produce in the worst case AL_MAX_SECTION.
   The user might want to add his own section and should allocate in consequence.
*****************************************************************************/
AL_TStreamMetaData* AL_StreamMetaData_Create(uint16_t uMaxNumSection);
AL_TStreamMetaData* AL_StreamMetaData_Clone(AL_TStreamMetaData* pMeta);

/*****************************************************************************
   \brief Add a section to the stream. Sections represent the stream
   parts where relevant data can be found. They act as a kind of scatter gather
   list.
   You can add a maximum of uMaxNumSection to a stream metadata.
   \param[in] pMetaData Pointer to the stream metadata
   \param[in] uOffset offset in the stream data of the section
   \param[in] uLength size of the data of the section
   \param[in] eFlags stream section bitfield (see SECTION_xxxxx_FLAG)
   \return return the id given to the added section, AL_INVALID_STREAMSECTION_ID if the section couldn't be added
*****************************************************************************/
int AL_StreamMetaData_AddSection(AL_TStreamMetaData* pMetaData, uint32_t uOffset, uint32_t uLength, AL_ESectionFlags eFlags);

/*****************************************************************************
   \brief Change the information of a previously added section
   \param[in] pMetaData Pointer to the stream metadata
   \param[in] uSectionID id representing the section you want to change
   \param[in] uOffset new offset of the section
   \param[in] uLength new size of the section
*****************************************************************************/
void AL_StreamMetaData_ChangeSection(AL_TStreamMetaData* pMetaData, uint16_t uSectionID, uint32_t uOffset, uint32_t uLength);

/*****************************************************************************
   \brief Change the flags related to a section (see SECTION_xxxxx_FLAG)
   \param[in] pMetaData Pointer to the stream metadata
   \param[in] uSectionID id representing the section you want to change
   \param[in] eFlags stream section bitfield (see SECTION_xxxxx_FLAG)
*****************************************************************************/
void AL_StreamMetaData_SetSectionFlags(AL_TStreamMetaData* pMetaData, uint16_t uSectionID, AL_ESectionFlags eFlags);

/*****************************************************************************
   \brief Remove all the sections of a particular stream metadata
   \param[in] pMetaData Pointer to the stream metadata
*****************************************************************************/
void AL_StreamMetaData_ClearAllSections(AL_TStreamMetaData* pMetaData);

/*****************************************************************************
   \brief Add a SEI section to the stream
   \param[in] pMetaData Pointer to the stream metadata
   \param[in] isPrefix prefix or a suffix SEI
   \param[in] uOffset offset of the section data in the stream
   \param[in] uLength length of the section data in the stream
   \return returns the section id, AL_INVALID_STREAMSECTION_ID on failure
*****************************************************************************/
int AL_StreamMetaData_AddSeiSection(AL_TStreamMetaData* pMetaData, bool isPrefix, uint32_t uOffset, uint32_t uLength);

/*****************************************************************************
   \brief Get an unused part in the stream buffer
   The user needs to check if the offset is still inside his stream buffer
   \param[in] pMetaData Pointer to the stream metadata
   \return returns an offset where the section data can be inserted in the stream.
*****************************************************************************/
uint32_t AL_StreamMetaData_GetUnusedStreamPart(AL_TStreamMetaData* pMetaData);

/*****************************************************************************
   \brief Get an the last section in the stream buffer of containing the provided flag
   \param[in] pMetaData Pointer to the stream metadata
   \param[in] uFlag Section's flag
   \return returns the section id, -1 on failure
*****************************************************************************/
int AL_StreamMetaData_GetLastSectionOfFlag(AL_TStreamMetaData* pMetaData, uint32_t uFlag);

/*!@}*/
