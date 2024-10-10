#ifndef CAN_H
#define CAN_H

#include <stdint.h>

typedef struct can_msg{
    uint16_t id;
    uint8_t data_length;
    uint8_t payload[8];
}can_msg;

void can_transmit(can_msg* msg);
void can_receive(can_msg* msg);

#endif