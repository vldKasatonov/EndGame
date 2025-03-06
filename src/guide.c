#include "../inc/header.h"

void check_collision(Vector2 mouse, bool *cursor_changed, Rectangle button, t_game_screen state) {
    if (CheckCollisionPointRec(mouse, button)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        *cursor_changed = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = state;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
}

static Vector2 get_text_pos(void) {
    Vector2 text_page_size = {
        MeasureText("PAGE 2", 90),
        MeasureText("PAGE 2", 25)
    };
    Vector2 text_pos_page = {
        GetScreenWidth() - text_page_size.x,
        GetScreenHeight() - text_page_size.y
    };
    return text_pos_page;
}

void mx_render_guide_page1(t_game_textures *textures) {
    Vector2 text_pos_page = get_text_pos();
    Rectangle back_button = mx_draw_back_button(textures);
    Rectangle right_arrow_rec = { 1495, 420, 60, 60};
    Vector2 mouse = GetMousePosition();
    bool cursor_changed = false;

    DrawTextEx(mx_get_custom_font(), "PAGE 1", text_pos_page,
               70, 3, WHITE);
    mx_draw_arrow(textures->right_arrow, right_arrow_rec);
    DrawTexturePro(textures->guide_juice, (Rectangle) { 0, 0,
                   textures->guide_juice.width,
                   textures->guide_juice.height}, (Rectangle) { 178, 100,
                   1244, 700 }, (Vector2) { 0, 0 }, 0.0f, WHITE);
    check_collision(mouse, &cursor_changed, back_button, previous_guide_state);
    check_collision(mouse, &cursor_changed, right_arrow_rec, GUIDE_PAGE2);
    if (!cursor_changed) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

void mx_render_guide_page2(t_game_textures *textures) {
    Vector2 text_pos_page = get_text_pos();
    Rectangle back_button = mx_draw_back_button(textures);
    Rectangle right_arrow_rec = { 1495, 420, 60, 60};
    Rectangle left_arrow_rec = { 45, 420, 60, 60};
    Vector2 mouse = GetMousePosition();
    bool cursor_changed = false;

    DrawTextEx(mx_get_custom_font(), "PAGE 2", text_pos_page,
               70, 3, WHITE);
    mx_draw_arrow(textures->right_arrow, right_arrow_rec);
    mx_draw_arrow(textures->left_arrow, left_arrow_rec);
    DrawTexturePro(textures->guide_potato, (Rectangle) { 0, 0,
                   textures->guide_potato.width,
                   textures->guide_potato.height }, (Rectangle) { 178,
                   125, 1244, 700 }, (Vector2) { 0, 0 }, 0.0f, WHITE);
    check_collision(mouse, &cursor_changed, back_button, previous_guide_state);
    check_collision(mouse, &cursor_changed, right_arrow_rec, GUIDE_PAGE3);
    check_collision(mouse, &cursor_changed, left_arrow_rec, GUIDE_PAGE1);
    if (!cursor_changed) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

void mx_render_guide_page3(t_game_textures *textures) {
    Vector2 text_pos_page = get_text_pos();
    Rectangle back_button = mx_draw_back_button(textures);
    Rectangle left_arrow_rec = { 45, 420, 60, 60};
    Vector2 mouse = GetMousePosition();
    bool cursor_changed = false;

    DrawTextEx(mx_get_custom_font(), "PAGE 3", text_pos_page,
               70, 3, WHITE);
    mx_draw_arrow(textures->left_arrow, left_arrow_rec);
    DrawTexturePro(textures->guide_salad, (Rectangle) { 0, 0,
                   textures->guide_salad.width,
                   textures->guide_salad.height }, (Rectangle) { 178,
                   125, 1244, 700 }, (Vector2) { 0, 0 }, 0.0f, WHITE);
    check_collision(mouse, &cursor_changed, back_button, previous_guide_state);
    check_collision(mouse, &cursor_changed, left_arrow_rec, GUIDE_PAGE2);
    if (!cursor_changed) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}
