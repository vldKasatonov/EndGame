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


void mx_render_main_menu(t_game_textures *textures, bool *isExitPopupOpen) {
    Vector2 mouse = GetMousePosition();

    int buttonX = (GetScreenWidth() - game_config.button_width) / 2 - 75;
    int buttonY = (int)(GetScreenHeight() * 0.55) ;
    Rectangle buttonRect = { buttonX, buttonY, 450, 150 };

    bool cursorChanged = false;

    int gearSize = 115;
    Rectangle gearRect = { game_config.screen_width - gearSize - 30, 20, gearSize, gearSize };
    DrawTexturePro(textures->settings, (Rectangle){ 0, 0, textures->settings.width, textures->settings.height }, gearRect, (Vector2){0, 0}, 0.0f, WHITE);

    int textWidth = MeasureText("EXIT", game_config.font_size_paragraph + 50);
    int button_height = 80;
    int iconWidth = textures->exit.width - 10;
    int iconHeight = textures->exit.height - 10;
    int button_width = iconWidth + textWidth + 50;
    Rectangle exitButton = { 30, 40, button_width, button_height };
    Rectangle exitTextRect = { exitButton.x + textures->exit.width + 5, exitButton.y, textWidth, button_height };
    Rectangle exitRect = { exitButton.x , exitButton.y + (button_height - iconHeight) / 2, iconWidth, iconHeight };
    DrawTexturePro(textures->exit, (Rectangle){0, 0, textures->exit.width, textures->exit.height}, exitRect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 textPos1 = {exitTextRect.x, exitTextRect.y - 10};
    DrawTextEx(mx_get_custom_font(), "EXIT", textPos1, game_config.font_size_paragraph + 70, 3, WHITE);

    Vector2 textDev = MeasureTextEx(mx_get_custom_font(), "DEVELOPERS", game_config.font_size_paragraph + 50, 3);
    Vector2 textPosDev = {
        exitRect.x,
        game_config.screen_height - textPos1.y - textDev.y - 10
    };
    DrawTextEx(mx_get_custom_font(), "DEVELOPERS", textPosDev, game_config.font_size_paragraph + 50, 3, WHITE);
    Rectangle DevButton = { textPosDev.x, textPosDev.y, textDev.x, textDev.y };

    Rectangle srcImageChef = { 0, 0, textures->chef.width, textures->chef.height };
    Vector2 sizeImage = { 104 * 2, 194 * 2 };
    Rectangle imageChef = { game_config.screen_width - sizeImage.x * 2, game_config.screen_height - sizeImage.y, sizeImage.x, sizeImage.y };

    DrawTexturePro(textures->chef, srcImageChef, imageChef,
                   (Vector2){0, 0}, 0.0f, WHITE);

    if (!(*isExitPopupOpen)) {
        if (CheckCollisionPointRec(mouse, buttonRect)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mx_play_sound_effect(button_click);
                current_state = SELECT_PLAYER;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }

        if (CheckCollisionPointRec(mouse, gearRect)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                previous_state = current_state;
                mx_play_sound_effect(button_click);
                current_state = SETTINGS;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }

        if (CheckCollisionPointRec(mouse, exitButton)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mx_play_sound_effect(button_click);
                *isExitPopupOpen = true;
            }
        }

        if (CheckCollisionPointRec(mouse, DevButton)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mx_play_sound_effect(button_click);
                current_state = DEVELOPERS;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
    }

    Vector2 textSize = MeasureTextEx(mx_get_custom_font(), "FUNNY CHEF", 140, 3);
    Vector2 textPos = {
        (GetScreenWidth() - textSize.x) / 2 - 180,
        (GetScreenHeight() - textSize.y) / 2 - 130
    };
    DrawTextEx(mx_get_custom_font(), "FUNNY CHEF", textPos, 200, 3, WHITE);

    DrawCenteredButton("PLAY", game_config.font_size_header2 + 100, custom_colors.button_background_color, WHITE, buttonRect);

    if (*isExitPopupOpen) {
        DrawExitConfirmation(isExitPopupOpen);
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

}
