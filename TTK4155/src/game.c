#include "game.h"
#include "can.h"
#include "textbox.h"
#include "human_interface.h"
#include "mcp2515.h"
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "main.h"
#include <string.h>

void play_game(){
    printf("playing...\r\n");

    uint32_t score = 0;
    char score_str[10];

    can_msg tx_msg;
    can_msg rx_msg;

	tx_msg.data_length = 0;
	tx_msg.id = 0xAA;

	can_transmit(&tx_msg);


    //Send start game message over can
    //Update screen
    //start timer

    tx_msg.id = 0x22;
    tx_msg.data_length = 7;
    while(1){
        read_human_interface();
		
		tx_msg.payload[0] = get_joy_position().x_pos & 0xFF;
        tx_msg.payload[1] = (get_joy_position().x_pos >> 8) & 0xFF;
        tx_msg.payload[2] = get_joy_position().y_pos & 0xFF;
        tx_msg.payload[3] = (get_joy_position().y_pos >> 8) & 0xFF;
        tx_msg.payload[4] = get_slider_l();
        tx_msg.payload[5] = get_slider_r();
        tx_msg.payload[6] = get_l() | (get_r() << 1) | (get_j() << 2);

		can_transmit(&tx_msg);

        uint8_t intf = MCP2515_read(MCP_CANINTF_ADDR);
        if(intf & 1){
            //printf("Still Okily dokily\r\n");
            can_receive(&rx_msg);
            if (rx_msg.id == 0x01){
                printf("game over\r\n");
                return;
            }
        }

        if (score %10 == 0){
            tbh.carriage_x = 0;
            tbh.carriage_y = 0;
            textbox_clear(&tbh);
            snprintf(score_str, 10, "%d", score/10);
            tbh.inverted = 1;
            textbox_println(&tbh, "Score:");
            tbh.inverted = 0;
            textbox_print(&tbh, score_str);
            OLED_write(&oledh, framebuffer);
        }
        score++;
        _delay_ms(20);
        
    }
    //loop
        //send joystick values
        //poll can
    //display score 
}