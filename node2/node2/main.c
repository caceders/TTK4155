/*
 * node2.c
 *
 * Created: 10.10.2024 11:30:08
 * Author : Simen
 */ 


#include "sam.h"
#include "uart.h"

#define F_CPU 84000000

int my_putc(char data, FILE* f )
{
	(void)f;
	uart_tx(data);
	//textbox_put_char(&tbh, data);
}

int my_getc(FILE* f){
    NULL;
}

int main(void)
{
    uart_init(F_CPU, 9600);
    fdevopen(&my_putc, &my_getc); //redirect stdout/stdin to uart
    /* Initialize the SAM system */
    SystemInit();

    printf("Hello world!");

    /* Replace with your application code */
    while (1);
}
