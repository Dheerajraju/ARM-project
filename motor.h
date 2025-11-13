#include <LPC21xx.h>


// P0.7 = MOTOR
// P0.8 = LIGHT

void control_init(void)
{
    IODIR0 |= (1<<7) | (1<<8);   // both outputs
}

void motor_on(void)
{
    IO0SET = (1<<7);
}

void motor_off(void)
{
    IO0CLR = (1<<7);
}

void light_on(void)
{
    IO0SET = (1<<8);
}

void light_off(void)
{
    IO0CLR = (1<<8);
}
