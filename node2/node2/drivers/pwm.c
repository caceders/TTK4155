#include "pwm.h"
#include "sam.h"
#include <stdio.h>


void pwm_init(){
    const int WP_KEY = 0x50574D;
    PWM->PWM_WPCR |= WP_KEY << 8;
    PWM->PWM_WPCR |= 0b11111100; //disable write protect on all register groups;

    //set up clock source A
    PWM->PWM_CLK |= 0b0011 << 8; //select prescaler 8
    
    PWM->PWM_CLK |= 105; //select divider 105

    PWM->PWM_CH_NUM[1].PWM_CMR = 0b1011; //select clock source A
    PWM->PWM_CH_NUM[1].PWM_CMR |= 1 << 9; //select clock source A

    PWM->PWM_CH_NUM[1].PWM_CPRD  = 2000; //period

    PWM->PWM_CH_NUM[1].PWM_CDTY  = 150; // we start with the servo in the middle


    PWM->PWM_ENA |= 1 << 1;


    //set PB13 (servo signal) to alternate function
    PIOB->PIO_ABSR |= PIO_PB13; // Set PB13 as peripheral type B
    PIOB->PIO_PDR |= PIO_PB13;

    //PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_CMD | (ID_PWM << PMC_PCR_PID_Pos); 
    PMC->PMC_PCER1 |= 1 << (ID_PWM - 32); //enable pwm peripheral clock

}

void servo_update_angle(uint8_t degrees){
    uint16_t duty = degrees*120/180 + 90;
    if (duty < 90) duty = 90;
    else if (duty > 210) duty = 210;
    PWM->PWM_CH_NUM[1].PWM_CDTYUPD  = duty;
}