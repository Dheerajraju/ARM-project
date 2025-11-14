#include <LPC21xx.h>
#include "delay.h"

void can_init(void)
{
    PINSEL1 |= (1<<18) | (1<<20);  // TXD1, RXD1
    C1MOD = 1;
    C1BTR = 0x001C001D;            // ~125 kbps
    C1MOD = 0;
}

void can_send(unsigned int id, unsigned char d)
{
    C1TID1 = id;
    C1TDA1 = d;
    C1TFI1 = (1<<16);
    C1CMR = 0x21;
}
