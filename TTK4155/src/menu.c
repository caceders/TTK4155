#include "menu.h"
#include "menu_navigation.h"
#include "game.h"

menu_handle_t main_menu, high_score_menu, settings_menu, credits_menu, play_game_menu, contrast_menu, brightness_menu, difficulty_menu;

void create_menu(menu_handle_t* menu, char* title){
    menu->title = title;
    menu->num_sub_menus = 0;
    menu->parent_menu = NULL;
    menu->selected_sub_menu = 0; 
}

void add_sub_menu(menu_handle_t* parent, menu_handle_t* child, char* child_name){
    create_menu(child, child_name);
    
    parent->sub_menus[parent->num_sub_menus] = child;
    parent->num_sub_menus ++;
    if(parent->num_sub_menus > 7){
        parent->num_sub_menus = 0;
    }
    child->parent_menu = parent;
}

void initialize_menu(){

    create_menu(&main_menu, "Main menu");
    add_sub_menu(&main_menu, &play_game_menu, "Play Game");
    play_game_menu.action = play_game;
    add_sub_menu(&main_menu, &high_score_menu, "View high score");
    add_sub_menu(&main_menu, &settings_menu, "Settings");
    add_sub_menu(&main_menu, &credits_menu, "Credits");

    // play_game_menu.action = play_game();
    // high_score_menu.action = view_high_score();
    // credits.action = view_credits);

    add_sub_menu(&settings_menu, &contrast_menu, "Contrast");
    add_sub_menu(&settings_menu, &brightness_menu, "Brightness");
    add_sub_menu(&settings_menu, &difficulty_menu, "Difficulty");

    set_active_menu(&main_menu);
}