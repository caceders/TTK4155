#ifndef MCP2515_H
#define MCP2515_H

#include <stdint.h>

#define MCP_MODE_BP 5
#define MCP_MODE_MASK (0xE0)

#define MCP_CANCTRL_ADDR (0x0F)
#define MCP_CANSTAT_ADDR (0x0E)
#define MCP_CANINTF_ADDR (0x2C)

typedef enum{
    WRITE           = 0b00000010,
    READ            = 0b00000011,
    BIT_MODIFY      = 0b00000101,
    LOAD_TX_BUFFER  = 0b01000000,
    READ_RX_BUFFER  = 0b10010000,
    READ_STATUS     = 0b10100000,
    RX_STATUS       = 0b10110000,
    RESET           = 0b11000000,
    RTS             = 0b10000000,
}MCP2515_instruction;

typedef enum{
    RTS_TXB0            = 0b00000001,
    RTS_TXB1            = 0b00000010,
    RTS_TXB2            = 0b00000100,
}RTS_transmit_buffer_reg;

typedef enum{
    LOAD_TXB0_SIDH      = 0b00000000,
    LOAD_TXB0_DATA      = 0b00000001,
    LOAD_TXB1_SIDH      = 0b00000010,
    LOAD_TXB1_DATA      = 0b00000011,
    LOAD_TXB2_SIDH      = 0b00000101,
    LOAD_TXB2_DATA      = 0b00000101,
}Load_transmit_buffer_reg;

typedef enum{
    LOAD_RXB0_SIDH      = 0b00000000,
    LOAD_RXB0_DATA      = 0b00000001,
    LOAD_RXB1_SIDH      = 0b00000010,
    LOAD_RXB1_DATA      = 0b00000011,
}Load_receive_buffer_reg;

typedef enum{
    MCP_MODE_NORMAL = 0b000,
    MCP_MODE_SLEEP = 0b001,
    MCP_MODE_LOOPBACK = 0b010,
    MCP_MODE_LISTEN_ONLY = 0b011,
    MCP_MODE_CONFIG = 0b100,
}MCP_mode;





void MCP2515_init();

uint8_t MCP2515_read(uint8_t addr);

void MCP2515_write(uint8_t addr, uint8_t data);

void MCP2515_RTS(RTS_transmit_buffer_reg TX_reg);

void MCP2515_load_tx_buffer(Load_transmit_buffer_reg TX_reg, uint8_t* buff, uint8_t num_reg);

void MCP2515_read_rx_buffer(Load_transmit_buffer_reg TX_reg, uint8_t* buff, uint8_t num_reg);

void MCP2515_set_mode(MCP_mode mode);

uint8_t MCP2515_read_status();

void MCP2515_bit_modify(uint8_t addr, uint8_t mask, uint8_t data);

void MCP2515_reset();

#endif