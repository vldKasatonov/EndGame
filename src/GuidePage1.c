#include "../inc/header.h"

void renderGuidePage1(GameTextures *textures) {
    int textWidthPage = MeasureText("PAGE 2", gameConfig.fontSizeParagraph + 70);
    int textHeightPage = MeasureText("PAGE 2", gameConfig.fontSizeParagraph + 5);
    Vector2 textPosPage = { 
        gameConfig.screenWidth - textWidthPage,
        gameConfig.screenHeight - textHeightPage
    };
    DrawTextEx(GetCustomFont(), "PAGE 1", textPosPage,
               gameConfig.fontSizeParagraph + 50, 3, WHITE);
    
        
    Rectangle rightArrow = { 1525 - 30, 450 - 30, 60, 60};
    DrawTexturePro(textures->right_arrow,(Rectangle){ 0, 0,
                   textures->right_arrow.width, textures->right_arrow.height },
                   rightArrow, (Vector2){0, 0}, 0.0f, WHITE);
                   
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

    DrawTexturePro(textures->guideJuice, (Rectangle) { 0, 0, textures->guideJuice.width, textures->guideJuice.height},
        (Rectangle) {
        178,  100, 1244, 700
    }, (Vector2) { 0, 0 }, 0.0f, WHITE);

    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;
    
    if (CheckCollisionPointRec(mouse, backButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySoundEffect(buttonClick);
            currentState = previousGuideState;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointRec(mouse, rightArrow)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
	    PlaySoundEffect(buttonClick);
            currentState = GUIDE_PAGE2;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}
