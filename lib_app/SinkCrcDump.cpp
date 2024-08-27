// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include <fstream>
#include <string>
#include <iomanip>

#include "lib_app/SinkCrcDump.h"
#include "lib_app/Sink.h"
#include "lib_app/utils.h"

extern "C"
{
#include "lib_common/PixMapBuffer.h"
#include "lib_common/BufferStreamMeta.h"
#include "lib_common/DisplayInfoMeta.h"
}

class StreamCrcDump : public IFrameSink
{
public:
  StreamCrcDump(std::string const& path)
  {
    if(!path.empty())
    {
      OpenOutput(m_CrcFile, path, false);
      m_CrcFile << std::hex << std::uppercase;
    }
  }

  void ProcessFrame(AL_TBuffer* pBuf) override
  {
    AL_TDisplayInfoMetaData* pMeta = reinterpret_cast<AL_TDisplayInfoMetaData*>(AL_Buffer_GetMetaData(pBuf, AL_META_TYPE_DISPLAY_INFO));

    if(pMeta && pMeta->eOutputID == AL_OUTPUT_MAIN)
    {
      if(m_CrcFile.is_open())
      {
        m_CrcFile << std::setfill('0') << std::setw(8) << (int)pMeta->uCrc;
        m_CrcFile << std::endl;
      }
    }
  }

private:
  std::ofstream m_CrcFile;
};

IFrameSink* createStreamCrcDump(std::string const& path)
{
  return new StreamCrcDump(path);
}
