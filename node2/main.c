#include <LPC21xx.h>
#include <stdio.h>
#include "delay.h"
#include "lcd.h"
#include "adc.h"
#include "can.h"

#define CAN_ID_LIGHT 0x02

int main(void)
{
    unsigned int light;
    char buf[24];

    timer0_init();
    lcd_init();
    adc_init();
    can_init();

    lcd_cmd(0x01); lcd_string("Node2: LDR"); delay_ms(800); lcd_cmd(0x01);

    while(1)
    {
        light = adc_read_ch1();
        lcd_cmd(0x80);
        sprintf(buf, "Light:%u   ", light);
        lcd_string(buf);

        // threshold: calibrate for your resistor
        if(light < 400)
        {
            // low light -> tell Node4 to turn ON lights
            can_send_4byte(CAN_ID_LIGHT, 0x11,0x00,0x00,0x00);
            lcd_cmd(0xC0);
            lcd_string("Low Light -> CAN");
        }
        else
        {
            lcd_cmd(0xC0);
            lcd_string("Bright          ");
        }
        delay_ms(1000);
    }
    return 0;
}
