LIB_APP_A=$(BIN)/liballegro_app.a
LIB_APP_DLL=$(BIN)/liballegro_app.so

LIB_APP_SRC:=\
  lib_app/utils.cpp\
  lib_app/convert.cpp\
  lib_app/BufPool.cpp\
  lib_app/PixMapBufPool.cpp\
  lib_app/AllocatorTracker.cpp\
  lib_app/YuvIO.cpp\
  lib_app/JsonFile.cpp\
  lib_app/FileUtils.cpp\
  lib_app/MD5.cpp\
  lib_app/Parser.cpp\
  lib_app/Tokenizer.cpp\
  lib_app/FrameReader.cpp\
  lib_app/UnCompFrameReader.cpp\
  lib_app/UnCompFrameWriter.cpp\
  lib_app/CompFrameCommon.cpp\
  lib_app/BaseFrameWriter.cpp\
	lib_app/SinkFrame.cpp\
	lib_app/SinkCrop.cpp\
  lib_app/SinkCrcDump.cpp\
  lib_app/SinkStreamMd5.cpp\
  lib_app/PlaneUtils.cpp\
  $(LIB_LOG_SRC)\
  $(LIB_COMMON_SRC)\





ifneq ($(ENABLE_FBC), 0)
  LIB_APP_SRC+=lib_app/CompFrameWriter.cpp
  LIB_APP_SRC+=lib_app/CompFrameReader.cpp
endif

ifeq ($(findstring mingw,$(TARGET)),mingw)
  LIB_APP_SRC+=lib_app/console_windows.cpp
  LIB_APP_SRC+=lib_app/plateform_windows.cpp
else
  LIB_APP_SRC+=lib_app/console_linux.cpp
  LIB_APP_SRC+=lib_app/plateform_linux.cpp
endif

LIB_APP_OBJ:=$(LIB_APP_SRC:%=$(BIN)/%.o)

$(LIB_APP_A): $(LIB_APP_OBJ)

$(LIB_APP_DLL): $(LIB_APP_OBJ)

liballegro_app: liballegro_app_dll liballegro_app_a

liballegro_app_dll: $(LIB_APP_DLL)

liballegro_app_a: $(LIB_APP_A)

TARGETS+=liballegro_app_dll
CFLAGS+=-Wno-date-time


liballegro_app_src: $(LIB_APP_SRC)
	@echo $(LIB_APP_SRC)

.PHONY: liballegro_app liballegro_app_dll liballegro_app_a liballegro_app_src
