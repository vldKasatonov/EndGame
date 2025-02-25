#include "../inc/header.h"

PlayerConfig playerConfig = {
    10.0f, // speed
    104,   // width
    20,    // height
};

static void updateGameplay(Player* playerData, Surface* surfaces, const int surfaceCount) {
    Vector2 newPos = playerData->position;

    if (IsKeyDown(KEY_W)) newPos.y -= playerConfig.speed;
    if (IsKeyDown(KEY_S)) newPos.y += playerConfig.speed;
    if (IsKeyDown(KEY_A)) newPos.x -= playerConfig.speed;
    if (IsKeyDown(KEY_D)) newPos.x += playerConfig.speed;

    bool collision = false;

    Rectangle playerHitbox = { newPos.x + 5, newPos.y + 8, 90, 1};
//    /////////////////
//    DrawRectangle(newPos.x + 5, newPos.y + 8, 90, 1, RED);

    for (int i = 0; i < surfaceCount; i++) {
        if (CheckCollisionRecs(playerHitbox, surfaces[i].rect)) {
            collision = true;
            break;
        }
    }

    if (!collision) {
        playerData->position = newPos;
    }
}

void renderGameplay(Player* playerData, GameTextures* textures, bool* isPopupOpen, int* servedCounter, int maxServed) {
    Rectangle player = { playerData->position.x, playerData->position.y, playerConfig.playerWidth, playerConfig.playerHeight };

    float textureDrawX = playerData->position.x - textures->chef.width + playerConfig.playerWidth;
    float textureDrawY = playerData->position.y - textures->chef.height + playerConfig.playerHeight;

    // player movement and colission check
    if (!(*isPopupOpen)) {
        updateGameplay(playerData, surfaces, surfaceCount);
    }
    

    // draw surfaces
    for (int i = 0; i < surfaceCount; i++) {
        DrawRectangleRec(surfaces[i].rect, surfaces[i].color);
    }
    switch (levelNumber) {
        case 1:
            DrawTexture(textures->map1, 0, 0, WHITE);
            break;
        case 2:
            DrawTexture(textures->map2, 0, 0, WHITE);
            break;
        case 3:
            DrawTexture(textures->map3, 0, 0, WHITE);
            break;
        default:
          break;
    }
//    DrawTexture(textures->map3, 0, 0, WHITE);
    // draw player
    DrawTexture(textures->chef, textureDrawX, textureDrawY, WHITE);

//    ////////////
//    DrawRectangle(player.x, player.y, player.width, player.height, BLUE);
    
    int interactableObject = getNearbyInteractable(player, surfaces, surfaceCount);
    for (int i = 0; i < surfaceCount; i++) {
        if (CheckCollisionRecs(player, surfaces[i].rect)) {
            if (surfaces[i].type != NONE)
                DrawTexturePro(textures->fButton, (Rectangle) { 0, 0, textures->fButton.width, textures->fButton.height },
                    (Rectangle) {
                surfaces[i].rect.x + surfaces[i].rect.width - 100, surfaces[i].rect.y - 50, 150, 150
            }, (Vector2) { 0, 0 }, 0.0f, WHITE);
                //DrawText("F", surfaces[i].rect.x - 10, surfaces[i].rect.y - 10, 20, BLACK);
            break;
        }
    }
    // interacting with objects
    if (interactableObject != -1 && !(*isPopupOpen)) {
        if (IsKeyPressed(KEY_F)) {
            interactWithObject(&hotbar, surfaces[interactableObject].type);
        }
    }

    int pauseSize = 100;
    Rectangle gearRect = { gameConfig.screenWidth - pauseSize - 30, 30, pauseSize, pauseSize };
    DrawTexturePro(textures->pause, (Rectangle){ 0, 0, textures->pause.width, textures->pause.height }, gearRect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;
    if (!(*isPopupOpen)) {
        if (CheckCollisionPointRec(mouse, gearRect)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                PlaySoundEffect(buttonClick);
                currentState = GAMEPLAY_SETTINGS;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
        if (*servedCounter == maxServed) {
            PlaySoundEffect(levelComplete);
            *isPopupOpen = true;
        }
    }
    if (*isPopupOpen) {      
        DrawLevelSucsses(isPopupOpen, textures, servedCounter);
        PauseGameTimer();
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    renderQueue(player, isPopupOpen, servedCounter, textures);
}
