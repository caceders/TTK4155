/*
 * node2.c
 *
 * Created: 10.10.2024 11:30:08
 * Author : Simen
 */ 


//#include <stdarg.h>
#include <stdio.h>
#include "sam.h"
#include "uart.h"
#include "can.h"

/*
 * Remember to update the Makefile with the (relative) path to the uart.c file.
 * This starter code will not compile until the UART file has been included in the Makefile. 
 * If you get somewhat cryptic errors referencing functions such as _sbrk, 
 * _close_r, _write_r, _fstat etc, you have most likely not done that correctly.

 * If you get errors such as "arm-none-eabi-gcc: no such file", you may need to reinstall the arm gcc packages using
 * apt or your favorite package manager.
 */

#define F_CPU 84000000
#define _XTAL_FREQ 84000000
#define CAN_BAUD 125000

typedef enum{
    NEUTRAL = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UNDEFINED

}direction;

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer
    uart_init(F_CPU, 9600);
    // Set bit timing, want Bitrate = 125kbit/sec, BRP = 20, syncseg = 1, propseg = 5, phaseseg1 = 6, phasseg2 = 4, sjw = 1
    printf("Hello world\r\n");
    
    CanInit caninit = {
        .phase1 = 5,
        .phase2 = 3,
        .propag = 4,
        .sjw = 0,
        .brp = 41,
        .smp = 0
    };
    //BRP = (F_CPU/BAUD)/(how many time quanta in one bit time) - 1
    can_init(caninit, 0);

    

    printf("Hello world!\r\n");

    CanMsg msg;
    msg.length = 1;
    msg.id = 0x123;
    msg.byte[0] = 0b01010101;
    while (1){
        if(can_rx(&msg)){
            if (msg.id = 0x11){
                printf("joystick position:");
                switch((direction) msg.byte[0]){
                    case NEUTRAL:
                        printf("NEUTRAL\r\n");
                        break;
                    case UP:
                        printf("UP\r\n");
                        break;
                    case DOWN:
                        printf("DOWN\r\n");
                        break;
                    case LEFT:
                        printf("LEFT\r\n");
                        break;
                    case RIGHT:
                        printf("RIGHT\r\n");
                        break;
                    default:
                        printf("Unknown??\r\n");
                        break;
                }
            }else{
                printf("Happy day caloo calay message of length %d was received, Yay!\r\n", msg.length);
                printf("Id of sender: %x\r\n", msg.id);
                for (int i = 0; i < msg.length; i++){
                    printf("byte[%d] = %x\r\n", i, msg.byte[i]);
                }
            }
        }

    }
}
