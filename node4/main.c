//Display and control node (LCD + motor + CAN RX)
#include <LPC21xx.h>
#include <stdio.h>
#include "delay.h"
#include "lcd.h"
#include "motor.h"
#include "can.h"

#define CAN_ID_OBSTACLE 0x01
#define CAN_ID_LIGHT    0x02
#define CAN_ID_RFID     0x03

int main(void)
{
    unsigned int id, data;
    char buf[24];

    timer0_init();
    lcd_init();
    motor_init();
    can_init();

    lcd_cmd(0x01); lcd_string("Node4: Control"); delay_ms(800); lcd_cmd(0x01);

    // default state
    motor_off();
    light_off();

    while(1)
    {
        if(can_receive_available())
        {
            id = can_read_id();
            data = can_read_data();
            // release buffer
            C1CMR = (1<<2);

            lcd_cmd(0x80);
            sprintf(buf, "ID:0x%02X", id & 0xFF);
            lcd_string(buf);

            if((id & 0xFF) == CAN_ID_OBSTACLE)
            {
                motor_off();
                light_on();
                lcd_cmd(0xC0); lcd_string("Obstacle: STOP ");
            }
            else if((id & 0xFF) == CAN_ID_LIGHT)
            {
                light_on();
                lcd_cmd(0xC0); lcd_string("Light: ON      ");
            }
            else if((id & 0xFF) == CAN_ID_RFID)
            {
                // parse data: here we simulated 3rd byte as status
                unsigned char status = (data>>16) & 0xFF;
                if(status == 1)
                {
                    motor_on();
                    lcd_cmd(0xC0); lcd_string("RFID: Auth->ON ");
                }
                else
                {
                    motor_off();
                    lcd_cmd(0xC0); lcd_string("RFID: Denied   ");
                }
            }
            else
            {
                lcd_cmd(0xC0); lcd_string("Unknown Msg    ");
            }
            delay_ms(1200);
            lcd_cmd(0x01);
        }
        // else poll again
    }
    return 0;
}
