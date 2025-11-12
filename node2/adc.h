//Light / Envirnoment node (LDR + CAN TX)
#ifndef __ADC_H__
#define __ADC_H__
#include <LPC21xx.h>

// AD0.1 -> P0.28
static inline void adc_init(void)
{
    PINSEL1 |= (1<<24); // P0.28 AD0.1
    AD0CR = (1<<1) | (4<<8) | (1<<21); // select ch1, clkdiv, PDN on
}

static inline unsigned int adc_read_ch1(void)
{
    AD0CR &= ~(0xFF<<24);
    AD0CR |= (1<<24); // start now
    while(!(AD0DR1 & (1u<<31)));
    return (AD0DR1 >> 6) & 0x3FF;
}
#endif
