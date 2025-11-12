#ifndef __DELAY_H__
#define __DELAY_H__
#include <LPC21xx.h>

// Initialize Timer0 for 1us tick
static inline void timer0_init(void)
{
    VPBDIV = 0x02;      // VPB = CCLK/2 (commonly 30 MHz)
    T0CTCR = 0x0;       // Timer mode
    T0PR = 29;          // Prescale: 30MHz/(29+1) = 1MHz -> 1us tick
    T0TCR = 0x02;       // Reset
    T0TCR = 0x01;       // Enable
}

static inline void delay_us(unsigned int us)
{
    T0TCR = 0x02; // reset
    T0TCR = 0x01; // start
    while (T0TC < us) { }
    T0TCR = 0x00; // stop
}

static inline void delay_ms(unsigned int ms)
{
    while(ms--) delay_us(1000);
}

#endif
