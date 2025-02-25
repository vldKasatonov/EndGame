#include "../inc/header.h"

static void DrawExitConfirmation(bool *isExitPopupOpen, int *counter)
{
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
    DrawTextEx(GetCustomFont(), "Are you sure you want to quit?", textPos, 50, 3, WHITE);

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
            ResetGameTimer();
            currentState = LEVEL_MENU;
            *isExitPopupOpen = false;
            *counter = 0;
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

void renderGameplaySettings(GameTextures *textures, float *volumeMusic, float *volumeEffects, bool *isExitPopupOpen, int *counter) {
    int sliderWidth = 500;
    int sliderHeight = 30;
    int knobSize = 30;

    int centerX = gameConfig.screenWidth / 2;
    int centerY = gameConfig.screenHeight / 2;

    Rectangle sliderBarMusic = { centerX - sliderWidth / 2, centerY - 50, sliderWidth, sliderHeight };
    Rectangle sliderBarEffects = { centerX - sliderWidth / 2, centerY  + 90 , sliderWidth, sliderHeight };

    Rectangle sliderKnobMusic = { sliderBarMusic.x + (*volumeMusic) * sliderWidth - knobSize / 2,
                                  sliderBarMusic.y - (knobSize - sliderHeight) / 2,
                                  knobSize, knobSize };

    Rectangle sliderKnobEffects = { sliderBarEffects.x + (*volumeEffects) * sliderWidth - knobSize / 2,
                                    sliderBarEffects.y - (knobSize - sliderHeight) / 2,
                                    knobSize, knobSize };

    int iconSize = 50;
    Rectangle iconMusicRect = { sliderBarMusic.x - iconSize - 30, sliderBarMusic.y + (sliderHeight - iconSize) / 2, iconSize, iconSize };
    Rectangle iconEffectsRect = { sliderBarEffects.x - iconSize - 30, sliderBarEffects.y + (sliderHeight - iconSize) / 2, iconSize, iconSize };

    Vector2 mouse = GetMousePosition();


    sliderKnobMusic.x = sliderBarMusic.x + (*volumeMusic) * sliderWidth - knobSize / 2;
    sliderKnobEffects.x = sliderBarEffects.x + (*volumeEffects) * sliderWidth - knobSize / 2;

    float cornerRadius = 0.8f;
    int segments = 10;

    Rectangle filledBarMusic = { sliderBarMusic.x, sliderBarMusic.y, (*volumeMusic) * sliderWidth, sliderHeight };
    Rectangle filledBarEffects = { sliderBarEffects.x, sliderBarEffects.y, (*volumeEffects) * sliderWidth, sliderHeight };

    DrawRectangleRounded(sliderBarMusic, cornerRadius, segments, WHITE);
    DrawRectangleRounded(filledBarMusic, cornerRadius, segments, customColors.musicColor);
    DrawCircleV((Vector2){sliderKnobMusic.x + knobSize / 2, sliderKnobMusic.y + knobSize / 2}, knobSize * 0.65, customColors.sliderColor);
    DrawRectangleRounded(sliderBarEffects, cornerRadius, segments, WHITE);
    DrawRectangleRounded(filledBarEffects, cornerRadius, segments, customColors.musicColor);
    DrawCircleV((Vector2){sliderKnobEffects.x + knobSize / 2, sliderKnobEffects.y + knobSize / 2}, knobSize * 0.65, customColors.sliderColor);

    if (sliderKnobMusic.x <= sliderBarMusic.x) {
        DrawTexturePro(textures->music_off, (Rectangle){0, 0, textures->music_off.width, textures->music_off.height}, iconMusicRect, (Vector2){0, 0}, 0.0f, WHITE);
    } else {
        DrawTexturePro(textures->music_on, (Rectangle){0, 0, textures->music_on.width, textures->music_on.height}, iconMusicRect, (Vector2){0, 0}, 0.0f, WHITE);
    }

    if (sliderKnobEffects.x <= sliderBarEffects.x) {
        DrawTexturePro(textures->volume_off, (Rectangle){0, 0, textures->volume_off.width, textures->volume_off.height}, iconEffectsRect, (Vector2){0, 0}, 0.0f,WHITE);
    } else if (sliderKnobEffects.x <= sliderBarEffects.x + (sliderWidth / 2)) {
        DrawTexturePro(textures->volume_on2, (Rectangle){0, 0, textures->volume_on2.width, textures->volume_on2.height}, iconEffectsRect, (Vector2){0, 0}, 0.0f, WHITE);
    } else {
        DrawTexturePro(textures->volume_on, (Rectangle){0, 0, textures->volume_on.width, textures->volume_on.height}, iconEffectsRect, (Vector2){0, 0}, 0.0f, WHITE);
    }

    float textWidthMusic = MeasureText("Music Volume", gameConfig.fontSizeParagraph + 20);
    float textWidthEffects = MeasureText("Effects Volume", gameConfig.fontSizeParagraph + 20);
    Vector2 textPos_music = {(GetScreenWidth() - textWidthMusic) / 2, sliderBarMusic.y - 70};
    DrawTextEx(GetCustomFont(), "Music Volume", textPos_music, gameConfig.fontSizeParagraph + 20, 3, WHITE);
    Vector2 textPos_effects = {(GetScreenWidth() - textWidthEffects) / 2, sliderBarEffects.y - 70};
    DrawTextEx(GetCustomFont(), "Effects Volume", textPos_effects, gameConfig.fontSizeParagraph + 20, 3, WHITE);

    const char* buttonText = "GUIDE";
    iconSize += 40;
    int buttonX1 = (GetScreenWidth() - (MeasureText(buttonText, gameConfig.fontSizeParagraph + 100) + iconSize )) / 2 - 20;
    int buttonY1 = 150;
    int textWidth2 = MeasureText(buttonText, gameConfig.fontSizeHeader2 + 30);
    int buttonWidth2 = iconSize + textWidth2 + 190;
    int textOffsetX = buttonX1 + iconSize + 10;
    Rectangle guideButton = { buttonX1, buttonY1, buttonWidth2, 90 };
    Rectangle guideIconRect = { buttonX1, buttonY1 + (50 - iconSize) / 2 + 20, iconSize, iconSize };
    Rectangle guideTextRect = { textOffsetX, buttonY1 + (50 - gameConfig.fontSizeHeader2 + 30) / 2 - 5, textWidth2, 50 };
    DrawTexturePro(textures->guide, (Rectangle){0, 0, textures->guide.width, textures->guide.height}, guideIconRect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 textPos2 = { guideTextRect.x, guideTextRect.y - 40 };
    DrawTextEx(GetCustomFont(), buttonText, textPos2, gameConfig.fontSizeParagraph + 100, 3, WHITE);

    int buttonWidth3 = 220;
    int buttonHeight3 = 70;
    int buttonSpacing = 90;
    int totalButtonsWidth = buttonWidth3 * 2 + buttonSpacing;
    int buttonX2 = centerX - totalButtonsWidth / 2;
    int buttonY2 = sliderBarEffects.y + sliderHeight + 100;
    Rectangle resumeButton = { buttonX2, buttonY2, buttonWidth3, buttonHeight3 };
    Rectangle quitButton = { buttonX2 + buttonWidth3 + buttonSpacing, buttonY2, buttonWidth3, buttonHeight3 };
    float cornerRadius1 = 0.5f;
    DrawRectangleRounded(resumeButton, cornerRadius1, segments, customColors.musicColor);
    DrawRectangleRounded(quitButton, cornerRadius1, segments, customColors.musicColor);
    int newFontSize = gameConfig.fontSizeParagraph + 20;
    Vector2 textPos_resume = {
        resumeButton.x + (resumeButton.width - MeasureText("RESUME", newFontSize)) / 2 - 10,
        resumeButton.y + (resumeButton.height - newFontSize) / 2
    };
    DrawTextEx(GetCustomFont(), "RESUME", textPos_resume, newFontSize, 3, WHITE);
    Vector2 textPos_quit = {
        quitButton.x + (quitButton.width - MeasureText("QUIT", newFontSize)) / 2,
        quitButton.y + (quitButton.height - newFontSize) / 2
    };
    DrawTextEx(GetCustomFont(), "QUIT", textPos_quit, newFontSize, 3, WHITE);

    bool cursorChanged = false;
    if (!(*isExitPopupOpen)) {
        if (CheckCollisionPointRec(mouse, sliderKnobMusic) || CheckCollisionPointRec(mouse, sliderKnobEffects)) {
            cursorChanged = true;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(mouse, sliderBarMusic)) {
                cursorChanged = true;
                *volumeMusic = (mouse.x - sliderBarMusic.x) / sliderWidth;
                if (*volumeMusic < 0.0f) {
                    *volumeMusic = 0.0f;
                }
                if (*volumeMusic > 1.0f) {
                    *volumeMusic = 1.0f;
                }
                UpdateMusicVolume(*volumeMusic);
            }
            if (CheckCollisionPointRec(mouse, sliderBarEffects)) {
                cursorChanged = true;
                *volumeEffects = (mouse.x - sliderBarEffects.x) / sliderWidth;
                if (*volumeEffects < 0.0f) {
                    *volumeEffects = 0.0f;
                }
                if (*volumeEffects > 1.0f) {
                    *volumeEffects = 1.0f;
                }
                SetEffectsVolume(*volumeEffects);
            }
        }
        if (cursorChanged) {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
        } else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        if (CheckCollisionPointRec(mouse, guideButton)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            previousGuideState = currentState;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                PlaySoundEffect(buttonClick);
                currentState = GUIDE_PAGE1;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }

        if (CheckCollisionPointRec(mouse, resumeButton)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                PlaySoundEffect(buttonClick);
                currentState = GAMEPLAY;
            }
        }

        if (CheckCollisionPointRec(mouse, quitButton)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                PlaySoundEffect(buttonClick);
                *isExitPopupOpen = true;
            }
        }
    }
    if (*isExitPopupOpen) {
        DrawExitConfirmation(isExitPopupOpen, counter);
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}
