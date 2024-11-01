THIS_EXE_ENCODER:=$(call get-my-dir)

EXE_ENCODER_SRCS:=\
  $(THIS_EXE_ENCODER)/CodecUtils.cpp\
  $(THIS_EXE_ENCODER)/IpDevice.cpp\
  $(THIS_EXE_ENCODER)/container.cpp\
  $(THIS_EXE_ENCODER)/main.cpp\
  $(THIS_EXE_ENCODER)/sink_bitstream_writer.cpp\
  $(THIS_EXE_ENCODER)/sink_bitrate.cpp\
  $(THIS_EXE_ENCODER)/sink_yuv_md5.cpp\
  $(THIS_EXE_ENCODER)/EncCmdMngr.cpp\
  $(THIS_EXE_ENCODER)/QPGenerator.cpp\
  $(THIS_EXE_ENCODER)/CommandsSender.cpp\
  $(THIS_EXE_ENCODER)/CfgParser.cpp\

ifneq ($(ENABLE_ROI),0)
  EXE_ENCODER_SRCS+=$(THIS_EXE_ENCODER)/ROIMngr.cpp
endif


ifneq ($(ENABLE_ENC_SW_MULTIPASS),0)
  EXE_ENCODER_SRCS+=$(THIS_EXE_ENCODER)/TwoPassMngr.cpp
endif

ifneq ($(ENABLE_HIGH_DYNAMIC_RANGE),0)
  EXE_ENCODER_SRCS+=$(THIS_EXE_ENCODER)/HDRParser.cpp
endif



EXE_ENCODER_OBJ:=$(EXE_ENCODER_SRCS:%=$(BIN)/%.o)

$(BIN)/$(THIS_EXE_ENCODER)/main.cpp.o: CFLAGS+=$(SCM_REV_SW)
$(BIN)/$(THIS_EXE_ENCODER)/main.cpp.o: CFLAGS+=$(SCM_BRANCH)
$(BIN)/$(THIS_EXE_ENCODER)/main.cpp.o: CFLAGS+=$(DELIVERY_BUILD_NUMBER)
$(BIN)/$(THIS_EXE_ENCODER)/main.cpp.o: CFLAGS+=$(DELIVERY_SCM_REV)
$(BIN)/$(THIS_EXE_ENCODER)/main.cpp.o: CFLAGS+=$(DELIVERY_DATE)

$(BIN)/$(THIS_EXE_ENCODER)/main.cpp.o: INTROSPECT_FLAGS=-DAL_COMPIL_FLAGS='"$(CFLAGS)"'
$(BIN)/$(THIS_EXE_ENCODER)/main.cpp.o: INTROSPECT_FLAGS+=-DHAS_COMPIL_FLAGS=1


$(BIN)/AL_Encoder.exe: $(EXE_ENCODER_OBJ) $(LIB_REFENC_A) $(LIB_REFALLOC_A) $(LIB_ENCODER_A) $(LIB_APP_A) $(LIB_CONV_YUV_A)
AL_Encoder.exe: $(BIN)/AL_Encoder.exe
TARGETS+=AL_Encoder.exe

ifneq ($(ENABLE_LIB_ISCHEDULER),0)
$(BIN)/AL_Encoder.sh: $(BIN)/AL_Encoder.exe
	@echo "Generate script $@"
	$(shell echo 'LD_LIBRARY_PATH=$(BIN) $(BIN)/AL_Encoder.exe "$$@"' > $@ && chmod a+x $@)

AL_Encoder.sh: $(BIN)/AL_Encoder.sh
TARGETS+=AL_Encoder.sh
endif

EXE_CFG_PARSER_SRCS:=\
  $(THIS_EXE_ENCODER)/ParserMain.cpp\
  $(THIS_EXE_ENCODER)/CfgParser.cpp\

EXE_CFG_PARSER_OBJ:=$(EXE_CFG_PARSER_SRCS:%=$(BIN)/%.o)

$(BIN)/AL_CfgParser.exe: $(EXE_CFG_PARSER_OBJ) $(LIB_ENCODER_A) $(LIB_APP_A)
AL_CfgParser.exe: $(BIN)/AL_CfgParser.exe
TARGETS+=AL_CfgParser.exe

exe_encoder_src: $(EXE_ENCODER_SRCS) $(EXE_CFG_PARSER_SRCS)
	@echo $(EXE_ENCODER_SRCS) $(EXE_CFG_PARSER_SRCS)

$(BIN)/$(THIS_EXE_ENCODER)/unittests/commandsparser.cpp.o: CFLAGS+=-Wno-missing-field-initializers


.PHONY: exe_encoder_src
