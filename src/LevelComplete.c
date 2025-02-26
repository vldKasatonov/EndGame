#include "../inc/header.h"

void drawStars_gameplay(int space, double elapsedTime, GameTextures *textures, Vector2 circle) {
    Rectangle starRec = { 225, 390, 75, 75 };
    Rectangle srcStar = { 0, 0, textures->star.width, textures->star.height };

    Color starColors[3] = {
        customColors.nonactiveStarColor,
        customColors.nonactiveStarColor,
        customColors.nonactiveStarColor
    };

    if (elapsedTime > 1.0) {
        if (elapsedTime <= 120.0) {
            starColors[0] = customColors.activeStarColor;
            starColors[1] = customColors.activeStarColor;
            starColors[2] = customColors.activeStarColor;
        } else if (elapsedTime <= 180.0) {
            starColors[0] = customColors.activeStarColor;
            starColors[1] = customColors.activeStarColor;
            starColors[2] = customColors.nonactiveStarColor;
        } else if (elapsedTime <= 300.0) {
            starColors[0] = customColors.activeStarColor;
            starColors[1] = customColors.nonactiveStarColor;
            starColors[2] = customColors.nonactiveStarColor;
        }
    }
    for (int i = 0; i < 3; ++i) {
        float offsetX = circle.x + (i * (starRec.width + space));
        DrawTexturePro(textures->star, srcStar, (Rectangle){ offsetX, circle.y, starRec.width, starRec.height },
                       (Vector2){ 0, 0 }, 0.0f, starColors[i]);
    }
}

void DisableGameplayInput(bool isPopupOpen) {
    if (currentState == GAMEPLAY && isPopupOpen) {
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

void DrawLevelSucsses(bool *isExitPopupOpen, GameTextures *textures, int *servedCounter) {
    int popupWidth = 900;
    int popupHeight = 500;
    Rectangle popupRect = {
        (GetScreenWidth() - popupWidth) / 2,
        (GetScreenHeight() - popupHeight) / 2,
        popupWidth,
        popupHeight
    };

    DrawRectangleRounded(popupRect, 0.5f, 10, customColors.buttonBackgroundColor);
    DrawRectangleRoundedLinesEx(popupRect, 0.5f, 10, 5, WHITE);

    Vector2 textSize = MeasureTextEx(GetCustomFont(), "Congratulations!", 70, 3);
    Vector2 textPos = {
        popupRect.x + (popupRect.width - textSize.x) / 2,
        popupRect.y + 60
    };
    DrawTextEx(GetCustomFont(), "Congratulations!", textPos, 70, 3, WHITE);

    double elapsedTime = GetElapsedTime();
    Vector2 popupCenter = { popupRect.x + popupWidth / 2 - 130 , popupRect.y + popupHeight / 2 - 90};
    int space = 10;
    drawStars_gameplay(space, elapsedTime, textures, popupCenter);

    int minutes = (int)(elapsedTime / 60);
    int seconds = (int)(elapsedTime) % 60;
    char yourTime[10];
    snprintf(yourTime, sizeof(yourTime), "%02d:%02d", minutes, seconds);
    Vector2 timeTextSize = MeasureTextEx(GetCustomFont(), "Your time", 50, 3);
    Vector2 timeTextPos = {
        popupRect.x + (popupRect.width - timeTextSize.x) / 2,
        popupRect.y + 260
    };
    DrawTextEx(GetCustomFont(), "Your time", timeTextPos, 50, 3, WHITE);
    Vector2 yourTimeSize = MeasureTextEx(GetCustomFont(), yourTime, 50, 3);
    Vector2 yourTimePos = {
        popupRect.x + (popupRect.width - yourTimeSize.x) / 2,
        popupRect.y + 320
    };
    DrawTextEx(GetCustomFont(), yourTime, yourTimePos, 50, 3, WHITE);

    Rectangle okeyButton = { popupRect.x + (popupRect.width - 150) / 2, popupRect.y + popupHeight - 100, 150, 60 };
    DrawRectangleRounded(okeyButton, 0.5f, 10, GREEN);
    Vector2 okeyTextSize = MeasureTextEx(GetCustomFont(), "OK", 40, 3);
    Vector2 okeyTextPos = {
        okeyButton.x + (okeyButton.width - okeyTextSize.x) / 2,
        okeyButton.y + (okeyButton.height - okeyTextSize.y) / 2
    };
    DrawTextEx(GetCustomFont(), "OK", okeyTextPos, 40, 3, WHITE);

    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;
    if (CheckCollisionPointRec(mouse, okeyButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySoundEffect(buttonClick);
            currentState = LEVEL_MENU;
            *isExitPopupOpen = false;
            SaveBestTime();
            ResumeGameTimer();
            *servedCounter = 0;
        }
    }

    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

void updateLevelStars(Level_stars *gameState, int level, int stars) {
    if (level >= 0 && level < NUM_LEVELS) {
        gameState->levelStars[level] = stars;
    }
}

int calculateStarsForLevel(void) {
    double bestTime = GetBestTime();
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
