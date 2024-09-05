/*
 * TTK4155.c
 *
 * Created: 02.09.2024 12:14:52
 * Author : Carl Anders J. Cederström, Simen Haug & Siver Grimstad
 */ 
#define F_CPU 4915200
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Create a square wave for testing purposes
	DDRA = 00000001; // Set PA0 output
	
    while (1) 
    {
		PORTA |= (1<<PA0);			// Set PA0 high
		_delay_ms(100);
		PORTA &= ~(1<<PA0);			// Set PA0 low
		_delay_ms(100);
    }
}