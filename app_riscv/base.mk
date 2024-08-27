##############################################################
#general rules
##############################################################
.SUFFIXES:

BIN?=bin
V?=0

ifeq ($(V),0)
	Q=@
else
	Q=
endif

$(BIN)/%.S.o: %.S
	@mkdir -p $(dir $@)
	@echo "CC $<"
	$(Q)$(CC) $(CFLAGS) -c $(INCLUDES) -o $@ -c $<
	@$(CC) -MP -MM "$<" -MT "$@" -o "$(BIN)/$*_S.deps" $(INCLUDES) $(CFLAGS)

$(BIN)/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "CXX $<"
	$(Q)$(CXX) $(CFLAGS) $(INTROSPECT_FLAGS) $(INCLUDES) -std=gnu++11 -o $@ -c $<
	@$(CXX) -MP -MM "$<" -MT "$@" -o "$(BIN)/$*_cpp.deps" $(INCLUDES) $(CFLAGS) -std=gnu++11

$(BIN)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@echo "CC $<"
	$(Q)$(CC) $(CFLAGS) -Wstrict-prototypes $(INTROSPECT_FLAGS) $(INCLUDES) -std=gnu11 -o $@ -c $<
	@$(CC) -MP -MM "$<" -MT "$@" -o "$(BIN)/$*_c.deps" $(INCLUDES) $(CFLAGS)

$(BIN)/%.a:
	@mkdir -p $(dir $@)
	$(Q)$(AR) cr $@ $^
	@echo "AR $@"

$(BIN)/%.elf:
	@mkdir -p $(dir $@)
	@echo "CXX $@"
	$(Q)$(CXX) $^ -o $@ $(INCLUDES) $(LDFLAGS)
	@cp "$@" "$(BIN)/$*"

$(BIN)/%.exe:
	@mkdir -p $(dir $@)
	$(Q)$(CXX) -o $@ $^ $(LINK_COMPAT) $(LDFLAGS)
	@echo "CXX $@"

clean:
	@echo "CLEAN $(ROOT_BIN)"
	$(Q)rm -rf $(ROOT_BIN)

define get-my-dir
$(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
endef

include $(shell test -d $(ROOT_BIN) && find $(ROOT_BIN) -name "*.deps")
