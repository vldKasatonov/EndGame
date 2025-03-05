#ifndef HEADER_H
#define HEADER_H

#include "raylib.h"
#include <stdio.h>
#include <float.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

Font mx_get_custom_font(void);
void mx_unload_custom_font(void);

#define MX_NUM_LEVELS 3
#define MX_INVENTORY_SIZE 7
#define MX_MAX_QUEUE 3
#define MX_MAX_LEVEL_GUESTS 6

// gamestate
typedef enum e_game_screen {
    MAIN_MENU = 0,
    SELECT_PLAYER,
    SETTINGS,
    GUIDE_PAGE1,
    GUIDE_PAGE2,
    GUIDE_PAGE3,
    LEVEL_MENU,
    LEVEL_MENU2,
    GAMEPLAY,
    GAMEPLAY_SETTINGS,
    DEVELOPERS
} t_game_screen;

typedef struct s_level_stars {
    int level_stars[MX_NUM_LEVELS];
} t_level_stars;

typedef struct s_game_config {
    double screen_width;
    double screen_height;
    double button_width;
    double button_height;
    double font_size_header1;
    double font_size_header2;
    double font_size_header3;
    double font_size_paragraph;
} t_game_config;

typedef struct s_custom_colors {
    Color button_background_color;
    Color menu_background_color;
    Color music_color;
    Color slider_color;
    Color red_color;
    Color level_rectangle_color;
    Color circle_color;
    Color circle_stroke_color;
    Color nonactive_star_color;
    Color active_star_color;
    Color none_color;
    Color nonactive_level_color;
    Color tonedreview_color;
} t_custom_colors;

typedef struct s_game_textures {
    Texture2D settings;
    Texture2D volume_on;
    Texture2D volume_on2;
    Texture2D music_on;
    Texture2D volume_off;
    Texture2D music_off;
    Texture2D arrow;
    Texture2D del_texture;
    Texture2D guide;
    Texture2D exit;
    Texture2D pause;
    Texture2D background;
    Texture2D play_button;
    Texture2D star;
    Texture2D one_player;
    Texture2D two_players;
    Texture2D chef;
    Texture2D right_arrow;
    Texture2D left_arrow;
    Texture2D map3;
    Texture2D image3;
    Texture2D level_preview;
    Texture2D served_icon;
    Texture2D guest;
    Texture2D reversed_guest;
    Texture2D dirty_apple;
    Texture2D washed_apple;
    Texture2D sliced_apple;
    Texture2D juice;
    Texture2D dirty_potato;
    Texture2D washed_potato;
    Texture2D sliced_potato;
    Texture2D peeled_potato;
    Texture2D fried_potato;
    Texture2D dirty_cucumber;
    Texture2D washed_cucumber;
    Texture2D sliced_cucumber;
    Texture2D dirty_tomato;
    Texture2D washed_tomato;
    Texture2D sliced_tomato;
    Texture2D salad;
    Texture2D guide_juice;
    Texture2D guide_potato;
    Texture2D guide_salad;
    Texture2D image1;
    Texture2D image2;
    Texture2D map1;
    Texture2D map2;
    Texture2D cloud;
    Texture2D f_button;
} t_game_textures;

void mx_load_textures(t_game_textures *textures);
void mx_unload_textures(t_game_textures *textures);

// gameplay
typedef struct s_player {
    Vector2 position;
} t_player;

typedef struct s_player_config {
    float speed;
    float player_width;
    float player_height;
} t_player_config;

typedef struct {
    int x;
    int y;
} t_position;

typedef struct s_queue_config {
    int register_x;
    int register_y;
    t_position spots[MX_MAX_QUEUE];
} t_queue_config;

typedef struct s_hotbar_config {
    int cell_width;
    int cell_height;
    int margin;
    Color cell_color;
    Color cell_border_color;
    Color cell_border_color_active;
} t_hotbar_config;

typedef enum {
    NONE,
    POTATO_BED,
    TOMATO_BED,
    CUCUMBER_BED,
    APPLE_TREE,
    WASHBASIN,
    PEELING_TABLE,
    SLICING_TABLE,
    GARBAGE_CAN,
    STOVE,
    JUICEMAKER,
    PICK_UP,
    CASHBOX,
    PLATE
} t_interactable_type;

typedef struct {
    Rectangle rect;
    Color color;
    t_interactable_type type;
} t_surface;

typedef enum {
    DIRTY,
    CLEAN,
    PEELED,
    JUICED,
    FRIED,
    SLICED,
    MIXED
} t_ingredient_state;

typedef enum {
    APPLE,
    POTATO,
    CUCUMBER,
    TOMATO,
    SALAD
} t_ingredient;

typedef struct {
    t_ingredient_state state;
    t_ingredient type;
} t_item;

typedef struct {
    t_item* items[MX_INVENTORY_SIZE];
    int active_item;
} t_inventory;

typedef struct s_level_data {
    int guest_count;
    t_item level_menu[MX_MAX_LEVEL_GUESTS];
    t_surface surfaces[34];
    int surface_count;
} t_level_data;

typedef struct {
    int id;
    int arrival_time;
    t_item* order;
    int x;
    int y;
    int target_x;
    int target_y;
} t_guest;

typedef struct {
    t_guest* queue[MX_MAX_QUEUE];
    int queue_size;
    t_guest* at_register;
    t_guest* out_of_queue;
} t_queue;

typedef struct {
    t_guest* all_guests;
    int next_guest_index;
    int guest_count;
} t_level;

void mx_initialize_queue(t_queue*);
bool mx_has_queue_space(t_queue*);
bool mx_accept_order(t_queue*);
void mx_serve_guest_at_index(t_queue*, int);
void mx_initialize_level(t_level_data*, t_level*);
void mx_load_level(t_level_data*, t_level*);
void mx_clear_level(t_level*);
void mx_try_add_guest_to_register(t_level*, t_queue*, int);
void mx_initialize_surfaces(t_level_data*);
void mx_initialize_inventory(t_inventory*);
int mx_find_free_cell(t_inventory*);
int mx_add_item(t_inventory*, t_item*);
t_item* mx_remove_active_item(t_inventory*);
void mx_clear_inventory(t_inventory*);
void mx_set_active_item(t_inventory*, int);
void mx_reload_inventory(t_inventory*);
extern t_level_data level_data[];

bool mx_can_fry(t_item*);
bool mx_can_wash(t_item*);
bool mx_can_peel(t_item*);
bool mx_can_juice(t_item*);
bool mx_can_slice(t_item*);
bool mx_can_serve(t_item*);
bool mx_can_throw_away(t_item* item);

t_item* mx_get_dirty_item(t_ingredient);
void mx_update_item(t_item*, t_ingredient_state);
void mx_delete_item(t_item**);
t_item* mx_get_salad(void);

// game render
void mx_render_timer(void);
void mx_render_level_menu(t_game_textures*, t_level_stars*, t_player*);
void mx_render_level_menu2(t_game_textures*);
void mx_render_developers(t_game_textures*);
void mx_draw_stars(int, int, t_game_textures*, Vector2);
void mx_draw_text_score(int, Rectangle, Vector2, char*, char*);
void mx_draw_level(int, int, t_game_textures*, Texture2D, Vector2);
void mx_toned_rect(int);
Rectangle mx_draw_back_button(t_game_textures*);
Rectangle mx_draw_settings_icon(t_game_textures*);
void mx_draw_arrow(Texture2D, Rectangle);
void mx_render_main_menu(t_game_textures*, bool*);
void mx_render_gameplay_settings(t_game_textures*, float*, float*, bool*, int*);
void mx_render_guide_page1(t_game_textures *textures);
void mx_render_guide_page2(t_game_textures *textures);
void mx_render_guide_page3(t_game_textures *textures);
void mx_render_select_player(t_game_textures*);
void mx_render_settings(t_game_textures*, float*, float*, t_level_stars*, bool*);
void mx_render_hotbar(t_game_textures*);
void mx_render_queue(Rectangle, bool*, int*, t_game_textures*);
void mx_render_gameplay(t_player*, t_game_textures*, bool*, int*, int);
void mx_draw_stars_gameplay(int, double, t_game_textures*, Vector2);
void mx_disable_gameplay_input(bool);
void mx_draw_level_sucsses(bool*, t_game_textures*, int*, bool*);
void mx_update_level_stars(t_level_stars*, int, int);
int mx_calculate_stars_for_level(void);
void mx_interact_with_guest(t_inventory*, t_queue*, int, t_interactable_type);
int mx_get_nearby_interactable(Rectangle, t_surface*, int);
void mx_interact_with_object(t_inventory*, t_interactable_type);
void mx_init_game_audio(void);
void mx_updat_game_audio(void);
void mx_unload_game_audio(void);
void mx_set_music_volume_level(float);
void mx_update_menu_music(void);
void mx_update_gameplay_music(void);
void mx_update_music_volume(float);
void mx_init_sound_effects(void);
void mx_unload_sound_effects(void);
void mx_play_sound_effect(Sound);
void mx_set_effects_volume(float);
void mx_start_game_timer(void);
void mx_pause_game_timer(void);
void mx_resume_game_timer(void);
void mx_reset_game_timer(void);
double mx_get_elapsed_time(void);
void mx_load_best_time(void);
void mx_save_best_time(void);
double mx_get_best_time(void);

void check_collision(Vector2, bool*, Rectangle, t_game_screen);

extern t_game_screen current_state;
extern t_game_screen previous_state;
extern t_game_screen previous_guide_state;
extern t_inventory hotbar;
extern t_queue queue;
extern t_level level;
extern t_surface surfaces[];
extern int surface_count;
extern t_game_config game_config;
extern t_custom_colors custom_colors;
extern t_queue_config queue_config;
extern t_hotbar_config hotbar_config;
extern t_player_config player_config;
extern int level_number;
extern Sound button_click;
extern Sound item_pickup;
extern Sound complete_order;
extern Sound cutting;
extern Sound frying;
extern Sound leaves;
extern Sound peeling;
extern Sound washing;
extern Sound wrong_order;
extern Sound pouring;
extern Sound level_complete;

#endif
