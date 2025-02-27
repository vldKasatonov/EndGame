#include "../inc/header.h"

static Vector2 get_text_pos(void) {
    Vector2 text_page_size = {
        MeasureText("PAGE 2", game_config.font_size_paragraph + 70),
        MeasureText("PAGE 2", game_config.font_size_paragraph + 5)
    };
    Vector2 text_pos_page = {
        game_config.screen_width - text_page_size.x,
        game_config.screen_height - text_page_size.y
    };
    return text_pos_page;
}

void mx_render_guide_page1(t_game_textures *textures) {
    Vector2 text_pos_page = get_text_pos();
    DrawTextEx(mx_get_custom_font(), "PAGE 1", text_pos_page,
               game_config.font_size_paragraph + 50, 3, WHITE);

    Rectangle back_button = mx_draw_back_button(textures);
    Rectangle right_arrow_rec = { 1495, 420, 60, 60};
    mx_draw_arrow(textures->right_arrow, right_arrow_rec);

    DrawTexturePro(textures->guide_juice, (Rectangle) { 0, 0,
                   textures->guide_juice.width,
                   textures->guide_juice.height}, (Rectangle) { 178, 100,
                   1244, 700 }, (Vector2) { 0, 0 }, 0.0f, WHITE);

    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;
    
    if (CheckCollisionPointRec(mouse, back_button)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = previous_guide_state;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointRec(mouse, right_arrow_rec)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
	    mx_play_sound_effect(button_click);
            current_state = GUIDE_PAGE2;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

void mx_render_guide_page2(t_game_textures *textures) {
    Vector2 text_pos_page = get_text_pos();
    DrawTextEx(mx_get_custom_font(), "PAGE 2", text_pos_page,
               game_config.font_size_paragraph + 50, 3, WHITE);

    Rectangle back_button = mx_draw_back_button(textures);
    Rectangle right_arrow_rec = { 1495, 420, 60, 60};
    mx_draw_arrow(textures->right_arrow, right_arrow_rec);
    Rectangle left_arrow_rec = { 45, 420, 60, 60};
    mx_draw_arrow(textures->left_arrow, left_arrow_rec);

    DrawTexturePro(textures->guide_potato, (Rectangle) { 0, 0,
                   textures->guide_potato.width,
                   textures->guide_potato.height }, (Rectangle) { 178,
                   125, 1244, 700 }, (Vector2) { 0, 0 }, 0.0f, WHITE);

    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;

    if (CheckCollisionPointRec(mouse, back_button)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = previous_guide_state;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointRec(mouse, right_arrow_rec)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
	    mx_play_sound_effect(button_click);
            current_state = GUIDE_PAGE3;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointRec(mouse, left_arrow_rec)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
	    mx_play_sound_effect(button_click);
            current_state = GUIDE_PAGE1;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

void mx_render_guide_page3(t_game_textures *textures) {
    Vector2 text_pos_page = get_text_pos();
    DrawTextEx(mx_get_custom_font(), "PAGE 3", text_pos_page,
               game_config.font_size_paragraph + 50, 3, WHITE);

    Rectangle back_button = mx_draw_back_button(textures);
    Rectangle left_arrow_rec = { 45, 420, 60, 60};
    mx_draw_arrow(textures->left_arrow, left_arrow_rec);

    DrawTexturePro(textures->guide_salad, (Rectangle) { 0, 0,
                   textures->guide_salad.width,
                   textures->guide_salad.height }, (Rectangle) { 178,
                   125, 1244, 700 }, (Vector2) { 0, 0 }, 0.0f, WHITE);

    Vector2 mouse = GetMousePosition();
    bool cursorChanged = false;

    if (CheckCollisionPointRec(mouse, back_button)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = previous_guide_state;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (CheckCollisionPointRec(mouse, left_arrow_rec)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = GUIDE_PAGE2;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}
