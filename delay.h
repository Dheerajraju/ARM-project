#include <LPC21xx.h>

void delay_init(void)
{
    VPBDIV = 2;   // PCLK = CCLK/2
    T0PR = 29;    // 30MHz -> 1us/tick
}

void delay_us(unsigned int x)
{
    T0TCR = 2;      // reset
    T0TCR = 1;      // run
    while(T0TC < x);
    T0TCR = 0;      // stop
}

void delay_ms(unsigned int x)
{
    while(x--) delay_us(1000);
}
