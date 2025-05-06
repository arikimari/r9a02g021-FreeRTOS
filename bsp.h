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

#ifndef BSP_H
#define BSP_H

#include "stdint.h"

#define REG_IELSR_BASE		0x40006300UL

#define REG32_MACTCR		0x4001A000UL
#define REG32_SCKDIVCR		0x4001E020UL
#define REG8_SCKSRC			0x4001E026UL
#define REG8_HOCOCR			0x4001E036UL
#define REG8_HOCOCR2		0x4001E037UL
#define REG8_OSCSF			0x4001E03CUL
#define REG8_OPCCR			0x4001E0A0UL
#define REG16_PRCR			0x4001E3FEUL


#define REG16_PODR_0		0x40040000UL
#define REG16_PDR_0			0x40040002UL
#define REG16_PIDR_0		0x40040006UL
#define REG16_PORR_0		0x40040008UL
#define REG16_POSR_0		0x4004000AUL

#define REG16_PODR_1		0x40040020UL
#define REG16_PDR_1			0x40040022UL
#define REG16_PIDR_1		0x40040026UL
#define REG16_PORR_1		0x40040028UL
#define REG16_POSR_1		0x4004002AUL

#define REG16_PODR_2		0x40040040UL
#define REG16_PDR_2			0x40040042UL
#define REG16_PIDR_2		0x40040046UL
#define REG16_PORR_2		0x40040048UL
#define REG16_POSR_2		0x4004004AUL

#define REG16_PODR_3		0x40040060UL
#define REG16_PDR_3			0x40040062UL
#define REG16_PIDR_3		0x40040066UL
#define REG16_PORR_3		0x40040068UL
#define REG16_POSR_3		0x4004006AUL

#define REG16_PODR_4		0x40040080UL
#define REG16_PDR_4			0x40040082UL
#define REG16_PIDR_4		0x40040086UL
#define REG16_PORR_4		0x40040088UL
#define REG16_POSR_4		0x4004008AUL

#define REG32_PFS_BASE		0x40040800UL
#define REG8_PWPR			0x40040D03UL

#define REG32_MSTPCRB		0x40047000UL

#define REG16_SDR00			0x40094000UL
#define REG16_SSR00			0x40094080UL
#define REG16_SIR00			0x40094088UL
#define REG16_SMR00			0x40094090UL
#define REG16_SCR00			0x40094098UL
#define REG16_SE0			0x400940A0UL
#define REG16_SS0			0x400940A2UL
#define REG16_ST0			0x400940A4UL
#define REG16_SPS0			0x400940A6UL
#define REG16_SO0			0x400940A8UL
#define REG16_SOE0			0x400940AAUL
#define REG16_SOL0			0x400940B4UL


#define REG8_CLIC_CFG		0xE2000000UL
#define REG32_CLIC_INFO		0xE2000004UL
#define REG_CLIC_INT_BASE	0xE2001000UL


#define bspREG32_WRITE(reg, value) *(uint32_t *)(reg) = value
#define bspREG16_WRITE(reg, value) *(uint16_t *)(reg) = value
#define bspREG8_WRITE(reg, value) *(uint8_t *)(reg) = value

#define bspREG32_READ(reg) (*((uint32_t *)(reg)))
#define bspREG16_READ(reg) (*((uint16_t *)(reg)))
#define bspREG8_READ(reg) (*((uint8_t *)(reg)))


#endif /* BSP_H */
