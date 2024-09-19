#include "adc.h"

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

void ADC_read(ADC_handle_t* adch){
    *(adch->addr) = adch->config; //write config / dummy value
    _delay_us(adch->sample_time_us); //wait for sample and conversion
    for (int i = 0; i < 4; i++){
        adch->ch[i] = *(adch->addr); //read all channels
    }
}