#ifndef ADC_H
#define ADC_H

#include <stdint.h>

typedef enum{
    ADC_MODE_HARDWIRED = 0,
    ADC_MODE_INOUT = 1
}ADC_mode;

typedef struct ADC_handle_t{
    uint8_t* addr;
    uint8_t config;
    ADC_mode mode;
    uint8_t ch[4];
    uint16_t sample_time_us;
}ADC_handle_t;

void ADC_read(ADC_handle_t* adch);


#endif