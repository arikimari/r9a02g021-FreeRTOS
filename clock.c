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

#include "bsp.h"


void clock_initialize(void)
{
	/* unlock clk registers */
	bspREG16_WRITE(REG16_PRCR, 0xA503);
    
    /* MCU is configured to start with 32MHz HOCO clock
     * with options settigs (linker script)
     * But this does not always work with Segger
     * debugger so this start code is for that */
    if (bspREG8_READ(REG8_HOCOCR) == 1) {
		/* set HOCO to 32MHz */
		bspREG8_WRITE(REG8_HOCOCR2, 0x10);
		/* start HOCO */
		bspREG8_WRITE(REG8_HOCOCR, 0);
	}
    /* wait for HOCO to stab */
    while (bspREG8_READ(REG8_OSCSF) == 0);
    
    /* switch to high speed mode */
    bspREG8_WRITE(REG8_OPCCR, 0);
    
    /* wait for high speed to READY */
    while (bspREG8_READ(REG8_OPCCR) == 0x10);
    
    /* switch to HOCO */
    bspREG8_WRITE(REG8_SCKSRC, 0);
    
    /* CLK divs to x1 = 32MHz */
    bspREG32_WRITE(REG32_SCKDIVCR, 0x04);

	/* lock clk registers */
	bspREG16_WRITE(REG16_PRCR, 0xA500);
}


