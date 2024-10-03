#include "mcp2515.h"
#include "spi.h"
#include <avr/io.h>



void select_slave(){
    PORTB &= ~(1 << PB4);
}

void deselect_slave(){
    PORTB |= (1 << PB4);
}

void MCP2515_init(){
    //set SS to output
    DDRB |= (1 << 4);
    
    SPI_init();

    deselect_slave();
}

uint8_t MCP2515_read(uint8_t addr){
    select_slave();

    SPI_transmit_byte(READ);
    SPI_transmit_byte(addr);
    uint8_t data = SPI_receive_byte();
    
    deselect_slave();
    return data;
}

uint8_t MCP2515_write(uint8_t addr, uint8_t data){
    select_slave();

    SPI_transmit_byte(WRITE);
    SPI_transmit_byte(addr);
    SPI_transmit_byte(data);
    
    deselect_slave();
}