LIB_DECODE_SRC+=\
  lib_decode/NalUnitParser.c\
  lib_decode/FrameParam.c\
  lib_decode/DefaultDecoder.c\
  lib_decode/LibDecoderHost.c\
  lib_decode/lib_decode.c\
  lib_decode/UnsplitBufferFeeder.c\
  lib_decode/Patchworker.c\
  lib_decode/DecoderFeeder.c\
  lib_decode/SplitBufferFeeder.c\
  lib_decode/I_DecScheduler.c\
  lib_decode/WorkPool.c\
  lib_decode/DecSettings.c\
  lib_decode/SearchDecUnit.c

ifneq ($(ENABLE_RISCV),0)
  LIB_DECODE_SRC+=\
    lib_decode/msg_interface_generated.c

# seems that old gcc doesn't apply `#pragma GCC diagnostic ignored "-Wunused-function"`
# so also disable in CFLAGS
  $(BIN)/lib_decode/msg_interface_generated.c.o: CFLAGS+=-Wno-unused-function
endif

ifneq ($(ENABLE_DEC_ITU), 0)
  LIB_DECODE_SRC +=\
    lib_decode/SliceDataParsing.c
endif



ifneq ($(ENABLE_DEC_AVC),0)
  LIB_DECODE_SRC+=lib_decode/AvcDecoder.c
  LIB_DECODE_SRC+=lib_decode/AvcHwBufInitialization.c
endif

ifneq ($(ENABLE_DEC_HEVC),0)
  LIB_DECODE_SRC+=lib_decode/HevcDecoder.c
  LIB_DECODE_SRC+=lib_decode/HevcHwBufInitialization.c
endif




ifneq ($(ENABLE_DEC_JPEG),0)
  LIB_DECODE_SRC+=lib_decode/JpegDecoder.c
endif


