// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_app/FrameReader.h"

#include <fstream>

int FrameReader::GetFileSize(void)
{
  auto position = m_recFile.tellg();
  m_recFile.seekg(0, std::ios_base::end);
  auto size = m_recFile.tellg();
  m_recFile.seekg(position);
  return size;
}

int FrameReader::GotoNextPicture(int iFileFrameRate, int iEncFrameRate, int iEncPictCount, int iFilePictCount)
{
  const int iMove = ((iEncPictCount * iFileFrameRate) / iEncFrameRate) - iFilePictCount;

  if(iMove)
    this->SeekR(iMove);

  return iMove;
}
