INCLUDE constants.lds

MEMORY
{
    if_dbus (wxa) : org = __FW_BASE_ADDR + __BOOT_HEADER_MAX_SIZE, len = __PLUGIN_MAX_SIZE
}

SECTIONS
{
  . = ORIGIN(if_dbus);
  .text_plugin ALIGN(8) : {
    KEEP (*(.text_plugin))
  } >if_dbus
  .rodata ALIGN(8) : {
    *(.rodata)
    *(.rodata.*)
    *($.rodata.*)
    *(.gnu.linkonce.r.*)
  } >if_dbus
  .data ALIGN(8) : {
    *(.data)
    *(.data.*)
    *($.data.*)
    *(.gnu.linkonce.d.*)
    *(.sbss)
    *(.sbss.*)
    *($.sbss.*)
    *(.gnu.linkonce.sb.*)
    *(.bss)
    *(.bss.*)
    *($.bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
  } >if_dbus
  .sdata ALIGN(8) : {
    *(.sdata)
    *(.sdata.*)
    *($.sdata.*)
    *(.gnu.linkonce.s.*)
  } >if_dbus
}
