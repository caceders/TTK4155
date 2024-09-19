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

#define BAUD 9600

int main(void)
{
	USART_init(9600);
	
	fdevopen(&USART_Transmit, &USART_Receive); //redirect stdout/stdin to uart
	
	XMEM_init();

	printf("Hello world!\n\r");

	SRAM_test();

	ADC_handle_t adc;
	adc.addr = 0x1400;
	adc.mode = ADC_MODE_HARDWIRED;
	adc.sample_time_us = (2*4*9)/(F_CPU/1000000) + 2; //according to datasheet + margin

	volatile char* sram_addr = 0x1801;
	volatile char* oled_addr = 0x1001;
    while (1) 
    {
		ADC_read(&adc);
		printf("ADC values: ch0: %u, ch1: %u, ch2:%u, ch3: %u\n\r", adc.ch[0], adc.ch[1], adc.ch[2], adc.ch[3]);
		_delay_ms(1000);
    }
}