#include "../inc/header.h"

t_hotbar_config hotbar_config = {
    75, // cell_width
    75, // cellheight
    15, // margin
    (Color) { 255, 255, 255, 200 }, // cell_color
    (Color) { 169, 169, 169, 200 }, // cell_border_color
    (Color) { 255, 0, 0, 200 }      // cell_border_color_active
};

static void update_hotbar(void) {
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

static const char* get_active_ingredient_name(t_item* item) {
    static char buffer[50];
    const char* state_str;
    const char* type_str;

    switch (item->state) {
    case DIRTY:   state_str = "Dirty"; break;
    case CLEAN:   state_str = "Washed"; break;
    case PEELED:  state_str = "Peeled"; break;
    case JUICED:  state_str = "Juiced"; break;
    case FRIED:   state_str = "Fryied"; break;
    case SLICED:  state_str = "Sliced"; break;
    default:      state_str = ""; break;
    }

    switch (item->type) {
    case APPLE:    type_str = "apple"; break;
    case POTATO:   type_str = "potato"; break;
    case CUCUMBER: type_str = "cucumber"; break;
    case TOMATO:   type_str = "tomato"; break;
    case SALAD:    type_str = "salad"; break;
    default:       type_str = "unknown"; break;
    }

    snprintf(buffer, sizeof(buffer), "%s %s", state_str, type_str);
    return buffer;
}

static void draw_hotbar_text(const char* text) {
    int screen_width = GetScreenWidth();
    int font_size = 20;

    int text_width = MeasureText(text, font_size);
    int x_pos = (screen_width / 2) - (text_width / 2);

    DrawText(text, x_pos, 750, font_size, BLACK);
}

static void drawIngredient(Rectangle rect, t_item* item, t_game_textures *textures) {
    switch (item->type) {
        case POTATO:
            if (item->state == DIRTY) {
                DrawTexturePro(textures->dirty_potato, (Rectangle) { 0, 0, textures->dirty_potato.width, textures->dirty_potato.height },
                    (Rectangle) {
                    rect.x + 2.5, rect.y + 2.5, 70, 70
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == CLEAN) {
               DrawTexturePro(textures->washed_potato, (Rectangle) { 0, 0, textures->washed_potato.width, textures->washed_potato.height },
                   (Rectangle) {
                   rect.x + 2.5, rect.y + 2.5, 70, 70
               }, (Vector2) { 0, 0 }, 0.0f, WHITE);
               
            }
            else if (item->state == PEELED) {
                DrawTexturePro(textures->peeled_potato, (Rectangle) { 0, 0, textures->peeled_potato.width, textures->peeled_potato.height },
                    (Rectangle) {
                    rect.x + 2.5, rect.y + 5, 70, 70
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == SLICED) {
                DrawTexturePro(textures->sliced_potato, (Rectangle) { 0, 0, textures->sliced_potato.width, textures->sliced_potato.height },
                    (Rectangle) {
                    rect.x + 5, rect.y + 10, 65, 65
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else {
                DrawTexturePro(textures->fried_potato, (Rectangle) { 0, 0, textures->fried_potato.width, textures->fried_potato.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 85
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            break;

        case TOMATO:
            if (item->state == DIRTY) {
                DrawTexturePro(textures->dirty_tomato, (Rectangle) { 0, 0, textures->dirty_tomato.width, textures->dirty_tomato.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == CLEAN) {
                DrawTexturePro(textures->washed_tomato, (Rectangle) { 0, 0, textures->washed_tomato.width, textures->washed_tomato.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else {
                DrawTexturePro(textures->sliced_tomato, (Rectangle) { 0, 0, textures->sliced_tomato.width, textures->sliced_tomato.height },
                    (Rectangle) {
                    rect.x + 5, rect.y + 5, 70, 70
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            break;
        case CUCUMBER:
            if (item->state == DIRTY) {
                DrawTexturePro(textures->dirty_cucumber, (Rectangle) { 0, 0, textures->dirty_cucumber.width, textures->dirty_cucumber.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == CLEAN) {
                DrawTexturePro(textures->washed_cucumber, (Rectangle) { 0, 0, textures->washed_cucumber.width, textures->washed_cucumber.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else {
                DrawTexturePro(textures->sliced_cucumber, (Rectangle) { 0, 0, textures->sliced_cucumber.width, textures->sliced_cucumber.height },
                    (Rectangle) {
                    rect.x + 3, rect.y + 5, 65, 65
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            break;
        case SALAD:
            if (item->state == MIXED) {
                DrawTexturePro(textures->salad, (Rectangle) { 0, 0, textures->salad.width, textures->salad.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            break;
        case APPLE:
            if (item->state == DIRTY) {
                DrawTexturePro(textures->dirty_apple, (Rectangle) { 0, 0, textures->dirty_apple.width, textures->dirty_apple.height },
                    (Rectangle) { rect.x, rect.y, 75, 75 }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == CLEAN) {
                DrawTexturePro(textures->washed_apple, (Rectangle) { 0, 0, textures->washed_apple.width, textures->washed_apple.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else if (item->state == SLICED) {
                DrawTexturePro(textures->sliced_apple, (Rectangle) { 0, 0, textures->sliced_apple.width, textures->sliced_apple.height },
                    (Rectangle) {
                    rect.x, rect.y, 75, 75
                }, (Vector2) { 0, 0 }, 0.0f, WHITE);
            }
            else {
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
    int hotbar_cell_width = hotbar_config.cell_width;
    int hotbar_cell_height = hotbar_config.cell_height;
    int margin = hotbar_config.margin;
    int start_position_x = (game_config.screen_width - (hotbar_cell_width * MX_INVENTORY_SIZE + margin * (MX_INVENTORY_SIZE - 1))) / 2;

    update_hotbar();
    
    // draw active item name
    if (hotbar.items[hotbar.active_item]) {
        const char* active_ingredient = get_active_ingredient_name(hotbar.items[hotbar.active_item]);
        draw_hotbar_text(active_ingredient);
    }
    
    // draw hotbar cells
    for (int i = 0; i < MX_INVENTORY_SIZE; i++) {
        Rectangle rect = { start_position_x, 780, hotbar_cell_width, hotbar_cell_height };

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

        start_position_x += margin + hotbar_cell_width;
    }
}
