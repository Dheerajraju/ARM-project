#include <LPC21xx.h>
#include "delay.h"

unsigned int get_distance(void)
{
    unsigned int t;

    IO0CLR = (1<<10);
    delay_us(2);
    IO0SET = (1<<10);
    delay_us(10);
    IO0CLR = (1<<10);

    t = 300000;
    while(!(IO0PIN & (1<<11)))
        if(--t == 0) return 999;

    T0TCR = 2;
    T0TCR = 1;

    t = 300000;
    while(IO0PIN & (1<<11))
        if(--t == 0) break;

    T0TCR = 0;

    return T0TC/58;
}
