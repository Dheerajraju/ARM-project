#ifndef __LCD_H__
#define __LCD_H__
#include <LPC21xx.h>
#include "delay.h"

#define LCD_DATA_MASK  (0x00FF0000) // P1.16..P1.23
#define LCD_RS         (1<<16)
#define LCD_EN         (1<<17)

static inline void lcd_cmd(unsigned char cmd)
{
    IO1CLR = LCD_DATA_MASK;
    IO1SET = ((unsigned int)cmd << 16) & LCD_DATA_MASK;
    IO1CLR = LCD_RS;
    IO1SET = LCD_EN;
    delay_ms(2);
    IO1CLR = LCD_EN;
}

static inline void lcd_data(unsigned char data)
{
    IO1CLR = LCD_DATA_MASK;
    IO1SET = ((unsigned int)data << 16) & LCD_DATA_MASK;
    IO1SET = LCD_RS;
    IO1SET = LCD_EN;
    delay_ms(2);
    IO1CLR = LCD_EN;
}

static inline void lcd_init(void)
{
    delay_ms(50);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
    delay_ms(5);
}

static inline void lcd_string(const char *s)
{
    while(*s) lcd_data(*s++);
}



