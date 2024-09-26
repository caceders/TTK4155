#include "textbox.h"


void textbox_get_default(textbox_handle_t* tbh, char* framebuffer){
    tbh->framebuffer = framebuffer;
    tbh->rows = 8;
    tbh->pixel_width = 128;
    tbh->carriage_x = 0;
    tbh->carriage_y = 0;
    tbh->font_width = 5;
    tbh->font = font5;
    tbh->font_ascii_offset = 32;
}

void textbox_put_char(textbox_handle_t* tbh, char c){
    if(tbh->carriage_x + tbh->font_width > tbh->pixel_width){
        textbox_newline(tbh);
    }
    if(c == '\n'){
        tbh->carriage_y ++;
        tbh->carriage_y %= tbh->rows;
    }else if (c == '\r'){
        tbh->carriage_x = 0;
    }else if(c >= tbh->font_ascii_offset){
        for (uint8_t i = 0; i < tbh->font_width; i++ ){
            tbh->framebuffer[tbh->carriage_x + tbh->carriage_y*tbh->pixel_width] = pgm_read_byte(&(font5[c - tbh->font_ascii_offset][i]));
            tbh->carriage_x++;
        }
        tbh->carriage_x++;
        
        /*
        tbh->framebuffer[tbh->carriage_x + 0] = pgm_read_byte( &(font5[c - 32][0]) );
        tbh->framebuffer[tbh->carriage_x + 1] = pgm_read_byte( &(font5[c - 32][1]) );
        tbh->framebuffer[tbh->carriage_x + 2] = pgm_read_byte( &(font5[c - 32][2]) );
        tbh->framebuffer[tbh->carriage_x + 3] = pgm_read_byte( &(font5[c - 32][3]) );
        tbh->framebuffer[tbh->carriage_x + 4] = pgm_read_byte( &(font5[c - 32][4]) );
        tbh->carriage_x += tbh->font_width + 1;
        */
    }
}

void textbox_newline(textbox_handle_t* tbh){
    tbh->carriage_y ++;
    tbh->carriage_y %= tbh->rows;
    tbh->carriage_x = 0;
}
