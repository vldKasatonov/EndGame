#include "../inc/header.h"

static void draw_select_icon(Vector2 pos_circle, int space, int radius,
                             Color color, Texture2D icon, char *text) {
    Vector2 circle = { space - pos_circle.x, pos_circle.y };
    int icon_size = 270;
    DrawCircleV(circle, radius, color);
    Rectangle icon_rect = { circle.x - icon_size / 2, circle.y
                           - icon_size / 2, icon_size, icon_size };
    DrawTexturePro(icon, (Rectangle){ 0, 0, icon.width, icon.height },
                   icon_rect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 text_size = MeasureTextEx(mx_get_custom_font(), text, 60, 3);
    Vector2 text_pos = {
        circle.x - text_size.x / 2 - 2,
        circle.y + 230
    };
    DrawTextEx(mx_get_custom_font(), text, text_pos, 60, 3, WHITE);
}

static void toned_circle(Vector2 circle, int radius) {
    DrawCircle(game_config.screen_width - circle.x, circle.y, radius,
               custom_colors.nonactive_level_color);
}

void mx_render_select_player(t_game_textures *textures) {
    Vector2 circle = {
        game_config.screen_width / 3, game_config.screen_height / 2
    };
    int radius = 200;
    Rectangle gear_rect = mx_draw_settings_icon(textures);
    Rectangle back_button = mx_draw_back_button(textures);
    bool cursor_changed = false;
    Vector2 mouse = GetMousePosition();

    draw_select_icon(circle, 2 * circle.x, radius,
                     custom_colors.button_background_color,
                     textures->one_player, "1 PLAYER");
    draw_select_icon(circle, game_config.screen_width, radius,
                     custom_colors.button_background_color,
                     textures->two_players, "2 PLAYERS");
    toned_circle(circle, radius);

    check_collision(mouse, &cursor_changed, back_button, MAIN_MENU);
    if (CheckCollisionPointRec(mouse, gear_rect)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursor_changed = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            previous_state = current_state;
            mx_play_sound_effect(button_click);
            current_state = SETTINGS;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointCircle(mouse, circle, radius)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursor_changed = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = LEVEL_MENU;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (!cursor_changed) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}
