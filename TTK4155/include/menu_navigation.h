#ifndef MENU_NAVIGATION_H_
#define MENU_NAVIGATION_H_

#include <stdint.h>

typedef struct menu_handle_t{

    char* title;
    uint8_t selected_sub_menu;
    uint8_t num_sub_menus;
    struct menu_handle_t* parent_menu;
    struct menu_handle_t* sub_menus[8];
    void (*action)();

}menu_handle_t;

void next_sub_menu();

void previous_sub_menu();

void next_menu();

void previous_menu();

void render_menu();

#endif