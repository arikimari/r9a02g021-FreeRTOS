/*
Copyright (c) 2025 Ari Kimari

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <FreeRTOS.h>
#include <task.h>

#include "string.h"
#include "bsp.h"
#include "interrupt.h"

/* trace ring buffer */
static char trace_buffer[256];

/* trace indexes */
static volatile uint8_t trace_buffer_write_index;
static volatile uint8_t trace_buffer_read_index;

/* trace active flag */
static volatile uint8_t trace_active;

void trace_initialize(void)
{
	
	/* enable SAU0 */
	 bspREG32_WRITE(REG32_MSTPCRB, 0xFFDFFFFF);

	/* config IELSR8 for SAU0_ENDI0 */
	icu_select_int(8, 0x12);
	
	/* config IELSR8 */
	clic_set_priority(27, 0);
    clic_set_attribute(27, 1);
    clic_enable_int(27);

	/* UART 16MHz */
	bspREG16_WRITE(REG16_SPS0, 0x0011);
	
	/* UART mode */ 
	bspREG16_WRITE(REG16_SMR00, 0x0022);
 
	/* 8N1 */ 
	bspREG16_WRITE(REG16_SCR00, 0x8097);
    
    /* 68x */ 
	bspREG16_WRITE(REG16_SDR00, 0x8800);
    
    /* UART output enable */ 
    bspREG16_WRITE(REG16_SOE0, 0x0001);
         
    /* UART start */
    bspREG16_WRITE(REG16_SS0, 0x0001);
}

/* Direct trace with while busy loop */
/* Use this from interrupts or exceptions */
/* Use this if interrupts are disabled */
void trace_direct(const char *text)
{
	while (*text != 0) {
		while (bspREG16_READ(REG16_SSR00) & 0x20);
		bspREG16_WRITE(REG16_SDR00, (uint8_t)(*text++));
	}
	
}

/* Normal trace using interrupt */
void trace(const char *text)
{
	uint32_t size = strlen(text);
	uint32_t max_size;
	uint8_t size_left;
	
	
	taskDISABLE_INTERRUPTS();
	
	if (trace_buffer_write_index > trace_buffer_read_index) {
		max_size = 256 - (trace_buffer_write_index - trace_buffer_read_index);
	} else if (trace_buffer_write_index < trace_buffer_read_index){
		max_size = trace_buffer_read_index - trace_buffer_write_index;
	} else {
		max_size = 256;
	}
	if (size > max_size) {
		/* no room on buffer for trace */
		taskENABLE_INTERRUPTS();
		return;
	}
	
	size_left = 256 - trace_buffer_write_index;
	if (size_left > size) {
		size_left = size;
	}
	
	memcpy(&trace_buffer[trace_buffer_write_index], text, size_left);
	size -= size_left;
	trace_buffer_write_index += size_left;
	if (size) {
		memcpy(&trace_buffer[0], &text[size_left], size);
		trace_buffer_write_index = size;
	}
	
	if (trace_active == 0) {
		/* trace not active, write first byte and activate it */
		bspREG16_WRITE(REG16_SDR00, trace_buffer[trace_buffer_read_index++]);
		trace_active = 1;
	}
	
	taskENABLE_INTERRUPTS();
}

/* Trace interrupt handler */
__attribute__ ((interrupt)) void trace_send_interrupt(void)
{
	if (trace_buffer_write_index != trace_buffer_read_index)
	{
		/* write next byte */
		bspREG16_WRITE(REG16_SDR00, trace_buffer[trace_buffer_read_index++]);
	} else {
		/* no more to trace, deactivate */
		trace_active = 0;
	}
	
	icu_clear_int(8);
}



