#include "../inc/header.h"

t_player_config player_config = {
    10.0f, // speed
    104,   // width
    20,    // height
};

static void updateGameplay(t_player* playerData, t_surface* surfaces, const int surface_count) {
    Vector2 newPos = playerData->position;

    if (IsKeyDown(KEY_W)) newPos.y -= player_config.speed;
    if (IsKeyDown(KEY_S)) newPos.y += player_config.speed;
    if (IsKeyDown(KEY_A)) newPos.x -= player_config.speed;
    if (IsKeyDown(KEY_D)) newPos.x += player_config.speed;

    bool collision = false;

    Rectangle playerHitbox = { newPos.x + 5, newPos.y + 8, 90, 1};
//    /////////////////
//    DrawRectangle(newPos.x + 5, newPos.y + 8, 90, 1, RED);

    for (int i = 0; i < surface_count; i++) {
        if (CheckCollisionRecs(playerHitbox, surfaces[i].rect)) {
            collision = true;
            break;
        }
    }

    if (!collision) {
        playerData->position = newPos;
    }
}

void mx_render_gameplay(t_player* playerData, t_game_textures* textures, bool* isPopupOpen, int* servedCounter, int maxServed) {
    Rectangle player = { playerData->position.x, playerData->position.y, player_config.player_width, player_config.player_height };

    float textureDrawX = playerData->position.x - textures->chef.width + player_config.player_width;
    float textureDrawY = playerData->position.y - textures->chef.height + player_config.player_height;

    // player movement and colission check
    if (!(*isPopupOpen)) {
        updateGameplay(playerData, surfaces, surface_count);
    }
    

    // draw surfaces
    for (int i = 0; i < surface_count; i++) {
        DrawRectangleRec(surfaces[i].rect, surfaces[i].color);
    }
    switch (level_number) {
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
    
    int interactableObject = mx_get_nearby_interactable(player, surfaces, surface_count);
    for (int i = 0; i < surface_count; i++) {
        if (CheckCollisionRecs(player, surfaces[i].rect)) {
            if (surfaces[i].type != NONE)
                DrawTexturePro(textures->f_button, (Rectangle) { 0, 0, textures->f_button.width, textures->f_button.height },
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
            mx_interact_with_object(&hotbar, surfaces[interactableObject].type);
        }
    }

    int pauseSize = 100;
    Rectangle gearRect = { game_config.screen_width - pauseSize - 30, 30, pauseSize, pauseSize };
    DrawTexturePro(textures->pause, (Rectangle){ 0, 0, textures->pause.width, textures->pause.height }, gearRect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;
    if (!(*isPopupOpen)) {
        if (CheckCollisionPointRec(mouse, gearRect)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursorChanged = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mx_play_sound_effect(button_click);
                current_state = GAMEPLAY_SETTINGS;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
        if (*servedCounter == maxServed) {
            mx_play_sound_effect(level_complete);
            *isPopupOpen = true;
        }
    }
    if (*isPopupOpen) {      
        mx_draw_level_sucsses(isPopupOpen, textures, servedCounter);
        mx_pause_game_timer();
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    mx_render_queue(player, isPopupOpen, servedCounter, textures);
}
