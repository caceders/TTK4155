#ifndef OLED_H
#define OLED_H

#include <stdint.h>

typedef enum{
    OLED_SET_ADDRESSING_MODE = 0b00100000,
    OLED_SET_ENTIRE_DISPLAY_OFF = 0b10100100,
    OLED_SET_ENTIRE_DISPLAY_ON = 0b10100101,
    OLED_SET_DISPLAY_NORMAL = 0b10100110,
    OLED_SET_DISPLAY_INVERSE = 0b10100111,
    OLED_SET_DISPLAY_OFF = 0b10101110,
    OLED_SET_DISPLAY_ON = 0b10101111,
    OLED_SET_SCAN_DIRECTION_NORMAL = 0b11000000,
    OLED_SET_SCAN_DIRECTION_REMAPPED = 0b11001000,
    OLED_SET_SEGMENT_NORMAL = 0b10100000,
    OLED_SET_SEGMENT_REMAPPED = 0b10100001, 

}OLED_command;

typedef enum{
    OLED_ADDRESSING_HORIZONTAL = 0b00,
    OLED_ADDRESSING_VERTICAL = 0b01,
    OLED_ADDRESSING_PAGE = 0b10,
}OLED_addressing_mode;

typedef struct OLED_handle_t{
    uint8_t* cmd_addr;
    uint8_t* data_addr;
    uint8_t columns;
    uint8_t pages;
}OLED_handle_t;

void OLED_init(OLED_handle_t* oledh);
void OLED_write(OLED_handle_t* oledh, char* framebuffer);
void OLED_clear(OLED_handle_t* oledh);

void OLED_set_addressing_mode(OLED_handle_t* oledh, OLED_addressing_mode mode);



#endif