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

#include "stdlib.h"

#include "interrupt.h"
#include "trace.h"
#include "bsp.h"

extern void main_blinky( void );
extern void clock_initialize(void);
extern void pins_initialize(void);

uint8_t ucHeap[ configTOTAL_HEAP_SIZE ]   __attribute__ ((section (".freertos_heap")));

static void machine_timer_initialize( void )
{
    /* Set mtip interrupt */
    clic_set_priority(7, 0);
    clic_set_attribute(7, 1);
    clic_enable_int(7);
    /* start mtimer, clk source CPU clock */
    bspREG32_WRITE(REG32_MACTCR, 3);
}

int main(void)
{
    clock_initialize();
    pins_initialize();
    trace_initialize();
    
    trace_direct("\nr9a02g021 - FreeRTOS\n\n");
    
    machine_timer_initialize();
    main_blinky();

    return 0;
}

void vAssertCalled(const char *pcFile, unsigned long ulLine )
{    	
	char line[10];
	
	taskDISABLE_INTERRUPTS();
	
	trace_direct("Assert ");
	trace_direct(pcFile);
	trace_direct(" : ");
	itoa(ulLine, line, 10);
	trace_direct(line);
	trace_direct("\n");
    
	while (1);
}

void vToggleLED(void)
{
	bspREG16_WRITE(REG16_PODR_1, bspREG16_READ(REG16_PODR_1) ^ 0x0081);
}




