#include "textbox.h"
#include "string.h"


void pad_line(textbox_handle_t* tbh);


void textbox_get_default(textbox_handle_t* tbh, char* framebuffer){
    tbh->framebuffer = framebuffer;
    tbh->rows = 8;
    tbh->pixel_width = 128;
    tbh->carriage_x = 0;
    tbh->carriage_y = 0;
    tbh->font_width = 5;
    tbh->font = font5;
    tbh->inverted = 0;
    tbh->font_ascii_offset = 32;
}

void textbox_put_char(textbox_handle_t* tbh, char c){
    if(c == '\n'){
        pad_line(tbh);
        tbh->carriage_y ++;
        tbh->carriage_y %= tbh->rows;
    }else if (c == '\r'){
        tbh->carriage_x = 0;
    }else if(c >= tbh->font_ascii_offset){
        if(tbh->carriage_x + tbh->font_width > tbh->pixel_width){
            textbox_newline(tbh);
        }
        for (uint8_t i = 0; i < tbh->font_width; i++ ){
            if (tbh->inverted){
                tbh->framebuffer[tbh->carriage_x + tbh->carriage_y*tbh->pixel_width] = ~pgm_read_byte(&(font5[c - tbh->font_ascii_offset][i]));
            }else{
                tbh->framebuffer[tbh->carriage_x + tbh->carriage_y*tbh->pixel_width] = pgm_read_byte(&(font5[c - tbh->font_ascii_offset][i]));
            }
            tbh->carriage_x++;
        }
        if (tbh->inverted){
            tbh->framebuffer[tbh->carriage_x + tbh->carriage_y*tbh->pixel_width] = 0xFF;
        }else{
            tbh->framebuffer[tbh->carriage_x + tbh->carriage_y*tbh->pixel_width] = 0x00;
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

void pad_line(textbox_handle_t* tbh){
    for(int i = tbh->carriage_x; i < tbh->pixel_width; i++){
        if (tbh->inverted){
            tbh->framebuffer[i + tbh->carriage_y*tbh->pixel_width] = 0xFF;
        }else{
            tbh->framebuffer[i + tbh->carriage_y*tbh->pixel_width] = 0x00;
        }
    }
}

void textbox_newline(textbox_handle_t* tbh){
    pad_line(tbh);
    tbh->carriage_y ++;
    tbh->carriage_y %= tbh->rows;
    tbh->carriage_x = 0;
}

void textbox_print(textbox_handle_t* tbh, char* string){
    uint8_t len = strlen(string);
    for(uint8_t i = 0; i < len; i++){
        textbox_put_char(tbh, string[i]);
        if(tbh->carriage_x + tbh->font_width > tbh->pixel_width){
            break;
        }
    }
}

void textbox_println(textbox_handle_t* tbh, char* string){
    textbox_print(tbh, string);
    textbox_newline(tbh);
}
