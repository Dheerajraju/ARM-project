#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__
#include <LPC21xx.h>
#include "delay.h"

#define TRIG_PIN (1<<10) // P0.10
#define ECHO_PIN (1<<11) // P0.11

static inline void ultrasonic_init(void)
{
    IODIR0 |= TRIG_PIN;   // trig out
    IODIR0 &= ~ECHO_PIN;  // echo in
}

// Uses Timer0 microsecond tick from delay.h
static inline unsigned int ultrasonic_distance_cm(void)
{
    unsigned int start, stop;
    unsigned int timeout = 300000; // large timeout
    // trigger
    IO0CLR = TRIG_PIN;
    delay_us(2);
    IO0SET = TRIG_PIN;
    delay_us(10);
    IO0CLR = TRIG_PIN;

    // wait echo high
    timeout = 300000;
    while(!(IO0PIN & ECHO_PIN) && --timeout) { }
    if(!timeout) return 0xFFFF;

    // measure width (use timer T0TC in us)
    T0TCR = 0x02; // reset
    T0TCR = 0x01; // start
    timeout = 300000;
    while((IO0PIN & ECHO_PIN) && --timeout) { }
    stop = T0TC;
    T0TCR = 0x00; // stop

    // distance in cm: pulse_us/58
    return (stop/58);
}

#endif
