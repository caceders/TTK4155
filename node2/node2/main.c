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
#include "PID.h"
#include "pulse.h"

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

const uint32_t MAX_RANGE_MOTOR = 5644;

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

    configure_timer_for_pulse(100000);

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
    uint8_t prev_button_j = 0;

    int16_t motor_power = 0;
    motor_dir_t motor_direction;

    while (1){
        if(can_rx(&rx_msg)){
            if(rx_msg.id == 0xAA){
                state_playing = 1;
                printf("playing...\r\n");
                get_ir_flag(); //dummy read to clear flagtarget_position - current_position;
            }else if(rx_msg.id == 0x22){
                joy_x = rx_msg.byte[0] | (rx_msg.byte[1] << 8);
                joy_y = rx_msg.byte[2] | (rx_msg.byte[3] << 8);
                slider_l = rx_msg.byte[4];
                slider_r = rx_msg.byte[5];
                button_l = rx_msg.byte[6] & 1;
                button_r = (rx_msg.byte[6] >> 1) & 1;
                button_j = (rx_msg.byte[6] >> 2) & 1;

                if (button_j == 1 & prev_button_j == 0){
                    generate_pulse();
                }
                prev_button_j = button_j;

                // Calculate motor input

                int32_t current_position = encoder_read();
                int32_t target_position = ((slider_l)* MAX_RANGE_MOTOR)/255;
                int32_t PID_output = get_PID_output(current_position, target_position);
                motor_power = abs(PID_output/100);
                
                //motor_power = abs(slider_l - 128);
                
                if(PID_output > 0){
                //if(target_position - current_position > 0){
                    motor_direction = MOTOR_DIR_LEFT;
                }else{
                    motor_direction = MOTOR_DIR_RIGHT;
                }
                //printf("PID_output: %d\r\n", PID_output);
                //printf("motor power: %d\r\n", motor_power);
                //printf("motor direction: %d\r\n", motor_direction);
//
                //printf("target pos: %d\r\n", target_position);
                //printf("encoder: %d\r\n", encoder_read());
//
            }else{
                printf("Happy day caloo calay message of length %d was received, Yay!\r\n", rx_msg.length);
                printf("Id of sender: %x\r\n", rx_msg.id);
                for (int i = 0; i < rx_msg.length; i++){
                    printf("byte[%d] = %x\r\n", i, rx_msg.byte[i]);
                }
            }
        }

        if(state_playing){

            motor_update_direction(motor_direction);
            motor_update_power(motor_power);

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
