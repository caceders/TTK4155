#ifndef HUMAN_INTERFACE_H
#define HUMAN_INTERFACE_H

#include <stdint.h>

typedef enum{
    NEUTRAL = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UNDEFINED

}direction;

typedef struct position{
    int16_t x_pos;
    int16_t y_pos;
}position;

void init_human_interface();

void calibrate_joy_position();

position get_joy_position();

direction get_joy_direction();

uint8_t get_r();
uint8_t get_l();
uint8_t get_j();

void set_joy_deadzone();

void read_human_interface();

#endif