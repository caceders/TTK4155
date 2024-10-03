#ifndef SPI_H
#define SPI_H

#include <stdint.h>

void SPI_init(void);

void SPI_transmit_byte(uint8_t data);

uint8_t SPI_receive_byte();


#endif 