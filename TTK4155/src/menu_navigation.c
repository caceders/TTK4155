#include "menu_navigation.h"
#include "textbox.h"
#include <stdio.h>

menu_handle_t* active_menu;

void set_active_menu(menu_handle_t* menu){
    active_menu = menu;
}

void next_sub_menu(){
    if(active_menu->num_sub_menus != 0){
        active_menu->selected_sub_menu ++;
        active_menu->selected_sub_menu %= active_menu->num_sub_menus;
    }
}

void previous_sub_menu(){
    if(active_menu->selected_sub_menu == 0){
        active_menu->selected_sub_menu = active_menu->num_sub_menus - 1;
    }else{
        active_menu->selected_sub_menu --;
    }
}

void next_menu(){
    if(active_menu->num_sub_menus == 0){
        return;
    }else if (active_menu->sub_menus[active_menu->selected_sub_menu]->action != NULL){
        active_menu->sub_menus[active_menu->selected_sub_menu]->action();
        printf("action complete\r\n");
    }else{
        set_active_menu(active_menu->sub_menus[active_menu->selected_sub_menu]);
    }
}

void previous_menu(){
    if (active_menu->parent_menu != NULL){
        set_active_menu(active_menu->parent_menu);
    }
}

void render_menu(textbox_handle_t* tbh){
    textbox_clear(tbh);
    tbh->carriage_x = 0;
    tbh->carriage_y = 0;
    
    tbh->inverted = 1;
    textbox_println(tbh, active_menu->title);

    tbh->inverted = 0;
    for (int i = 0; i < active_menu->num_sub_menus; i++){
        if(i == active_menu->selected_sub_menu){
            textbox_print(tbh, "* ");
        }else{
            textbox_print(tbh, "  ");
        }
        textbox_println(tbh, active_menu->sub_menus[i]->title);
    }
}
