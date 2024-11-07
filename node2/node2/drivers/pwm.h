#ifndef PWM_H
#define PWM_H

#include <stdint.h>

typedef enum  {
    MOTOR_DIR_RIGHT,
    MOTOR_DIR_LEFT
}motor_dir_t;

void pwm_init();
void servo_update_angle(uint8_t degrees);

void motor_update_power(uint32_t val);

void motor_update_direction(motor_dir_t dir);



#endif