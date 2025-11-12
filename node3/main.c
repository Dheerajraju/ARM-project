//Access Control NOde (RFID + CAN TX)
#include <LPC21xx.h>
#include <stdio.h>
#include "delay.h"
#include "lcd.h"
#include "can.h"
#include "rfid.h"

#define CAN_ID_RFID 0x03

int main(void)
{
    char buf[24];
    int tag_status;

    timer0_init();
    lcd_init();
    rfid_init();
    can_init();

    lcd_cmd(0x01); lcd_string("Node3: RFID"); delay_ms(800); lcd_cmd(0x01);

    while(1)
    {
        lcd_cmd(0x80); lcd_string("Waiting Tag    ");
        tag_status = rfid_read_tag();
        if(tag_status == 1)
        {
            // authorized
            can_send_4byte(CAN_ID_RFID, 0xAA,0xBB,0x01,0x00);
            lcd_cmd(0xC0); lcd_string("Auth Tag Sent  ");
            delay_ms(1500);
        }
        else if(tag_status == 0)
        {
            // unauthorized -- sample
            can_send_4byte(CAN_ID_RFID, 0xAA,0xBB,0x00,0x00);
            lcd_cmd(0xC0); lcd_string("UnAuth Tag    ");
            delay_ms(1500);
        }
        delay_ms(300);
    }
    return 0;
}
