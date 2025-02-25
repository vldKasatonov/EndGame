#include "../inc/header.h"

void renderLevelMenu2(GameTextures *textures) {
    int space = 450;
    Vector2 circle = { 350, 475 };
    Rectangle mainRec = { 150, 250, 400, 450 };
    
    drawLevel(0, 0, textures, textures->level_preview, circle);
    drawLevel(space, 0, textures,textures->level_preview, circle);
    drawLevel(space * 2, 0, textures, textures->level_preview, circle);
        
    Rectangle leftArrow = { 75 - 30, circle.y - 30, 60, 60};
    DrawTexturePro(textures->left_arrow,(Rectangle){ 0, 0,
                   textures->left_arrow.width, textures->left_arrow.height },
                   leftArrow, (Vector2){0, 0}, 0.0f, WHITE);
    
    drawText(0, mainRec, circle, "LEVEL 4", " - - : - -");   
    drawText(space, mainRec, circle, "LEVEL 5", " - - : - -");
    drawText(space * 2, mainRec, circle, "LEVEL 6", " - - : - -");
    tonedRect(0);
    tonedRect(space);
    tonedRect(space * 2);
      
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
    
    int gearSize = 115;
    Rectangle gearRect = { gameConfig.screenWidth - gearSize - 30, 20, gearSize, gearSize };
    DrawTexturePro(textures->gearTexture, (Rectangle){ 0, 0,
    		   textures->gearTexture.width, textures->gearTexture.height },
    		   gearRect, (Vector2){0, 0}, 0.0f, WHITE);
    
    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;
        
    if (CheckCollisionPointRec(mouse, gearRect)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySoundEffect(buttonClick);
            previousState = currentState;
            currentState = SETTINGS;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }  
    if (CheckCollisionPointRec(mouse, backButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySoundEffect(buttonClick);
            currentState = SELECT_PLAYER;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointRec(mouse, leftArrow)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySoundEffect(buttonClick);
            currentState = LEVEL_MENU;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    } 
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

}
