#include <LPC21xx.h>
#include "delay.h"
#include "lcd.h"
#include "can.h"
#include "ultrasonic.h"

int main()
{
    unsigned int d;

    IODIR1 |= 0x00FF0000 | (1<<16) | (1<<17);  
    IODIR0 |= (1<<10);       
    IODIR0 &= ~(1<<11);      

    delay_init();
    lcd_init();
    can_init();

    while(1)
    {
        d = get_distance();

        lcd_cmd(0x80);
        lcd_data((d/100)+'0');
        lcd_data(((d/10)%10)+'0');
        lcd_data((d%10)+'0');

        if(d < 20)
            can_send(1,1);      // ID=1, data=1

        delay_ms(500);
    }
}
