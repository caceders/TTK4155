/*
 * node2.c
 *
 * Created: 10.10.2024 11:30:08
 * Author : Simen
 */ 


#include <stdarg.h>
#include <stdio.h>
#include "sam.h"
#include "uart.h"

/*
 * Remember to update the Makefile with the (relative) path to the uart.c file.
 * This starter code will not compile until the UART file has been included in the Makefile. 
 * If you get somewhat cryptic errors referencing functions such as _sbrk, 
 * _close_r, _write_r, _fstat etc, you have most likely not done that correctly.

 * If you get errors such as "arm-none-eabi-gcc: no such file", you may need to reinstall the arm gcc packages using
 * apt or your favorite package manager.
 */

#define F_CPU 84000000

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    // Set bit timing, want Bitrate = 125kbit/sec, BRP = 20, syncseg = 1, propseg = 5, phaseseg1 = 6, phasseg2 = 4, sjw = 1

    uart_init(F_CPU, 9600);

    printf("Hello world!");

    /* Replace with your application code */
    while (1);
}
