#include "../inc/header.h"

extern int currentLevel;

static void reset_player_data(t_player* playerData) {
    Vector2 pos = { 300, 350 };
    playerData->position = pos;
}

void mx_render_level_menu(t_game_textures* textures, t_level_stars* game_state, t_player* player) {
    int space = 450;
    Vector2 circle = { 350, 475 };
    int radius = 50;
    Rectangle main_rec = { 150, 250, 400, 450 };

    double best_times[3];
    for (int i = 0; i < 3; i++) {
        currentLevel = i;
        mx_load_best_time();
        best_times[i] = mx_get_best_time();
    }
    char best_time_text[3][11];
    for (int i = 0; i < 3; i++) {
        if (best_times[i] <= 0) {
            snprintf(best_time_text[i], sizeof(best_time_text[i]), " - - : - -");
        }
        else {
            int best_min = (int)best_times[i] / 60;
            int best_sec = (int)best_times[i] % 60;
            snprintf(best_time_text[i], sizeof(best_time_text[i]), "%02d:%02d", best_min, best_sec);
            int stars_earned = mx_calculate_stars_for_level();
            mx_update_level_stars(game_state, i, stars_earned);
        }
    }
    int level_1_stars = game_state->level_stars[0];
    int level_2_stars = game_state->level_stars[1];
    int level_3_stars = game_state->level_stars[2];

    mx_draw_level(0, level_1_stars, textures, textures->image1, circle);
    mx_draw_level(space, level_2_stars, textures, textures->image2, circle);
    mx_draw_level(space * 2, level_3_stars, textures, textures->image3, circle);

    mx_draw_text_score(0, main_rec, circle, "LEVEL 1", best_time_text[0]);
    mx_draw_text_score(space, main_rec, circle, "LEVEL 2", best_time_text[1]);
    mx_draw_text_score(space * 2, main_rec, circle, "LEVEL 3", best_time_text[2]);

    Rectangle gear_rect = mx_draw_settings_icon(textures);
    Rectangle back_button = mx_draw_back_button(textures);
    Rectangle right_arrow_rec = { 1495, circle.y - 30, 60, 60 };
    mx_draw_arrow(textures->right_arrow, right_arrow_rec);
    
    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;

    if (CheckCollisionPointRec(mouse, gear_rect)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            previous_state = current_state;
            current_state = SETTINGS;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }  
    if (CheckCollisionPointRec(mouse, back_button)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = SELECT_PLAYER;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointRec(mouse, right_arrow_rec)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = LEVEL_MENU2;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointCircle(mouse, circle, radius)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            
            currentLevel = 0;
            mx_load_best_time();
            mx_start_game_timer();
            current_state = GAMEPLAY;

            reset_player_data(player);
            mx_initialize_surfaces(&level_data[0]);
            mx_initialize_inventory(&hotbar);            //
            mx_initialize_queue(&queue);                 // gameplay initializers
            mx_initialize_level(&level_data[0], &level);  //
            level_number = 1;

            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointCircle(mouse, (Vector2){ circle.x + space, circle.y }, radius)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            
            currentLevel = 1;
            mx_load_best_time();
            mx_start_game_timer();
            current_state = GAMEPLAY;

            reset_player_data(player);
            mx_initialize_surfaces(&level_data[1]);
            mx_initialize_inventory(&hotbar);            //
            mx_initialize_queue(&queue);                 // gameplay initializers
            mx_initialize_level(&level_data[1], &level);  //
            level_number = 2;

            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointCircle(mouse, (Vector2) { circle.x + space * 2, circle.y }, radius)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            
            currentLevel = 2;
            mx_load_best_time();
            mx_start_game_timer();
            current_state = GAMEPLAY;

            reset_player_data(player);
            mx_initialize_surfaces(&level_data[2]);
            mx_initialize_inventory(&hotbar);            //
            mx_initialize_queue(&queue);                 // gameplay initializers
            mx_initialize_level(&level_data[2], &level);  //
            level_number = 3;

            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

}

void mx_render_level_menu2(t_game_textures *textures) {
    int space = 450;
    Vector2 circle = { 350, 475 };
    Rectangle main_rec = { 150, 250, 400, 450 };

    mx_draw_level(0, 0, textures, textures->level_preview, circle);
    mx_draw_level(space, 0, textures,textures->level_preview, circle);
    mx_draw_level(space * 2, 0, textures, textures->level_preview, circle);

    mx_draw_text_score(0, main_rec, circle, "LEVEL 4", " - - : - -");
    mx_draw_text_score(space, main_rec, circle, "LEVEL 5", " - - : - -");
    mx_draw_text_score(space * 2, main_rec, circle, "LEVEL 6", " - - : - -");

    mx_toned_rect(0);
    mx_toned_rect(space);
    mx_toned_rect(space * 2);

    Rectangle gear_rect = mx_draw_settings_icon(textures);
    Rectangle back_button = mx_draw_back_button(textures);
    Rectangle left_arrow_rec = { 45, circle.y - 30, 60, 60};
    mx_draw_arrow(textures->left_arrow, left_arrow_rec);

    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;

    if (CheckCollisionPointRec(mouse, gear_rect)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            previous_state = current_state;
            current_state = SETTINGS;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointRec(mouse, back_button)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = SELECT_PLAYER;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointRec(mouse, left_arrow_rec)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = LEVEL_MENU;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}
