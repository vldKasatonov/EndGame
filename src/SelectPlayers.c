#include "../inc/header.h"

void renderSelectPlayer(GameTextures *textures) {
    Vector2 circle = { gameConfig.screenWidth / 3,
    		      gameConfig.screenHeight / 2 };
    int radius = 200;
    Color non_acctive = { 0, 0, 0, 100};

    DrawCircleV(circle, radius, customColors.buttonBackgroundColor);
    DrawCircle(gameConfig.screenWidth - circle.x, circle.y,
    	       radius, customColors.levelRectangleColor);
    DrawCircle(gameConfig.screenWidth - circle.x, circle.y,
    	       radius, non_acctive);
    
    int player_icon_size = 270;
    int half_size_icon = player_icon_size / 2;
    Rectangle one_player_icon_rect = { circle.x - half_size_icon, circle.y
    				      - half_size_icon, player_icon_size,
    				      player_icon_size };
    DrawTexturePro(textures->one_player, (Rectangle){ 0, 0,
    		   textures->one_player.width, textures->one_player.height },
    		   one_player_icon_rect, (Vector2){0, 0}, 0.0f, WHITE);
    int text_player1 = MeasureText("1 PLAYER", gameConfig.fontSizeParagraph + 40);
    Vector2 textPos_one = {
        circle.x - text_player1 / 2 - 10,
        circle.y + 230
    };
    DrawTextEx(GetCustomFont(), "1 PLAYER", textPos_one, gameConfig.fontSizeParagraph + 40, 3, WHITE);
    
    Rectangle two_players_icon_rect = { gameConfig.screenWidth - circle.x -
    				       half_size_icon, circle.y - half_size_icon,
    				       player_icon_size, player_icon_size };
    DrawTexturePro(textures->two_players, (Rectangle){ 0, 0,
    		   textures->two_players.width, textures->two_players.height },
    		   two_players_icon_rect, (Vector2){0, 0}, 0.0f, WHITE);
    
    int text_player2 = MeasureText("2 PLAYERS", gameConfig.fontSizeParagraph + 40);
    Vector2 textPos_two = {
        gameConfig.screenWidth - circle.x - text_player2 / 2 - 2,
        circle.y + 230
    };
    DrawTextEx(GetCustomFont(), "2 PLAYERS", textPos_two, gameConfig.fontSizeParagraph + 40, 3, WHITE);
  
    int textWidth = MeasureText("BACK", gameConfig.fontSizeParagraph + 50);
    int buttonHeight = 80;
    int iconWidth = textures->exit.width ;
    int iconHeight = textures->exit.height ;
    int buttonWidth = iconWidth + textWidth + 80;
    Rectangle backButton = { 30, 40, buttonWidth, buttonHeight };
    Rectangle backTextRect = { backButton.x + textures->arrow.width + 5, backButton.y, textWidth, buttonHeight };
    Rectangle backRect = { backButton.x , backButton.y + (buttonHeight - iconHeight) / 2, iconWidth, iconHeight };
    DrawTexturePro(textures->arrow, (Rectangle){0, 0, textures->arrow.width, textures->arrow.height}, backRect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 textPos1 = { backTextRect.x, backTextRect.y - 10};
    DrawTextEx(GetCustomFont(), "BACK", textPos1, gameConfig.fontSizeParagraph + 70, 3, WHITE);
    
    int gearSize = 115;
    Rectangle gearRect = { gameConfig.screenWidth - gearSize - 30, 20, gearSize, gearSize };
    DrawTexturePro(textures->gearTexture, (Rectangle){ 0, 0, textures->gearTexture.width, textures->gearTexture.height }, gearRect, (Vector2){0, 0}, 0.0f, WHITE);

    bool cursorChanged = false;
    Vector2 mouse = GetMousePosition();
    
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
            currentState = MAIN_MENU;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }

    if (CheckCollisionPointCircle(mouse, circle, radius)) {
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
