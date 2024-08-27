include $(PLUGIN)/plugin_src.mk

$(BIN)/plugin.elf: LDFLAGS+=-Wl,--defsym=_PLUGIN_MAX_SIZE=$(PLUGIN_MAX_SIZE)
$(BIN)/plugin.elf: $(PLUGIN_FIRMWARE_SRC:%=$(BIN)/%.o)

$(BIN)/plugged_encoder_firmware.bin: $(BIN)/plugin.bin $(SOFT)/../allegro-vcu2-firmware/encoder_firmware.bin
	$(Q)cp $(SOFT)/../allegro-vcu2-firmware/encoder_firmware.bin $@
	$(Q)dd conv=notrunc bs=1 seek=4096 if=$< of=$@
	@echo "GEN $@"

TARGETS+=$(BIN)/plugged_encoder_firmware.bin
