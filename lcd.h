#include <LPC21xx.h>
#include "delay.h"
#define LCD_H

void lcd_cmd(unsigned char c)
{
    IO1CLR = 0x00FF0000;
    IO1SET = (c << 16);

    IO1CLR = (1<<16);   // RS = 0
    IO1SET = (1<<17);   // EN = 1
    delay_ms(2);
    IO1CLR = (1<<17);   // EN = 0
}

void lcd_data(unsigned char d)
{
    IO1CLR = 0x00FF0000;
    IO1SET = (d << 16);

    IO1SET = (1<<16);   // RS = 1
    IO1SET = (1<<17);
    delay_ms(2);
    IO1CLR = (1<<17);
}

void lcd_init(void)
{
    delay_ms(20);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}
