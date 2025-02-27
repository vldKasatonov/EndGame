#include "../inc/header.h"

t_hotbar_config hotbar_config = {
    75, // cell_width
    75, // cellheight
    15, // margin
    (Color) { 255, 255, 255, 200 }, // cell_color
    (Color) { 169, 169, 169, 200 }, // cell_border_color
    (Color) { 255, 0, 0, 200 }      // cell_border_color_active
};

static void updateHotbar(void) {
    if (IsKeyDown(KEY_ONE)) hotbar.active_item = 0;
    if (IsKeyDown(KEY_TWO)) hotbar.active_item = 1;
    if (IsKeyDown(KEY_THREE)) hotbar.active_item = 2;
    if (IsKeyDown(KEY_FOUR)) hotbar.active_item = 3;
    if (IsKeyDown(KEY_FIVE)) hotbar.active_item = 4;
    if (IsKeyDown(KEY_SIX)) hotbar.active_item = 5;
    if (IsKeyDown(KEY_SEVEN)) hotbar.active_item = 6;
    if (GetMouseWheelMove() > 0) {
        if (hotbar.active_item == 0)
            hotbar.active_item = 6;
        else
            hotbar.active_item -= 1;
    }
    if (GetMouseWheelMove() < 0) {
        if (hotbar.active_item == 6)
            hotbar.active_item = 0;
        else
            hotbar.active_item += 1;
    }
}

static const char* getActiveIngredientName(t_item* item) {
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

static void drawIngredient(Rectangle rect, t_item* item, t_game_textures *textures) {
    switch (item->type) {
        case POTATO:
            if (item->state == DIRTY) {
                // DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, (Color) { 64, 52, 0, 255 });
                DrawTexturePro(textures->dirty_potato, (Rectangle) { 0, 0, textures->dirty_potato.width, textures->dirty_potato.height },
                    (Rectangle) {
                    rect.x + 2.5, rect.y + 2.5, 70, 70
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == CLEAN) {
              // DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, (Color) { 105, 52, 0, 255 });
               DrawTexturePro(textures->washed_potato, (Rectangle) { 0, 0, textures->washed_potato.width, textures->washed_potato.height },
                   (Rectangle) {
                   rect.x + 2.5, rect.y + 2.5, 70, 70
               }, (Vector2) { 0, 0 }, 0.0f, WHITE);
               
            }
            else if (item->state == PEELED) {
               // DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, YELLOW);
                DrawTexturePro(textures->peeled_potato, (Rectangle) { 0, 0, textures->peeled_potato.width, textures->peeled_potato.height },
                    (Rectangle) {
                    rect.x + 2.5, rect.y + 5, 70, 70
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == SLICED) {
               // DrawRectangle(rect.x + 30, rect.y + 30, 10, 20, YELLOW);
               // DrawRectangle(rect.x + 50, rect.y + 30, 10, 20, YELLOW);
                DrawTexturePro(textures->sliced_potato, (Rectangle) { 0, 0, textures->sliced_potato.width, textures->sliced_potato.height },
                    (Rectangle) {
                    rect.x + 5, rect.y + 10, 65, 65
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else {
                // DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, BLACK);
                DrawTexturePro(textures->fried_potato, (Rectangle) { 0, 0, textures->fried_potato.width, textures->fried_potato.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 85
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            break;

        case TOMATO:
            if (item->state == DIRTY) {
                //DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, DARKPURPLE);
                DrawTexturePro(textures->dirty_tomato, (Rectangle) { 0, 0, textures->dirty_tomato.width, textures->dirty_tomato.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == CLEAN) {
               // DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, RED);
                DrawTexturePro(textures->washed_tomato, (Rectangle) { 0, 0, textures->washed_tomato.width, textures->washed_tomato.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else {
                //DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, BLACK);
                DrawTexturePro(textures->sliced_tomato, (Rectangle) { 0, 0, textures->sliced_tomato.width, textures->sliced_tomato.height },
                    (Rectangle) {
                    rect.x + 5, rect.y + 5, 70, 70
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            break;
        case CUCUMBER:
            if (item->state == DIRTY) {
                //DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, DARKPURPLE);
                DrawTexturePro(textures->dirty_cucumber, (Rectangle) { 0, 0, textures->dirty_cucumber.width, textures->dirty_cucumber.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == CLEAN) {
                // DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, RED);
                DrawTexturePro(textures->washed_cucumber, (Rectangle) { 0, 0, textures->washed_cucumber.width, textures->washed_cucumber.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else {
                //DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, BLACK);
                DrawTexturePro(textures->sliced_cucumber, (Rectangle) { 0, 0, textures->sliced_cucumber.width, textures->sliced_cucumber.height },
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
                DrawTexturePro(textures->dirty_apple, (Rectangle) { 0, 0, textures->dirty_apple.width, textures->dirty_apple.height },
                    (Rectangle) { rect.x, rect.y, 75, 75 }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == CLEAN) {
                //DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, (Color) { 255, 0, 0, 255 });
                DrawTexturePro(textures->washed_apple, (Rectangle) { 0, 0, textures->washed_apple.width, textures->washed_apple.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == SLICED) {
                //DrawRectangle(rect.x + 30, rect.y + 30, 20, 20, (Color) { 240, 190, 0, 255 });
                DrawTexturePro(textures->sliced_apple, (Rectangle) { 0, 0, textures->sliced_apple.width, textures->sliced_apple.height },
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

void mx_render_hotbar(t_game_textures *textures) {
    int hotbarCellWidth = hotbar_config.cell_width;
    int hotbarCellHeight = hotbar_config.cell_height;
    int margin = hotbar_config.margin;
    int startPositionX = (game_config.screen_width - (hotbarCellWidth * MX_INVENTORY_SIZE + margin * (MX_INVENTORY_SIZE - 1))) / 2;

    updateHotbar();
    
    // draw active item name
    if (hotbar.items[hotbar.active_item]) {
        const char* activeIngredient = getActiveIngredientName(hotbar.items[hotbar.active_item]);
        drawHotbarText(activeIngredient);
    }
    
    // draw hotbar cells
    for (int i = 0; i < MX_INVENTORY_SIZE; i++) {
        Rectangle rect = { startPositionX, 780, hotbarCellWidth, hotbarCellHeight };

        // draw a cell
        DrawRectangleRec(rect, hotbar_config.cell_color);

        // highlight an active cell
        if (hotbar.active_item == i) {
            DrawRectangleLinesEx(rect, 5, hotbar_config.cell_border_color_active);
        }
        else {
            DrawRectangleLinesEx(rect, 3, hotbar_config.cell_border_color);
        }

        if (hotbar.items[i] != NULL) {
            // draw ingredient icon
            drawIngredient(rect, hotbar.items[i], textures);
        }

        startPositionX += margin + hotbarCellWidth;
    }
}
