#include "../inc/header.h"

extern int currentLevel;

static void resetPlayerData(t_player* playerData) {
    Vector2 pos = { 300, 350 };
    playerData->position = pos;
}

void mx_render_level_menu(t_game_textures* textures, t_level_stars* gameState, t_player* player) {
    int space = 450;
    Vector2 circle = { 350, 475 };
    int radius = 50;
    Rectangle mainRec = { 150, 250, 400, 450 };

    double bestTimes[3];
    for (int i = 0; i < 3; i++) {
        currentLevel = i;
        mx_load_best_time();    bestTimes[i] = mx_get_best_time();
    }
    char bestTimeText[3][11];
    for (int i = 0; i < 3; i++) {
        if (bestTimes[i] <= 0) {
            snprintf(bestTimeText[i], sizeof(bestTimeText[i]), " - - : - -");
        }
        else {
            int bestMin = (int)bestTimes[i] / 60;
            int bestSec = (int)bestTimes[i] % 60;
            snprintf(bestTimeText[i], sizeof(bestTimeText[i]), "%02d:%02d", bestMin, bestSec);
            int starsEarned = mx_calculate_stars_for_level();
            mx_update_level_stars(gameState, i, starsEarned);
        }
    }
    int level1Stars = gameState->level_stars[0];
    int level2Stars = gameState->level_stars[1];
    int level3Stars = gameState->level_stars[2];

    mx_draw_level(0, level1Stars, textures, textures->image1, circle);
    mx_draw_level(space, level2Stars, textures, textures->image2, circle);
    mx_draw_level(space * 2, level3Stars, textures, textures->image3, circle);

    Rectangle rightArrow = { 1525 - 30, circle.y - 30, 60, 60 };
    DrawTexturePro(textures->right_arrow, (Rectangle) {
        0, 0,
            textures->right_arrow.width, textures->right_arrow.height
    },
        rightArrow, (Vector2) { 0, 0 }, 0.0f, WHITE);
    mx_draw_text(0, mainRec, circle, "LEVEL 1", bestTimeText[0]);
    mx_draw_text(space, mainRec, circle, "LEVEL 2", bestTimeText[1]);    
    mx_draw_text(space * 2, mainRec, circle, "LEVEL 3", bestTimeText[2]);
    //mx_toned_rect(space);
    /*mx_toned_rect(space * 2);*/
      
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
    
    int gearSize = 115;
    Rectangle gearRect = { game_config.screen_width - gearSize - 30, 20, gearSize, gearSize };
    DrawTexturePro(textures->settings, (Rectangle){ 0, 0,
    		   textures->settings.width, textures->settings.height },
    		   gearRect, (Vector2){0, 0}, 0.0f, WHITE);
    
    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;
        
    if (CheckCollisionPointRec(mouse, gearRect)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            previous_state = current_state;
            current_state = SETTINGS;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }  
    if (CheckCollisionPointRec(mouse, backButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = SELECT_PLAYER;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointCircle(mouse, circle, radius)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            
            currentLevel = 0;
            mx_load_best_time();
            mx_start_game_timer();
            current_state = GAMEPLAY;

            resetPlayerData(player);
            mx_initialize_surfaces(&level_data[0]);
            mx_initialize_inventory(&hotbar);            //
            mx_initialize_queue(&queue);                 // gameplay initializers
            mx_initialize_level(&level_data[0], &level);  //
            level_number = 1;

            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointCircle(mouse, (Vector2){ circle.x + space, circle.y }, radius)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            
            currentLevel = 1;
            mx_load_best_time();
            mx_start_game_timer();
            current_state = GAMEPLAY;

            resetPlayerData(player);
            mx_initialize_surfaces(&level_data[1]);
            mx_initialize_inventory(&hotbar);            //
            mx_initialize_queue(&queue);                 // gameplay initializers
            mx_initialize_level(&level_data[1], &level);  //
            level_number = 2;

            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointCircle(mouse, (Vector2) { circle.x + space * 2, circle.y }, radius)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            
            currentLevel = 2;
            mx_load_best_time();
            mx_start_game_timer();
            current_state = GAMEPLAY;

            resetPlayerData(player);
            mx_initialize_surfaces(&level_data[2]);
            mx_initialize_inventory(&hotbar);            //
            mx_initialize_queue(&queue);                 // gameplay initializers
            mx_initialize_level(&level_data[2], &level);  //
            level_number = 3;

            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointRec(mouse, rightArrow)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
	    mx_play_sound_effect(button_click);
            current_state = LEVEL_MENU2;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

}
