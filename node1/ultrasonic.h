#include <LPC21xx.h>
#include "delay.h"
unsigned int get_distance(void)
{
    unsigned int t;

    // Trigger pulse
    IO0CLR = (1<<10);
    delay_ms(1);
    IO0SET = (1<<10);
    delay_ms(1);
    IO0CLR = (1<<10);

    // Wait for echo HIGH
    t = 50000;
    while(!(IO0PIN & (1<<11)))
        if(--t == 0) return 999;

    // Measure pulse width using Timer1
    T1PR = 14;     // approx 1us
    T1TCR = 2;     // reset
    T1TCR = 1;     // start

    t = 50000;
    while(IO0PIN & (1<<11))
        if(--t == 0) break;

    T1TCR = 0;     // stop

    return T1TC / 58;  // convert to cm
}
