#include "../inc/header.h"

static void drawTextDev(char *text, int space) {
    Vector2 textSize = MeasureTextEx(mx_get_custom_font(), text, 70, 3);
    Vector2 textPos = {
        (GetScreenWidth() - textSize.x) / 2,
        (GetScreenHeight() - textSize.y) / 3
    };
    DrawTextEx(mx_get_custom_font(), text, (Vector2){textPos.x, textPos.y + space}, 70, 3, WHITE);
}

void mx_render_developers(t_game_textures *textures) {
    Vector2 textSizeHeader = MeasureTextEx(mx_get_custom_font(), "OUR TEAM:", 100, 3);
    Vector2 textPosHeader = {
        (game_config.screen_width - textSizeHeader.x) / 2,
        (game_config.screen_height - textSizeHeader.y) / 6
    };
    DrawTextEx(mx_get_custom_font(), "OUR TEAM:", textPosHeader, 100, 3, WHITE);
    int space = 90;
    drawTextDev("Daniil Burlachenko", 0);
    drawTextDev("Albina Milshyna", space * 1);
    drawTextDev("Mariia Kashuashvili", space * 2);
    drawTextDev("Mariia Mykhalchenko", space * 3);
    drawTextDev("Viktoriia Shaforostova", space * 4);
    drawTextDev("Vladyslav Kasatonov", space * 5);

    int textWidth = MeasureText("BACK", game_config.font_size_paragraph + 50);
    int button_height = 80;
    int iconWidth = textures->exit.width ;
    int iconHeight = textures->exit.height ;
    int button_width = iconWidth + textWidth + 80;
    Rectangle backButton = { 30, 40, button_width, button_height };
    Rectangle backTextRect = { backButton.x + textures->arrow.width + 5,
                      backButton.y, textWidth, button_height };

    Rectangle backRect = { backButton.x , backButton.y + (button_height -
                  iconHeight) / 2, iconWidth, iconHeight };

    DrawTexturePro(textures->arrow, (Rectangle){0, 0, textures->arrow.width,
               textures->arrow.height}, backRect, (Vector2){0, 0},
               0.0f, WHITE);

    Vector2 textPos1 = { backTextRect.x, backTextRect.y - 10};
    DrawTextEx(mx_get_custom_font(), "BACK", textPos1, game_config.font_size_paragraph + 70, 3, WHITE);

    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;

    if (CheckCollisionPointRec(mouse, backButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = MAIN_MENU;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}
