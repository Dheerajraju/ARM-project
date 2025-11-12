#include <LPC21xx.h>
#include <stdio.h>
#include "delay.h"
#include "lcd.h"
#include "can.h"
#include "ultrasonic.h"
#include "motor.h"

#define CAN_ID_OBSTACLE 0x01

int main(void)
{
    unsigned int dist;
    char buf[20];

    timer0_init();
    lcd_init();
    ultrasonic_init();
    motor_init();
    can_init();

    lcd_cmd(0x01); lcd_string("Node1: Ultrasonic"); delay_ms(800); lcd_cmd(0x01);

    while(1)
    {
        dist = ultrasonic_distance_cm();
        lcd_cmd(0x80);
        sprintf(buf, "Dist:%ucm    ", dist);
        lcd_string(buf);

        if(dist != 0xFFFF && dist < 20)
        {
            motor_off(); // local safety
            // send CAN alert (4 bytes example)
            can_send_4byte(CAN_ID_OBSTACLE, 0xDE,0xAD,0x00,0x01);
            lcd_cmd(0xC0);
            lcd_string("Obstacle! Sent");
        }
        else
        {
            lcd_cmd(0xC0);
            lcd_string("Clear         ");
            motor_on();
        }
        delay_ms(800);
    }
    return 0;
}
