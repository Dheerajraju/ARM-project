#include <LPC21xx.h>
#include "delay.h"
#include "lcd.h"
#include "can.h"
#include "ultrasonic.h"
#include "delay.c"
int main()
{
    unsigned int dist;

    // LCD pins
    IODIR1 |= 0x00FF0000 | (1<<16) | (1<<17);

    // Ultrasonic pins
    IODIR0 |= (1<<10);       // TRIG
    IODIR0 &= ~(1<<11);      // ECHO

    can_init();
    lcd_init();

    while(1)
    {
        dist = get_distance();

        lcd_cmd(0x80);
        lcd_data((dist/100) + '0');
        lcd_data(((dist/10)%10) + '0');
        lcd_data((dist%10) + '0');

        if(dist < 20)
        {
            can_send(1, 1);  // ID=1, obstacle found
            lcd_cmd(0xC0);
            lcd_data('O');
            lcd_data('B');
            lcd_data('S');
        }

        delay_ms(300);
    }
}
