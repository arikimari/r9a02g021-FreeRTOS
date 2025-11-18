MEMORY
{
	ROM : ORIGIN = 0x0, LENGTH = 131072
	ECCRAM : ORIGIN = 0x20000000, LENGTH = 4096
	RAM : ORIGIN = 0x20004000, LENGTH = 12288
}


SECTIONS
{
	.reset 0x0:
	{
		*/start.S.o (.text)
	} > ROM

	.vects 0x100 :
	{
		KEEP(*(.vects))
	} > ROM

	.trap 0x200 :
	{
		*(.text.freertos_risc_v_trap_handler)
	} > ROM

	.option_settings 0x400 :
	{
		LONG(0xFFFFFFFF)	/* OFS0 */
		LONG(0x7FFFAEFF)	/* OFS1 */
							/* 32Mhz HOCO clock */
		LONG(0xFFFFFFFF)
		LONG(0xFFFFFFFF)
		LONG(0xFFFFFFFF)
		LONG(0xFFFFFFFF)
		LONG(0x000FFFFC)	/* FLRPROTS */
		LONG(0x000FFFFF)	/* FLRPROTE */
		LONG(0xFFFFFFFF)
		LONG(0xFFFFFFFF)
		LONG(0xFFFFFFFF)
		LONG(0xFFFFFFFF)
		LONG(0xFFFFFFFF)
		LONG(0xFFFFFFFF)
		LONG(0xFFFFFFFF)	/* FLRPROTAC */
		LONG(0xFFFFFFFF)
	} > ROM

	.option_osis 0x800 : 
	{
		LONG(0xFFFFFFFF)
		LONG(0xFFFFFFFF)
		LONG(0xFFFFFFFF)
		LONG(0xFFFFFFFF)
	} > ROM

	.text 0x1000: 
	 {
		*(.text)
		*(.text.*)
		/*INPUT_SECTION_FLAGS(SHF_EXECINSTR) *(*_n)*/
	} >ROM AT>ROM

	.rodata :
	{
		. = ALIGN(2);
		__rodata = .;
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(2);
		*(.const)
		*(.const.*)
		__erodata = .;
	}>ROM

	.data 0x20004000 :
	{
		. = ALIGN(2);
		PROVIDE (__datastart = .);
		__data = .;
		*(.sdata .sdata.*)
		*(.data)
		*(.data.*)
		. = ALIGN(2);
		__edata = .;
	} >RAM AT>ROM

	PROVIDE(__romdatastart = LOADADDR(.data));
	PROVIDE (__romdatacopysize = SIZEOF(.data));

	.bss :
	{
		PROVIDE(__bssstart = .);
		. = ALIGN(2);
		__bss = .;
		*(.sbss .sbss.*)
		*(.bss)
		*(.bss.*)
		. = ALIGN(2);
		*(.bss_bit)
		. = ALIGN(2);
		*(COMMON)
		. = ALIGN(2);
		__ebss = .;
		end = .;
	} >RAM AT>RAM
	PROVIDE(__bsssize = SIZEOF(.bss));

	.freertos_heap (NOLOAD) :
	{
		*(.freertos_heap)
		*(.freertos_heap.**)
	} >ECCRAM

	PROVIDE(__stack_size = 0x200);
	.stack 0x20007000 (NOLOAD) :
	{
		PROVIDE(__stack = .);
		PROVIDE(__freertos_irq_stack_start = (__stack - __stack_size));
		ASSERT(__freertos_irq_stack_start > end, "Error: Too much data - no room left for the stack");
		PROVIDE(__freertos_irq_stack_top = .);
	} >RAM

    /DISCARD/ :
	{
		*(.note)
		*(.note.*)
		*(.gnu.warning*)
	}
}
