#include "../inc/header.h"

t_player_config player_config = {
    10.0f, // speed
    104,   // width
    20,    // height
};

static void update_gameplay(t_player* player_data, t_surface* surfaces, const int surface_count) {
    Vector2 new_pos = player_data->position;

    if (IsKeyDown(KEY_W)) new_pos.y -= player_config.speed;
    if (IsKeyDown(KEY_S)) new_pos.y += player_config.speed;
    if (IsKeyDown(KEY_A)) new_pos.x -= player_config.speed;
    if (IsKeyDown(KEY_D)) new_pos.x += player_config.speed;

    bool collision = false;

    Rectangle player_hitbox = { new_pos.x + 5, new_pos.y + 8, 90, 1};
//    /////////////////
//    DrawRectangle(new_pos.x + 5, new_pos.y + 8, 90, 1, RED);

    for (int i = 0; i < surface_count; i++) {
        if (CheckCollisionRecs(player_hitbox, surfaces[i].rect)) {
            collision = true;
            break;
        }
    }

    if (!collision) {
        player_data->position = new_pos;
    }
}

void mx_render_gameplay(t_player* player_data, t_game_textures* textures, bool* is_popup_open, int* served_counter, int max_served) {
    Rectangle player = { player_data->position.x, player_data->position.y, player_config.player_width, player_config.player_height };

    float texture_draw_x = player_data->position.x - textures->chef.width + player_config.player_width;
    float texture_draw_y = player_data->position.y - textures->chef.height + player_config.player_height;

    // player movement and colission check
    if (!(*is_popup_open)) {
        update_gameplay(player_data, surfaces, surface_count);
    }
    

    // draw surfaces
    for (int i = 0; i < surface_count; i++) {
        DrawRectangleRec(surfaces[i].rect, surfaces[i].color);
    }
    switch (level_number) {
        case 1:
            DrawTexture(textures->map1, 0, 0, WHITE);
            break;
        case 2:
            DrawTexture(textures->map2, 0, 0, WHITE);
            break;
        case 3:
            DrawTexture(textures->map3, 0, 0, WHITE);
            break;
        default:
          break;
    }
//    DrawTexture(textures->map3, 0, 0, WHITE);
    // draw player
    DrawTexture(textures->chef, texture_draw_x, texture_draw_y, WHITE);

//    ////////////
//    DrawRectangle(player.x, player.y, player.width, player.height, BLUE);
    
    int interactable_object = mx_get_nearby_interactable(player, surfaces, surface_count);
    for (int i = 0; i < surface_count; i++) {
        if (CheckCollisionRecs(player, surfaces[i].rect)) {
            if (surfaces[i].type != NONE)
                DrawTexturePro(textures->f_button, (Rectangle) { 0, 0, textures->f_button.width, textures->f_button.height },
                    (Rectangle) {
                surfaces[i].rect.x + surfaces[i].rect.width - 100, surfaces[i].rect.y - 50, 150, 150
            }, (Vector2) { 0, 0 }, 0.0f, WHITE);
                //DrawText("F", surfaces[i].rect.x - 10, surfaces[i].rect.y - 10, 20, BLACK);
            break;
        }
    }
    // interacting with objects
    if (interactable_object != -1 && !(*is_popup_open)) {
        if (IsKeyPressed(KEY_F)) {
            mx_interact_with_object(&hotbar, surfaces[interactable_object].type);
        }
    }

    int pause_size = 100;
    Rectangle gear_rect = { game_config.screen_width - pause_size - 30, 30, pause_size, pause_size };
    DrawTexturePro(textures->pause, (Rectangle){ 0, 0, textures->pause.width, textures->pause.height }, gear_rect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 mouse = GetMousePosition();
    bool cursor_changed = false;
    if (!(*is_popup_open)) {
        if (CheckCollisionPointRec(mouse, gear_rect)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursor_changed = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mx_play_sound_effect(button_click);
                current_state = GAMEPLAY_SETTINGS;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
        if (*served_counter == max_served) {
            mx_play_sound_effect(level_complete);
            *is_popup_open = true;
        }
    }
    if (*is_popup_open) {      
        mx_draw_level_sucsses(is_popup_open, textures, served_counter);
        mx_pause_game_timer();
    }
    if (!cursor_changed) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    mx_render_queue(player, is_popup_open, served_counter, textures);
}
