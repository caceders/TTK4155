#include "spi.h"
#include <avr/io.h>




void SPI_init(void){
    //Set MOSI and SCK as output
    DDRB |= (1 << PB5) | (1 << PB7);
    
    //Set MISO as output
    DDRB &= ~(1 << PB6);

    //Enable SPI in master mode. clock is prescaled by 16
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI_transmit_byte(uint8_t data){
    SPDR = data;
    //wait until data is transmitted
    while(!(SPSR & (1 << SPIF)));
}

uint8_t SPI_receive_byte(){
    SPDR = 0xFF;
    //wait until data is recieved
    while(!(SPSR & (1 << SPIF)));
    return SPDR;
}
