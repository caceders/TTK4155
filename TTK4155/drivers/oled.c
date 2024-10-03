#include "oled.h"


void OLED_init(OLED_handle_t* oledh){
    *(oledh->cmd_addr) = OLED_SET_DISPLAY_OFF;
    *(oledh->cmd_addr) = OLED_SET_ENTIRE_DISPLAY_OFF;
    *(oledh->cmd_addr) = OLED_SET_SCAN_DIRECTION_REMAPPED;
    *(oledh->cmd_addr) = OLED_SET_SEGMENT_REMAPPED;
    OLED_set_addressing_mode(oledh, OLED_ADDRESSING_HORIZONTAL);
    OLED_clear(oledh);
    *(oledh->cmd_addr) = OLED_SET_DISPLAY_ON;
}

void OLED_clear(OLED_handle_t* oledh){
    for (uint16_t i = 0; i < oledh->columns*oledh->pages; i ++){
        *(oledh->data_addr) = 0;
    }
}



void OLED_write(OLED_handle_t* oledh, char* framebuffer){
    for (uint16_t i = 0; i < oledh->columns*oledh->pages; i ++){
        *(oledh->data_addr) = framebuffer[i];
    }
}

void OLED_set_addressing_mode(OLED_handle_t* oledh, OLED_addressing_mode mode){
    *(oledh->cmd_addr) = OLED_SET_ADDRESSING_MODE;
    *(oledh->cmd_addr) = mode;
}