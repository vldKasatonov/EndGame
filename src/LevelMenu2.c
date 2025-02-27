#include "../inc/header.h"

void mx_render_level_menu2(t_game_textures *textures) {
    int space = 450;
    Vector2 circle = { 350, 475 };
    Rectangle mainRec = { 150, 250, 400, 450 };
    
    mx_draw_level(0, 0, textures, textures->level_preview, circle);
    mx_draw_level(space, 0, textures,textures->level_preview, circle);
    mx_draw_level(space * 2, 0, textures, textures->level_preview, circle);
        
    Rectangle leftArrow = { 75 - 30, circle.y - 30, 60, 60};
    DrawTexturePro(textures->left_arrow,(Rectangle){ 0, 0,
                   textures->left_arrow.width, textures->left_arrow.height },
                   leftArrow, (Vector2){0, 0}, 0.0f, WHITE);
    
    mx_draw_text(0, mainRec, circle, "LEVEL 4", " - - : - -");   
    mx_draw_text(space, mainRec, circle, "LEVEL 5", " - - : - -");
    mx_draw_text(space * 2, mainRec, circle, "LEVEL 6", " - - : - -");
    mx_toned_rect(0);
    mx_toned_rect(space);
    mx_toned_rect(space * 2);
      
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
    if (CheckCollisionPointRec(mouse, leftArrow)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = LEVEL_MENU;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    } 
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

}
