#ifndef UART_H
#define UART_H

#include <stdio.h>

void USART_init(uint32_t baud);
int USART_Transmit(char data, FILE* f );
int USART_Receive(FILE* f );

#endif