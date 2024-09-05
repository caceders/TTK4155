/*
 * TTK4155.c
 *
 * Created: 02.09.2024 12:14:52
 * Author : Carl Anders J. Cederström, Simen Haug & Siver Grimstad
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <delay.h>

int main(void)
{
	// Create a square wave for testing purposes
	DDRA = 0000 0001; // Set PA0 output
	
    while (1) 
    {
		PORTA |= (1<<PA0);			// Set PA0 high
		delay_ms(300);
		PORTA |= (0<<PA0);			// Set PA0 low
		delay_ms(300);
    }
}

