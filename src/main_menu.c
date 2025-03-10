#include "../inc/header.h"

static void draw_centered_button(const char* text, int font_size, Color button_background,
                                 Color font_color, Rectangle button_rect) {
    DrawRectangleRounded(button_rect, 0.5f, 10, button_background);

    Vector2 text_size = MeasureTextEx(mx_get_custom_font(), text, font_size, 2);
    Vector2 text_pos = {
        button_rect.x + (button_rect.width - text_size.x) / 2,
        button_rect.y + (button_rect.height - text_size.y) / 2
    };
    DrawTextEx(mx_get_custom_font(), text, text_pos, font_size, 2, font_color);
}

static void draw_exit_confirmation(bool *is_exit_popup_open, bool *cursor_changed) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.4f));
    int popup_width = 900;
    int popup_height = 400;
    Rectangle popup_rect = {
        (GetScreenWidth() - popup_width) / 2,
        (GetScreenHeight() - popup_height) / 2,
        popup_width,
        popup_height
    };

    DrawRectangleRounded(popup_rect, 0.5f, 10, custom_colors.button_background_color);
    DrawRectangleRoundedLinesEx(popup_rect, 0.5f, 10, 5, WHITE);

    Vector2 text_size = MeasureTextEx(mx_get_custom_font(),
                                      "Are you sure you want to exit?", 50, 3);
    Vector2 text_pos = {
        popup_rect.x + (popup_rect.width - text_size.x) / 2,
        popup_rect.y + 100
    };
    DrawTextEx(mx_get_custom_font(), "Are you sure you want to exit?",
               text_pos, 50, 3, WHITE);

    Rectangle yes_button = {popup_rect.x + 150,
                            popup_rect.y + popup_height - 150, 150, 60};
    Rectangle no_button = {popup_rect.x + popup_width - 300,
                           popup_rect.y + popup_height - 150, 150, 60};

    DrawRectangleRounded(yes_button, 0.5f, 10, GREEN);
    DrawRectangleRounded(no_button, 0.5f, 10, RED);

    Vector2 yestext_size = MeasureTextEx(mx_get_custom_font(), "YES", 40, 3);
    Vector2 yestext_pos = {
        yes_button.x + (yes_button.width - yestext_size.x) / 2,
        yes_button.y + (yes_button.height - yestext_size.y) / 2
    };
    DrawTextEx(mx_get_custom_font(), "YES", yestext_pos, 40, 3, WHITE);

    Vector2 notext_size = MeasureTextEx(mx_get_custom_font(), "NO", 40, 3);
    Vector2 notext_pos = {
        no_button.x + (no_button.width - notext_size.x) / 2,
        no_button.y + (no_button.height - notext_size.y) / 2
    };
    DrawTextEx(mx_get_custom_font(), "NO", notext_pos, 40, 3, WHITE);

    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, yes_button)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        *cursor_changed = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            exit(0);
        }
    }
    if (CheckCollisionPointRec(mouse, no_button)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        *cursor_changed = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            *is_exit_popup_open = false;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
}

static Rectangle draw_exit_button(Texture2D icon) {
    int text_width = MeasureText("EXIT", 70);
    int button_height = 80;
    int icon_width = icon.width - 10;
    int icon_height = icon.height - 10;
    int button_width = icon_width + text_width + 50;
    Rectangle exit_button = { 30, 40, button_width, button_height };
    Rectangle exit_text_rect = {exit_button.x + icon.width + 5,
                              exit_button.y, text_width, button_height};
    Rectangle exit_rect = {exit_button.x,
                           exit_button.y + (button_height - icon_height) / 2,
                           icon_width, icon_height };
    DrawTexturePro(icon, (Rectangle){0, 0, icon.width, icon.height},
                   exit_rect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 text_pos = {exit_text_rect.x, exit_text_rect.y - 10};
    DrawTextEx(mx_get_custom_font(), "EXIT",
               text_pos, 90, 3, WHITE);
    return exit_button;
}

static Rectangle draw_dev_button(void) {
    Vector2 text_dev = MeasureTextEx(mx_get_custom_font(),
                                     "DEVELOPERS", 70, 3);
    Vector2 text_pos_dev = {
        30,
        GetScreenHeight() - 40 - text_dev.y
    };
    DrawTextEx(mx_get_custom_font(), "DEVELOPERS", text_pos_dev,
               70, 3, WHITE);
    Rectangle dev_button = {text_pos_dev.x, text_pos_dev.y,
                            text_dev.x, text_dev.y};
    return dev_button;
}

static void draw_chef(Texture2D image) {
    Rectangle src_image_chef = {0, 0, image.width, image.height};
    Vector2 size_image = {104 * 2, 194 * 2};
    Rectangle image_chef = {GetScreenWidth() - size_image.x * 2,
                            GetScreenHeight() - size_image.y,
                            size_image.x, size_image.y};
    DrawTexturePro(image, src_image_chef, image_chef,
                   (Vector2){0, 0}, 0.0f, WHITE);
}

static Rectangle draw_play_button(void) {
    Vector2 button = {
        (GetScreenWidth() - 300) / 2 - 75,
        (int)(GetScreenHeight() * 0.55)
    };
    Rectangle button_rect = {button.x, button.y, 450, 150};
    Vector2 mouse = GetMousePosition();
    bool mouse_hovered = CheckCollisionPointRec(mouse, button_rect);
    float scale = mouse_hovered ? 1.1f : 1.0f;
    Rectangle scaled_button_rect = {
        button.x - (button_rect.width * (scale - 1)) / 2,
        button.y - (button_rect.height * (scale - 1)) / 2,
        button_rect.width * scale,
        button_rect.height * scale
    };
    Vector2 text_size = MeasureTextEx(mx_get_custom_font(),
                                      "FUNNY CHEF", 140, 3);
    Vector2 text_pos = {
        (GetScreenWidth() - text_size.x) / 2 - 180,
        (GetScreenHeight() - text_size.y) / 2 - 130
    };
    DrawTextEx(mx_get_custom_font(), "FUNNY CHEF",
               text_pos, 200, 3, WHITE);
    draw_centered_button("PLAY", 135 * scale,
                         custom_colors.button_background_color,
                         WHITE, scaled_button_rect);

    return scaled_button_rect;
}

void mx_render_main_menu(t_game_textures *textures, bool *is_exit_popup_open) {
    Vector2 mouse = GetMousePosition();
    bool cursor_changed = false;
    Rectangle button_rect = draw_play_button();
    Rectangle gear_rect = mx_draw_settings_icon(textures);
    Rectangle exit_button = draw_exit_button(textures->exit);
    Rectangle dev_button = draw_dev_button();

    draw_chef(textures->chef);
    if (!(*is_exit_popup_open)) {
        check_collision(mouse, &cursor_changed, button_rect, SELECT_PLAYER);
        check_collision(mouse, &cursor_changed, dev_button, DEVELOPERS);
        if (CheckCollisionPointRec(mouse, gear_rect)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursor_changed = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                previous_state = current_state;
                mx_play_sound_effect(button_click);
                current_state = SETTINGS;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
        if (CheckCollisionPointRec(mouse, exit_button)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursor_changed = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mx_play_sound_effect(button_click);
                *is_exit_popup_open = true;
            }
        }
    }
    if (*is_exit_popup_open) {
        draw_exit_confirmation(is_exit_popup_open, &cursor_changed);
    }
    if (!cursor_changed) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}
