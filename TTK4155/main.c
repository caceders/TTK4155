/*
 * TTK4155.c
 *
 * Created: 02.09.2024 12:14:52
 * Author : Carl Anders J. Cederstr�m, Simen Haug & Siver Grimstad
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

// Driver includes
#include "uart.h"
#include "xmem.h"
#include "adc.h"
#include "human_interface.h"

#define BAUD 9600

int main(void)
{
	USART_init(9600);
	
	fdevopen(&USART_Transmit, &USART_Receive); //redirect stdout/stdin to uart
	
	XMEM_init();

	printf("Hello world!\n\r");

	SRAM_test();

	init_human_interface();
	calibrate_joy_position();
	//volatile char* sram_addr = 0x1801;
	//volatile char* oled_addr = 0x1001;

	//enable pullup on joystick button
	PORTB |= (1 << PIN1);

    while (1) 
    {
		read_human_interface();
		
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

		_delay_ms(1001);
    }
}