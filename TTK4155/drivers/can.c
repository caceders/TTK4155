#include "can.h"
#include "mcp2515.h"
#include <avr/io.h>
#include <stdio.h>


// Hard coded to only use transmit buffer 0
void can_transmit(can_msg* msg){
    // Set id high
    uint8_t id_high = msg->id >> 3;

    // Set id low
    uint8_t id_low = msg->id << 5;
    id_low &= ~(1 << 3); // Set extended id bit to 0
    id_low &= 0xFF;

    uint8_t control[5];
    control[0] = id_high;
    control[1] = id_low;
    control[4] = msg->data_length & ~(1 << 7);

    MCP2515_load_tx_buffer(LOAD_TXB0_SIDH, control, sizeof(control));

    MCP2515_load_tx_buffer(LOAD_TXB0_DATA, msg->payload, msg->data_length);
    
    MCP2515_RTS(RTS_TXB0);
}

void can_receive(can_msg* msg){

    uint8_t control[5];

    printf("Preparing to read msg control\n\r");
    MCP2515_read_rx_buffer(LOAD_RXB0_SIDH, control, sizeof(control));
    printf("Read msg control\n\r");
    uint8_t id_high, id_low;
    id_high = control[0];
    id_low = control[1];
    msg->id = (id_high << 3) | (id_low >> 5); 
    msg->data_length = control[4] & 0xF;

    printf("Length of recieved message = %u\n\r", msg->data_length);
    MCP2515_read_rx_buffer(LOAD_RXB0_DATA, msg->payload, msg->data_length);

    //printf("Read msg\n\r");
}