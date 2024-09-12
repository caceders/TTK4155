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

#define BAUD 9600

int main(void)
{
	USART_init(9600);
	
	fdevopen(&USART_Transmit, &USART_Receive); //redirect stdout/stdin to uart
	
	XMEM_init();

	printf("Hello world!\n\r");

	SRAM_test();
	
	volatile char* adc_addr = 0x1401;
	volatile char* sram_addr = 0x1801;
	volatile char* oled_addr = 0x1001;
    while (1) 
    {
		*adc_addr = 1;
		_delay_ms(100);
		*sram_addr = 1;
		_delay_ms(100);
		*oled_addr = 1;
		_delay_ms(100);
    }
}