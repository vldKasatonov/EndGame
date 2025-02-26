#include "../inc/header.h"

HotbarConfig hotbarConfig = {
    75, // cellWidth
    75, // cellheight
    15, // margin
    (Color) { 255, 255, 255, 200 }, // cellColor
    (Color) { 169, 169, 169, 200 }, // cellBorderColor
    (Color) { 255, 0, 0, 200 }      // cellBorderColorActive
};

static void updateHotbar(void) {
    if (IsKeyDown(KEY_ONE)) hotbar.activeItem = 0;
    if (IsKeyDown(KEY_TWO)) hotbar.activeItem = 1;
    if (IsKeyDown(KEY_THREE)) hotbar.activeItem = 2;
    if (IsKeyDown(KEY_FOUR)) hotbar.activeItem = 3;
    if (IsKeyDown(KEY_FIVE)) hotbar.activeItem = 4;
    if (IsKeyDown(KEY_SIX)) hotbar.activeItem = 5;
    if (IsKeyDown(KEY_SEVEN)) hotbar.activeItem = 6;
    if (GetMouseWheelMove() > 0) {
        if (hotbar.activeItem == 0)
            hotbar.activeItem = 6;
        else
            hotbar.activeItem -= 1;
    }
    if (GetMouseWheelMove() < 0) {
        if (hotbar.activeItem == 6)
            hotbar.activeItem = 0;
        else
            hotbar.activeItem += 1;
    }
}

static const char* getActiveIngredientName(Item* item) {
    static char buffer[50];
    const char* stateStr;
    const char* typeStr;

    switch (item->state) {
    case DIRTY:   stateStr = "Dirty"; break;
    case CLEAN:   stateStr = "Washed"; break;
    case PEELED:  stateStr = "Peeled"; break;
    case JUICED:  stateStr = "Juiced"; break;
    case FRIED:   stateStr = "Fryied"; break;
    case SLICED:  stateStr = "Sliced"; break;
    default:      stateStr = ""; break;
    }

    switch (item->type) {
    case APPLE:    typeStr = "apple"; break;
    case POTATO:   typeStr = "potato"; break;
    case CUCUMBER: typeStr = "cucumber"; break;
    case TOMATO:   typeStr = "tomato"; break;
    case SALAD:    typeStr = "salad"; break;
    default:       typeStr = "unknown"; break;
    }

    snprintf(buffer, sizeof(buffer), "%s %s", stateStr, typeStr);
    return buffer;
}

static void drawHotbarText(const char* text) {
    int screenWidth = GetScreenWidth();
    int fontSize = 20;

    int textWidth = MeasureText(text, fontSize);
    int xPos = (screenWidth / 2) - (textWidth / 2);

    DrawText(text, xPos, 750, fontSize, BLACK);
}

static void drawIngredient(Rectangle rect, Item* item, GameTextures *textures) {
    switch (item->type) {
        case POTATO:
            if (item->state == DIRTY) {
                // DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, (Color) { 64, 52, 0, 255 });
                DrawTexturePro(textures->dirtyPotato, (Rectangle) { 0, 0, textures->dirtyPotato.width, textures->dirtyPotato.height },
                    (Rectangle) {
                    rect.x + 2.5, rect.y + 2.5, 70, 70
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == CLEAN) {
              // DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, (Color) { 105, 52, 0, 255 });
               DrawTexturePro(textures->washedPotato, (Rectangle) { 0, 0, textures->washedPotato.width, textures->washedPotato.height },
                   (Rectangle) {
                   rect.x + 2.5, rect.y + 2.5, 70, 70
               }, (Vector2) { 0, 0 }, 0.0f, WHITE);
               
            }
            else if (item->state == PEELED) {
               // DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, YELLOW);
                DrawTexturePro(textures->peeledPotato, (Rectangle) { 0, 0, textures->peeledPotato.width, textures->peeledPotato.height },
                    (Rectangle) {
                    rect.x + 2.5, rect.y + 5, 70, 70
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == SLICED) {
               // DrawRectangle(rect.x + 30, rect.y + 30, 10, 20, YELLOW);
               // DrawRectangle(rect.x + 50, rect.y + 30, 10, 20, YELLOW);
                DrawTexturePro(textures->slicedPotato, (Rectangle) { 0, 0, textures->slicedPotato.width, textures->slicedPotato.height },
                    (Rectangle) {
                    rect.x + 5, rect.y + 10, 65, 65
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else {
                // DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, BLACK);
                DrawTexturePro(textures->friedPotato, (Rectangle) { 0, 0, textures->friedPotato.width, textures->friedPotato.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 85
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            break;

        case TOMATO:
            if (item->state == DIRTY) {
                //DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, DARKPURPLE);
                DrawTexturePro(textures->dirtyTomato, (Rectangle) { 0, 0, textures->dirtyTomato.width, textures->dirtyTomato.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == CLEAN) {
               // DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, RED);
                DrawTexturePro(textures->washedTomato, (Rectangle) { 0, 0, textures->washedTomato.width, textures->washedTomato.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else {
                //DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, BLACK);
                DrawTexturePro(textures->slicedTomato, (Rectangle) { 0, 0, textures->slicedTomato.width, textures->slicedTomato.height },
                    (Rectangle) {
                    rect.x + 5, rect.y + 5, 70, 70
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            break;
        case CUCUMBER:
            if (item->state == DIRTY) {
                //DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, DARKPURPLE);
                DrawTexturePro(textures->dirtyCucumber, (Rectangle) { 0, 0, textures->dirtyCucumber.width, textures->dirtyCucumber.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == CLEAN) {
                // DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, RED);
                DrawTexturePro(textures->washedCucumber, (Rectangle) { 0, 0, textures->washedCucumber.width, textures->washedCucumber.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else {
                //DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, BLACK);
                DrawTexturePro(textures->slicedCucumber, (Rectangle) { 0, 0, textures->slicedCucumber.width, textures->slicedCucumber.height },
                    (Rectangle) {
                    rect.x + 3, rect.y + 5, 65, 65
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            break;
        case SALAD:
            if (item->state == MIXED) {
                //DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, DARKPURPLE);
                DrawTexturePro(textures->salad, (Rectangle) { 0, 0, textures->salad.width, textures->salad.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            break;
        case APPLE:
            if (item->state == DIRTY) {
                //DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, (Color) { 102, 0, 0, 255 });
                DrawTexturePro(textures->dirtyApple, (Rectangle) { 0, 0, textures->dirtyApple.width, textures->dirtyApple.height },
                    (Rectangle) { rect.x, rect.y, 75, 75 }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == CLEAN) {
                //DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, (Color) { 255, 0, 0, 255 });
                DrawTexturePro(textures->washedApple, (Rectangle) { 0, 0, textures->washedApple.width, textures->washedApple.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == SLICED) {
                //DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, (Color) { 240, 190, 0, 255 });
                DrawTexturePro(textures->slicedApple, (Rectangle) { 0, 0, textures->slicedApple.width, textures->slicedApple.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else {
               // DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, BLACK);
                DrawTexturePro(textures->juice, (Rectangle) { 0, 0, textures->juice.width, textures->juice.height },
                    (Rectangle) {
                    rect.x + 5, rect.y + 5, 65, 65
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
        default:
            break;
    }
}

void renderHotbar(GameTextures *textures) {
    int hotbarCellWidth = hotbarConfig.cellWidth;
    int hotbarCellHeight = hotbarConfig.cellHeight;
    int margin = hotbarConfig.margin;
    int startPositionX = (gameConfig.screenWidth - (hotbarCellWidth * INVENTORY_SIZE + margin * (INVENTORY_SIZE - 1))) / 2;

    updateHotbar();
    
    // draw active item name
    if (hotbar.items[hotbar.activeItem]) {
        const char* activeIngredient = getActiveIngredientName(hotbar.items[hotbar.activeItem]);
        drawHotbarText(activeIngredient);
    }
    
    // draw hotbar cells
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        Rectangle rect = { startPositionX, 780, hotbarCellWidth, hotbarCellHeight };

        // draw a cell
        DrawRectangleRec(rect, hotbarConfig.cellColor);

        // highlight an active cell
        if (hotbar.activeItem == i) {
            DrawRectangleLinesEx(rect, 5, hotbarConfig.cellBorderColorActive);
        }
        else {
            DrawRectangleLinesEx(rect, 3, hotbarConfig.cellBorderColor);
        }

        if (hotbar.items[i] != NULL) {
            // draw ingredient icon
            drawIngredient(rect, hotbar.items[i], textures);
        }

        startPositionX += margin + hotbarCellWidth;
    }
}
