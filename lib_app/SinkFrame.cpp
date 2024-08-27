// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_app/SinkFrame.h"
#include "lib_app/UnCompFrameWriter.h"
#include "lib_app/CompFrameWriter.h"
#include  "lib_common/DisplayInfoMeta.h"
#include <fstream>
#include <stdexcept>

class SinkUnCompFrame : public IFrameSink
{
public:
  SinkUnCompFrame(const std::shared_ptr<std::ostream>& recFile, AL_EFbStorageMode eStorageMode) :
    m_RecFile(recFile),
    m_Writer(m_RecFile, eStorageMode)
  {
    if(!m_RecFile || m_RecFile->fail())
      throw std::runtime_error("Invalid output file");
  }

  SinkUnCompFrame(std::string const& sRecFileName, AL_EFbStorageMode eStorageMode) :
    SinkUnCompFrame(std::shared_ptr<std::ostream>(new std::ofstream(sRecFileName.c_str(), std::ios::binary)), eStorageMode)
  {}

  void ProcessFrame(AL_TBuffer* pBuf) override
  {
    AL_TDisplayInfoMetaData* pMeta = reinterpret_cast<AL_TDisplayInfoMetaData*>(AL_Buffer_GetMetaData(pBuf, AL_META_TYPE_DISPLAY_INFO));

    AL_TCropInfo* pCrop = nullptr;

    if(pMeta)
      pCrop = &pMeta->tCrop;

    m_Writer.WriteFrame(pBuf, pCrop);
  }

private:
  std::shared_ptr<std::ostream> m_RecFile;

  UnCompFrameWriter m_Writer;
};

IFrameSink* createUnCompFrameSink(const std::shared_ptr<std::ostream>& recFile, AL_EFbStorageMode eStorageMode)
{
  return new SinkUnCompFrame(recFile, eStorageMode);
}

IFrameSink* createUnCompFrameSink(std::string const& sRecFile, AL_EFbStorageMode eStorageMode)
{
  return new SinkUnCompFrame(sRecFile, eStorageMode);
}

class SinkCompFrame : public IFrameSink
{
public:
  SinkCompFrame(const std::shared_ptr<std::ostream>& recFile, const std::shared_ptr<std::ostream>& mapFile, AL_EFbStorageMode eStorageMode, uint8_t uCompMode) :
    m_RecFile(recFile),
    m_MapFile(mapFile),
    m_Writer(recFile, mapFile, eStorageMode, uCompMode)
  {
    if(!m_RecFile || m_RecFile->fail())
      throw std::runtime_error("Invalid output file");

    if(!m_MapFile || m_MapFile->fail())
      throw std::runtime_error("Invalid output map file");
  }

  SinkCompFrame(std::string const& sRecFileName, std::string const& sMapFileName, AL_EFbStorageMode eStorageMode, uint8_t uCompMode) :
    SinkCompFrame(std::shared_ptr<std::ostream>(new std::ofstream(sRecFileName.c_str(), std::ios::binary)), std::shared_ptr<std::ostream>(new std::ofstream(sMapFileName.c_str(), std::ios::binary)), eStorageMode, uCompMode)
  {
  }

  void ProcessFrame(AL_TBuffer* pBuf) override
  {
    AL_TDisplayInfoMetaData* pMeta = reinterpret_cast<AL_TDisplayInfoMetaData*>(AL_Buffer_GetMetaData(pBuf, AL_META_TYPE_DISPLAY_INFO));

    AL_TCropInfo* pCrop = nullptr;
    AL_EPicStruct ePicStruct = AL_PS_FRM;

    if(pMeta)
    {
      pCrop = &pMeta->tCrop;
      ePicStruct = pMeta->ePicStruct;
    }

    m_Writer.WriteFrame(pBuf, pCrop, ePicStruct);
  }

private:
  std::shared_ptr<std::ostream> m_RecFile;
  std::shared_ptr<std::ostream> m_MapFile;

  CompFrameWriter m_Writer;
};

IFrameSink* createCompFrameSink(const std::shared_ptr<std::ostream>& recFile, const std::shared_ptr<std::ostream>& mapFile, AL_EFbStorageMode eStorageMode, uint8_t uCompMode)
{
  return new SinkCompFrame(recFile, mapFile, eStorageMode, uCompMode);
}

IFrameSink* createCompFrameSink(std::string const& sRecFileName, std::string const sMapFileName, AL_EFbStorageMode eStorageMode, uint8_t uCompMode)
{
  return new SinkCompFrame(sRecFileName, sMapFileName, eStorageMode, uCompMode);
}

