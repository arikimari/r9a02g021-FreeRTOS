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

static void pins_set_config(uint8_t port, uint8_t pin, uint32_t config)
{
	bspREG32_WRITE(REG32_PFS_BASE + (port * 0x40) + (pin * 0x04), config);
}


void pins_initialize(void)
{
	
	/* unprotect registers */
	bspREG8_WRITE(REG8_PWPR, 0x0);
	bspREG8_WRITE(REG8_PWPR, 0x40);
	
	/* leds to output */
	pins_set_config(1,0,0x04);
	pins_set_config(1,7,0x04);
	
	/* UART */
	pins_set_config(3,2,0x11010007);
	
	/* protect registers */
	bspREG8_WRITE(REG8_PWPR, 0x0);
	bspREG8_WRITE(REG8_PWPR, 0x80);	
}
