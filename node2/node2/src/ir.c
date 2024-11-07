#include "ir.h"
#include "sam.h"
#include <stdint.h>

uint8_t ir_flag = 0;

void ir_init(){
    // IR PIN: PC22
    // Set IR pin as Input
    PIOC->PIO_PER |= PIO_PC22;

    //enable debouncing filter
    PIOC->PIO_DIFSR |= PIO_PC22;
    PIOC->PIO_SCDR = 1024;
    PIOC->PIO_IFER |= PIO_PC22;

    
    //PIO_ESR
    PIOC->PIO_ESR |= PIO_PC22;
    //PIO_REHLSR
    PIOC->PIO_REHLSR |= PIO_PC22;

    PMC->PMC_PCER0 |= 1 << (ID_PIOC); //enable pwm peripheral clock

    //PIO_IER
    PIOC->PIO_IER |= PIO_PC22;

    NVIC_EnableIRQ(PIOC_IRQn);

}

void PIOC_Handler(void){
    if (PIOC->PIO_ISR & PIO_PC22 && PIOC->PIO_PDSR & PIO_PC22){
        ir_flag = 1;
    }

}

uint8_t get_ir_flag(){
    uint8_t return_value = ir_flag;
    ir_flag = 0;
    return return_value;

}