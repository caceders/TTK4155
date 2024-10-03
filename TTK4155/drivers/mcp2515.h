#ifndef MCP2515_H
#define MCP2515_H

#include <stdint.h>

typedef enum{
    WRITE           = 0b00000010,
    READ            = 0b00000011,
    BIT_MODIFY      = 0b00000101,
    LOAD_TX_BUFFER  = 0b01000000,
    READ_RX_BUFFER  = 0b10010000,
    READ_STATUS     = 0b10100000,
    RX_STATUS       = 0b10110000,
    RESET           = 0b11000000, 
}MCP2515_instruction;

void MCP2515_init();

uint8_t MCP2515_read(uint8_t addr);

uint8_t MCP2515_write(uint8_t addr, uint8_t data);

#endif