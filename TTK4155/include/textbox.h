#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <stdint.h>
#include "font.h"

typedef struct textbox_handle_t{
    char* framebuffer;
    uint8_t rows; // pixel_height / 8
    uint8_t pixel_width;
    uint8_t carriage_x;
    uint8_t carriage_y;
    uint8_t font_width;
    unsigned char** font;
    uint8_t inverted;
    uint8_t font_ascii_offset;
}textbox_handle_t;

void textbox_get_default(textbox_handle_t* tbh, char* framebuffer);
void textbox_put_char(textbox_handle_t* tbh, char c);
void textbox_newline(textbox_handle_t* tbh);
void textbox_printline(textbox_handle_t* tbh, char* string, uint8_t inverted);

#endif