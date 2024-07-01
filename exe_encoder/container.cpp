// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include <fstream>
#include <string>
#include "lib_app/InputFiles.h"
#include "CodecUtils.h"

using namespace std;

void WriteContainerHeader(ofstream& fp, AL_TEncSettings const& Settings, AL_TYUVFileInfo const& FileInfo, int numFrames)
{
  (void)fp;
  (void)Settings;
  (void)FileInfo;
  (void)numFrames;
}
