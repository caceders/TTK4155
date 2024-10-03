#include "menu.h"
#include "menu_navigation.h"

menu_handle_t main_menu, sub_menu_1, sub_menu_2;


void initialize_menu(){
    main_menu.title = "Main menu";
    main_menu.selected_sub_menu = 0;
    main_menu.parent_menu = NULL;
    main_menu.sub_menus[0] = &sub_menu_1;
    main_menu.sub_menus[1] = &sub_menu_2;
    main_menu.num_sub_menus = 2;

    sub_menu_1.title = "Sub menu 1";
    sub_menu_1.selected_sub_menu = 0;
    sub_menu_1.parent_menu = &main_menu;
    sub_menu_1.sub_menus[0] = NULL;
    sub_menu_1.num_sub_menus = 0;

    sub_menu_2.title = "Sub menu 2";
    sub_menu_2.selected_sub_menu = 0;
    sub_menu_2.parent_menu = &main_menu;
    sub_menu_2.sub_menus[0] = NULL;
    sub_menu_2.num_sub_menus = 0;

    set_active_menu(&main_menu);
}