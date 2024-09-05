/*
 * TTK4155.c
 *
 * Created: 02.09.2024 12:14:52
 * Author : Carl Anders J. Cederström, Simen Haug & Siver Grimstad
 */ 
#define F_CPU 4915200
#include <avr/io.h>
#include "uart.h"

#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void)
{
	// Test to echo back received char
	USART_init(MYUBRR);
    while (1) 
    {
		char test_char = USART_Receive();
		USART_Transmit(test_char);
    }
}