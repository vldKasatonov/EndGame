#include "../inc/header.h"

t_game_screen current_state = MAIN_MENU;
t_game_screen previous_state = MAIN_MENU;
t_game_screen previous_guide_state = SETTINGS;

t_inventory hotbar;
t_queue queue;
t_level level;
int surface_count;
t_surface surfaces[34];

