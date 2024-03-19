// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once
extern "C"
{
#include "lib_log/LoggerDefault.h"
}
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

struct Logger
{
  Logger(std::string const& outputFile) : outputFile{outputFile}
  {
    if(outputFile.empty())
      maxCount = 0;

    samples.resize(maxCount);

    logger = AL_DefaultLogger_Init(AL_DefaultLogger_Get(), NULL, samples.data(), maxCount);
  }

  ~Logger()
  {
    dump();
    AL_ILogger_Deinit(logger);
  }

  void dump()
  {
    if(outputFile.empty())
      return;

    std::ofstream tracer(outputFile);

    for(int i = 0; i < AL_DefaultLogger_Get()->count; i++)
      tracer << std::string(samples[i].label) << " " << samples[i].timestamp << std::endl;
  }

  int maxCount = 32000;
  std::vector<LogEvent> samples;
  std::string outputFile;
  AL_ILogger* logger;
};
