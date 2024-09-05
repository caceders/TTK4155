/*
 * TTK4155.c
 *
 * Created: 02.09.2024 12:14:52
 * Author : Carl Anders J. Cederström, Simen Haug & Siver Grimstad
 */ 
#define F_CPU 4915200
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

// Driver includes
#include "drivers/uart.h"

#define BAUD 9600

int main(void)
{
	USART_init(F_CPU/16/BAUD-1);
	
	fdevopen(&USART_Transmit, &USART_Receive);
	printf("Hello world!");
	
    while (1) 
    {
		char c = USART_Receive();
		USART_Transmit(c);
    }
}