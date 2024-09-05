/*
 * TTK4155.c
 *
 * Created: 02.09.2024 12:14:52
 * Author : Carl Anders J. Cederström, Simen Haug & Siver Grimstad
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

// Driver includes
#include "uart.h"

#define BAUD 9600

int main(void)
{
	USART_init(9600);
	
	fdevopen(&USART_Transmit, &USART_Receive); //redirect stdout/stdin to uart
	
	printf("Hello world!");
	
    while (1) 
    {
		char c = USART_Receive(NULL);
		USART_Transmit(c, NULL);
    }
}