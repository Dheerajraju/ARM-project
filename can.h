#ifndef __CAN_H__
#define __CAN_H__
#include <LPC21xx.h>

// Basic CAN1 init + simple send. Tune C1BTR for your clock/baud.
static inline void can_init(void)
{
    // Map P0.25 = TXD1, P0.26 = RXD1
    PINSEL1 |= (1<<18) | (1<<20);
    VPBDIV = 0x02;    // PCLK
    C1MOD = 1;        // reset
    C1BTR = 0x001C001D; // sample bit-timing (example for 125kbps)
    C1MOD = 0;        // normal mode
}

// Send up to 4 bytes (packed into TDA)
static inline void can_send_4byte(unsigned int id, unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3)
{
    // Wait optionally or just load mailbox
    C1TID1 = id & 0x7FF;
    C1TDA1 = (b0) | (b1<<8) | (b2<<16) | (b3<<24);
    C1TFI1 = ( (4 & 0x0F) << 16 ); // DLC=4
    // request transmit buffer 1: C1CMR bits may vary; 0x21 worked in earlier snippets.
    C1CMR = 0x21;
    // small delay to allow hardware to accept
    delay_ms(2);
}

static inline int can_receive_available(void)
{
    return (C1GSR & (1<<0)); // RBS (receive buffer status) depending on chip mapping
}

static inline unsigned int can_read_id(void)
{
    return C1RID;
}

static inline unsigned int can_read_data(void)
{
    return C1RDA; // data low register
}

#endif
