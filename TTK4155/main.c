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

#define BAUD 9600

char* framebuffer = 0x1800;

textbox_handle_t tbh;

int my_putc(char data, FILE* f )
{
	(void)f;
	USART_Transmit(data, f);
	textbox_put_char(&tbh, data);
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
	oledh.cmd_addr = 0x1000;
	oledh.data_addr = 0x1200;
	oledh.columns = 128;
	oledh.pages = 8;
	OLED_init(&oledh);

	memset(framebuffer, 0, 128*8);
	textbox_get_default(&tbh, framebuffer);

	printf("Hello world!\n\r");
	//textbox_printline(&tbh, "inverted", 1);
	textbox_printline(&tbh, "not inverted", 0);

	//memcpy(framebuffer, font5['Q'-32], 5);
	OLED_write(&oledh, framebuffer);

	//enable pullup on joystick button
	PORTB |= (1 << PIN1);

    while (1) 
    {
		/*read_human_interface();
		
		position pos = get_joy_position();
		printf("\n\rbuttons: l:%u, r:%u, joy:%u", get_l(), get_r(), get_j());
		printf("\n\rx: %d, y: %d => ", pos.x_pos, pos.y_pos);
		switch (get_joy_direction())
		{
		case NEUTRAL:
			printf("NEUTRAL");
			break;
		
		case UP:
			printf("UP");
			break;

		case DOWN:
			printf("DOWN");
			break;

		case LEFT:
			printf("LEFT");
			break;

		case RIGHT:
			printf("RIGHT");
			break;

		case UNDEFINED:
			printf("????");
			break;
		
		default:
			break;
		}	

		_delay_ms(1000);
		*/
		char c = USART_Receive(NULL);
		printf("%c", c);
		OLED_write(&oledh, framebuffer);
    }
}