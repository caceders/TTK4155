#include "mcp2515.h"
#include "spi.h"
#include <avr/io.h>
#include <stdio.h>



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
    MCP2515_reset();

    // Self-test
    uint8_t value = MCP2515_read(MCP_CANSTAT_ADDR);
    printf("MCP CANSTAT = %X\n\r", value);
    if ((value & MCP_MODE_MASK)>>MCP_MODE_BP != MCP_MODE_CONFIG){
        printf("MCP2515 is NOT in configuration mode after reset! \n\r");
    }

    deselect_slave();
}

void MCP2515_set_mode(MCP_mode mode){
    MCP2515_bit_modify(MCP_CANCTRL_ADDR, MCP_MODE_MASK, mode << MCP_MODE_BP);
}

uint8_t MCP2515_read(uint8_t addr){
    select_slave();

    SPI_transmit_byte(READ);
    SPI_transmit_byte(addr);
    uint8_t data = SPI_receive_byte();
    
    deselect_slave();
    return data;
}

void MCP2515_write(uint8_t addr, uint8_t data){
    select_slave();

    SPI_transmit_byte(WRITE);
    SPI_transmit_byte(addr);
    SPI_transmit_byte(data);
    
    deselect_slave();
}

void MCP2515_RTS(RTS_transmit_buffer_reg TX_reg){
    select_slave();

    SPI_transmit_byte(RTS | TX_reg);
    
    deselect_slave();
}

void MCP2515_load_tx_buffer(Load_transmit_buffer_reg TX_reg, uint8_t* buff, uint8_t num_reg){
    select_slave();

    SPI_transmit_byte(LOAD_TX_BUFFER | TX_reg);
    for(uint8_t i = 0; i < num_reg; i++){
        SPI_transmit_byte(buff[i]);
    }
    deselect_slave();
}

void MCP2515_read_rx_buffer(Load_transmit_buffer_reg RX_reg, uint8_t* buff, uint8_t num_reg){
    select_slave();
    
    SPI_transmit_byte(READ_RX_BUFFER | (RX_reg << 1)); //bit shift by one according to the READ_RX_BUFFER instruction in datasheet
    for(uint8_t i = 0; i < num_reg; i++){
        uint8_t data = SPI_receive_byte();
        buff[i] = data;
    }
    
    deselect_slave();
}

uint8_t MCP2515_read_status(){
    select_slave();

    SPI_transmit_byte(READ_STATUS);
    uint8_t data = SPI_receive_byte();
    
    deselect_slave();
    return data;
}

void MCP2515_bit_modify(uint8_t addr, uint8_t mask, uint8_t data){
    select_slave();

    SPI_transmit_byte(BIT_MODIFY);
    SPI_transmit_byte(addr);
    SPI_transmit_byte(mask);
    SPI_transmit_byte(data);
    
    deselect_slave();
}

void MCP2515_reset(){
    select_slave();

    SPI_transmit_byte(RESET);
    
    deselect_slave();
}

void MCP2515_set_bit_timing(uint8_t BRP, uint8_t prop_seg_TQ, uint8_t phase_seg_1_TQ, uint8_t phase_seg_2_TQ, uint8_t sjw_TQ){ 
    MCP2515_write(MCP_CNF_3, phase_seg_2_TQ); // Assume user passes SOF and WAKFIL to 0
    phase_seg_1_TQ = phase_seg_1_TQ << 3;
    phase_seg_1_TQ |= 0b10000000; // Set BTLMODE = 1
    uint8_t cnf_2 = phase_seg_1_TQ | prop_seg_TQ; // Assume user only write lower bits of prop_seg_TQ
    MCP2515_write(MCP_CNF_2, cnf_2);

    uint8_t cnf_1 = BRP | (sjw_TQ << 6);
    MCP2515_write(MCP_CNF_1, cnf_1);
}