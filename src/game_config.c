#include "../inc/header.h"

//t_game_config game_config = {
//	1600, // screen_width
//	900, // screen_height
//	300, // button_width
//	60,  // button_height
//	80,  // font_size_header1
//	35,  // font_size_header2
//	25,	 // font_size_header3
//	20,  // font_size_paragraph
//};

t_custom_colors custom_colors = {
    { 241, 129, 59, 255 }, // button_background_color
    { 242, 155, 101, 100 }, // menu_background_color
    { 232, 110, 35, 255 }, // music_color
    { 186, 77, 9, 255 }, // slider_color
    { 255, 0, 0, 255 }, // red_color
    { 207, 99, 32, 255 }, // level rectangle
    { 217, 105, 35, 255 }, // circle
    { 135, 65, 21, 255 }, // circle stroke
    { 65, 65, 65, 255 }, // nonactive star 
    { 255, 217, 0, 255 }, // active star
    { 0, 0, 0, 0 }, // none
    { 0, 0, 0, 100}, // nonactive level
    { 0, 0, 0, 40}, // toned level preview
};

int level_number = 0;
