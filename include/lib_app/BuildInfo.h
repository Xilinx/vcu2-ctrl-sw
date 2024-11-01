#pragma once
#include "lib_app/utils.h"
#include <functional>
#include <cstring>

#ifndef DELIVERY_BUILD_NUMBER
#define DELIVERY_BUILD_NUMBER 0
#endif

#ifndef DELIVERY_SCM_REV
#define DELIVERY_SCM_REV "unknown"
#endif

#ifndef DELIVERY_DATE
#define DELIVERY_DATE "unknown"
#endif

#ifndef SCM_REV_SW
#define SCM_REV_SW ""
#endif

#ifndef SCM_BRANCH
#define SCM_BRANCH ""
#endif

struct BuildInfoDisplay
{
  BuildInfoDisplay(char const* scmRevision, char const* scmBranch, char const* configureCmdline, char const* compilationFlags, int deliveryBuildNumber = 0, char const* deliveryScmRevision = "unknown", char const* deliveryDate = "unknown") : scmRevision{scmRevision}, scmBranch{scmBranch}, configureCmdline{configureCmdline}, compilationFlags{compilationFlags}, deliveryBuildNumber{deliveryBuildNumber}, deliveryScmRevision{deliveryScmRevision}, deliveryDate{deliveryDate}
  {
  }

  void operator () (void)
  {
    displayTimeOfBuild();

    if(displayFeatures)
      displayFeatures();
    displayBuildOptions();
  }

  void setLibrefRevision(const char* librefsha1)
  {
    librefRevision = librefsha1;
  }

  void displayTimeOfBuild(void)
  {
    LogInfo("Compiled on %s at %s", __DATE__, __TIME__);

    if(strcmp(scmRevision, "0") && strcmp(scmRevision, ""))
      LogInfo(" from GIT revision %s", scmRevision);

    if(strcmp(scmBranch, "unknown"))
      LogInfo(" (%s)", scmBranch);

    LogInfo(".\n");

    if(strcmp(librefRevision, "0") && strcmp(librefRevision, ""))
      LogInfo("\nUsing reference library version %s", librefRevision);

    if(strcmp(deliveryDate, "unknown") && strcmp(deliveryDate, ""))
      LogInfo("\nDelivery created the %s", deliveryDate);

    if(deliveryBuildNumber != 0)
      LogInfo(". CI Build Number: %d", deliveryBuildNumber);

    if(strcmp(deliveryScmRevision, "unknown") && strcmp(deliveryScmRevision, ""))
      LogInfo(". GIT revision %s.\n", deliveryScmRevision);
  }

  void displayBuildOptions(void)
  {
    if(strcmp(configureCmdline, ""))
      LogInfo("\nUsing configuration:\n%s\n", configureCmdline);

#if HAS_COMPIL_FLAGS

    if(strcmp(compilationFlags, ""))
      LogInfo("\nUsing compilation options:\n%s\n", compilationFlags);
#endif

    LogInfo("\nUsing allegro library version: %d.%d.%d\n", AL_VERSION_MAJOR, AL_VERSION_MINOR, AL_VERSION_PATCH);
  }

  char const* scmRevision;
  char const* scmBranch;
  char const* configureCmdline;
  char const* compilationFlags;
  int deliveryBuildNumber;
  char const* deliveryScmRevision;
  char const* deliveryDate;
  char const* librefRevision;

  std::function<void(void)> displayFeatures {};
};

static inline void DisplayVersionInfo(char const* company, char const* productName, int versionMajor, int versionMinor, int versionPatch, char const* copyright, char const* comments)
{
  LogVerbose("%s - %s v%d.%d.%d - %s\n", company,
             productName,
             versionMajor,
             versionMinor,
             versionPatch,
             copyright);

  LogVerbose(CC_YELLOW, "%s\n\n", comments);
}
