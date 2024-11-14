#include "PID.h"
#include "sam.h"
#include "time.h"
#include <stdint.h>

const uint8_t PID_NUM_SAMPLES = 10;
const uint8_t PID_SAMPLING_TIME = 20; //ms
const int8_t PID_K_P = 4;
const int8_t PID_K_I = 2;
const int8_t PID_K_D = 0;

int32_t _prev_errors[10];

// Expect user to call this every PID_SAMPLING_TIME ms
uint32_t get_PID_output(int16_t curr_pos, int16_t target_pos){
    
    uint32_t error = target_pos - curr_pos;
    
    uint32_t proporsonal = PID_K_P * error;

    // Calculate integral part
    uint32_t integral = PID_SAMPLING_TIME * PID_K_I * error;
    for(uint8_t i = 0; i < PID_NUM_SAMPLES; i++){
        integral += PID_SAMPLING_TIME * PID_K_I * _prev_errors[i]/15;
    }

    uint32_t differential = (PID_K_D/PID_SAMPLING_TIME) * (error - _prev_errors[0]);

    uint32_t PID_output = (proporsonal + integral - differential);

    // Propagate samples in previous errors
    for(uint8_t i = 0; i < PID_NUM_SAMPLES - 1; i++){
        _prev_errors[i + 1] = _prev_errors[i];
    }
    _prev_errors[0] = error;

    return PID_output;
}