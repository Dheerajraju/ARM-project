#ifndef __RFID_H__
#define __RFID_H__
#include <LPC21xx.h>
#include "delay.h"

// Placeholder: implement real RFID reading (SPI-based MFRC522 or UART-based reader)
// For demonstration we simulate reading an authorized tag on button press P0.4.

#define RFID_BUTTON (1<<4)

static inline void rfid_init(void)
{
    IODIR0 &= ~RFID_BUTTON; // input button simulating tag read
}

// Simulated function: returns 1 if authorized tag read, 0 if unauthorized, -1 if none
static inline int rfid_read_tag(void)
{
    // If button pressed simulate authorized
    if(!(IO0PIN & RFID_BUTTON))
    {
        delay_ms(200); // debounce
        if(!(IO0PIN & RFID_BUTTON))
        {
            // For real RFID, read tag UID and compare with stored list
            return 1; // authorized (simulate)
        }
    }
    return -1; // no read
}

#endif
