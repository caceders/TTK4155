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
	PORTB |= (1 << PIN1);

	printf("Hello world!\n\r");

	direction last_dir = NEUTRAL;

    while (1) 
    {
		read_human_interface();
		
		direction dir = get_joy_direction();

		if (last_dir == NEUTRAL && dir != NEUTRAL){
			if(dir == DOWN){
				next_sub_menu();
			}else if (dir == UP){
				previous_sub_menu();
			}else if (dir == RIGHT){
				next_menu();
			}else if (dir == LEFT){
				previous_menu();
			}
			render_menu(&tbh);
			OLED_write(&oledh, framebuffer);
		}
		last_dir = dir;
    }
}