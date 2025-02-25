#include "../inc/header.h"

static void drawTextDev(char *text, int space) {
    Vector2 textSize = MeasureTextEx(GetCustomFont(), text, 70, 3);
    Vector2 textPos = {
        (GetScreenWidth() - textSize.x) / 2,
        (GetScreenHeight() - textSize.y) / 3
    };
    DrawTextEx(GetCustomFont(), text, (Vector2){textPos.x, textPos.y + space}, 70, 3, WHITE);
}

void renderDevelopers(GameTextures *textures) {
    Vector2 textSizeHeader = MeasureTextEx(GetCustomFont(), "OUR TEAM:", 100, 3);
    Vector2 textPosHeader = {
        (gameConfig.screenWidth - textSizeHeader.x) / 2,
        (gameConfig.screenHeight - textSizeHeader.y) / 6
    };
    DrawTextEx(GetCustomFont(), "OUR TEAM:", textPosHeader, 100, 3, WHITE);
    int space = 90;
    drawTextDev("Daniil Burlachenko", 0);
    drawTextDev("Albina Milshyna", space * 1);
    drawTextDev("Mariia Kashuashvili", space * 2);
    drawTextDev("Mariia Mykhalchenko", space * 3);
    drawTextDev("Viktoriia Shaforostova", space * 4);
    drawTextDev("Vladyslav Kasatonov", space * 5);

    int textWidth = MeasureText("BACK", gameConfig.fontSizeParagraph + 50);
    int buttonHeight = 80;
    int iconWidth = textures->exit.width ;
    int iconHeight = textures->exit.height ;
    int buttonWidth = iconWidth + textWidth + 80;
    Rectangle backButton = { 30, 40, buttonWidth, buttonHeight };
    Rectangle backTextRect = { backButton.x + textures->arrow.width + 5,
                      backButton.y, textWidth, buttonHeight };

    Rectangle backRect = { backButton.x , backButton.y + (buttonHeight -
                  iconHeight) / 2, iconWidth, iconHeight };

    DrawTexturePro(textures->arrow, (Rectangle){0, 0, textures->arrow.width,
               textures->arrow.height}, backRect, (Vector2){0, 0},
               0.0f, WHITE);

    Vector2 textPos1 = { backTextRect.x, backTextRect.y - 10};
    DrawTextEx(GetCustomFont(), "BACK", textPos1, gameConfig.fontSizeParagraph + 70, 3, WHITE);

    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;

    if (CheckCollisionPointRec(mouse, backButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySoundEffect(buttonClick);
            currentState = MAIN_MENU;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}
