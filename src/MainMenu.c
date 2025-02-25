#include "../inc/header.h"
void DrawCenteredButton(const char* text, int fontSize, Color buttonBackground, Color fontColor, Rectangle buttonRect) {
    DrawRectangleRounded(buttonRect, 0.5f, 10, buttonBackground);
    /*int textWidth = MeasureText(text, fontSize);
    int textX = buttonRect.x + (buttonRect.width - textWidth) / 2;
    int textY = buttonRect.y + (buttonRect.height - fontSize) / 2;
    DrawText(text, textX, textY, fontSize, fontColor);*/

    Vector2 textSize = MeasureTextEx(GetCustomFont(), text, fontSize, 2);
    Vector2 textPos = {
        buttonRect.x + (buttonRect.width - textSize.x) / 2,
        buttonRect.y + (buttonRect.height - textSize.y) / 2
    };
    DrawTextEx(GetCustomFont(), text, textPos, fontSize, 2, fontColor);
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

    DrawRectangleRounded(popupRect, 0.5f, 10, customColors.buttonBackgroundColor);
    DrawRectangleRoundedLinesEx(popupRect, 0.5f, 10, 5, WHITE);

    Vector2 textSize = MeasureTextEx(GetCustomFont(), "Are you sure you want to exit?", 50, 3);
    Vector2 textPos = {
        popupRect.x + (popupRect.width - textSize.x) / 2,
        popupRect.y + 100
    };
    DrawTextEx(GetCustomFont(), "Are you sure you want to exit?", textPos, 50, 3, WHITE);

    Rectangle yesButton = { popupRect.x + 150, popupRect.y + popupHeight - 150, 150, 60 };
    Rectangle noButton = { popupRect.x + popupWidth - 300, popupRect.y + popupHeight - 150, 150, 60 };

    DrawRectangleRounded(yesButton, 0.5f, 10, GREEN);
    DrawRectangleRounded(noButton, 0.5f, 10, RED);

    Vector2 yesTextSize = MeasureTextEx(GetCustomFont(), "YES", 40, 3);
    Vector2 yesTextPos = {
        yesButton.x + (yesButton.width - yesTextSize.x) / 2,
        yesButton.y + (yesButton.height - yesTextSize.y) / 2
    };
    DrawTextEx(GetCustomFont(), "YES", yesTextPos, 40, 3, WHITE);

    Vector2 noTextSize = MeasureTextEx(GetCustomFont(), "NO", 40, 3);
    Vector2 noTextPos = {
        noButton.x + (noButton.width - noTextSize.x) / 2,
        noButton.y + (noButton.height - noTextSize.y) / 2
    };
    DrawTextEx(GetCustomFont(), "NO", noTextPos, 40, 3, WHITE);

    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;
    if (CheckCollisionPointRec(mouse, yesButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySoundEffect(buttonClick);
            exit(0);
        }
    }
    if (CheckCollisionPointRec(mouse, noButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySoundEffect(buttonClick);
            *isExitPopupOpen = false;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}


void renderMainMenu(GameTextures *textures, bool *isExitPopupOpen) {
    Vector2 mouse = GetMousePosition();

    int buttonX = (GetScreenWidth() - gameConfig.buttonWidth) / 2 - 75;
    int buttonY = (int)(GetScreenHeight() * 0.55) ;
    Rectangle buttonRect = { buttonX, buttonY, 450, 150 };

    bool cursorChanged = false;

    int gearSize = 115;
    Rectangle gearRect = { gameConfig.screenWidth - gearSize - 30, 20, gearSize, gearSize };
    DrawTexturePro(textures->gearTexture, (Rectangle){ 0, 0, textures->gearTexture.width, textures->gearTexture.height }, gearRect, (Vector2){0, 0}, 0.0f, WHITE);

    int textWidth = MeasureText("EXIT", gameConfig.fontSizeParagraph + 50);
    int buttonHeight = 80;
    int iconWidth = textures->exit.width - 10;
    int iconHeight = textures->exit.height - 10;
    int buttonWidth = iconWidth + textWidth + 50;
    Rectangle exitButton = { 30, 40, buttonWidth, buttonHeight };
    Rectangle exitTextRect = { exitButton.x + textures->exit.width + 5, exitButton.y, textWidth, buttonHeight };
    Rectangle exitRect = { exitButton.x , exitButton.y + (buttonHeight - iconHeight) / 2, iconWidth, iconHeight };
    DrawTexturePro(textures->exit, (Rectangle){0, 0, textures->exit.width, textures->exit.height}, exitRect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 textPos1 = {exitTextRect.x, exitTextRect.y - 10};
    DrawTextEx(GetCustomFont(), "EXIT", textPos1, gameConfig.fontSizeParagraph + 70, 3, WHITE);

    Vector2 textDev = MeasureTextEx(GetCustomFont(), "DEVELOPERS", gameConfig.fontSizeParagraph + 50, 3);
    Vector2 textPosDev = {
        exitRect.x,
        gameConfig.screenHeight - textPos1.y - textDev.y - 10
    };
    DrawTextEx(GetCustomFont(), "DEVELOPERS", textPosDev, gameConfig.fontSizeParagraph + 50, 3, WHITE);
    Rectangle DevButton = { textPosDev.x, textPosDev.y, textDev.x, textDev.y };

    Rectangle srcImageChef = { 0, 0, textures->chef.width, textures->chef.height };
    Vector2 sizeImage = { 104 * 2, 194 * 2 };
    Rectangle imageChef = { gameConfig.screenWidth - sizeImage.x * 2, gameConfig.screenHeight - sizeImage.y, sizeImage.x, sizeImage.y };

    DrawTexturePro(textures->chef, srcImageChef, imageChef,
                   (Vector2){0, 0}, 0.0f, WHITE);

    if (!(*isExitPopupOpen)) {
        if (CheckCollisionPointRec(mouse, buttonRect)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                PlaySoundEffect(buttonClick);
                currentState = SELECT_PLAYER;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }

        if (CheckCollisionPointRec(mouse, gearRect)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                previousState = currentState;
                PlaySoundEffect(buttonClick);
                currentState = SETTINGS;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }

        if (CheckCollisionPointRec(mouse, exitButton)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                PlaySoundEffect(buttonClick);
                *isExitPopupOpen = true;
            }
        }

        if (CheckCollisionPointRec(mouse, DevButton)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                PlaySoundEffect(buttonClick);
                currentState = DEVELOPERS;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
    }

    Vector2 textSize = MeasureTextEx(GetCustomFont(), "FUNNY CHEF", 140, 3);
    Vector2 textPos = {
        (GetScreenWidth() - textSize.x) / 2 - 180,
        (GetScreenHeight() - textSize.y) / 2 - 130
    };
    DrawTextEx(GetCustomFont(), "FUNNY CHEF", textPos, 200, 3, WHITE);

    DrawCenteredButton("PLAY", gameConfig.fontSizeHeader2 + 100, customColors.buttonBackgroundColor, WHITE, buttonRect);

    if (*isExitPopupOpen) {
        DrawExitConfirmation(isExitPopupOpen);
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

}
