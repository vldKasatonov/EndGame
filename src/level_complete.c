#include "../inc/header.h"

void mx_draw_stars_gameplay(int space, double elapsedTime, t_game_textures *textures, Vector2 circle) {
    Rectangle starRec = { 225, 390, 75, 75 };
    Rectangle srcStar = { 0, 0, textures->star.width, textures->star.height };
    Color starColors[3] = {
        custom_colors.nonactive_star_color,
        custom_colors.nonactive_star_color,
        custom_colors.nonactive_star_color
    };
    if (elapsedTime > 1.0) {
        if (elapsedTime <= 120.0) {
            starColors[0] = custom_colors.active_star_color;
            starColors[1] = custom_colors.active_star_color;
            starColors[2] = custom_colors.active_star_color;
        } else if (elapsedTime <= 180.0) {
            starColors[0] = custom_colors.active_star_color;
            starColors[1] = custom_colors.active_star_color;
            starColors[2] = custom_colors.nonactive_star_color;
        } else if (elapsedTime <= 300.0) {
            starColors[0] = custom_colors.active_star_color;
            starColors[1] = custom_colors.nonactive_star_color;
            starColors[2] = custom_colors.nonactive_star_color;
        }
    }
    for (int i = 0; i < 3; ++i) {
        float offsetX = circle.x + (i * (starRec.width + space));
        DrawTexturePro(textures->star, srcStar, (Rectangle){ offsetX, circle.y, starRec.width, starRec.height },
                       (Vector2){ 0, 0 }, 0.0f, starColors[i]);
    }
}

void mx_disable_gameplay_input(bool isPopupOpen) {
    if (current_state == GAMEPLAY && isPopupOpen) {
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

void mx_draw_level_sucsses(bool *isExitPopupOpen, t_game_textures *textures, int *servedCounter) {
    int popupWidth = 900;
    int popupHeight = 500;
    Rectangle popupRect = {
        (GetScreenWidth() - popupWidth) / 2,
        (GetScreenHeight() - popupHeight) / 2,
        popupWidth,
        popupHeight
    };
    DrawRectangleRounded(popupRect, 0.5f, 10, custom_colors.button_background_color);
    DrawRectangleRoundedLinesEx(popupRect, 0.5f, 10, 5, WHITE);

    Vector2 textSize = MeasureTextEx(mx_get_custom_font(), "Congratulations!", 70, 3);
    Vector2 textPos = {
        popupRect.x + (popupRect.width - textSize.x) / 2,
        popupRect.y + 60
    };
    DrawTextEx(mx_get_custom_font(), "Congratulations!", textPos, 70, 3, WHITE);

    double elapsedTime = mx_get_elapsed_time();
    Vector2 popupCenter = { popupRect.x + popupWidth / 2 - 130 , popupRect.y + popupHeight / 2 - 90};
    int space = 10;
    mx_draw_stars_gameplay(space, elapsedTime, textures, popupCenter);

    int minutes = (int)(elapsedTime / 60);
    int seconds = (int)(elapsedTime) % 60;
    char yourTime[10];
    snprintf(yourTime, sizeof(yourTime), "%02d:%02d", minutes, seconds);
    Vector2 timeTextSize = MeasureTextEx(mx_get_custom_font(), "Your time", 50, 3);
    Vector2 timeTextPos = {
        popupRect.x + (popupRect.width - timeTextSize.x) / 2,
        popupRect.y + 260
    };
    DrawTextEx(mx_get_custom_font(), "Your time", timeTextPos, 50, 3, WHITE);
    Vector2 yourTimeSize = MeasureTextEx(mx_get_custom_font(), yourTime, 50, 3);
    Vector2 yourTimePos = {
        popupRect.x + (popupRect.width - yourTimeSize.x) / 2,
        popupRect.y + 320
    };
    DrawTextEx(mx_get_custom_font(), yourTime, yourTimePos, 50, 3, WHITE);

    Rectangle okeyButton = { popupRect.x + (popupRect.width - 150) / 2, popupRect.y + popupHeight - 100, 150, 60 };
    DrawRectangleRounded(okeyButton, 0.5f, 10, GREEN);
    Vector2 okeyTextSize = MeasureTextEx(mx_get_custom_font(), "OK", 40, 3);
    Vector2 okeyTextPos = {
        okeyButton.x + (okeyButton.width - okeyTextSize.x) / 2,
        okeyButton.y + (okeyButton.height - okeyTextSize.y) / 2
    };
    DrawTextEx(mx_get_custom_font(), "OK", okeyTextPos, 40, 3, WHITE);

    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;
    if (CheckCollisionPointRec(mouse, okeyButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = LEVEL_MENU;
            *isExitPopupOpen = false;
            mx_save_best_time();
            mx_resume_game_timer();
            *servedCounter = 0;
        }
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

void mx_update_level_stars(t_level_stars *game_state, int level, int stars) {
    if (level >= 0 && level < MX_NUM_LEVELS) {
        game_state->level_stars[level] = stars;
    }
}

int mx_calculate_stars_for_level(void) {
    double bestTime = mx_get_best_time();
    int stars = 0;

    if (bestTime < 120) {
        stars = 3;
    } else if (bestTime < 180) {
        stars = 2;
    } else if (bestTime < 300) {
        stars = 1;
    }
    return stars;
}
