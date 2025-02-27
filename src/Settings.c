#include "../inc/header.h"

void resetGameProgress(t_level_stars *gameState) {
    char filename[50];

    for (int i = 0; i < 3; i++) {  
        snprintf(filename, sizeof(filename), "resource/best_time_level_%d.txt", i);
        remove(filename); 
    }

    printf("INFO: All best time files deleted\n");

    for (int i = 0; i < 3; i++) { 
        gameState->level_stars[i] = 0;
    }

    printf("INFO: Deleting progress and resetting stars\n");
}

void mx_render_settings(t_game_textures *textures, float *volumeMusic, float *volumeEffects, t_level_stars *gameState) {
    int sliderWidth = 500;
    int sliderHeight = 30;
    int knobSize = 30;

    int centerX = game_config.screen_width / 2;
    int centerY = game_config.screen_height / 2;

    Rectangle sliderBarMusic = { centerX - sliderWidth / 2, centerY - 100 - 50, sliderWidth, sliderHeight };
    Rectangle sliderBarEffects = { centerX - sliderWidth / 2, centerY + 40 - 30, sliderWidth, sliderHeight };

    Rectangle sliderKnobMusic = { sliderBarMusic.x + (*volumeMusic) * sliderWidth - knobSize / 2,
                                  sliderBarMusic.y - (knobSize - sliderHeight) / 2,
                                  knobSize, knobSize };

    Rectangle sliderKnobEffects = { sliderBarEffects.x + (*volumeEffects) * sliderWidth - knobSize / 2,
                                    sliderBarEffects.y - (knobSize - sliderHeight) / 2,
                                    knobSize, knobSize };

    int iconSize = 60;
    Rectangle iconMusicRect = { sliderBarMusic.x - iconSize - 35, sliderBarMusic.y + (sliderHeight - iconSize) / 2, iconSize, iconSize };
    Rectangle iconEffectsRect = { sliderBarEffects.x - iconSize - 30, sliderBarEffects.y + (sliderHeight - iconSize) / 2, iconSize, iconSize };

    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;

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
            mx_update_music_volume(*volumeMusic);
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
            mx_set_effects_volume(*volumeEffects);
        }
    }
    if (cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    sliderKnobMusic.x = sliderBarMusic.x + (*volumeMusic) * sliderWidth - knobSize / 2;
    sliderKnobEffects.x = sliderBarEffects.x + (*volumeEffects) * sliderWidth - knobSize / 2;

    float cornerRadius = 0.8f;
    int segments = 10;

    Rectangle filledBarMusic = { sliderBarMusic.x, sliderBarMusic.y, (*volumeMusic) * sliderWidth, sliderHeight };
    Rectangle filledBarEffects = { sliderBarEffects.x, sliderBarEffects.y, (*volumeEffects) * sliderWidth, sliderHeight };

    DrawRectangleRounded(sliderBarMusic, cornerRadius, segments, WHITE);
    DrawRectangleRounded(filledBarMusic, cornerRadius, segments, custom_colors.music_color);
    DrawCircleV((Vector2){sliderKnobMusic.x + knobSize / 2, sliderKnobMusic.y + knobSize / 2}, knobSize * 0.65, custom_colors.slider_color);
    DrawRectangleRounded(sliderBarEffects, cornerRadius, segments, WHITE);
    DrawRectangleRounded(filledBarEffects, cornerRadius, segments, custom_colors.music_color);
    DrawCircleV((Vector2){sliderKnobEffects.x + knobSize / 2, sliderKnobEffects.y + knobSize / 2}, knobSize * 0.65, custom_colors.slider_color);

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

    float textWidthMusic = MeasureText("Music Volume", game_config.font_size_paragraph + 20);
    float textWidthEffects = MeasureText("Effects Volume", game_config.font_size_paragraph + 20);
    Vector2 textPos_music = {(GetScreenWidth() - textWidthMusic) / 2 - 80, sliderBarMusic.y - 80};
    DrawTextEx(mx_get_custom_font(), "Music Volume", textPos_music, game_config.font_size_paragraph + 40, 3, WHITE);
    Vector2 textPos_effects = {(GetScreenWidth() - textWidthEffects) / 2 - 80, sliderBarEffects.y - 80};
    DrawTextEx(mx_get_custom_font(), "Effects Volume", textPos_effects, game_config.font_size_paragraph + 40, 3, WHITE);


    int textWidth = MeasureText("BACK", game_config.font_size_paragraph + 50);
    int button_height = 80;
    int iconWidth = textures->exit.width ;
    int iconHeight = textures->exit.height ;
    int button_width = iconWidth + textWidth + 80;
    Rectangle backButton = { 30, 40, button_width, button_height };
    Rectangle backTextRect = { backButton.x + textures->arrow.width + 5, backButton.y, textWidth, button_height };
    Rectangle backRect = { backButton.x , backButton.y + (button_height - iconHeight) / 2, iconWidth, iconHeight };
    DrawTexturePro(textures->arrow, (Rectangle){0, 0, textures->arrow.width, textures->arrow.height}, backRect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 textPos1 = { backTextRect.x, backTextRect.y - 10};
    DrawTextEx(mx_get_custom_font(), "BACK", textPos1, game_config.font_size_paragraph + 70, 3, WHITE);


    int buttonX2 = (1600 - (MeasureText("DELETE PROGRESS", game_config.font_size_paragraph + 20) + iconSize + 10)) / 2 - 90;
    int buttonY2 = sliderBarEffects.y + 150;
    int textOffsetX2 = buttonX2 + iconSize + 10;
    Rectangle deleteButton = { buttonX2, buttonY2, MeasureText("DELETE PROGRESS", game_config.font_size_paragraph + 31) + iconSize + 10, 50 };
    Rectangle deleteIconRect = { buttonX2, buttonY2 + (50 - iconSize) / 2 + 10, iconSize, iconSize };
    Rectangle deleteTextRect = { textOffsetX2, buttonY2 + (50 - game_config.font_size_paragraph + 15) / 2 - 5, MeasureText("DELETE PROGRESS", game_config.font_size_paragraph + 20), 50 };
    DrawTexturePro(textures->del_texture, (Rectangle){0, 0, textures->del_texture.width, textures->del_texture.height}, deleteIconRect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 textPos3 = {
        deleteTextRect.x,
        deleteTextRect.y - 10
    };
    DrawTextEx(mx_get_custom_font(), "DELETE PROGRESS", textPos3, game_config.font_size_paragraph + 30, 3, custom_colors.red_color);


    int buttonX1 = 1200;
    int buttonY1 = 780;
    iconSize += 20;
    const char* buttonText = "GUIDE";
    int textWidth2 = MeasureText(buttonText, game_config.font_size_header2 + 30) + 45;
    int buttonWidth2 = iconSize + textWidth2 + 55;
    int textOffsetX = buttonX1 + iconSize + 10;
    Rectangle guideButton = { buttonX1, buttonY1, buttonWidth2, 50 };
    Rectangle guideIconRect = { buttonX1, buttonY1 + (50 - iconSize) / 2 + 20, iconSize, iconSize };
    Rectangle guideTextRect = { textOffsetX, buttonY1 + (50 - game_config.font_size_header2 + 30) / 2 - 5, textWidth2, 50 };
    DrawTexturePro(textures->guide, (Rectangle){0, 0, textures->guide.width, textures->guide.height}, guideIconRect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 textPos2 = { guideTextRect.x, guideTextRect.y - 20 };
    DrawTextEx(mx_get_custom_font(), buttonText, textPos2, game_config.font_size_paragraph + 70, 3, WHITE);

    if (CheckCollisionPointRec(mouse, backButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = previous_state;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }

    if (CheckCollisionPointRec(mouse, deleteButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            resetGameProgress(gameState);
        }
    }

    if (CheckCollisionPointRec(mouse, guideButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        previous_guide_state = current_state;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = GUIDE_PAGE1;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }

    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }


}
