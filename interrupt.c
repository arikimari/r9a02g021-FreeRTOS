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

#include "stdlib.h"

#include "interrupt.h"
#include "bsp.h"
#include "trace.h"

void freertos_risc_v_mtimer_interrupt_handler(void);
void trace_send_interrupt(void);

__attribute__ ((interrupt)) void INT_DUMMY(void) 
{
	trace_direct("Unexpected interrupt!\n");
}


void freertos_risc_v_application_interrupt_handler(uint32_t mcause)
{  
    char cause[10];
    
    trace_direct("Unexpected trap interrupt: ");
    itoa(mcause & 0xFFFF, cause, 10);
    trace_direct(cause);
    trace_direct("!\n");
}



void freertos_risc_v_application_exception_handler(uint32_t mcause)
{ 
    char cause[10];
    
    trace_direct("Exception: ");
    itoa(mcause & 0xFFFF, cause, 10);
    trace_direct(cause);
    trace_direct("!\n");
    
    while (1);
}



#define VECT_SECT __attribute__ ((section (".vects")))
const void * gp_Vectors[] VECT_SECT = {
/*
 * Reserved (0x00)
 */
    INT_DUMMY,

/*
 * Reserved (0x04)
 */
    INT_DUMMY,

/*
 * Reserved (0x08)
 */
    INT_DUMMY,

/*
 * INT_ACLINT_MSIP (0x0C)
 */
    INT_DUMMY,

/*
 * Reserved (0x10)
 */
    INT_DUMMY,

/*
 * Reserved (0x14)
 */
    INT_DUMMY,

/*
 * Reserved (0x18)
 */
    INT_DUMMY,

/*
 * INT_ACLINT_MTIP (0x1C)
 */
    freertos_risc_v_mtimer_interrupt_handler,

/*
 * Reserved (0x20)
 */
    INT_DUMMY,

/*
 * Reserved (0x24)
 */
    INT_DUMMY,

/*
 * Reserved (0x28)
 */
    INT_DUMMY,

/*
 * Reserved (0x2C)
 */
    INT_DUMMY,

/*
 * Reserved (0x30)
 */
    INT_DUMMY,

/*
 * Reserved (0x34)
 */
    INT_DUMMY,

/*
 * Reserved (0x38)
 */
    INT_DUMMY,

/*
 * Reserved (0x3C)
 */
    INT_DUMMY,

/*
 * Reserved (0x40)
 */
    INT_DUMMY,

/*
 * Reserved (0x44)
 */
    INT_DUMMY,

/*
 * Reserved (0x48)
 */
    INT_DUMMY,

/*
 * INT_IELSR0 (0x4C)
 */
    INT_DUMMY,

/*
 * INT_IELSR1 (0x50)
 */
    INT_DUMMY,

/*
 * INT_IELSR2 (0x54)
 */
    INT_DUMMY,

/*
 * INT_IELSR3 (0x58)
 */
    INT_DUMMY,

/*
 * INT_IELSR4 (0x5C)
 */
    INT_DUMMY,

/*
 * INT_IELSR5 (0x60)
 */
    INT_DUMMY,

/*
 * INT_IELSR6 (0x64)
 */
    INT_DUMMY,

/*
 * INT_IELSR7 (0x68)
 */
    INT_DUMMY,

/*
 * INT_IELSR8 (0x6C)
 */
    trace_send_interrupt,

/*
 * INT_IELSR9 (0x70)
 */
    INT_DUMMY,

/*
 * INT_IELSR10 (0x74)
 */
    INT_DUMMY,

/*
 * INT_IELSR11 (0x78)
 */
    INT_DUMMY,

/*
 * INT_IELSR12 (0x7C)
 */
    INT_DUMMY,

/*
 * INT_IELSR13 (0x80)
 */
    INT_DUMMY,

/*
 * INT_IELSR14 (0x84)
 */
    INT_DUMMY,

/*
 * INT_IELSR15 (0x88)
 */
    INT_DUMMY,

/*
 * INT_IELSR16 (0x8C)
 */
    INT_DUMMY,

/*
 * INT_IELSR17 (0x90)
 */
    INT_DUMMY,

/*
 * INT_IELSR18 (0x94)
 */
    INT_DUMMY,

/*
 * INT_IELSR19 (0x98)
 */
    INT_DUMMY,

/*
 * INT_IELSR20 (0x9C)
 */
    INT_DUMMY,

/*
 * INT_IELSR21 (0xA0)
 */
    INT_DUMMY,

/*
 * INT_IELSR22 (0xA4)
 */
    INT_DUMMY,

/*
 * INT_IELSR23 (0xA8)
 */
    INT_DUMMY,

/*
 * INT_IELSR24 (0xAC)
 */
    INT_DUMMY,

/*
 * INT_IELSR25 (0xB0)
 */
    INT_DUMMY,

/*
 * INT_IELSR26 (0xB4)
 */
    INT_DUMMY,

/*
 * INT_IELSR27 (0xB8)
 */
    INT_DUMMY,

/*
 * INT_IELSR28 (0xBC)
 */
    INT_DUMMY,

/*
 * INT_IELSR29 (0xC0)
 */
    INT_DUMMY,

/*
 * INT_IELSR30 (0xC4)
 */
    INT_DUMMY,

/*
 * INT_IELSR31 (0xC8)
 */
    INT_DUMMY,
};



void clic_set_priority(uint8_t interrupt, uint8_t priority)
{
	bspREG8_WRITE((REG_CLIC_INT_BASE + (interrupt * 4) + 3), (priority << 4) | 0x0f);
}

void clic_set_attribute(uint8_t interrupt, uint8_t attr)
{
	bspREG8_WRITE((REG_CLIC_INT_BASE + (interrupt * 4) + 2), attr | 0xc2);
}

void clic_clear_int(uint8_t interrupt)
{
	bspREG8_WRITE((REG_CLIC_INT_BASE + (interrupt * 4)), 0);
}

void clic_enable_int(uint8_t interrupt)
{
	bspREG8_WRITE((REG_CLIC_INT_BASE + (interrupt * 4) + 1), 1);
}

void clic_disable_int(uint8_t interrupt)
{
	bspREG8_WRITE((REG_CLIC_INT_BASE + (interrupt * 4) + 1), 0);
}

void icu_select_int(uint8_t interrupt, uint8_t select)
{
	bspREG32_WRITE((REG_IELSR_BASE + (interrupt * 4)), (uint32_t)select);
}

void icu_clear_int(uint8_t interrupt)
{
	bspREG32_WRITE((REG_IELSR_BASE + (interrupt * 4)), bspREG32_READ(REG_IELSR_BASE + (interrupt * 4)) & 0xFFFEFFFF);
}
