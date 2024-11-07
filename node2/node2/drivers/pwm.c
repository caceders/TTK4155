#include "pwm.h"
#include "sam.h"
#include <stdio.h>


void pwm_init(){

    //set up clock source A
    PWM->PWM_CLK |= 0b0011 << 8; //select prescaler 8
    
    PWM->PWM_CLK |= 105; //select divider 105

    PWM->PWM_CH_NUM[1].PWM_CMR = 0b1011; //select clock source A
    PWM->PWM_CH_NUM[1].PWM_CMR |= 1 << 9; //invert polarity

    PWM->PWM_CH_NUM[1].PWM_CPRD  = 2000; //period

    PWM->PWM_CH_NUM[1].PWM_CDTY  = 150; // we start with the servo in the middle

    


    //set PB13 (servo signal) to alternate function
    PIOB->PIO_ABSR |= PIO_PB13; // Set PB13 as peripheral type B
    PIOB->PIO_PDR |= PIO_PB13;

    //PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_CMD | (ID_PWM << PMC_PCR_PID_Pos); 
    PMC->PMC_PCER1 |= 1 << (ID_PWM - 32); //enable pwm peripheral clock

    PWM->PWM_ENA |= 1 << 1;

    //Motor:

    PIOB->PIO_ABSR |= PIO_PB12;
    PIOB->PIO_PDR |= PIO_PB12;

    PWM->PWM_CH_NUM[0].PWM_CMR = PWM_CMR_CPRE_MCK;
    PWM->PWM_CH_NUM[0].PWM_CMR |= 1 << 9; //invert polarity

    PWM->PWM_CH_NUM[0].PWM_CPRD  = 4095; //period
    PWM->PWM_CH_NUM[0].PWM_CDTY  = 0; // we start with the motor off

    PWM->PWM_ENA |= 1;

    

    //set dir pin PC23
    PIOC->PIO_PER = PIO_PC23;
    PIOC->PIO_OER = PIO_PC23;
}

void motor_update_power(uint32_t val){
    PWM->PWM_CH_NUM[0].PWM_CDTYUPD  = val;
}

void motor_update_direction(motor_dir_t dir){
    if(dir == MOTOR_DIR_RIGHT){
        PIOC->PIO_SODR = PIO_PC23;
    }else if (dir == MOTOR_DIR_LEFT){
        PIOC->PIO_CODR = PIO_PC23;
    }
}

void servo_update_angle(uint8_t degrees){
    uint16_t duty = degrees*120/180 + 90;
    if (duty < 90) duty = 90;
    else if (duty > 210) duty = 210;
    PWM->PWM_CH_NUM[1].PWM_CDTYUPD  = duty;
}