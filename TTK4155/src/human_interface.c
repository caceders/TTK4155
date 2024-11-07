#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "adc.h"
#include <util/delay.h>
#include "human_interface.h"


typedef struct human_interface_handle{
    ADC_handle_t adc;

    uint8_t joy_calibration[2];

    position joy_position;
    direction joy_direction;

    uint8_t deadzone_size;

    uint8_t slider_l;
    uint8_t slider_r;

    unsigned char joy_button;
    unsigned char right_button;
	unsigned char left_button;

}human_interface_handle;

human_interface_handle HI;

void init_human_interface(){
    //setup ADC
	HI.adc.addr = (uint8_t*)0x1400;
	HI.adc.mode = ADC_MODE_HARDWIRED;
	HI.adc.sample_time_us = (2*4*9)/(F_CPU/1000000) + 2; //according to datasheet + margin

    //enable pullup on joystick button
	PORTB |= (1 << PIN1);

    //Hardcoded deadzone
    HI.deadzone_size = 50;
}

void calibrate_joy_position(){
    ADC_read(&HI.adc);
    HI.joy_calibration[0] = HI.adc.ch[2];
    HI.joy_calibration[1] = HI.adc.ch[3];
}

position get_joy_position(){
    return HI.joy_position;
}

uint8_t get_slider_l(){
    return HI.slider_l;
}

uint8_t get_slider_r(){
    return HI.slider_r;
}



direction get_joy_direction(){
    return HI.joy_direction;
};

void read_human_interface(){
    //Read joystick
    ADC_read(&HI.adc);
    HI.joy_position.x_pos = HI.adc.ch[2] - HI.joy_calibration[0];
    HI.joy_position.y_pos = HI.adc.ch[3] - HI.joy_calibration[1];
    HI.slider_l = HI.adc.ch[0];
    HI.slider_r = HI.adc.ch[1];
    
    int16_t x = HI.joy_position.x_pos;
    int16_t y = HI.joy_position.y_pos;
    uint8_t abs_x = abs(HI.joy_position.x_pos);
    uint8_t abs_y = abs(HI.joy_position.y_pos);

    if(abs_x < HI.deadzone_size && abs_y < HI.deadzone_size){
        HI.joy_direction = NEUTRAL;
    }
    else if (x >= abs_y){
        HI.joy_direction = RIGHT;
    }
    else if (-x >= abs_y){
        HI.joy_direction = LEFT;
    }
    else if (y >= abs_x){
        HI.joy_direction = UP;
    }
    else if (-y >= abs_x){
        HI.joy_direction = DOWN;
    }else{
        HI.joy_direction = UNDEFINED;
    }

    HI.joy_button  = ~(PINB >> PIN1) & 1;
    HI.right_button = (PINB >> PIN2) & 1;
	HI.left_button = (PINB >> PIN3) & 1;
};

uint8_t get_r(){
    return HI.right_button;
}
uint8_t get_l(){
    return HI.left_button;
}
uint8_t get_j(){
    return HI.joy_button;
}