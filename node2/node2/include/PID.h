#ifndef PID_H
#define PID_H

#include <stdint.h>

uint32_t get_PID_output(int16_t curr_pos, int16_t target_pos);

#endif