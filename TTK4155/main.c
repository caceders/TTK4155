/*
 * TTK4155.c
 *
 * Created: 02.09.2024 12:14:52
 * Author : Carl Anders J. Cederstr�m, Simen Haug & Siver Grimstad
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

// Driver includes
#include "uart.h"
#include "xmem.h"
#include "adc.h"
#include "oled.h"
#include "human_interface.h"
#include "textbox.h"
#include "menu_navigation.h"
#include "menu.h"
#include "mcp2515.h"
#include "can.h"
#include "pwm.h"

#define BAUD 9600

char* framebuffer = (uint8_t*)0x1800; //SRAM address

textbox_handle_t tbh;

int my_putc(char data, FILE* f )
{
	(void)f;
	USART_Transmit(data, f);
	//textbox_put_char(&tbh, data);
}

int main(void)
{
	USART_init(9600);
	
	fdevopen(&my_putc, &USART_Receive); //redirect stdout/stdin to uart
	
	XMEM_init();

	//SRAM_test();

	init_human_interface();
	calibrate_joy_position();
	//volatile char* sram_addr = 0x1801;
	//volatile char* oled_addr = 0x1001;

	OLED_handle_t oledh;
	oledh.cmd_addr = (uint8_t*)0x1000;
	oledh.data_addr = (uint8_t*)0x1200;
	oledh.columns = 128;
	oledh.pages = 8;
	OLED_init(&oledh);

	memset(framebuffer, 0, 128*8);
	textbox_get_default(&tbh, framebuffer);

	initialize_menu();
	render_menu(&tbh);

	//memcpy(framebuffer, font5['Q'-32], 5);
	OLED_write(&oledh, framebuffer);

	//enable pullup on joystick button
	//PORTB |= (1 << PIN1);

	MCP2515_init();
	//printf("SPCR = %u\r\n", SPCR);

	//Set bit timing for can - values standard values j.f chattarn
	//Nominal bitrate target = 125 kbit/s
	MCP2515_set_bit_timing(3, 4, 5, 3, 0);

	//uint8_t cnf1 = MCP2515_read(MCP_CNF_1);
	//uint8_t cnf2 = MCP2515_read(MCP_CNF_2);
	//uint8_t cnf3 = MCP2515_read(MCP_CNF_3);
	//printf("%x and %x and %x", cnf1, cnf2, cnf3);

	

	MCP2515_set_mode(MCP_MODE_NORMAL);

	printf("Hello world!\r\n");
	
	can_msg msg;

	msg.data_length = 8;
	msg.payload[0] = 0xA6;
	msg.payload[1] = 0x5F;
	msg.payload[2] = 0x5E;
	msg.payload[3] = 0x5D;
	msg.payload[4] = 0x5C;
	msg.payload[5] = 0x5B;
	msg.payload[6] = 0x5A;
	msg.payload[7] = 0x59;
	msg.id = 0xFF;

	can_transmit(&msg);

	_delay_ms(10);

	uint8_t intf = MCP2515_read(MCP_CANINTF_ADDR);
	if(intf & 1){
		printf("Okily dokily\r\n");
		can_msg rmsg;
		//printf("Still Okily dokily\r\n");
		can_receive(&rmsg);
		printf("ding-dong-diddily-do, message with ID %X has been looped back to you: 0: %X, 1: %X\r\n", rmsg.id, rmsg.payload[0], rmsg.payload[1]);
	}else{
		printf("Stranger danger\r\n");	
	}

	//MCP2515_write(0x0C, 63);
	//printf("Written to mcp\r\n");
	//uint8_t val = MCP2515_read(0x0F);
	//printf("MCP magic canary value %u\r\n", val);

	/* uint8_t received[8];
	MCP2515_read_rx_buffer(LOAD_RXB0_SIDH, received);
	printf("Magic values in buffer register \n");
	for(uint8_t i = 0; i <8; i++){
		printf("%u\r\n",received[i]);
	} */

	//uint8_t val = MCP2515_read_status(0x0C, 63);
	//printf("MCP status value %u\r\n", val);


	direction last_dir = NEUTRAL;

	can_msg joy_msg;

	joy_msg.data_length = 1;
	joy_msg.id = 0x11;
    while (1) 
    {
		read_human_interface();
		
		joy_msg.payload[0] = (uint8_t)get_joy_direction();

		can_transmit(&joy_msg);

		_delay_ms(1000);

    }
}