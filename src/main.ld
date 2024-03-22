/*
# Author : Mayank Manohare <mayankmanohare7@gmail.com>
*/

/*
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")  specifies output format for ELF*/
/*OUTPUT_ARCH(arm)  specifies target architecture for out file */

MEMORY /* MEMORY command for describing Memory Layout */
{
    FLASH (rx): ORIGIN = 0x08000000, LENGTH = 1024K
    SRAM (rwx): ORIGIN = 0X20000000, LENGTH = 96K
}

PROVIDE(_stack_top = ORIGIN(SRAM) + LENGTH(SRAM)); /* creating symbol for top of the stack */
ENTRY(Reset_Handler) /* ENTRY command for defining the first executable instruction */

SECTIONS /* SECTIONS command for defining output sections and content to put inside those sections */
{
  .vector :
  {
      . = ALIGN(4);
      _svector = .;
      KEEP(*(.vector)) /* KEEP, keeps any section named .vectors or .Reset_Handler from being optimized by linker  */
     /* KEEP(*(.reset_handler))*/
      . = ALIGN(4);
      _evector = .; 

  } > FLASH 

  .text :
  {
      . = ALIGN(4); 
      _stext = .; 

      *(.text) 
      *(.rodata)

      . = ALIGN(4);
      _etext = .; 

  } > FLASH

  .data :
  {
      . = ALIGN(4); 
      _srelocate = .; 

      *(.data)

      . = ALIGN(4); 
      _erelocate = .; 

  } > SRAM AT > FLASH

  /*.bss (NOLOAD) :*/
  .bss :
  {
      . = ALIGN(4);
      _sbss = .;

      *(.bss)

      . = ALIGN(4);
      _ebss = .; 

  } > SRAM

  . = ALIGN(4);
  _end = .;
}
