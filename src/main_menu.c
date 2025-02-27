#include "../inc/header.h"

void DrawCenteredButton(const char* text, int fontSize, Color buttonBackground, Color fontColor, Rectangle buttonRect) {
    DrawRectangleRounded(buttonRect, 0.5f, 10, buttonBackground);
    /*int textWidth = MeasureText(text, fontSize);
    int textX = buttonRect.x + (buttonRect.width - textWidth) / 2;
    int textY = buttonRect.y + (buttonRect.height - fontSize) / 2;
    DrawText(text, textX, textY, fontSize, fontColor);*/

    Vector2 textSize = MeasureTextEx(mx_get_custom_font(), text, fontSize, 2);
    Vector2 textPos = {
        buttonRect.x + (buttonRect.width - textSize.x) / 2,
        buttonRect.y + (buttonRect.height - textSize.y) / 2
    };
    DrawTextEx(mx_get_custom_font(), text, textPos, fontSize, 2, fontColor);
}

static void DrawExitConfirmation(bool *isExitPopupOpen) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.4f));
    int popupWidth = 900;
    int popupHeight = 400;
    Rectangle popupRect = {
        (GetScreenWidth() - popupWidth) / 2,
        (GetScreenHeight() - popupHeight) / 2,
        popupWidth,
        popupHeight
    };

    DrawRectangleRounded(popupRect, 0.5f, 10, custom_colors.button_background_color);
    DrawRectangleRoundedLinesEx(popupRect, 0.5f, 10, 5, WHITE);

    Vector2 textSize = MeasureTextEx(mx_get_custom_font(), "Are you sure you want to exit?", 50, 3);
    Vector2 textPos = {
        popupRect.x + (popupRect.width - textSize.x) / 2,
        popupRect.y + 100
    };
    DrawTextEx(mx_get_custom_font(), "Are you sure you want to exit?", textPos, 50, 3, WHITE);

    Rectangle yesButton = { popupRect.x + 150, popupRect.y + popupHeight - 150, 150, 60 };
    Rectangle noButton = { popupRect.x + popupWidth - 300, popupRect.y + popupHeight - 150, 150, 60 };

    DrawRectangleRounded(yesButton, 0.5f, 10, GREEN);
    DrawRectangleRounded(noButton, 0.5f, 10, RED);

    Vector2 yesTextSize = MeasureTextEx(mx_get_custom_font(), "YES", 40, 3);
    Vector2 yesTextPos = {
        yesButton.x + (yesButton.width - yesTextSize.x) / 2,
        yesButton.y + (yesButton.height - yesTextSize.y) / 2
    };
    DrawTextEx(mx_get_custom_font(), "YES", yesTextPos, 40, 3, WHITE);

    Vector2 noTextSize = MeasureTextEx(mx_get_custom_font(), "NO", 40, 3);
    Vector2 noTextPos = {
        noButton.x + (noButton.width - noTextSize.x) / 2,
        noButton.y + (noButton.height - noTextSize.y) / 2
    };
    DrawTextEx(mx_get_custom_font(), "NO", noTextPos, 40, 3, WHITE);

    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;
    if (CheckCollisionPointRec(mouse, yesButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            exit(0);
        }
    }
    if (CheckCollisionPointRec(mouse, noButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            *isExitPopupOpen = false;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

static Rectangle draw_exit_button(Texture2D icon) {
    int text_width = MeasureText("EXIT", game_config.font_size_paragraph + 50);
    int button_height = 80;
    int icon_width = icon.width - 10;
    int icon_height = icon.height - 10;
    int button_width = icon_width + text_width + 50;
    Rectangle exit_button = { 30, 40, button_width, button_height };
    Rectangle exit_text_rect = { exit_button.x + icon.width + 5,
                              exit_button.y, text_width, button_height };
    Rectangle exit_rect = { exit_button.x , exit_button.y + (button_height
                          - icon_height) / 2, icon_width, icon_height };
    DrawTexturePro(icon, (Rectangle){0, 0, icon.width, icon.height},
                   exit_rect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 text_pos = {exit_text_rect.x, exit_text_rect.y - 10};
    DrawTextEx(mx_get_custom_font(), "EXIT", text_pos,
               game_config.font_size_paragraph + 70, 3, WHITE);
    return exit_button;
}

static Rectangle draw_dev_button(void) {
    Vector2 text_dev = MeasureTextEx(mx_get_custom_font(),
                                     "DEVELOPERS", 70, 3);
    Vector2 text_pos_dev = {
        30,
        game_config.screen_height - 30 - text_dev.y - 10
    };
    DrawTextEx(mx_get_custom_font(), "DEVELOPERS", text_pos_dev,
               game_config.font_size_paragraph + 50, 3, WHITE);
    Rectangle dev_button = { text_pos_dev.x, text_pos_dev.y,
                            text_dev.x, text_dev.y };
    return dev_button;
}

static void draw_chef(Texture2D image) {
    Rectangle src_image_chef = { 0, 0, image.width, image.height };
    Vector2 size_image = { 104 * 2, 194 * 2 };
    Rectangle image_chef = { game_config.screen_width - size_image.x * 2,
                           game_config.screen_height - size_image.y,
                           size_image.x, size_image.y };
    DrawTexturePro(image, src_image_chef, image_chef,
                   (Vector2){0, 0}, 0.0f, WHITE);
}

static Rectangle draw_play_button(void) {
    Vector2 button = {
        (GetScreenWidth() - game_config.button_width) / 2 - 75,
        (int)(GetScreenHeight() * 0.55)
    };
    Rectangle button_rect = { button.x, button.y, 450, 150 };
    Vector2 text_size = MeasureTextEx(mx_get_custom_font(),
                                      "FUNNY CHEF", 140, 3);
    Vector2 text_pos = {
        (GetScreenWidth() - text_size.x) / 2 - 180,
        (GetScreenHeight() - text_size.y) / 2 - 130
    };
    DrawTextEx(mx_get_custom_font(), "FUNNY CHEF", text_pos, 200, 3, WHITE);
    DrawCenteredButton("PLAY", game_config.font_size_header2 + 100,
                       custom_colors.button_background_color, WHITE, button_rect);
    return button_rect;
}

void mx_render_main_menu(t_game_textures *textures, bool *isExitPopupOpen) {
    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;
    Rectangle button_rect = draw_play_button();
    Rectangle gear_rect = mx_draw_settings_icon(textures);
    Rectangle exit_button = draw_exit_button(textures->exit);
    Rectangle dev_button = draw_dev_button();

    draw_chef(textures->chef);
    if (!(*isExitPopupOpen)) {
        if (CheckCollisionPointRec(mouse, button_rect)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mx_play_sound_effect(button_click);
                current_state = SELECT_PLAYER;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
        if (CheckCollisionPointRec(mouse, gear_rect)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                previous_state = current_state;
                mx_play_sound_effect(button_click);
                current_state = SETTINGS;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
        if (CheckCollisionPointRec(mouse, exit_button)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mx_play_sound_effect(button_click);
                *isExitPopupOpen = true;
            }
        }
        if (CheckCollisionPointRec(mouse, dev_button)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mx_play_sound_effect(button_click);
                current_state = DEVELOPERS;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
    }
    if (*isExitPopupOpen) {
        DrawExitConfirmation(isExitPopupOpen);
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

}
