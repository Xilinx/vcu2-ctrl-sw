/* Default linker script, for plugin */
OUTPUT_FORMAT ("riscv64-unknown-elf")
__FW_BASE_ADDR = 0xFFFFFFFFC0000000;

INCLUDE plugin_common.lds
