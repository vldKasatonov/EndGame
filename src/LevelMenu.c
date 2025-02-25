#include "../inc/header.h"

extern int currentLevel;

static void resetPlayerData(Player* playerData) {
    Vector2 pos = { 300, 350 };
    playerData->position = pos;
}

void renderLevelMenu(GameTextures* textures, Level_stars* gameState, Player* player) {
    int space = 450;
    Vector2 circle = { 350, 475 };
    int radius = 50;
    Rectangle mainRec = { 150, 250, 400, 450 };

    double bestTimes[3];
    for (int i = 0; i < 3; i++) {
        currentLevel = i;
        LoadBestTime();    bestTimes[i] = GetBestTime();
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
            int starsEarned = calculateStarsForLevel();
            updateLevelStars(gameState, i, starsEarned);
        }
    }
    int level1Stars = gameState->levelStars[0];
    int level2Stars = gameState->levelStars[1];
    int level3Stars = gameState->levelStars[2];

    drawLevel(0, level1Stars, textures, textures->image1, circle);
    drawLevel(space, level2Stars, textures, textures->image2, circle);
    drawLevel(space * 2, level3Stars, textures, textures->image3, circle);

    Rectangle rightArrow = { 1525 - 30, circle.y - 30, 60, 60 };
    DrawTexturePro(textures->right_arrow, (Rectangle) {
        0, 0,
            textures->right_arrow.width, textures->right_arrow.height
    },
        rightArrow, (Vector2) { 0, 0 }, 0.0f, WHITE);
    drawText(0, mainRec, circle, "LEVEL 1", bestTimeText[0]);
    drawText(space, mainRec, circle, "LEVEL 2", bestTimeText[1]);    
    drawText(space * 2, mainRec, circle, "LEVEL 3", bestTimeText[2]);
    //tonedRect(space);
    /*tonedRect(space * 2);*/
      
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
    if (CheckCollisionPointCircle(mouse, circle, radius)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySoundEffect(buttonClick);
            
            currentLevel = 0;
            LoadBestTime();
            StartGameTimer();
            currentState = GAMEPLAY;

            resetPlayerData(player);
            initializeSurfaces(&levelData[0]);
            initializeInventory(&hotbar);            //
            initializeQueue(&queue);                 // gameplay initializers
            initializeLevel(&levelData[0], &level);  //
            levelNumber = 1;

            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointCircle(mouse, (Vector2){ circle.x + space, circle.y }, radius)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySoundEffect(buttonClick);
            
            currentLevel = 1;
            LoadBestTime();
            StartGameTimer();
            currentState = GAMEPLAY;

            resetPlayerData(player);
            initializeSurfaces(&levelData[1]);
            initializeInventory(&hotbar);            //
            initializeQueue(&queue);                 // gameplay initializers
            initializeLevel(&levelData[1], &level);  //
            levelNumber = 2;

            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointCircle(mouse, (Vector2) { circle.x + space * 2, circle.y }, radius)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            PlaySoundEffect(buttonClick);
            
            currentLevel = 2;
            LoadBestTime();
            StartGameTimer();
            currentState = GAMEPLAY;

            resetPlayerData(player);
            initializeSurfaces(&levelData[2]);
            initializeInventory(&hotbar);            //
            initializeQueue(&queue);                 // gameplay initializers
            initializeLevel(&levelData[2], &level);  //
            levelNumber = 3;

            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointRec(mouse, rightArrow)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
	    PlaySoundEffect(buttonClick);
            currentState = LEVEL_MENU2;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

}
