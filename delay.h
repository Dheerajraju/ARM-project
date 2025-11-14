#ifndef DELAY_H
#define DELAY_H

void delay_ms(unsigned int ms);

#endif
/*
#include<LPC21XX.H>
#define DELAY_H

void delay_ms(unsigned int);

void delay_ms(unsigned int ms)
{
    T0PR  = 15000-1;
    T0TCR = 0x01;
    while(T0TC < ms);
    T0TCR = 0x03;
    T0TCR = 0x00;
}
*/



