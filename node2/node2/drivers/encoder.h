#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>

void encoder_init();
uint32_t encoder_read();
void encoder_reset();

#endif