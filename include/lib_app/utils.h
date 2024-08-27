// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once
#include <fstream>
#include <memory>
#include "lib_app/console.h" // EConColor

extern int g_Verbosity;

void LogError(const char* sMsg, ...);
void LogWarning(const char* sMsg, ...);
void LogDimmedWarning(const char* sMsg, ...);
void LogInfo(const char* sMsg, ...);
void LogInfo(EConColor Color, const char* sMsg, ...);
void LogVerbose(const char* sMsg, ...);
void LogDebug(const char* sMsg, ...);
void LogVerbose(EConColor Color, const char* sMsg, ...);

void OpenInput(std::ifstream& fp, std::string const& filename, bool binary = true);
void OpenOutput(std::ofstream& fp, std::string const& filename, bool binary = true);

/*****************************************************************************/

template<typename Lambda>
class ScopeExitClass
{
public:
  ScopeExitClass(Lambda fn) : m_fn(fn)
  {
  }

  ~ScopeExitClass(void)
  {
    m_fn();
  }

private:
  Lambda m_fn;
};

template<typename Lambda>
ScopeExitClass<Lambda> scopeExit(Lambda fn)
{
  return ScopeExitClass<Lambda>(fn);
}

#if __cplusplus < 201402 && !defined(_MSC_VER) // has c++14 ? (Visual 2015 defines __cplusplus as "199711L" ...)
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args && ... args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args) ...));
}

#endif

enum class AL_EIpCtrlMode
{
  AL_IPCTRL_MODE_STANDARD,
  AL_IPCTRL_MODE_TIMERS,
  AL_IPCTRL_MODE_LOGS,
  AL_IPCTRL_MODE_TRACE, // codec-agnostic raw register r/w and irq dump
};

enum class AL_ESchedulerType
{
  AL_SCHEDULER_TYPE_CPU,
  AL_SCHEDULER_TYPE_MULTIINST,
};

enum class AL_EDeviceType
{
  AL_DEVICE_TYPE_AUTO,
  AL_DEVICE_TYPE_BOARD,
  AL_DEVICE_TYPE_REFSW,
  AL_DEVICE_TYPE_EMBEDDED,
};
