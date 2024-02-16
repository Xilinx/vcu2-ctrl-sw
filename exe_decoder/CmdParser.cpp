// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include <algorithm>

#include "CmdParser.h"
#include "exe_decoder/CodecUtils.h"
#include "lib_app/CommandLineParser.h"
#include "lib_common/RoundUp.h"

/******************************************************************************/
static void Usage(CommandLineParser const& opt, char* ExeName)
{
  cout << "Usage: " << ExeName << " -in <bitstream_file> -out <yuv_file> [options]" << endl;
  cout << "Options:" << endl;

  opt.usage();

  cout << endl << "Examples:" << endl;
  cout << "  " << ExeName << " -avc  -in bitstream.264 -out decoded.yuv -bd 8 " << endl;
  cout << "  " << ExeName << " -hevc -in bitstream.265 -out decoded.yuv -bd 10" << endl;
  cout << "  " << ExeName << " -jpeg -in bitstream.jpg -out decoded.yuv" << endl;
  cout << endl;
}

/******************************************************************************/
static AL_TDecSettings GetDefaultDecSettings()
{
  AL_TDecSettings settings {};
  AL_DecSettings_SetDefaults(&settings);
  settings.uNumBuffersHeldByNextComponent = uDefaultNumBuffersHeldByNextComponent;
  return settings;
}

/******************************************************************************/
Config::Config()
{
  tDecSettings = GetDefaultDecSettings();

}

/******************************************************************************/
static EDecErrorLevel ParseExitOn(const string& toParse)
{
  string toParseLower = toParse;
  std::for_each(toParseLower.begin(), toParseLower.end(), [](char& c) { c = ::tolower(c); });

  if(toParseLower == "w" || toParseLower == "warning")
    return DEC_WARNING;
  else if(toParseLower == "e" || toParseLower == "error")
    return DEC_ERROR;
  else
    throw runtime_error("wrong exit condition");
}

/******************************************************************************/
static TFourCC ParseFourCCFormat(const string& sOutputFormat)
{
  uint32_t uFourCC = 0;

  if(sOutputFormat.size() >= 1)
    uFourCC = ((uint32_t)sOutputFormat[0]);

  if(sOutputFormat.size() >= 2)
    uFourCC |= ((uint32_t)sOutputFormat[1]) << 8;

  if(sOutputFormat.size() >= 3)
    uFourCC |= ((uint32_t)sOutputFormat[2]) << 16;

  if(sOutputFormat.size() >= 4)
    uFourCC |= ((uint32_t)sOutputFormat[3]) << 24;

  return (TFourCC)uFourCC;
}

/******************************************************************************/
static int ParseOutputBD(string& sOutputBitDepth)
{
  if(sOutputBitDepth == string("first"))
    return OUTPUT_BD_FIRST;
  else if(sOutputBitDepth == string("alloc"))
    return OUTPUT_BD_ALLOC;
  else if(sOutputBitDepth == string("stream"))
    return OUTPUT_BD_STREAM;
  else
  {
    int iBitDepth;
    stringstream ss(sOutputBitDepth);
    ss >> iBitDepth;

    bool bIsBitDepthValid = (iBitDepth == 8) || (iBitDepth == 10) || (iBitDepth == 12);

    if(ss.fail() || !bIsBitDepthValid)
      throw runtime_error("Unsupported output bitdepth");
    return iBitDepth;
  }
}

/******************************************************************************/
static AL_EProfile ParseProfile(string const& sProf)
{
  static const map<string, AL_EProfile> PROFILES =
  {
    { "HEVC_MONO10", AL_PROFILE_HEVC_MONO10 },
    { "HEVC_MONO", AL_PROFILE_HEVC_MONO },
    { "HEVC_MAIN_444_STILL", AL_PROFILE_HEVC_MAIN_444_STILL },
    { "HEVC_MAIN_444_10_INTRA", AL_PROFILE_HEVC_MAIN_444_10_INTRA },
    { "HEVC_MAIN_444_INTRA", AL_PROFILE_HEVC_MAIN_444_INTRA },
    { "HEVC_MAIN_444_10", AL_PROFILE_HEVC_MAIN_444_10 },
    { "HEVC_MAIN_444", AL_PROFILE_HEVC_MAIN_444 },
    { "HEVC_MAIN_422_10_INTRA", AL_PROFILE_HEVC_MAIN_422_10_INTRA },
    { "HEVC_MAIN_422_10", AL_PROFILE_HEVC_MAIN_422_10 },
    { "HEVC_MAIN_422_12", AL_PROFILE_HEVC_MAIN_422_12 },
    { "HEVC_MAIN_444_12", AL_PROFILE_HEVC_MAIN_444_12 },
    { "HEVC_MAIN_422", AL_PROFILE_HEVC_MAIN_422 },
    { "HEVC_MAIN_INTRA", AL_PROFILE_HEVC_MAIN_INTRA },
    { "HEVC_MAIN_STILL", AL_PROFILE_HEVC_MAIN_STILL },
    { "HEVC_MAIN10_INTRA", AL_PROFILE_HEVC_MAIN10_INTRA },
    { "HEVC_MAIN10", AL_PROFILE_HEVC_MAIN10 },
    { "HEVC_MAIN12", AL_PROFILE_HEVC_MAIN12 },
    { "HEVC_MAIN", AL_PROFILE_HEVC_MAIN },
    /* Baseline is mapped to Constrained_Baseline */
    { "AVC_BASELINE", AL_PROFILE_AVC_C_BASELINE },
    { "AVC_C_BASELINE", AL_PROFILE_AVC_C_BASELINE },
    { "AVC_MAIN", AL_PROFILE_AVC_MAIN },
    { "AVC_HIGH10_INTRA", AL_PROFILE_AVC_HIGH10_INTRA },
    { "AVC_HIGH10", AL_PROFILE_AVC_HIGH10 },
    { "AVC_HIGH_422_INTRA", AL_PROFILE_AVC_HIGH_422_INTRA },
    { "AVC_HIGH_422", AL_PROFILE_AVC_HIGH_422 },
    { "AVC_HIGH", AL_PROFILE_AVC_HIGH },
    { "AVC_C_HIGH", AL_PROFILE_AVC_C_HIGH },
    { "AVC_PROG_HIGH", AL_PROFILE_AVC_PROG_HIGH },
    { "AVC_CAVLC_444_INTRA", AL_PROFILE_AVC_CAVLC_444_INTRA },
    { "AVC_HIGH_444_INTRA", AL_PROFILE_AVC_HIGH_444_INTRA },
    { "AVC_HIGH_444_PRED", AL_PROFILE_AVC_HIGH_444_PRED },
    { "XAVC_HIGH10_INTRA_CBG", AL_PROFILE_XAVC_HIGH10_INTRA_CBG },
    { "XAVC_HIGH10_INTRA_VBR", AL_PROFILE_XAVC_HIGH10_INTRA_VBR },
    { "XAVC_HIGH_422_INTRA_CBG", AL_PROFILE_XAVC_HIGH_422_INTRA_CBG },
    { "XAVC_HIGH_422_INTRA_VBR", AL_PROFILE_XAVC_HIGH_422_INTRA_VBR },
    { "XAVC_LONG_GOP_MAIN_MP4", AL_PROFILE_XAVC_LONG_GOP_MAIN_MP4 },
    { "XAVC_LONG_GOP_HIGH_MP4", AL_PROFILE_XAVC_LONG_GOP_HIGH_MP4 },
    { "XAVC_LONG_GOP_HIGH_MXF", AL_PROFILE_XAVC_LONG_GOP_HIGH_MXF },
    { "XAVC_LONG_GOP_HIGH_422_MXF", AL_PROFILE_XAVC_LONG_GOP_HIGH_422_MXF },
    { "JPEG", AL_PROFILE_JPEG },
  };

  map<string, AL_EProfile>::const_iterator it = PROFILES.find(sProf);

  if(it == PROFILES.end())
    return AL_PROFILE_UNKNOWN;

  return it->second;
}

/******************************************************************************/
static void GetExpectedSeparator(stringstream& ss, char expectedSep)
{
  char sep;
  ss >> sep;

  if(sep != expectedSep)
    throw runtime_error("wrong prealloc arguments separator");
}

/******************************************************************************/
static void ParsePreAllocArgs(AL_TStreamSettings* settings, AL_ECodec codec, string const& toParse)
{
  stringstream ss(toParse);
  ss.unsetf(ios::dec);
  ss.unsetf(ios::hex);
  ss >> settings->tDim.iWidth;
  GetExpectedSeparator(ss, 'x');
  ss >> settings->tDim.iHeight;
  GetExpectedSeparator(ss, ':');
  char vm[6] {};
  ss >> vm[0];
  ss >> vm[1];
  ss >> vm[2];
  ss >> vm[3];
  ss >> vm[4];
  GetExpectedSeparator(ss, ':');
  char chroma[4] {};
  ss >> chroma[0];
  ss >> chroma[1];
  ss >> chroma[2];
  GetExpectedSeparator(ss, ':');
  ss >> settings->iBitDepth;
  GetExpectedSeparator(ss, ':');

  if(ss.peek() >= '0' && ss.peek() <= '9')
  {
    int iProfileIdc;
    ss >> iProfileIdc;
    settings->eProfile = AL_MAKE_PROFILE(codec, iProfileIdc, 0);
  }
  else
  {
    string const& sArgs = ss.str();
    string const& sProf = sArgs.substr(ss.tellg(), sArgs.find_first_of(':', ss.tellg()) - ss.tellg());
    settings->eProfile = ParseProfile(sProf);

    if(AL_GET_CODEC(settings->eProfile) != codec)
      throw runtime_error("The profile does not match the codec");

    ss.ignore(sProf.length());
  }

  GetExpectedSeparator(ss, ':');
  ss >> settings->iLevel;

  settings->iMaxRef = 0;

  if(ss.tellg() != streampos(-1))
  {
    GetExpectedSeparator(ss, ':');
    ss >> settings->iMaxRef;
  }
  switch(codec)
  {
  case AL_CODEC_AVC:
  case AL_CODEC_HEVC:

    if(settings->iLevel < 10 || settings->iLevel > 62)
      throw runtime_error("The level does not match the codec");
    break;
  case AL_CODEC_VVC:

    if(settings->iLevel < 10 || settings->iLevel > 63)
      throw runtime_error("The level does not match the codec");
    break;
  default:
    break;
  }

  if(string(chroma) == "400")
    settings->eChroma = AL_CHROMA_4_0_0;
  else if(string(chroma) == "420")
    settings->eChroma = AL_CHROMA_4_2_0;
  else if(string(chroma) == "422")
    settings->eChroma = AL_CHROMA_4_2_2;
  else if(string(chroma) == "444")
    settings->eChroma = AL_CHROMA_4_4_4;
  else
    throw runtime_error("wrong prealloc chroma format");

  if(string(vm) == "unkwn")
    settings->eSequenceMode = AL_SM_UNKNOWN;
  else if(string(vm) == "progr")
    settings->eSequenceMode = AL_SM_PROGRESSIVE;
  else if(string(vm) == "inter")
    settings->eSequenceMode = AL_SM_INTERLACED;
  else
    throw runtime_error("wrong prealloc video format");

  if((ss.tellg() != streampos(-1)))
    throw runtime_error("wrong prealloc arguments format");
}

/******************************************************************************/
static bool IsPrimaryOutputFormatAllowed(AL_EFbStorageMode mode)
{
  return AL_FB_RASTER == mode || AL_FB_TILE_32x4 == mode || AL_FB_TILE_64x4 == mode;
}

/******************************************************************************/
static bool IsSecondOutputFormatAllowed(AL_EFbStorageMode storageMode)
{
  bool bAllowed = (AL_FB_RASTER == storageMode);

  return bAllowed;
}

/******************************************************************************/
static void ProcessOutputArgs(Config& config, const string& sRasterOut)
{
  (void)sRasterOut;

  auto pOutputSettings = &config.tUserOutputSettings;

  /* --- Retro-compatibility --- */
  if(!sRasterOut.empty())
  {
    config.sMainOut = sRasterOut;
    pOutputSettings->tPicFormat.eStorageMode = AL_FB_RASTER;
    pOutputSettings->bCustomFormat = true;
  }
  /* ---------------------------- */

  if(pOutputSettings->bCustomFormat)
  {
    pOutputSettings->bCustomFormat = (pOutputSettings->tPicFormat.eStorageMode != config.tDecSettings.eFBStorageMode) ||
                                     (pOutputSettings->tPicFormat.bCompressed != config.tDecSettings.bFrameBufferCompression);
  }

  if(pOutputSettings->bCustomFormat && !IsSecondOutputFormatAllowed(pOutputSettings->tPicFormat.eStorageMode))
    throw runtime_error("Second output format is not allowed !");

  if(!IsPrimaryOutputFormatAllowed(config.tDecSettings.eFBStorageMode))
    throw runtime_error("Primary output format is not allowed !");

  if(!config.bEnableYUVOutput)
  {
    config.sMainOut = "";
  }
  else if(config.sMainOut.empty())
    config.sMainOut = "dec.yuv";

  if(config.tDecSettings.eCodec == AL_CODEC_JPEG && config.tDecSettings.bFrameBufferCompression)
    throw runtime_error("Frame buffer compression not allowed for JPEG");

  if(config.tDecSettings.eCodec == AL_CODEC_JPEG)
    config.tDecSettings.eFBStorageMode = AL_FB_RASTER;
}

/******************************************************************************/
static AL_EFbStorageMode ParseFrameBufferFormat(const string& sBufFormat, bool& bBufComp)
{
  bBufComp = false;

  if(sBufFormat == "raster")
    return AL_FB_RASTER;

  if(sBufFormat == "raster-msb")
    return AL_FB_RASTER;

  AL_EFbStorageMode eDefaultTileStorageMode = AL_FB_TILE_32x4;

  if(sBufFormat == "tile")
    return eDefaultTileStorageMode;

  if(sBufFormat == "tile64")
    return AL_FB_TILE_64x4;

  throw runtime_error("Invalid buffer format");
}

/******************************************************************************/
template<int Offset>
static int IntWithOffset(const string& word)
{
  return atoi(word.c_str()) + Offset;
}

/******************************************************************************/
template<typename TCouple, char Separator>
static TCouple CoupleWithSeparator(const string& str)
{
  TCouple Couple;
  struct t_couple
  {
    uint32_t first;
    uint32_t second;
  }* pCouple = reinterpret_cast<t_couple*>(&Couple);

  static_assert(sizeof(TCouple) == sizeof(t_couple), "Invalid structure size");

  size_t sep = str.find_first_of(Separator);
  pCouple->first = atoi(str.substr(0, sep).c_str());
  pCouple->second = atoi(str.substr(sep + 1).c_str());

  return Couple;
}

/******************************************************************************/
static std::string GetFrameBufferFormatOptDesc(bool bSecondOutput = false)
{
  std::string sFBufFormatOptDesc = "raster";

  if(!bSecondOutput)
  {
    sFBufFormatOptDesc += ", tile";
    sFBufFormatOptDesc += ", tile64 (64x4 tiling)";

  }

  sFBufFormatOptDesc += ", raster-msb (16-bit per sample, with MSB left-aligned)";

  return sFBufFormatOptDesc;
}

/******************************************************************************/
/* duplicated from Utils.h as we can't take these from inside the libraries */
static inline int RoundUp(int iVal, int iRnd)
{
  return (iVal + iRnd - 1) / iRnd * iRnd;
}

/******************************************************************************/
static std::string toStringPathsSet(std::set<std::string> paths)
{
  std::string out;

  for(auto path : paths)
  {
    if(out.length() != 0)
      out += string(", ");
    out += path;
  }

  return out;
}

/******************************************************************************/
Config ParseCommandLine(int argc, char* argv[])
{
  Config config {};

  int fps = 0;
  bool version = false;
  bool helpJson = false;

  string sRasterOut;
  string sOutputBitDepth = "";
  string sOutputFormat = "";
  std::set<std::string> const sDecDefaultDevicePath(DECODER_DEVICES);

  SetDefaultDecOutputSettings(&config.tUserOutputSettings);

  auto opt = CommandLineParser(ShouldShowAdvancedFeatures());

  opt.addFlag("--help,-h", &config.help, "Shows this help");
  opt.addFlag("--help-json", &helpJson, "Show this help (json)");
  opt.addFlag("--version", &version, "Show version");

  opt.addString("--input,--in,-in,--i,-i", &config.sIn, "Input bitstream");
  opt.addString("--output,--out,-out,--o,-o", &config.sMainOut, "Output YUV");

  opt.addFlag("--avc,-avc", &config.tDecSettings.eCodec,
              "Specify the input bitstream codec (default: HEVC)",
              AL_CODEC_AVC);

  opt.addFlag("--hevc,-hevc", &config.tDecSettings.eCodec,
              "Specify the input bitstream codec (default: HEVC)",
              AL_CODEC_HEVC);
  opt.addFlag("--jpeg,-jpeg", &config.tDecSettings.eCodec,
              "Specify the input bitstream codec (default: HEVC)",
              AL_CODEC_JPEG);
  opt.addInt("--framerate,--fps,-fps", &fps, "force framerate");
  opt.addCustom("--clock,--clk,-clk", &config.tDecSettings.uClkRatio, &IntWithOffset<1000>, "Set clock ratio, (0 for 1000, 1 for 1001)", "number");
  opt.addString("--bitdepth,--bd,-bd", &sOutputBitDepth, "Output YUV bitdepth (8, 10, 12, alloc (auto), stream, first)");
  opt.addString("--output-format", &sOutputFormat, "Output format FourCC (default: auto)");
  opt.addFlag("--sync-i-frames", &config.tDecSettings.bUseIFramesAsSyncPoint,
              "Allow decoder to sync on I frames if configurations' nals are presents",
              true);

  opt.addFlag("--wavefront-parallel-processing,--wpp,-wpp", &config.tDecSettings.bParallelWPP, "Wavefront parallelization processing activation");
  opt.addFlag("--low-latency-decoding,--lowlat,-lowlat", &config.tDecSettings.bLowLat, "Low latency decoding activation");
  opt.addOption("--slice-latency,--slicelat,-slicelat", [&](string)
  {
    config.tDecSettings.eDecUnit = AL_VCL_NAL_UNIT;
    config.tDecSettings.eDpbMode = AL_DPB_NO_REORDERING;
  }, "Specify decoder latency (default: Frame Latency)");

  opt.addFlag("--frame-latency,--framelat,-framelat", &config.tDecSettings.eDecUnit,
              "Specify decoder latency (default: Frame Latency)",
              AL_AU_UNIT);

  opt.addFlag("--no-reordering", &config.tDecSettings.eDpbMode,
              "Indicates to decoder that the stream doesn't contain B-frame & reference must be at best 1",
              AL_DPB_NO_REORDERING);

  opt.addOption("--fbuf-format,--ff,-ff", [&](string)
  {
    config.tDecSettings.eFBStorageMode = ParseFrameBufferFormat(opt.popWord(), config.tDecSettings.bFrameBufferCompression);
  }, "Specify the format of the decoded frame buffers (" + GetFrameBufferFormatOptDesc() + ")");

  opt.addOption("--fbuf-format-out,--ffo,-ffo", [&](string)
  {
    config.tUserOutputSettings.bCustomFormat = true;
    string sWordToParse = opt.popWord();
    config.tUserOutputSettings.tPicFormat.eStorageMode = ParseFrameBufferFormat(sWordToParse, config.tUserOutputSettings.tPicFormat.bCompressed);

    if(config.tUserOutputSettings.tPicFormat.eStorageMode == AL_FB_TILE_64x4 || config.tUserOutputSettings.tPicFormat.eStorageMode == AL_FB_TILE_32x4)
      config.tUserOutputSettings.tPicFormat.eSamplePackMode = AL_SAMPLE_PACK_MODE_PACKED;

  }, "Specify the format of the decoded frame buffers returned to the user (" + GetFrameBufferFormatOptDesc(true) + "). Default value aligned on --fbuf-format.");

  opt.addFlag("--split-input", &config.tDecSettings.eInputMode,
              "Send stream by decoding unit",
              AL_DEC_SPLIT_INPUT);
  opt.addString("--split-from-sizes", &config.sSplitSizesFile, "Send stream by decoding unit");
  opt.addString("--sei-file", &config.seiFile, "File in which the SEI decoded by the decoder will be dumped");
  opt.addString("--sei-file", &config.seiFile, "File in which the SEI decoded by the decoder will be dumped");

  opt.addString("--hdr-file", &config.hdrFile, "Parse and dump HDR data in the specified file");

  string preAllocArgs = "";
  opt.addString("--prealloc-args", &preAllocArgs, "Specify stream's parameters: 'widthxheight:video-mode:chroma-mode:bit-depth:profile:level' for example '1920x1080:progr:422:10:HEVC_MAIN:5'. video-mode values are: unkwn, progr or inter. Be careful cast is important.");
  opt.addCustom("--output-position", &config.tDecSettings.tOutputPosition, &CoupleWithSeparator<AL_TPosition, ','>, "Specify the position of the decoded frame in frame buffer");

  opt.addFlag("--decode-intraonly", &config.tDecSettings.tStream.bDecodeIntraOnly, "Decode Only I Frames");

  opt.startSection("Run");

  opt.addInt("--max-frames", &config.iMaxFrames, "Abort after max number of decoded frames (approximative abort)");
  opt.addInt("--loop,-loop", &config.iLoop, "Number of Decoding loop (optional)");
  opt.addInt("--timeout", &config.iTimeoutInSeconds, "Specify timeout in seconds");

  opt.addOption("--embedded,-embedded", [&](string)
  {
    config.iDeviceType = AL_DEVICE_TYPE_EMBEDDED;
  }, "Force usage of embedded mcu");

  bool dummyNextChan; // As the --next-channel is parsed elsewhere, this option is only used to add the description in the usage
  opt.addFlag("--next-chan", &dummyNextChan, "Start the configuration of a new decoding channel. The options that are applied on all channels must be specified in the first channel.");

  opt.addCustom("--exit-on", &config.eExitCondition, ParseExitOn, "Specifify early exit condition (e/error, w/warning)");

  opt.startSection("Trace && Debug");

  opt.addFlag("--multi-chunk", &config.bMultiChunk, "Allocate luma and chroma of decoded frames on different memory chunks");
  opt.addInt("--input-buffer-count,--nbuf,-nbuf", &config.uInputBufferNum, "Specify the number of input feeder buffer");
  opt.addInt("--input-buffer-size,--nsize,-nsize", &config.zInputBufferSize, "Specify the size (in bytes) of input feeder buffer");
  opt.addInt("--circular-buffer-size,-stream-buf-size", &config.tDecSettings.iStreamBufSize, "Specify the size (in bytes) of internal circular buffer size (0 = default)");

  opt.addString("--crc_ip,-crc_ip", &config.sCrc, "Output crc file");

  opt.addOption("--first-frame-to-trace,--t,-t", [&](string)
  {
    config.iTraceIdx = opt.popInt();
    config.iTraceNumber = std::max(1, config.iTraceNumber);
  }, "First frame to trace (optional)", "number");

  opt.addOption("--frame-to-trace-count,--num,-num", [&](string)
  {
    config.iTraceNumber = opt.popInt();
    config.iTraceIdx = std::max(0, config.iTraceIdx);
  }, "Number of frames to trace", "number");

  opt.addFlag("--use-early-callback", &config.tDecSettings.bUseEarlyCallback, "Low latency phase 2. Call end decoding at decoding launch. This only makes sense with special support for hardware synchronization");
  opt.addInt("--core,-core", &config.tDecSettings.uNumCore, "Number of decoder cores");
  opt.addFlag("--non-realtime", &config.tDecSettings.bNonRealtime, "Specifies that the channel is a non-realtime channel");
  opt.addInt("--ddrwidth,-ddrwidth", &config.tDecSettings.uDDRWidth, "Width of DDR requests (16, 32, 64) (default: 32)");
  opt.addFlag("--nocache,-nocache", &config.tDecSettings.bDisableCache, "Inactivate the cache");

  opt.addOption("--device", [&](string) {
    config.sDecDevicePath.insert(opt.popWord());
  }, std::string(std::string("Path of the driver device(s) file(s) used to talk with the IP. Default(s) are: ") + toStringPathsSet(sDecDefaultDevicePath)));

  opt.addFlag("--noyuv,-noyuv", &config.bEnableYUVOutput,
              "Disable writing output YUV file",
              false);

  opt.addString("--md5", &config.md5File, "Filename to the output MD5 of the YUV file");

  opt.addString("--log", &config.logsFile, "A file where logged events will be dumped");

  opt.startSection("Misc");
  opt.addOption("--color", [&](string)
  {
    SetEnableColor(true);
  }, "Enable color (Default: Auto)");

  opt.addOption("--no-color", [&](string)
  {
    SetEnableColor(false);
  }, "Disable color");

  opt.addFlag("--quiet,-q", &g_Verbosity, "Do not print anything", 0);
  opt.addInt("--verbosity", &g_Verbosity, "Choose the verbosity level (-q is equivalent to --verbosity 0)");

  opt.startDeprecatedSection();
  opt.addFlag("--lowref,-lowref", &config.tDecSettings.eDpbMode,
              "Use --no-reordering instead",
              AL_DPB_NO_REORDERING);

  opt.addUint("--conceal-max-fps", &config.tDecSettings.uConcealMaxFps, "Maximum fps to conceal invalid or corrupted stream header; 0 = no concealment");

  opt.addOption("--raster", [&](string)
  {
    config.tDecSettings.eFBStorageMode = AL_FB_RASTER;
    config.tDecSettings.bFrameBufferCompression = false;
  }, "Use \"--fbuf-format raster\" instead");

  AL_EFbStorageMode eDefaultTileStorageMode = AL_FB_TILE_32x4;

  opt.addOption("--tile", [&](string)
  {
    config.tDecSettings.eFBStorageMode = eDefaultTileStorageMode;
    config.tDecSettings.bFrameBufferCompression = false;
  }, "Use \"--fbuf-format tile\" instead");

  opt.addOption("--tile64", [&](string)
  {
    config.tDecSettings.eFBStorageMode = AL_FB_TILE_64x4;
    config.tDecSettings.bFrameBufferCompression = false;
  }, "Use \"--fbuf-format tile64\" instead");

  static const std::string OUT_RASTER_DESC = "Use \"-out <raster-file> --fbuf-format-out raster\" instead";
  opt.addString("--out-raster,-out-raster", &sRasterOut, OUT_RASTER_DESC);

  bool bHasDeprecated = opt.parse(argc, argv);

  if(config.help)
  {
    Usage(opt, argv[0]);
    return config;
  }

  if(helpJson)
  {
    opt.usageJson();
    exit(0);
  }

  if(version)
  {
    DisplayVersionInfo();
    DisplayBuildInfo();
    exit(0);
  }

  if(bHasDeprecated && g_Verbosity)
    opt.usageDeprecated();

  ProcessOutputArgs(config, sRasterOut);

  bool bMainOutputCompression = IsOutputStorageModeCompressed(config.tUserOutputSettings, config.tDecSettings.bFrameBufferCompression);

  if(bMainOutputCompression && config.bCertCRC)
    throw runtime_error("Certification CRC unavailable with fbc");

  if(config.sDecDevicePath.empty())
    config.sDecDevicePath = sDecDefaultDevicePath;

  if(fps > 0)
  {
    config.tDecSettings.uFrameRate = fps * 1000;
    config.tDecSettings.bForceFrameRate = true;
  }

  if(!config.sSplitSizesFile.empty())
    config.tDecSettings.eInputMode = AL_DEC_SPLIT_INPUT;

  if(!sOutputBitDepth.empty()
     )
  {
    config.iOutputBitDepth = ParseOutputBD(sOutputBitDepth);
  }

  if(!sOutputFormat.empty())
    config.tOutputFourCC = ParseFourCCFormat(sOutputFormat);

  {
    if(!preAllocArgs.empty())
    {
      ParsePreAllocArgs(&config.tDecSettings.tStream, config.tDecSettings.eCodec, preAllocArgs);

      /* For pre-allocation, we must use 8x8 (HEVC) or MB (AVC) rounded dimensions, like the SPS. */
      /* Actually, round up to the LCU so we're able to support resolution changes with the same LCU sizes. */
      /* And because we don't know the codec here, always use 64 as MB/LCU size. */
      int iAlignValue = 8;

      if(config.tDecSettings.eCodec == AL_CODEC_AVC)
        iAlignValue = 16;

      config.tDecSettings.tStream.tDim.iWidth = AL_RoundUp(config.tDecSettings.tStream.tDim.iWidth, iAlignValue);
      config.tDecSettings.tStream.tDim.iHeight = AL_RoundUp(config.tDecSettings.tStream.tDim.iHeight, iAlignValue);

      config.bUsePreAlloc = true;
    }

    if(config.tDecSettings.eInputMode == AL_DEC_SPLIT_INPUT && !config.bUsePreAlloc)
      throw std::runtime_error(" --split-input requires preallocation");

    if((config.tDecSettings.tOutputPosition.iX || config.tDecSettings.tOutputPosition.iY) && !config.bUsePreAlloc)
      throw std::runtime_error(" --output-position requires preallocation");
  }

  if(config.sIn.empty())
    throw runtime_error("No input file specified (use -h to get help)");

  return config;
}

bool IsOutputStorageModeCompressed(AL_TDecOutputSettings tUserOutputSettings, bool bMainOutputCompressed)
{
  (void)tUserOutputSettings;

  bool bOutputCompression = bMainOutputCompressed;

  if(tUserOutputSettings.bCustomFormat)
    bOutputCompression = tUserOutputSettings.tPicFormat.bCompressed;

  return bOutputCompression;
}

/******************************************************************************/
AL_EFbStorageMode GetMainOutputStorageMode(AL_TDecOutputSettings tUserOutputSettings, AL_EFbStorageMode eOutstorageMode)
{
  (void)tUserOutputSettings;
  AL_EFbStorageMode eOutputStorageMode = eOutstorageMode;

  if(tUserOutputSettings.bCustomFormat)
  {
    if(tUserOutputSettings.tPicFormat.eStorageMode != AL_FB_MAX_ENUM)
      eOutputStorageMode = tUserOutputSettings.tPicFormat.eStorageMode;
    else
      eOutputStorageMode = AL_FB_RASTER;
  }

  return eOutputStorageMode;
}

