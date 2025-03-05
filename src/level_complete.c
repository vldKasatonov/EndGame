#include "../inc/header.h"

void mx_draw_stars_gameplay(int space, double elapsed_time, t_game_textures *textures, Vector2 circle) {
    Rectangle star_rec = { 225, 390, 75, 75 };
    Rectangle src_star = { 0, 0, textures->star.width, textures->star.height };
    Color star_colors[3] = {
        custom_colors.nonactive_star_color,
        custom_colors.nonactive_star_color,
        custom_colors.nonactive_star_color
    };
    if (elapsed_time > 1.0) {
        if (elapsed_time <= 120.0) {
            star_colors[0] = custom_colors.active_star_color;
            star_colors[1] = custom_colors.active_star_color;
            star_colors[2] = custom_colors.active_star_color;
        } else if (elapsed_time <= 180.0) {
            star_colors[0] = custom_colors.active_star_color;
            star_colors[1] = custom_colors.active_star_color;
            star_colors[2] = custom_colors.nonactive_star_color;
        } else if (elapsed_time <= 300.0) {
            star_colors[0] = custom_colors.active_star_color;
            star_colors[1] = custom_colors.nonactive_star_color;
            star_colors[2] = custom_colors.nonactive_star_color;
        }
    }
    for (int i = 0; i < 3; ++i) {
        float offset_x = circle.x + (i * (star_rec.width + space));
        DrawTexturePro(textures->star, src_star, (Rectangle){ offset_x, circle.y, star_rec.width, star_rec.height },
                       (Vector2){ 0, 0 }, 0.0f, star_colors[i]);
    }
}

void mx_disable_gameplay_input(bool is_popup_open) {
    if (current_state == GAMEPLAY && is_popup_open) {
        if (IsKeyPressed(KEY_SPACE) ||
            IsKeyPressed(KEY_W) ||
            IsKeyPressed(KEY_A) ||
            IsKeyPressed(KEY_S) ||
            IsKeyPressed(KEY_D) ||
            IsKeyPressed(KEY_F) ||
            IsKeyPressed(KEY_E) ||
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            return;
        }
    }
}

void mx_draw_level_sucsses(bool *is_exit_popup_open, t_game_textures *textures,
                           int *served_counter, bool *cursor_changed) {
    int popup_width = 900;
    int popup_height = 500;
    Rectangle popup_rect = {
        (GetScreenWidth() - popup_width) / 2,
        (GetScreenHeight() - popup_height) / 2,
        popup_width,
        popup_height
    };
    DrawRectangleRounded(popup_rect, 0.5f, 10, custom_colors.button_background_color);
    DrawRectangleRoundedLinesEx(popup_rect, 0.5f, 10, 5, WHITE);

    Vector2 text_size = MeasureTextEx(mx_get_custom_font(), "Congratulations!", 70, 3);
    Vector2 text_pos = {
        popup_rect.x + (popup_rect.width - text_size.x) / 2,
        popup_rect.y + 60
    };
    DrawTextEx(mx_get_custom_font(), "Congratulations!", text_pos, 70, 3, WHITE);

    double elapsed_time = mx_get_elapsed_time();
    Vector2 popup_center = { popup_rect.x + popup_width / 2 - 130 , popup_rect.y + popup_height / 2 - 90};
    int space = 10;
    mx_draw_stars_gameplay(space, elapsed_time, textures, popup_center);

    int minutes = (int)(elapsed_time / 60);
    int seconds = (int)(elapsed_time) % 60;
    char your_time[10];
    snprintf(your_time, sizeof(your_time), "%02d:%02d", minutes, seconds);
    Vector2 timetext_size = MeasureTextEx(mx_get_custom_font(), "Your time", 50, 3);
    Vector2 timetext_pos = {
        popup_rect.x + (popup_rect.width - timetext_size.x) / 2,
        popup_rect.y + 260
    };
    DrawTextEx(mx_get_custom_font(), "Your time", timetext_pos, 50, 3, WHITE);
    Vector2 your_time_size = MeasureTextEx(mx_get_custom_font(), your_time, 50, 3);
    Vector2 your_time_pos = {
        popup_rect.x + (popup_rect.width - your_time_size.x) / 2,
        popup_rect.y + 320
    };
    DrawTextEx(mx_get_custom_font(), your_time, your_time_pos, 50, 3, WHITE);

    Rectangle okey_button = { popup_rect.x + (popup_rect.width - 150) / 2, popup_rect.y + popup_height - 100, 150, 60 };
    DrawRectangleRounded(okey_button, 0.5f, 10, GREEN);
    Vector2 okeytext_size = MeasureTextEx(mx_get_custom_font(), "OK", 40, 3);
    Vector2 okeytext_pos = {
        okey_button.x + (okey_button.width - okeytext_size.x) / 2,
        okey_button.y + (okey_button.height - okeytext_size.y) / 2
    };
    DrawTextEx(mx_get_custom_font(), "OK", okeytext_pos, 40, 3, WHITE);

    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, okey_button)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        *cursor_changed = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = LEVEL_MENU;
            *is_exit_popup_open = false;
            mx_save_best_time();
            mx_resume_game_timer();
            *served_counter = 0;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
}

void mx_update_level_stars(t_level_stars *game_state, int level, int stars) {
    if (level >= 0 && level < MX_NUM_LEVELS) {
        game_state->level_stars[level] = stars;
    }
}

int mx_calculate_stars_for_level(void) {
    double best_time = mx_get_best_time();
    int stars = 0;

    if (best_time < 120) {
        stars = 3;
    } else if (best_time < 180) {
        stars = 2;
    } else if (best_time < 300) {
        stars = 1;
    }
    return stars;
}
