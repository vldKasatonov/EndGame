#include "../inc/header.h"

static void draw_text_dev(char *text, int space) {
    Vector2 text_size = MeasureTextEx(mx_get_custom_font(), text, 70, 3);
    Vector2 text_pos = {
        (GetScreenWidth() - text_size.x) / 2,
        (GetScreenHeight() - text_size.y) / 3
    };
    DrawTextEx(mx_get_custom_font(), text,
               (Vector2){text_pos.x, text_pos.y + space}, 70, 3, WHITE);
}

void mx_render_developers(t_game_textures *textures) {
    Vector2 mouse = GetMousePosition();
    bool cursor_changed = false;
    Rectangle back_button = mx_draw_back_button(textures);
    int space = 90;
    Vector2 text_size_header = MeasureTextEx(mx_get_custom_font(),
                                             "OUR TEAM:", 100, 3);
    Vector2 text_pos_header = {
        (GetScreenWidth() - text_size_header.x) / 2,
        (GetScreenHeight() - text_size_header.y) / 6
    };

    DrawTextEx(mx_get_custom_font(), "OUR TEAM:", text_pos_header,
               100, 3, WHITE);
    draw_text_dev("Daniil Burlachenko", 0);
    draw_text_dev("Albina Milshyna", space * 1);
    draw_text_dev("Mariia Kashuashvili", space * 2);
    draw_text_dev("Mariia Mykhalchenko", space * 3);
    draw_text_dev("Viktoriia Shaforostova", space * 4);
    draw_text_dev("Vladyslav Kasatonov", space * 5);

    check_collision(mouse, &cursor_changed, back_button, MAIN_MENU);
    if (!cursor_changed) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}
