RM := rm -rf

GCC?=1
AL_ENABLE_GPROF?=0
PLUGIN?=plugin

ifeq ($(GCC),1)
CC := riscv64-unknown-elf-gcc
OBJDUMP := riscv64-unknown-elf-objdump
OBJCOPY := riscv64-unknown-elf-objcopy
SIZE := riscv64-unknown-elf-size
else
CC := bk5-64IMFDC-UTIDpbid-ia-clang
OBJDUMP := bk5-64IMFDC-UTIDpbid-ia-objdump
OBJCOPY := bk5-64IMFDC-UTIDpbid-ia-objcopy
SIZE := bk5-64IMFDC-UTIDpbid-ia-size
# seems -pg not working very well. Need further investigation
ifneq ($(AL_ENABLE_GPROF),0)
override AL_ENABLE_GPROF:=0
$(warning AL_ENABLE_GPROF has been disabled)
endif
endif

ROOT_BIN?=bin
BIN=$(ROOT_BIN)/riscv

ifneq ($(AL_ENABLE_GPROF),0)
CFLAGS_COMMON+=-pg
endif

CFLAGS_COMMON+=-DCOMPILE_FOR_MCU=1

ifeq ($(GCC),1)
# force the mabi to lp64, and the march to
# (rv64imac_zicsr / rv64gc if floating point is enabled). only for gcc targets.
CFLAGS_COMMON+=-gdwarf-2
# Check riscv compiler standards, if the F(float) or D(double) are enabled.
IS_FD_SUPPORTED := $(shell $(CC) -dM -E  - < /dev/null | grep -iw '__RISCV_F\|__RISCV_D')
ifeq ($(IS_FD_SUPPORTED),)
CFLAGS_COMMON+=-march=rv64imac_zicsr_zifencei -mabi=lp64
else
# F and D are both enabled.
# WARNING : Change this config to match with the toolchain you are using.
# in case of only F or D is enabled
CFLAGS_COMMON+=-march=rv64gc -mabi=lp64d
endif
endif
