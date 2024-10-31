#ifndef PWM_H
#define PWM_H

#include <stdint.h>

void pwm_init();
void servo_update_angle(uint8_t degrees);

#endif