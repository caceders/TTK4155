#include "sam.h"

void configure_timer_for_pulse(uint32_t pulse_width_us){
    PIOB->PIO_ABSR |= PIO_PB25;
    PIOB->PIO_PDR = PIO_PB25;

    // Enable peripheral clock for TC0
    PMC->PMC_PCER0 |= (1 << ID_TC0);

    // Configure TC0 cahnnel 0 for waveform mode
    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1
                                | TC_CMR_WAVE
                                | TC_CMR_WAVSEL_UP_RC
                                | TC_CMR_ACPA_CLEAR
                                | TC_CMR_ACPC_SET
                                | TC_CMR_CPCDIS;
    
    // Calculate the values for RA and RC
    uint32_t timer_clock_frequency = SystemCoreClock / 2;
    uint32_t ticks = (pulse_width_us * (timer_clock_frequency / 1000000));

    TC0 -> TC_CHANNEL[0].TC_RC = ticks;
    TC0 -> TC_CHANNEL[0].TC_RA = ticks / 2;

}

void generate_pulse(){
    TC0 -> TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
}