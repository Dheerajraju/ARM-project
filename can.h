#include <LPC21xx.h>
#include "delay.h"

void can_init(void)
{
    PINSEL1 |= (1<<18) | (1<<20);   // TXD1, RXD1
    C1MOD = 1;                       // reset mode
    C1BTR = 0x001C001D;              // approx 125kbps
    C1MOD = 0;                       // normal mode
}

void can_send(unsigned int id, unsigned char data)
{
    C1TID1 = id;
    C1TDA1 = data;
    C1TFI1 = (1<<16);                // DLC = 1 byte
    C1CMR = 0x21;                    // send
}

int can_available(void)
{
    return (C1GSR & 1);
}

unsigned int can_read_id(void)
{
    return C1RID;
}

unsigned char can_read_data(void)
{
    return (unsigned char)C1RDA;
}
