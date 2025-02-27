#include "../inc/header.h"

void mx_render_guide_page1(t_game_textures *textures) {
    int textWidthPage = MeasureText("PAGE 2", game_config.font_size_paragraph + 70);
    int textHeightPage = MeasureText("PAGE 2", game_config.font_size_paragraph + 5);
    Vector2 textPosPage = { 
        game_config.screen_width - textWidthPage,
        game_config.screen_height - textHeightPage
    };
    DrawTextEx(mx_get_custom_font(), "PAGE 1", textPosPage,
               game_config.font_size_paragraph + 50, 3, WHITE);
    
        
    Rectangle rightArrow = { 1525 - 30, 450 - 30, 60, 60};
    DrawTexturePro(textures->right_arrow,(Rectangle){ 0, 0,
                   textures->right_arrow.width, textures->right_arrow.height },
                   rightArrow, (Vector2){0, 0}, 0.0f, WHITE);
                   
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

    DrawTexturePro(textures->guide_juice, (Rectangle) { 0, 0, textures->guide_juice.width, textures->guide_juice.height},
        (Rectangle) {
        178,  100, 1244, 700
    }, (Vector2) { 0, 0 }, 0.0f, WHITE);

    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;
    
    if (CheckCollisionPointRec(mouse, backButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = previous_guide_state;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointRec(mouse, rightArrow)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
	    mx_play_sound_effect(button_click);
            current_state = GUIDE_PAGE2;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}
