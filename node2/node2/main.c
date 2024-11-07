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
#include "pwm.h"
#include "ir.h"
#include "encoder.h"

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

    pwm_init();
    //while(1);

    ir_init();

    encoder_init();

    

    printf("Hello world!\r\n");

    CanMsg rx_msg;

    uint8_t state_playing = 0;

    int16_t joy_x = 0;
    int16_t joy_y = 0;
    uint8_t slider_l = 0;
    uint8_t slider_r = 0;
    uint8_t button_r = 0;
    uint8_t button_l = 0;
    uint8_t button_j = 0;

    while (1){
        if(can_rx(&rx_msg)){
            if(rx_msg.id == 0xAA){
                state_playing = 1;
                printf("playing...\r\n");
                get_ir_flag(); //dummy read to clear flag;
            }else if(rx_msg.id == 0x22){
                joy_x = rx_msg.byte[0] | (rx_msg.byte[1] << 8);
                joy_y = rx_msg.byte[2] | (rx_msg.byte[3] << 8);
                slider_l = rx_msg.byte[4];
                slider_r = rx_msg.byte[5];
                button_l = rx_msg.byte[6] & 1;
                button_r = rx_msg.byte[6] & (1<<1);
                button_j = rx_msg.byte[6] & (1<<2);

                printf("encoder: %d\r\n", encoder_read());

            }else{
                printf("Happy day caloo calay message of length %d was received, Yay!\r\n", rx_msg.length);
                printf("Id of sender: %x\r\n", rx_msg.id);
                for (int i = 0; i < rx_msg.length; i++){
                    printf("byte[%d] = %x\r\n", i, rx_msg.byte[i]);
                }
            }
        }

        if(state_playing){
            int32_t slider_l_int = slider_l - 128;
            if(slider_l_int > 0){
                motor_update_direction(MOTOR_DIR_RIGHT);
            }else{
                motor_update_direction(MOTOR_DIR_LEFT);
            }


            motor_update_power(abs(slider_l_int));

            servo_update_angle(slider_r*180/256);
            //motor
            if(get_ir_flag()){
                printf("game over :(\r\n");
                state_playing = 0;
                CanMsg tx_msg;
                tx_msg.id = 0x01;
                can_tx(tx_msg);
                servo_update_angle(90); //neutral position
                motor_update_power(0);

            }
        }

    }
    
   
}
