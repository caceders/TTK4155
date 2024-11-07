#include "encoder.h"
#include "sam.h"


void encoder_init(){
    PIOC->PIO_ABSR |= PIO_PC25 | PIO_PC26;
    PIOC->PIO_PDR = PIO_PC25 | PIO_PC26;

    PMC->PMC_PCER1 |= 1 << (ID_TC6- 32); //enable pwm peripheral clock
    //PMC->PMC_PCER1 |= 1 << (ID_TC7- 32); //enable pwm peripheral clock
    //PMC->PMC_PCER1 |= 1 << (ID_TC8- 32); //enable pwm peripheral clock
    
    TC2->TC_BMR = TC_BMR_QDEN | TC_BMR_POSEN | TC_BMR_EDGPHA; 
    TC2->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_XC0 | TC_CMR_ETRGEDG_RISING | TC_CMR_ABETRG;
    TC2->TC_CHANNEL[0].TC_CCR |= TC_CCR_CLKEN;
    TC2->TC_BCR = TC_BCR_SYNC;

}

uint32_t encoder_read(){
    return TC2->TC_CHANNEL[0].TC_CV;
}