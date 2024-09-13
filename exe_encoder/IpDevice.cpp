// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include <stdexcept>

#include "IpDevice.h"
#include "lib_app/utils.h"
#include <algorithm>
#include <sstream>

extern "C"
{
#include "lib_fpga/DmaAlloc.h"
#include "lib_log/TimerSoftware.h"
}
using namespace std;

AL_TAllocator* createDmaAllocator(const char* deviceName)
{
  auto h = AL_DmaAlloc_Create(deviceName);

  if(h == nullptr)
    throw runtime_error("Can't find dma allocator (trying to use " + string(deviceName) + ")");
  return h;
}

extern "C"
{
#include "lib_encode/LibEncoderRiscv.h"
}

void CIpDevice::ConfigureRiscv(CIpDeviceParam& param)
{
  m_pScheduler = nullptr;
  m_ctx = AL_Riscv_Encode_CreateCtx(param.pCfgFile->RunInfo.encDevicePaths.back().c_str());

  if(!m_ctx)
    throw std::runtime_error("Failed to create context (trying to use " + param.pCfgFile->RunInfo.encDevicePaths.back() + ")");

  m_pAllocator = AL_Riscv_Encode_DmaAlloc_Create(m_ctx);
  m_pTimer = nullptr;

  if(!m_pAllocator)
    throw runtime_error("Can't find dma allocator");
}

CIpDevice::~CIpDevice(void)
{
  if(m_pScheduler)
    AL_IEncScheduler_Destroy(m_pScheduler);

  if(m_pTimer)
    AL_ITimer_Deinit(m_pTimer);

  if(m_ctx)
    AL_Riscv_Encode_DestroyCtx(m_ctx);

  if(m_pAllocator)
    AL_Allocator_Destroy(m_pAllocator);
}

void CIpDevice::Configure(CIpDeviceParam& param)
{

  if(param.eDeviceType == AL_EDeviceType::AL_DEVICE_TYPE_EMBEDDED)
  {
    ConfigureRiscv(param);
    return;
  }

  throw runtime_error("No support for this scheduling type");
}

