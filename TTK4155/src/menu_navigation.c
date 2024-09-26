#include "menu_navigation.h"
#include "textbox.h"

menu_handle_t* active_menu;

void next_sub_menu(){
    active_menu->selected_sub_menu ++;
    active_menu->selected_sub_menu %= active_menu->num_sub_menus;
}

void previous_sub_menu(){
    active_menu->selected_sub_menu --;
    if(active_menu->selected_sub_menu < 0){
        active_menu->selected_sub_menu = active_menu->num_sub_menus;
    }
}

void next_menu(){
    active_menu = active_menu->sub_menus[active_menu->selected_sub_menu];
}

void previous_menu(){
    active_menu = active_menu->parent_menu;
}

void render_menu(textbox_handle_t* tbh){
    tbh->carriage_x = 0;
    tbh->carriage_y = 0;
    
    tbh->framebuffer.
}
