/*
 * TTK4155.c
 *
 * Created: 02.09.2024 12:14:52
 * Author : Carl Anders J. Cederström, Simen Haug & Siver Grimstad
 */ 
#define F_CPU 4915200
#include <avr/io.h>
#include <util/delay.h>

#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void)
{
	// Create a square wave for testing purposes
	//DDRA = 00000001; // Set PA0 output
    //while (1) 
    //{
	//	PORTA |= (1<<PA0);			// Set PA0 high
	//	_delay_ms(100);
	//	PORTA &= ~(1<<PA0);			// Set PA0 low
	//	_delay_ms(100);
    //}
	
	// Test to echo back received char
	//USART_init(MYUBRR);
	//while (1)
	//{
	//	char test_char = USART_Receive();
	//	USART_Transmit(test_char);
	//}
	
	// Test to bind the printf function
	fdevopen(&USART_Transmit, &USART_Receive)
	printf("Hello world!")
}