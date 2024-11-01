// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_common/PicFormat.h"
#include <climits>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <regex>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#if defined(__linux__)
#include <dirent.h>
#endif

#if defined(_WIN32)
#include "extra/dirent/include/dirent.h"
#endif

#include "lib_app/BufPool.h"
#include "lib_app/FileUtils.h"
#include "lib_app/PixMapBufPool.h"
#include "lib_app/YuvIO.h"
#include "lib_app/console.h"
#include "lib_app/plateform.h"
#include "lib_app/utils.h"
#include "lib_app/CompFrameReader.h"
#include "lib_app/CompFrameCommon.h"
#include "lib_app/UnCompFrameReader.h"
#include "lib_app/SinkFrame.h"

#include "CfgParser.h"
#include "CodecUtils.h"
#include "IpDevice.h"
#include "resource.h"

extern "C" {
#include "lib_common/BufferPictureMeta.h"
#include "lib_common/BufferStreamMeta.h"
#include "lib_common/Error.h"
#include "lib_common/PixMapBuffer.h"
#include "lib_common/RoundUp.h"
#include "lib_common/StreamBuffer.h"
#include "lib_common_enc/RateCtrlMeta.h"
#include "lib_encode/lib_encoder.h"
#include "lib_rtos/lib_rtos.h"
#include "lib_common_enc/EncBuffers.h"
#include "lib_common_enc/IpEncFourCC.h"
}

#include "lib_conv_yuv/lib_conv_yuv.h"
#include "lib_conv_yuv/AL_RasterConvert.h"

#include "sink_encoder.h"
#include "sink_yuv_md5.h"
#include "sink_lookahead.h"
#include "QPGenerator.h"
#include "lib_app/SinkStreamMd5.h"
#include "sink_bitrate.h"
#include "sink_bitstream_writer.h"
#include "sink_repeater.h"

#include "RCPlugin.h"

static int g_numFrameToRepeat;
static int g_StrideHeight = -1;
static int g_Stride = -1;
static int constexpr g_defaultMinBuffers = 2;
static bool g_MultiChunk = false;

using namespace std;

static std::string toStringPathsSet(std::vector<std::string> paths)
{
  std::string out;

  for(auto const& path : paths)
  {
    if(out.length() != 0)
      out += string(", ");
    out += path;
  }

  return out;
}

/*****************************************************************************/
AL_HANDLE alignedAlloc(AL_TAllocator* pAllocator, char const* pBufName, uint32_t uSize, uint32_t uAlign, uint32_t* uAllocatedSize, uint32_t* uAlignmentOffset)
{
  *uAllocatedSize = 0;
  *uAlignmentOffset = 0;

  uSize += uAlign;

  auto pBuf = AL_Allocator_AllocNamed(pAllocator, uSize, pBufName);

  if(pBuf == nullptr)
    return nullptr;

  *uAllocatedSize = uSize;
  AL_PADDR pAddr = AL_Allocator_GetPhysicalAddr(pAllocator, pBuf);
  *uAlignmentOffset = AL_PhysAddrRoundUp(pAddr, uAlign) - pAddr;

  return pBuf;
}

/*****************************************************************************/

#include "lib_app/BuildInfo.h"

#if !HAS_COMPIL_FLAGS
#define AL_COMPIL_FLAGS ""
#endif

void DisplayBuildInfo(void)
{
  BuildInfoDisplay displayBuildInfo {
    SCM_REV_SW, SCM_BRANCH, AL_CONFIGURE_COMMANDLINE, AL_COMPIL_FLAGS, DELIVERY_BUILD_NUMBER, DELIVERY_SCM_REV, DELIVERY_DATE
  };
  displayBuildInfo.displayFeatures = [=](void)
                                     {
                                     };

  displayBuildInfo();
}

void DisplayVersionInfo(void)
{
  DisplayVersionInfo(AL_ENCODER_COMPANY,
                     AL_ENCODER_PRODUCT_NAME,
                     AL_ENCODER_VERSION,
                     AL_ENCODER_COPYRIGHT,
                     AL_ENCODER_COMMENTS);
}

/*****************************************************************************/
void SetDefaults(ConfigFile& cfg)
{
  cfg.BitstreamFileName = "Stream.bin";
  cfg.RecFourCC = FOURCC(NULL);
  AL_Settings_SetDefaults(&cfg.Settings);
  cfg.MainInput.FileInfo.FourCC = FOURCC(I420);
  cfg.MainInput.FileInfo.FrameRate = 0;
  cfg.MainInput.FileInfo.PictHeight = 0;
  cfg.MainInput.FileInfo.PictWidth = 0;
  cfg.RunInfo.encDevicePaths = ENCODER_DEVICES;
  cfg.RunInfo.eDeviceType = AL_EDeviceType::AL_DEVICE_TYPE_EMBEDDED;
  cfg.RunInfo.eSchedulerType = AL_ESchedulerType::AL_SCHEDULER_TYPE_CPU;
  cfg.RunInfo.bLoop = false;
  cfg.RunInfo.iMaxPict = INT_MAX; // ALL
  cfg.RunInfo.iFirstPict = 0;
  cfg.RunInfo.iScnChgLookAhead = 3;
  cfg.RunInfo.ipCtrlMode = AL_EIpCtrlMode::AL_IPCTRL_MODE_STANDARD;
  cfg.RunInfo.uInputSleepInMilliseconds = 0;
  cfg.strict_mode = false;
  cfg.iForceStreamBufSize = 0;
}

#include "lib_app/CommandLineParser.h"

static void Usage(CommandLineParser const& opt, char* ExeName)
{
  cout << "Usage: " << ExeName << " -cfg <configfile> [options]" << endl;
  cout << "Options:" << endl;

  opt.usage();

  cout << endl << "Examples:" << endl;
  cout << "  " << ExeName << " -cfg test/config/encode_simple.cfg -r rec.yuv -o output.hevc -i input.yuv" << endl;
}

static AL_EChromaMode stringToChromaMode(string s)
{
  if(s == "CHROMA_MONO")
    return AL_CHROMA_MONO;

  if(s == "CHROMA_4_0_0")
    return AL_CHROMA_4_0_0;

  if(s == "CHROMA_4_2_0")
    return AL_CHROMA_4_2_0;

  if(s == "CHROMA_4_2_2")
    return AL_CHROMA_4_2_2;

  if(s == "CHROMA_4_4_4")
    return AL_CHROMA_4_4_4;

  throw runtime_error("Unknown chroma mode: \"" + s + "\"");
}

static AL_EMultiChipClipMode stringToMultiChipClipMode(string const& sMCClipOption)
{
  map<char, AL_EMultiChipClipMode> mCClipMap =
  {
    { 'L', AL_MC_CLIP_LEFT }, { 'R', AL_MC_CLIP_RIGHT }, { 'T', AL_MC_CLIP_TOP }, { 'B', AL_MC_CLIP_BOTTOM }
  };
  AL_EMultiChipClipMode eMCClip = AL_MC_CLIP_NONE;

  if(sMCClipOption.empty() || sMCClipOption.length() > mCClipMap.size() || sMCClipOption.find_first_not_of("LRTB") != string::npos)
    throw runtime_error("Multi chip clip option must be a subset of: LRTB (Left, Right, Top, Bottom)");

  for(auto it = sMCClipOption.begin(); it != sMCClipOption.end(); ++it)
  {
    eMCClip = (AL_EMultiChipClipMode)(eMCClip | mCClipMap[*it]);
  }

  return eMCClip;
}

template<typename T>
function<T(string const &)> createCmdlineParsingFunc(CfgParser* pCfgParser, char const* name_, function<T(ConfigFile &)> extractWantedValue)
{
  string name = name_;
  auto lambda = [=](string const& value)
                {
                  ConfigFile cfg {};
                  cfg.strict_mode = true;
                  string toParse = name + string("=") + value;
                  pCfgParser->ParseConfig(toParse, cfg);
                  return extractWantedValue(cfg);
                };
  return lambda;
}

function<TFourCC(string const &)> createParseInputFourCC(CfgParser* pCfgParser)
{
  return createCmdlineParsingFunc<TFourCC>(pCfgParser, "[INPUT]\nFormat", [](ConfigFile& cfg) { return cfg.MainInput.FileInfo.FourCC; });
}

function<TFourCC(string const &)> createParseRecFourCC(CfgParser* pCfgParser)
{
  return createCmdlineParsingFunc<TFourCC>(pCfgParser, "[OUTPUT]\nFormat", [](ConfigFile& cfg) { return cfg.RecFourCC; });
}

function<AL_EProfile(string const &)> createParseProfile(CfgParser* pCfgParser)
{
  return createCmdlineParsingFunc<AL_EProfile>(pCfgParser, "[SETTINGS]\nProfile", [](ConfigFile& cfg) { return cfg.Settings.tChParam[0].eProfile; });
}

function<AL_ERateCtrlMode(string const &)> createParseRCMode(CfgParser* pCfgParser)
{
  return createCmdlineParsingFunc<AL_ERateCtrlMode>(pCfgParser, "[RATE_CONTROL]\nRateCtrlMode", [](ConfigFile& cfg) { return cfg.Settings.tChParam[0].tRCParam.eRCMode; });
}

function<AL_EGopCtrlMode(string const &)> createParseGopMode(CfgParser* pCfgParser)
{
  return createCmdlineParsingFunc<AL_EGopCtrlMode>(pCfgParser, "[GOP]\nGopCtrlMode", [](ConfigFile& cfg) { return cfg.Settings.tChParam[0].tGopParam.eMode; });
}

void introspect(ConfigFile& cfg)
{
  (void)cfg;
  throw runtime_error("introspection is not compiled in");
}

static void SetCodingResolution(ConfigFile& cfg)
{
  int iMaxSrcWidth = cfg.MainInput.FileInfo.PictWidth;
  int iMaxSrcHeight = cfg.MainInput.FileInfo.PictHeight;

  for(auto const& input: cfg.DynamicInputs)
  {
    iMaxSrcWidth = max(input.FileInfo.PictWidth, iMaxSrcWidth);
    iMaxSrcHeight = max(input.FileInfo.PictHeight, iMaxSrcHeight);
  }

  cfg.Settings.tChParam[0].uSrcWidth = iMaxSrcWidth;
  cfg.Settings.tChParam[0].uSrcHeight = iMaxSrcHeight;

  cfg.Settings.tChParam[0].uEncWidth = cfg.Settings.tChParam[0].uSrcWidth;
  cfg.Settings.tChParam[0].uEncHeight = cfg.Settings.tChParam[0].uSrcHeight;

  if(cfg.Settings.tChParam[0].bEnableSrcCrop)
  {
    cfg.Settings.tChParam[0].uEncWidth = cfg.Settings.tChParam[0].uSrcCropWidth;
    cfg.Settings.tChParam[0].uEncHeight = cfg.Settings.tChParam[0].uSrcCropHeight;
  }
}

/*****************************************************************************/
void ParseCommandLine(int argc, char** argv, ConfigFile& cfg, CfgParser& cfgParser)
{
  bool DoNotAcceptCfg = false;
  bool help = false;
  bool helpJson = false;
  bool version = false;
  stringstream warning;
  auto opt = CommandLineParser([&](string word)
  {
    if(word == "-cfg" || word == "-cfg-permissive" || word == "--cfg" || word == "--cfg-permissive")
    {
      if(DoNotAcceptCfg)
        throw runtime_error("Configuration files should be specified first, use -h to get help");
    }
    else
      DoNotAcceptCfg = true;
  });

  opt.addFlag("--help,-h", &help, "Show this help");
  opt.addFlag("--help-json", &helpJson, "Show this help (json)");
  opt.addFlag("--version", &version, "Show version");

  opt.addOption("--cfg,-cfg", [&](string)
  {
    auto const cfgPath = opt.popWord();
    cfg.strict_mode = true;
    cfgParser.ParseConfigFile(cfgPath, cfg, warning);
  }, "Specify configuration file", "string");

  opt.addOption("--cfg-permissive,-cfg-permissive", [&](string)
  {
    auto const cfgPath = opt.popWord();
    cfgParser.ParseConfigFile(cfgPath, cfg, warning);
  }, "Use it instead of -cfg. Errors in the configuration file will be ignored", "string");

  opt.addOption("--set", [&](string)
  {
    cfgParser.ParseConfig(opt.popWord(), cfg);
  }, "Use the same syntax as in the cfg to specify a parameter (Example: --set \"[INPUT] Width = 512\"", "string");

  opt.addString("--input,-i", &cfg.MainInput.YUVFileName, "YUV input file");
  opt.addString("--map,-m", &cfg.MainInput.sMapFileName, "Map input file");
  opt.addString("--output,-o", &cfg.BitstreamFileName, "Compressed output file");
  opt.addString("--output-rec,-r", &cfg.RecFileName, "Output reconstructed YUV file");
  opt.addString("--md5-rec", &cfg.RunInfo.sRecMd5Path, "Filename to the output MD5 of the reconstructed pictures");
  opt.addString("--md5-stream", &cfg.RunInfo.sStreamMd5Path, "Filename to the output MD5 of the bitstream");
  opt.addInt("--input-width", &cfg.MainInput.FileInfo.PictWidth, "Specifies YUV input width");
  opt.addInt("--input-height", &cfg.MainInput.FileInfo.PictHeight, "Specifies YUV input height");
  opt.addCustom("--input-format", &cfg.MainInput.FileInfo.FourCC, createParseInputFourCC(&cfgParser), "Specifies YUV input format (I420, IYUV, YV12, NV12, Y800, Y010, P010, I0AL ...)", "enum");
  opt.addCustom("--rec-format", &cfg.RecFourCC, createParseRecFourCC(&cfgParser), "Specifies output format", "enum");

  opt.addInt("--level", &cfg.Settings.tChParam[0].uLevel, "Specifies the level we want to encode with (10 to 62)");
  opt.addCustom("--profile", &cfg.Settings.tChParam[0].eProfile, createParseProfile(&cfgParser), string { "Specifies the profile we want to encode with (examples: " } +
                string { "HEVC_MAIN, " } +
                string { "AVC_MAIN, " } +
                string { "..)" }, "enum");
  opt.addOption("--chroma-mode", [&](string)
  {
    auto chromaMode = stringToChromaMode(opt.popWord());
    AL_SET_CHROMA_MODE(&cfg.Settings.tChParam[0].ePicFormat, chromaMode);
  }, string { "Specify chroma-mode (CHROMA_MONO, CHROMA_4_0_0" } +
                string { ", CHROMA_4_2_0" } +
                string { ", CHROMA_4_2_2" } +
                string { ", CHROMA_4_4_4" } +
                string { ")" }, "enum");

  int outputBitdepth = -1;
  opt.addInt("--out-bitdepth", &outputBitdepth, string { "Specifies bitdepth of output stream (8" } +
             string { ", 10" } +
             string { ", 12" } +
             string { ")" });

  opt.addInt("--num-slices", &cfg.Settings.tChParam[0].uNumSlices, "Specifies the number of slices to use");
  opt.addFlag("--slicelat", &cfg.Settings.tChParam[0].bSubframeLatency, "Enable subframe latency");
  opt.addFlag("--framelat", &cfg.Settings.tChParam[0].bSubframeLatency, "Disable subframe latency", false);
  opt.addString("--gmv", &cfg.sGMVFileName, "A file where the global motion vector which will be used to encode are stored");

  opt.addInt("--lookahead", &cfg.Settings.LookAhead, "Set the twopass LookAhead size");
  opt.addInt("--pass", &cfg.Settings.TwoPass, "Specify which pass we are encoding");
  opt.addString("--pass-logfile", &cfg.sTwoPassFileName, "LogFile to transmit dual pass statistics");
  opt.addFlag("--first-pass-scd", &cfg.Settings.bEnableFirstPassSceneChangeDetection, "During first pass, the encoder encode faster by only enabling scene change detection");

  opt.startSection("Rate Control && GOP");
  opt.addCustom("--ratectrl-mode", &cfg.Settings.tChParam[0].tRCParam.eRCMode, createParseRCMode(&cfgParser),
                "Specifies rate control mode (CONST_QP, CBR, VBR"
                ", LOW_LATENCY"
                ")", "enum"
                );
  opt.addOption("--bitrate", [&](string)
  {
    cfg.Settings.tChParam[0].tRCParam.uTargetBitRate = opt.popInt() * 1000;
  }, "Specifies bitrate in Kbits/s", "number");
  opt.addOption("--max-bitrate", [&](string)
  {
    cfg.Settings.tChParam[0].tRCParam.uMaxBitRate = opt.popInt() * 1000;
  }, "Specifies max bitrate in Kbits/s", "number");
  opt.addOption("--framerate", [&](string)
  {
    cfgParser.ParseConfig("[RATE_CONTROL]\nFrameRate=" + opt.popWord(), cfg);
  }, "Specifies the frame rate used for encoding", "number");
  opt.addInt("--sliceQP", &cfg.Settings.tChParam[0].tRCParam.iInitialQP, "Specifies the initial slice QP");

  opt.addCustom("--gop-mode", &cfg.Settings.tChParam[0].tGopParam.eMode, createParseGopMode(&cfgParser), "Specifies gop control mode (DEFAULT_GOP, LOW_DELAY_P)", "enum");
  opt.addInt("--gop-length", &cfg.Settings.tChParam[0].tGopParam.uGopLength, "Specifies the GOP length, 1 means I slice only");
  opt.addInt("--gop-numB", &cfg.Settings.tChParam[0].tGopParam.uNumB, "Number of consecutive B frame (0 .. 4)");

  opt.startSection("Run");

  opt.addInt("--first-picture", &cfg.RunInfo.iFirstPict, "First picture encoded (skip those before)");
  opt.addInt("--max-picture", &cfg.RunInfo.iMaxPict, "Maximum number of pictures encoded (1,2 .. -1 for ALL)");
  opt.addFlag("--loop", &cfg.RunInfo.bLoop, "Loop at the end of the yuv file");

  opt.addFlag("--embedded", &cfg.RunInfo.eDeviceType, "Force usage of embedded mcu", AL_EDeviceType::AL_DEVICE_TYPE_EMBEDDED);

  opt.addFlag("--multi-inst", &cfg.RunInfo.eSchedulerType, "Allow encoding spread on multiple IP instances", AL_ESchedulerType::AL_SCHEDULER_TYPE_MULTIINST);

  opt.addInt("--input-sleep", &cfg.RunInfo.uInputSleepInMilliseconds, "Minimum waiting time in milliseconds between each process frame (0 by default)");

  opt.startSection("Traces && Debug");

  opt.addInt("--stride-height", &g_StrideHeight, "Chroma offset (vertical stride)");
  opt.addInt("--stride", &g_Stride, "Luma stride");
  opt.addFlag("--multi-chunk", &g_MultiChunk, "Allocate source luma and chroma on different memory chunks");
  opt.addInt("--num-core", &cfg.Settings.tChParam[0].uNumCore, "Specifies the number of cores to use (resolution needs to be sufficient)");

  opt.addInt("--stream-buf-size", &cfg.iForceStreamBufSize, "Specify stream buffers size");
  opt.addFlag("--non-realtime", &cfg.Settings.tChParam[0].bNonRealtime, "Specifies that the channel is a non-realtime channel");
  opt.addFlag("--print-ratectrl-stat", &cfg.RunInfo.printRateCtrlStat, "Write rate-control related statistics for each frame in the file. Only a subset of the statistics is written, more data and motion vectors are also available.", true);
  opt.addFlag("--print-picture-type", &cfg.RunInfo.printPictureType, "Write picture type for each frame in the file", true);

  opt.addOption("--mc-clip", [&](string)
  {
    cfg.Settings.tChParam[0].tMCParam.eMCClipMode = stringToMultiChipClipMode(opt.popWord());
  }, "Multi-chip clip options: (Subset of LRTB)", "enum");
  opt.addOption("--device", [&](string) {
    cfg.RunInfo.encDevicePaths.push_back(opt.popWord());
  }, std::string(std::string("Path of the driver device(s) file(s) used to talk with the IP. Default(s) are: ") + toStringPathsSet(cfg.RunInfo.encDevicePaths)));
  opt.startSection("Misc");

  opt.addOption("--color", [&](string)
  {
    SetEnableColor(true);
  }, "Enable the display of command line color (Default: Auto)");

  opt.addOption("--no-color", [&](string)
  {
    SetEnableColor(false);
  }, "Disable the display of command line color");

  opt.addFlag("--quiet,-q", &g_Verbosity, "Do not print anything", 0);
  opt.addInt("--verbosity", &g_Verbosity, "Choose the verbosity level (-q is equivalent to --verbosity 0)");

  opt.startDeprecatedSection();
  opt.addString("--md5", &cfg.RunInfo.sRecMd5Path, "Use --md5-rec instead");
  opt.addInt("--ip-bitdepth", &outputBitdepth, "Use --out-bitdepth instead");

  opt.addFlag("--diagnostic", &cfg.Settings.bDiagnostic, "Additional checks meant for debugging. Not to be used on real usecases, might slow down encoding.");

  bool bHasDeprecated = opt.parse(argc, argv);
  cfgParser.PostParsingConfiguration(cfg, warning);

  if(help)
  {
    Usage(opt, argv[0]);
    exit(0);
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

  if(g_Verbosity)
    cerr << warning.str();

  SetCodingResolution(cfg);

  if(outputBitdepth != -1)
    AL_SET_BITDEPTH(&cfg.Settings.tChParam[0].ePicFormat, outputBitdepth);

  cfg.Settings.tChParam[0].uSrcBitDepth = AL_GET_BITDEPTH(cfg.Settings.tChParam[0].ePicFormat);

  if(AL_IS_STILL_PROFILE(cfg.Settings.tChParam[0].eProfile))
    cfg.RunInfo.iMaxPict = 1;

}

bool checkQPTableFolder(ConfigFile& cfg)
{
  std::regex qp_file_per_frame_regex("QP(^|)(s|_[0-9]+)\\.hex");

  if(!checkFolder(cfg.MainInput.sQPTablesFolder))
    return false;

  return checkFileAvailability(cfg.MainInput.sQPTablesFolder, qp_file_per_frame_regex);
}

void ValidateConfig(ConfigFile& cfg)
{
  string const invalid_settings("Invalid settings, check the [SETTINGS] section of your configuration file or check your commandline (use -h to get help)");

  if(cfg.MainInput.YUVFileName.empty())
    throw runtime_error("No YUV input was given, specify it in the [INPUT] section of your configuration file or in your commandline (use -h to get help)");

  if(!cfg.MainInput.sQPTablesFolder.empty() && ((cfg.RunInfo.eGenerateQpMode & AL_GENERATE_QP_TABLE_MASK) != AL_GENERATE_LOAD_QP))
    throw runtime_error("QPTablesFolder can only be specified with Load QP control mode");

  SetConsoleColor(CC_RED);

  FILE* out = stdout;

  if(!g_Verbosity)
    out = nullptr;

  auto const MaxLayer = cfg.Settings.NumLayer - 1;

  for(int i = 0; i < cfg.Settings.NumLayer; ++i)
  {
    auto const err = AL_Settings_CheckValidity(&cfg.Settings, &cfg.Settings.tChParam[i], out);

    if(err != 0)
    {
      stringstream ss;
      ss << "Found: " << err << " errors(s). " << invalid_settings;
      throw runtime_error(ss.str());
    }

    if((cfg.RunInfo.eGenerateQpMode & AL_GENERATE_QP_TABLE_MASK) == AL_GENERATE_LOAD_QP)
    {
      if(!checkQPTableFolder(cfg))
        throw runtime_error("No QP File found");
    }

    auto const incoherencies = AL_Settings_CheckCoherency(&cfg.Settings, &cfg.Settings.tChParam[i], cfg.MainInput.FileInfo.FourCC, out);

    if(incoherencies == -1)
      throw runtime_error("Fatal coherency error in settings (layer[" + to_string(i) + "/" + to_string(MaxLayer) + "])");

  }

  if(cfg.Settings.TwoPass == 1)
    AL_TwoPassMngr_SetPass1Settings(cfg.Settings);

  SetConsoleColor(CC_DEFAULT);
}

void SetMoreDefaults(ConfigFile& cfg)
{
  auto& FileInfo = cfg.MainInput.FileInfo;
  auto& Settings = cfg.Settings;
  auto& RecFourCC = cfg.RecFourCC;

  if(FileInfo.FrameRate == 0)
    FileInfo.FrameRate = Settings.tChParam[0].tRCParam.uFrameRate;

  if(RecFourCC == FOURCC(NULL))
  {
    AL_TPicFormat tOutPicFormat;

    if(AL_GetPicFormat(FileInfo.FourCC, &tOutPicFormat))
    {
      if(tOutPicFormat.eComponentOrder != AL_COMPONENT_ORDER_RGB && tOutPicFormat.eComponentOrder != AL_COMPONENT_ORDER_BGR)
        tOutPicFormat.eChromaMode = AL_GET_CHROMA_MODE(Settings.tChParam[0].ePicFormat);
      tOutPicFormat.ePlaneMode = tOutPicFormat.eChromaMode == AL_CHROMA_MONO ? AL_PLANE_MODE_MONOPLANE : tOutPicFormat.ePlaneMode;
      tOutPicFormat.uBitDepth = AL_GET_BITDEPTH(Settings.tChParam[0].ePicFormat);
      RecFourCC = AL_GetFourCC(tOutPicFormat);
    }
    else
    {
      RecFourCC = FileInfo.FourCC;
    }
  }

  AL_TPicFormat tRecPicFormat;

  if(AL_GetPicFormat(RecFourCC, &tRecPicFormat))
  {
    auto& RecFileName = cfg.RecFileName;

    if(!RecFileName.empty())
      if(tRecPicFormat.eStorageMode != AL_FB_RASTER && !tRecPicFormat.bCompressed)
        throw runtime_error("Reconstructed storage format can only be tiled if compressed.");
  }
}

/*****************************************************************************/
static shared_ptr<AL_TBuffer> AllocateConversionBuffer(int iWidth, int iHeight, TFourCC tFourCC)
{
  AL_TBuffer* pYuv = AllocateDefaultYuvIOBuffer(AL_TDimension { iWidth, iHeight }, tFourCC);

  if(pYuv == nullptr)
    return nullptr;
  return shared_ptr<AL_TBuffer>(pYuv, &AL_Buffer_Destroy);
}

bool ReadSourceFrameBuffer(AL_TBuffer* pBuffer, AL_TBuffer* conversionBuffer, unique_ptr<FrameReader> const& frameReader, AL_TDimension tUpdatedDim, uint8_t uSrcBitDepth, IConvSrc* hConv)
{

  AL_PixMapBuffer_SetDimension(pBuffer, tUpdatedDim);

  if(hConv)
  {
    AL_PixMapBuffer_SetDimension(conversionBuffer, tUpdatedDim);

    if(!frameReader->ReadFrame(conversionBuffer))
      return false;
    hConv->ConvertSrcBuf(uSrcBitDepth, conversionBuffer, pBuffer);
  }
  else
    return frameReader->ReadFrame(pBuffer);

  return true;
}

shared_ptr<AL_TBuffer> ReadSourceFrame(BaseBufPool* pBufPool, AL_TBuffer* conversionBuffer, unique_ptr<FrameReader> const& frameReader, AL_TDimension tUpdatedDim, uint8_t uSrcBitDepth, IConvSrc* hConv)
{
  shared_ptr<AL_TBuffer> sourceBuffer = pBufPool->GetSharedBuffer();

  if(sourceBuffer == nullptr)
    throw runtime_error("sourceBuffer must exist");

  if(!ReadSourceFrameBuffer(sourceBuffer.get(), conversionBuffer, frameReader, tUpdatedDim, uSrcBitDepth, hConv))
    return nullptr;
  return sourceBuffer;
}

AL_TPicFormat GetSrcPicFormat(AL_TEncChanParam const& tChParam)
{
  AL_ESrcMode eSrcMode = tChParam.eSrcMode;
  auto eChromaMode = AL_GET_CHROMA_MODE(tChParam.ePicFormat);

  return AL_EncGetSrcPicFormat(eChromaMode, tChParam.uSrcBitDepth, eSrcMode);
}

void CheckSrcComp(TFourCC tFileFourCC, TFourCC tSrcFourCC)
{
  if(AL_GetBitDepth(tFileFourCC) != AL_GetBitDepth(tSrcFourCC))
    throw runtime_error("We can't convert BitDepth for compressed source.");

  if(AL_GetChromaMode(tFileFourCC) != AL_GetChromaMode(tSrcFourCC))
    throw runtime_error("We can't convert ChromaMode for compressed source.");
}

struct SrcConverterParams
{
  AL_TDimension tDim;
  TFourCC tFileFourCC;
  AL_TPicFormat tSrcPicFmt;
  AL_ESrcFormat eSrcFormat;
};

unique_ptr<IConvSrc> AllocateSrcConverter(SrcConverterParams const& tSrcConverterParams, shared_ptr<AL_TBuffer>& pFileReaderYuv)
{
  pFileReaderYuv = nullptr;

  const TFourCC tSrcFourCC = AL_GetFourCC(tSrcConverterParams.tSrcPicFmt);
  bool bIsConversionNeeded = tSrcConverterParams.tFileFourCC != tSrcFourCC;

  if(!bIsConversionNeeded)
    return nullptr;

  if(AL_IsCompressed(tSrcFourCC))
    CheckSrcComp(tSrcConverterParams.tFileFourCC, tSrcFourCC);

  // ********** Allocate the YUV buffer to read in the file **********
  pFileReaderYuv = AllocateConversionBuffer(tSrcConverterParams.tDim.iWidth, tSrcConverterParams.tDim.iHeight, tSrcConverterParams.tFileFourCC);

  if(pFileReaderYuv == nullptr)
    throw runtime_error("Couldn't allocate source conversion buffer");

  // ************* Allocate the YUV converter *************
  TFrameInfo tSrcFrameInfo = { tSrcConverterParams.tDim, tSrcConverterParams.tSrcPicFmt.uBitDepth, tSrcConverterParams.tSrcPicFmt.eChromaMode };
  (void)tSrcFrameInfo;

  switch(tSrcConverterParams.eSrcFormat)
  {
  case AL_SRC_FORMAT_RASTER:
    return make_unique<CYuvSrcConv>(tSrcFrameInfo);
  case AL_SRC_FORMAT_RASTER_MSB:
    return make_unique<CYuvSrcConv>(tSrcFrameInfo);
  case AL_SRC_FORMAT_TILE_64x4:
  case AL_SRC_FORMAT_TILE_32x4:
    return make_unique<CYuvSrcConv>(tSrcFrameInfo);
  default:
    throw runtime_error("Unsupported source conversion.");
  }

  return nullptr;
}

static int ComputeYPitch(int iWidth, const AL_TPicFormat& tPicFormat)
{
  auto iPitch = AL_EncGetMinPitch(iWidth, &tPicFormat);

  if(g_Stride != -1)
  {
    if(g_Stride < iPitch)
      throw runtime_error("g_Stride(" + to_string(g_Stride) + ") must be higher or equal than iPitch(" + to_string(iPitch) + ")");
    iPitch = g_Stride;
  }
  return iPitch;
}

static bool isLastPict(int iPictCount, int iMaxPict)
{
  return (iPictCount >= iMaxPict) && (iMaxPict != -1);
}

static shared_ptr<AL_TBuffer> GetSrcFrame(int& iReadCount, int iPictCount, unique_ptr<FrameReader> const& frameReader, AL_TYUVFileInfo const& FileInfo, PixMapBufPool& SrcBufPool, AL_TBuffer* Yuv, AL_TEncChanParam const& tChParam, ConfigFile const& cfg, IConvSrc* pSrcConv)
{
  shared_ptr<AL_TBuffer> frame;

  if(!isLastPict(iPictCount, cfg.RunInfo.iMaxPict))
  {
    if(cfg.MainInput.FileInfo.FrameRate != tChParam.tRCParam.uFrameRate)
    {
      iReadCount += frameReader->GotoNextPicture(FileInfo.FrameRate, tChParam.tRCParam.uFrameRate, iPictCount, iReadCount);
    }

    auto tUpdatedDim = AL_TDimension {
      AL_GetSrcWidth(tChParam), AL_GetSrcHeight(tChParam)
    };
    frame = ReadSourceFrame(&SrcBufPool, Yuv, frameReader, tUpdatedDim, tChParam.uSrcBitDepth, pSrcConv);

    iReadCount++;
  }
  return frame;
}

AL_ESrcMode SrcFormatToSrcMode(AL_ESrcFormat eSrcFormat)
{
  switch(eSrcFormat)
  {
  case AL_SRC_FORMAT_RASTER:
    return AL_SRC_RASTER;
  case AL_SRC_FORMAT_RASTER_MSB:
    return AL_SRC_RASTER_MSB;
  case AL_SRC_FORMAT_TILE_64x4:
    return AL_SRC_TILE_64x4;
  case AL_SRC_FORMAT_TILE_32x4:
    return AL_SRC_TILE_32x4;
  default:
    throw runtime_error("Unsupported source format.");
  }
}

/*****************************************************************************/
static bool InitQpBufPool(BufPool& pool, AL_TEncSettings& Settings, AL_TEncChanParam& tChParam, int frameBuffersCount, AL_TAllocator* pAllocator)
{
  if(!AL_IS_QP_TABLE_REQUIRED(Settings.eQpTableMode))
    return true;

  AL_TDimension tDim = { tChParam.uEncWidth, tChParam.uEncHeight };
  return pool.Init(pAllocator, frameBuffersCount, AL_GetAllocSizeEP2(tDim, static_cast<AL_ECodec>(AL_GET_CODEC(tChParam.eProfile)), tChParam.uLog2MaxCuSize), nullptr, "qp-ext");
}

/*****************************************************************************/
struct SrcBufChunk
{
  int iChunkSize;
  std::vector<AL_TPlaneDescription> vPlaneDesc;
};

struct SrcBufDesc
{
  TFourCC tFourCC;
  std::vector<SrcBufChunk> vChunks;
};

static SrcBufDesc GetSrcBufDescription(AL_TDimension tDimension, uint8_t uBitDepth, AL_EChromaMode eCMode, AL_ESrcMode eSrcMode, AL_ECodec eCodec)
{
  (void)eCodec;

  AL_TPicFormat const tPicFormat = AL_EncGetSrcPicFormat(eCMode, uBitDepth, eSrcMode);

  SrcBufDesc srcBufDesc =
  {
    AL_GetFourCC(tPicFormat), {}
  };

  int iPitchY = ComputeYPitch(tDimension.iWidth, tPicFormat);

  int iAlignValue = 8;

  int iStrideHeight = g_StrideHeight != -1 ? g_StrideHeight : AL_RoundUp(tDimension.iHeight, iAlignValue);

  SrcBufChunk srcChunk = {};

  AL_EPlaneId usedPlanes[AL_MAX_BUFFER_PLANES];
  int iNbPlanes = AL_Plane_GetBufferPixelPlanes(tPicFormat, usedPlanes);

  for(int iPlane = 0; iPlane < iNbPlanes; iPlane++)
  {
    int iPitch = usedPlanes[iPlane] == AL_PLANE_Y ? iPitchY : AL_GetChromaPitch(srcBufDesc.tFourCC, iPitchY);
    srcChunk.vPlaneDesc.push_back(AL_TPlaneDescription { usedPlanes[iPlane], srcChunk.iChunkSize, iPitch });
    srcChunk.iChunkSize += AL_GetAllocSizeSrc_PixPlane(&tPicFormat, iPitchY, iStrideHeight, usedPlanes[iPlane]);

    if(g_MultiChunk)
    {
      srcBufDesc.vChunks.push_back(srcChunk);
      srcChunk = {};
    }
  }

  if(!g_MultiChunk)
    srcBufDesc.vChunks.push_back(srcChunk);

  return srcBufDesc;
}

/*****************************************************************************/
static uint8_t GetNumBufForGop(AL_TEncSettings Settings)
{
  int uNumFields = 1;

  if(AL_IS_INTERLACED(Settings.tChParam[0].eVideoMode))
    uNumFields = 2;
  int uAdditionalBuf = 0;
  return uNumFields * Settings.tChParam[0].tGopParam.uNumB + uAdditionalBuf;
}

/*****************************************************************************/
static bool InitStreamBufPool(BufPool& pool, AL_TEncSettings& Settings, int iLayerID, uint8_t uNumCore, int iForcedStreamBufferSize, AL_TAllocator* pAllocator)
{
  (void)uNumCore;

  int numStreams;

  AL_TDimension dim = { Settings.tChParam[iLayerID].uEncWidth, Settings.tChParam[iLayerID].uEncHeight };
  uint64_t streamSize = iForcedStreamBufferSize;

  if(streamSize == 0)
  {
    streamSize = AL_GetMitigatedMaxNalSize(dim, AL_GET_CHROMA_MODE(Settings.tChParam[0].ePicFormat), AL_GET_BITDEPTH(Settings.tChParam[0].ePicFormat));

    bool bIsXAVCIntraCBG = AL_IS_XAVC_CBG(Settings.tChParam[0].eProfile) && AL_IS_INTRA_PROFILE(Settings.tChParam[0].eProfile);

    if(bIsXAVCIntraCBG)
      streamSize = AL_GetMaxNalSize(dim, AL_GET_CHROMA_MODE(Settings.tChParam[0].ePicFormat), AL_GET_BITDEPTH(Settings.tChParam[0].ePicFormat), Settings.tChParam[0].eProfile, Settings.tChParam[0].uLevel);
  }

  {
    static const int smoothingStream = 2;
    numStreams = g_defaultMinBuffers + smoothingStream + GetNumBufForGop(Settings);
  }

  bool bHasLookAhead;
  bHasLookAhead = AL_TwoPassMngr_HasLookAhead(Settings);

  if(bHasLookAhead)
  {
    int extraLookAheadStream = 1;

    // the look ahead needs one more stream buffer to work in AVC due to (potential) multi-core
    if(AL_IS_AVC(Settings.tChParam[0].eProfile))
      extraLookAheadStream += 1;
    numStreams += extraLookAheadStream;
  }

  if(Settings.tChParam[0].bSubframeLatency)
  {
    numStreams *= Settings.tChParam[0].uNumSlices;

    {
      /* Due to rounding, the slices don't have all the same height. Compute size of the biggest slice */
      uint64_t lcuSize = 1ll << Settings.tChParam[0].uLog2MaxCuSize;
      uint64_t rndHeight = AL_RoundUp(dim.iHeight, lcuSize);
      streamSize = streamSize * lcuSize * (1 + rndHeight / (Settings.tChParam[0].uNumSlices * lcuSize)) / rndHeight;

      /* we need space for the headers on each slice */
      streamSize += AL_ENC_MAX_HEADER_SIZE;
      /* stream size is required to be 32bytes aligned */
      streamSize = AL_RoundUp(streamSize, HW_IP_BURST_ALIGNMENT);
    }
  }

  if(streamSize > INT32_MAX)
    throw runtime_error("streamSize(" + to_string(streamSize) + ") must be lower or equal than INT32_MAX(" + to_string(INT32_MAX) + ")");

  auto pMetaData = (AL_TMetaData*)AL_StreamMetaData_Create(AL_MAX_SECTION);
  bool bSucceed = pool.Init(pAllocator, numStreams, streamSize, pMetaData, "stream");
  AL_MetaData_Destroy(pMetaData);

  return bSucceed;
}

/*****************************************************************************/
static void InitSrcBufPool(PixMapBufPool& SrcBufPool, AL_TAllocator* pAllocator, TFrameInfo& FrameInfo, AL_ESrcMode eSrcMode, int frameBuffersCount, AL_ECodec eCodec)
{
  auto srcBufDesc = GetSrcBufDescription(FrameInfo.tDimension, FrameInfo.iBitDepth, FrameInfo.eCMode, eSrcMode, eCodec);

  SrcBufPool.SetFormat(FrameInfo.tDimension, srcBufDesc.tFourCC);

  for(auto& vChunk : srcBufDesc.vChunks)
    SrcBufPool.AddChunk(vChunk.iChunkSize, vChunk.vPlaneDesc);

  bool const ret = SrcBufPool.Init(pAllocator, frameBuffersCount, "input");

  if(!ret)
    throw std::runtime_error("src buf pool must succeed init");
}

/*****************************************************************************/

/*****************************************************************************/
struct LayerResources
{
  void Init(ConfigFile& cfg, AL_TEncoderInfo tEncInfo, int iLayerID, CIpDevice* pDevices, int chanId);

  void PushResources(ConfigFile& cfg, EncoderSink* enc
                     , EncoderLookAheadSink* encFirstPassLA
                     );

  void OpenEncoderInput(ConfigFile& cfg, AL_HEncoder hEnc);

  bool SendInput(ConfigFile& cfg, IFrameSink* firstSink, void* pTraceHook);

  bool sendInputFileTo(unique_ptr<FrameReader>& frameReader, PixMapBufPool& SrcBufPool, AL_TBuffer* Yuv, ConfigFile const& cfg, AL_TYUVFileInfo& FileInfo, IConvSrc* pSrcConv, IFrameSink* sink, int& iPictCount, int& iReadCount);

  unique_ptr<FrameReader> InitializeFrameReader(ConfigFile& cfg, ifstream& YuvFile, string sYuvFileName, ifstream& MapFile, string sMapFileName, AL_TYUVFileInfo& FileInfo);

  void ChangeInput(ConfigFile& cfg, int iInputIdx, AL_HEncoder hEnc);

  BufPool StreamBufPool;
  BufPool QpBufPool;
  PixMapBufPool SrcBufPool;

  // Input/Output Format conversion
  ifstream YuvFile;
  ifstream MapFile;
  unique_ptr<FrameReader> frameReader;
  unique_ptr<IConvSrc> pSrcConv;
  shared_ptr<AL_TBuffer> SrcYuv;

  vector<uint8_t> RecYuvBuffer;
  unique_ptr<IFrameSink> frameWriter;

  int iPictCount = 0;
  int iReadCount = 0;

  int iLayerID = 0;
  int iInputIdx = 0;
  vector<TConfigYUVInput> layerInputs;
};

void LayerResources::Init(ConfigFile& cfg, AL_TEncoderInfo tEncInfo, int iLayerID, CIpDevice* pDevices, int chanId)
{
  AL_TEncSettings& Settings = cfg.Settings;
  auto const eSrcMode = Settings.tChParam[iLayerID].eSrcMode;

  (void)chanId;
  this->iLayerID = iLayerID;

  {
    layerInputs.push_back(cfg.MainInput);
    layerInputs.insert(layerInputs.end(), cfg.DynamicInputs.begin(), cfg.DynamicInputs.end());
  }

  AL_TAllocator* pAllocator = pDevices->GetAllocator();

  // --------------------------------------------------------------------------------
  // Stream Buffers
  // --------------------------------------------------------------------------------
  if(!InitStreamBufPool(StreamBufPool, Settings, iLayerID, tEncInfo.uNumCore, cfg.iForceStreamBufSize, pAllocator))
    throw std::runtime_error("Error creating stream buffer pool");

  bool bUsePictureMeta = false;
  bUsePictureMeta |= cfg.RunInfo.printPictureType;

  bUsePictureMeta |= AL_TwoPassMngr_HasLookAhead(Settings);

  if(iLayerID == 0 && bUsePictureMeta)
  {
    auto pMeta = (AL_TMetaData*)AL_PictureMetaData_Create();

    if(pMeta == nullptr)
      throw std::runtime_error("Meta must be created");
    bool const bRet = StreamBufPool.AddMetaData(pMeta);

    if(!bRet)
      throw std::runtime_error("Meta must be added in stream pool");
    Rtos_Free(pMeta);
  }

  if(cfg.RunInfo.printRateCtrlStat)
  {
    AL_TDimension tDim = { Settings.tChParam[iLayerID].uEncWidth, Settings.tChParam[iLayerID].uEncHeight };
    auto pMeta = (AL_TMetaData*)AL_RateCtrlMetaData_Create(pAllocator, tDim, Settings.tChParam[iLayerID].uLog2MaxCuSize, AL_GET_CODEC(Settings.tChParam[iLayerID].eProfile));

    if(pMeta == nullptr)
      throw std::runtime_error("Meta must be created");
    bool const bRet = StreamBufPool.AddMetaData(pMeta);

    if(!bRet)
      throw std::runtime_error("Meta must be added in stream pool");
    Rtos_Free(pMeta);
  }

  // --------------------------------------------------------------------------------
  // Tuning Input Buffers
  // --------------------------------------------------------------------------------
  int frameBuffersCount = g_defaultMinBuffers + GetNumBufForGop(Settings);

  {
    frameBuffersCount = g_defaultMinBuffers + GetNumBufForGop(Settings);

    if(AL_TwoPassMngr_HasLookAhead(Settings))
    {
      frameBuffersCount += Settings.LookAhead + (GetNumBufForGop(Settings) * 2);

      if(AL_IS_AVC(cfg.Settings.tChParam[0].eProfile))
        frameBuffersCount += 1;
    }

  }

  if(!InitQpBufPool(QpBufPool, Settings, Settings.tChParam[iLayerID], frameBuffersCount, pAllocator))
    throw std::runtime_error("Error creating QP buffer pool");

  // --------------------------------------------------------------------------------
  // Application Input/Output Format conversion
  // --------------------------------------------------------------------------------
  const AL_TPicFormat tSrcPicFmt = GetSrcPicFormat(Settings.tChParam[iLayerID]);
  const SrcConverterParams tSrcConverterParams =
  {
    { AL_GetSrcWidth(Settings.tChParam[iLayerID]), AL_GetSrcHeight(Settings.tChParam[iLayerID]) },
    layerInputs[iInputIdx].FileInfo.FourCC,
    tSrcPicFmt,
    cfg.eSrcFormat,
  };
  pSrcConv = AllocateSrcConverter(tSrcConverterParams, SrcYuv);
  TFrameInfo tSrcFrameInfo = { tSrcConverterParams.tDim, tSrcConverterParams.tSrcPicFmt.uBitDepth, tSrcConverterParams.tSrcPicFmt.eChromaMode };

  // --------------------------------------------------------------------------------
  // Source Buffers
  // --------------------------------------------------------------------------------
  int srcBuffersCount = max(frameBuffersCount, g_numFrameToRepeat);

  InitSrcBufPool(SrcBufPool, pAllocator, tSrcFrameInfo, eSrcMode, srcBuffersCount, static_cast<AL_ECodec>(AL_GET_CODEC(Settings.tChParam[0].eProfile)));

  iPictCount = 0;
  iReadCount = 0;
}

void LayerResources::PushResources(ConfigFile& cfg, EncoderSink* enc
                                   , EncoderLookAheadSink* encFirstPassLA
                                   )
{
  (void)cfg;
  QPBuffers::QPLayerInfo qpInf
  {
    &QpBufPool,
    layerInputs[iInputIdx].sQPTablesFolder,
    layerInputs[iInputIdx].sRoiFileName
  };

  enc->AddQpBufPool(qpInf, iLayerID);

  if(AL_TwoPassMngr_HasLookAhead(cfg.Settings))
  {
    encFirstPassLA->AddQpBufPool(qpInf, iLayerID);
  }

  if(frameWriter)
    enc->RecOutput[iLayerID] = std::move(frameWriter);

  for(int i = 0; i < (int)StreamBufPool.GetNumBuf(); ++i)
  {
    std::shared_ptr<AL_TBuffer> pStream = StreamBufPool.GetSharedBuffer(AL_EBufMode::AL_BUF_MODE_NONBLOCK);

    if(pStream == nullptr)
      throw runtime_error("pStream must exist");

    AL_HEncoder hEnc = enc->hEnc;

    bool bRet = true;

    if(iLayerID == 0)
    {
      int iStreamNum = 1;

      // the look ahead needs one more stream buffer to work AVC due to (potential) multi-core
      if(AL_IS_AVC(cfg.Settings.tChParam[0].eProfile))
        iStreamNum += 1;

      if(AL_TwoPassMngr_HasLookAhead(cfg.Settings) && i < iStreamNum)
        hEnc = encFirstPassLA->hEnc;

      bRet = AL_Encoder_PutStreamBuffer(hEnc, pStream.get());
    }

    if(!bRet)
      throw std::runtime_error("bRet must be true");
  }
}

void LayerResources::OpenEncoderInput(ConfigFile& cfg, AL_HEncoder hEnc)
{
  ChangeInput(cfg, iInputIdx, hEnc);
}

bool LayerResources::SendInput(ConfigFile& cfg, IFrameSink* firstSink, void* pTraceHooker)
{
  (void)pTraceHooker;
  firstSink->PreprocessFrame();

  return sendInputFileTo(frameReader, SrcBufPool, SrcYuv.get(), cfg, layerInputs[iInputIdx].FileInfo, pSrcConv.get(), firstSink, iPictCount, iReadCount);
}

bool LayerResources::sendInputFileTo(unique_ptr<FrameReader>& frameReader, PixMapBufPool& SrcBufPool, AL_TBuffer* Yuv, ConfigFile const& cfg, AL_TYUVFileInfo& FileInfo, IConvSrc* pSrcConv, IFrameSink* sink, int& iPictCount, int& iReadCount)
{
  if(AL_IS_ERROR_CODE(GetEncoderLastError()))
  {
    sink->ProcessFrame(nullptr);
    return false;
  }

  shared_ptr<AL_TBuffer> frame = GetSrcFrame(iReadCount, iPictCount, frameReader, FileInfo, SrcBufPool, Yuv, cfg.Settings.tChParam[0], cfg, pSrcConv);

  sink->ProcessFrame(frame.get());

  if(!frame)
    return false;

  iPictCount++;
  return true;
}

unique_ptr<FrameReader> LayerResources::InitializeFrameReader(ConfigFile& cfg, ifstream& YuvFile, string sYuvFileName, ifstream& MapFile, string sMapFileName, AL_TYUVFileInfo& FileInfo)
{
  (void)(MapFile);

  unique_ptr<FrameReader> pFrameReader;
  bool bUseCompressedFormat = AL_IsCompressed(FileInfo.FourCC);
  bool bHasCompressionMapFile = !sMapFileName.empty();

  if(bUseCompressedFormat != bHasCompressionMapFile)
    throw runtime_error(std::string("Providing a map file is ") + std::string(bUseCompressedFormat ? "mandatory" : "forbidden") +
                        " when using " + std::string(bUseCompressedFormat ? "compressed" : "uncompressed") + " input.");

  YuvFile.close();
  OpenInput(YuvFile, sYuvFileName);

  if(!bUseCompressedFormat)
    pFrameReader = unique_ptr<FrameReader>(new UnCompFrameReader(YuvFile, FileInfo, cfg.RunInfo.bLoop));
  pFrameReader->SeekA(cfg.RunInfo.iFirstPict + iReadCount);

  return pFrameReader;
}

void LayerResources::ChangeInput(ConfigFile& cfg, int iInputIdx, AL_HEncoder hEnc)
{
  (void)hEnc;

  if(iInputIdx < static_cast<int>(layerInputs.size()))
  {
    this->iInputIdx = iInputIdx;
    AL_TDimension inputDim = { layerInputs[iInputIdx].FileInfo.PictWidth, layerInputs[iInputIdx].FileInfo.PictHeight };
    bool bResChange = (inputDim.iWidth != AL_GetSrcWidth(cfg.Settings.tChParam[iLayerID])) || (inputDim.iHeight != AL_GetSrcHeight(cfg.Settings.tChParam[iLayerID]));

    if(bResChange)
    {
      /* No resize with dynamic resolution changes */
      cfg.Settings.tChParam[iLayerID].uEncWidth = cfg.Settings.tChParam[iLayerID].uSrcWidth = inputDim.iWidth;
      cfg.Settings.tChParam[iLayerID].uEncHeight = cfg.Settings.tChParam[iLayerID].uSrcHeight = inputDim.iHeight;

      AL_Encoder_SetInputResolution(hEnc, inputDim);
    }

    frameReader = InitializeFrameReader(cfg, YuvFile,
                                        layerInputs[iInputIdx].YUVFileName,
                                        MapFile,
                                        cfg.MainInput.sMapFileName,
                                        layerInputs[iInputIdx].FileInfo);

  }
}

void SafeChannelMain(ConfigFile& cfg, CIpDevice* pIpDevice, CIpDeviceParam& param, int chanId)
{
  (void)param;
  auto& Settings = cfg.Settings;
  auto& StreamFileName = cfg.BitstreamFileName;
  auto& RunInfo = cfg.RunInfo;
  vector<LayerResources> layerResources(cfg.Settings.NumLayer);

  /* null if not supported */
  void* pTraceHook {};
  unique_ptr<EncoderSink> enc;
  unique_ptr<EncoderLookAheadSink> encFirstPassLA;

  auto pAllocator = pIpDevice->GetAllocator();
  auto pScheduler = pIpDevice->GetScheduler();

  auto ctx = pIpDevice->GetCtx();

  AL_EVENT hFinished = Rtos_CreateEvent(false);
  RCPlugin_Init(&cfg.Settings, &cfg.Settings.tChParam[0], pAllocator);

  auto OnScopeExit = scopeExit([&]() {
    Rtos_DeleteEvent(hFinished);
    AL_Allocator_Free(pAllocator, cfg.Settings.hRcPluginDmaContext);
  });

  // --------------------------------------------------------------------------------
  // Create Encoder

  if(ctx)
    enc.reset(new EncoderSink(cfg, ctx, pAllocator));
  else
  enc.reset(new EncoderSink(cfg, pScheduler, pAllocator));

  IFrameSink* firstSink = enc.get();

  if(AL_TwoPassMngr_HasLookAhead(cfg.Settings))
  {

    if(ctx)
      encFirstPassLA.reset(new EncoderLookAheadSink(cfg, ctx, pAllocator));
    else
    encFirstPassLA.reset(new EncoderLookAheadSink(cfg, pScheduler, pAllocator));

    encFirstPassLA->next = firstSink;
    firstSink = encFirstPassLA.get();
  }

  // --------------------------------------------------------------------------------
  // Allocate/Push Layers resources
  AL_TEncoderInfo tEncInfo;
  AL_Encoder_GetInfo(enc->hEnc, &tEncInfo);

  for(size_t i = 0; i < layerResources.size(); i++)
  {
    auto multisinkRec = unique_ptr<MultiSink>(new MultiSink);
    layerResources[i].Init(cfg, tEncInfo, i, pIpDevice, chanId);
    layerResources[i].PushResources(cfg, enc.get()
                                    ,
                                    encFirstPassLA.get()
                                    );

    // Rec file creation
    string LayerRecFileName = cfg.RecFileName;

    if(!LayerRecFileName.empty())
    {

      if(Settings.tChParam[0].eEncOptions & AL_OPT_COMPRESS)
      {
        std::unique_ptr<IFrameSink> recOutput(createCompFrameSink(LayerRecFileName, LayerRecFileName + ".map", AL_FB_TILE_64x4, 0));
        multisinkRec->addSink(recOutput);
      }
      else
      {
        std::unique_ptr<IFrameSink> recOutput(createUnCompFrameSink(LayerRecFileName, AL_FB_RASTER));
        multisinkRec->addSink(recOutput);
      }
    }
    enc->RecOutput[i] = std::move(multisinkRec);
  }

  auto multisink = unique_ptr<MultiSink>(new MultiSink);

  std::unique_ptr<IFrameSink> bitstreamOutput(createBitstreamWriter(StreamFileName, cfg));
  multisink->addSink(bitstreamOutput);

  if(!RunInfo.sStreamMd5Path.empty())
  {
    std::unique_ptr<IFrameSink> md5Calculator(createStreamMd5Calculator(RunInfo.sStreamMd5Path));
    multisink->addSink(md5Calculator);
  }

  if(!RunInfo.bitrateFile.empty())
  {
    std::unique_ptr<IFrameSink> bitrateOutput(createBitrateWriter(RunInfo.bitrateFile, cfg));
    multisink->addSink(bitrateOutput);
  }

  enc->BitstreamOutput[0] = std::move(multisink);

  // --------------------------------------------------------------------------------
  // Set Callbacks
  enc->m_InputChanged = ([&](int iInputIdx, int iLayerID) {
    layerResources[iLayerID].ChangeInput(cfg, iInputIdx, enc->hEnc);
  });

  enc->m_done = ([&]() {
    Rtos_SetEvent(hFinished);
  });

  if(!RunInfo.sRecMd5Path.empty())
  {
    for(int iLayerID = 0; iLayerID < Settings.NumLayer; ++iLayerID)
    {
      auto layer_multisink = unique_ptr<MultiSink>(new MultiSink);
      layer_multisink->addSink(enc->RecOutput[iLayerID]);
      string LayerMd5FileName = RunInfo.sRecMd5Path;
      std::unique_ptr<IFrameSink> md5Calculator(createYuvMd5Calculator(LayerMd5FileName, cfg));
      layer_multisink->addSink(md5Calculator);
      enc->RecOutput[iLayerID] = std::move(layer_multisink);
    }
  }

  unique_ptr<RepeaterSink> prefetch;

  if(g_numFrameToRepeat > 0)
  {
    prefetch.reset(new RepeaterSink(g_numFrameToRepeat, RunInfo.iMaxPict));
    prefetch->next = firstSink;
    firstSink = prefetch.get();
    RunInfo.iMaxPict = g_numFrameToRepeat;
  }

  bool hasInputAndNoError = true;

  for(int i = 0; i < Settings.NumLayer; ++i)
    layerResources[i].OpenEncoderInput(cfg, enc->hEnc);

  while(hasInputAndNoError)
  {
    AL_64U uBeforeTime = Rtos_GetTime();

    for(int i = 0; i < Settings.NumLayer; ++i)
      hasInputAndNoError = layerResources[i].SendInput(cfg, firstSink, pTraceHook) && hasInputAndNoError;

    AL_64U uAfterTime = Rtos_GetTime();

    if((uAfterTime - uBeforeTime) < RunInfo.uInputSleepInMilliseconds)
      Rtos_Sleep(RunInfo.uInputSleepInMilliseconds - (uAfterTime - uBeforeTime));
  }

  Rtos_WaitEvent(hFinished, AL_WAIT_FOREVER);

  if(auto err = GetEncoderLastError())
    throw codec_error(AL_Codec_ErrorToString(err), err);

}

struct channel_runtime_error : public runtime_error
{
  explicit channel_runtime_error() : runtime_error("")
  {
  }
};

static void ChannelMain(ConfigFile& cfg, CIpDevice* pIpDevice, CIpDeviceParam& param, exception_ptr& exception, int chanId)
{
  try
  {
    SafeChannelMain(cfg, pIpDevice, param, chanId);
    exception = nullptr;
    return;
  }
  catch(codec_error const& error)
  {
    cerr << endl << "Codec error: " << error.what() << endl;
    exception = current_exception();
  }
  catch(runtime_error const& error)
  {
    cerr << endl << "Exception caught: " << error.what() << endl;
    exception = make_exception_ptr(channel_runtime_error());
  }
}

/*****************************************************************************/
void SafeMain(int argc, char* argv[])
{
  InitializePlateform();

  ConfigFile cfg {
  }

  ;
  CfgParser cfgParser;
  {
    SetDefaults(cfg);
    ParseCommandLine(argc, argv, cfg, cfgParser);

    auto& Settings = cfg.Settings;
    auto& RecFileName = cfg.RecFileName;
    auto& RunInfo = cfg.RunInfo;

    AL_Settings_SetDefaultParam(&Settings);
    SetMoreDefaults(cfg);

    if(!RecFileName.empty() || !RunInfo.sRecMd5Path.empty())
    {
      Settings.tChParam[0].eEncOptions = (AL_EChEncOption)(Settings.tChParam[0].eEncOptions | AL_OPT_FORCE_REC);
    }

    Settings.tChParam[0].bUseGMV = !cfg.sGMVFileName.empty();

    AL_ESrcMode eSrcMode = SrcFormatToSrcMode(cfg.eSrcFormat);

    for(uint8_t uLayer = 0; uLayer < cfg.Settings.NumLayer; uLayer++)
      Settings.tChParam[uLayer].eSrcMode = eSrcMode;

    DisplayVersionInfo();

    ValidateConfig(cfg);

  }

  AL_ELibEncoderArch eArch = AL_LIB_ENCODER_ARCH_HOST;

  auto& RunInfo = cfg.RunInfo;

  if(RunInfo.eDeviceType == AL_EDeviceType::AL_DEVICE_TYPE_EMBEDDED)
    eArch = AL_LIB_ENCODER_ARCH_RISCV;

  if(AL_Lib_Encoder_Init(eArch) != AL_SUCCESS)
    throw runtime_error("Can't setup encode library");

  CIpDeviceParam param;
  param.eSchedulerType = RunInfo.eSchedulerType;
  param.eDeviceType = RunInfo.eDeviceType;

  param.pCfgFile = &cfg;
  param.bTrackDma = RunInfo.trackDma;

  auto pIpDevice = shared_ptr<CIpDevice>(new CIpDevice);

  if(!pIpDevice)
    throw runtime_error("Can't create IpDevice");

  pIpDevice->Configure(param);

  exception_ptr pError;
  ChannelMain(cfg, pIpDevice.get(), param, pError, 0);

  if(pError)
    rethrow_exception(pError);

  AL_Lib_Encoder_DeInit();
}

/******************************************************************************/
int main(int argc, char* argv[])
{
  try
  {
    SafeMain(argc, argv);
    return 0;
  }
  catch(codec_error const& error)
  {
    return error.GetCode();
  }
  catch(channel_runtime_error const &)
  {
    return 1;
  }
  catch(runtime_error const& error)
  {
    cerr << endl << "Exception caught: " << error.what() << endl;
    return 1;
  }
}
