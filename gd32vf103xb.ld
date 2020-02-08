OUTPUT_ARCH( "riscv" )

/*ENTRY( reset_handler )*/
ENTRY( _start )

MEMORY
{ 
  FLASH (rxai!w) : ORIGIN = 0x08000000, LENGTH = 128K
  RAM   (wxa!ri) : ORIGIN = 0x20000000, LENGTH = 32K 
}


SECTIONS
{
  __stack_size = DEFINED(__stack_size) ? __stack_size : 2K;

  .vector_table :
  {
    KEEP (*(SORT_NONE(.vector_table)))
  } >FLASH

  .text :
  {
    *(.rodata .rodata.*)  
    *(.text .text.*)
    *(.gnu.linkonce.t.*)
  } >FLASH

  . = ALIGN(4);

  PROVIDE (__etext = .);
  PROVIDE (_etext = .);
  PROVIDE (etext = .);

  _sidata = .;
  .data : AT( _sidata )
  {
    _sdata = .;
    *(.rdata) 

    *(.gnu.linkonce.r.*)
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    . = ALIGN(8);
    *(.sdata .sdata.*)
    *(.gnu.linkonce.s.*)
    . = ALIGN(8);
    *(.srodata.cst16)
    *(.srodata.cst8)
    *(.srodata.cst4)
    *(.srodata.cst2)
    *(.srodata .srodata.*)
    _edata = .;
  } >RAM

  . = ALIGN(4);
  PROVIDE( _edata = . );
  PROVIDE( edata = . );
  PROVIDE( _fbss = . );
  PROVIDE( __bss_start = . );

  .bss :
  {
    _sbss = .;
    *(.sbss*)
    *(.gnu.linkonce.sb.*)
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } >RAM

  . = ALIGN(8);
  PROVIDE( _end = . );
  PROVIDE( end = . );

  .stack ORIGIN(RAM) + LENGTH(RAM) - __stack_size :
  {
    PROVIDE( _heap_end = . ); 
    . = __stack_size;  
    PROVIDE( _sp = . ); 
  } >RAM
}
