#include "../inc/header.h"

static void draw_exit_confirmation(bool *is_exit_popup_open, int *counter, bool *cursor_changed) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.4f));
    int popup_width = 900;
    int popup_height = 400;
    Vector2 mouse = GetMousePosition();
    Rectangle popup_rect = {
        (GetScreenWidth() - popup_width) / 2,
        (GetScreenHeight() - popup_height) / 2,
        popup_width,
        popup_height
    };

    DrawRectangleRounded(popup_rect, 0.5f, 10, custom_colors.button_background_color);
    DrawRectangleRoundedLinesEx(popup_rect, 0.5f, 10, 5, WHITE);

    Vector2 text_size = MeasureTextEx(mx_get_custom_font(), "Are you sure you want to exit?", 50, 3);
    Vector2 text_pos = {
        popup_rect.x + (popup_rect.width - text_size.x) / 2,
        popup_rect.y + 100
    };
    DrawTextEx(mx_get_custom_font(), "Are you sure you want to quit?", text_pos, 50, 3, WHITE);

    Rectangle yes_button = { popup_rect.x + 150, popup_rect.y + popup_height - 150, 150, 60 };
    Rectangle no_button = { popup_rect.x + popup_width - 300, popup_rect.y + popup_height - 150, 150, 60 };

    DrawRectangleRounded(yes_button, 0.5f, 10, GREEN);
    DrawRectangleRounded(no_button, 0.5f, 10, RED);

    Vector2 yes_text_size = MeasureTextEx(mx_get_custom_font(), "YES", 40, 3);
    Vector2 yes_text_pos = {
        yes_button.x + (yes_button.width - yes_text_size.x) / 2,
        yes_button.y + (yes_button.height - yes_text_size.y) / 2
    };
    DrawTextEx(mx_get_custom_font(), "YES", yes_text_pos, 40, 3, WHITE);

    Vector2 no_text_size = MeasureTextEx(mx_get_custom_font(), "NO", 40, 3);
    Vector2 no_text_pos = {
        no_button.x + (no_button.width - no_text_size.x) / 2,
        no_button.y + (no_button.height - no_text_size.y) / 2
    };
    DrawTextEx(mx_get_custom_font(), "NO", no_text_pos, 40, 3, WHITE);

    if (CheckCollisionPointRec(mouse, yes_button)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        *cursor_changed = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            mx_reset_game_timer();
            current_state = LEVEL_MENU;
            *is_exit_popup_open = false;
            *counter = 0;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
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

void mx_render_gameplay_settings(t_game_textures *textures, float *volume_music, float *volume_effects, bool *is_exit_popup_open, int *counter) {
    int slider_width = 500;
    int slider_height = 30;
    int circle_size = 30;

    int center_x = GetScreenWidth() / 2;
    int center_y = GetScreenHeight() / 2;

    Rectangle slider_bar_music = { center_x - slider_width / 2, center_y - 50, slider_width, slider_height };
    Rectangle slider_bar_effects = { center_x - slider_width / 2, center_y  + 90 , slider_width, slider_height };

    Rectangle slider_knob_music = { slider_bar_music.x + (*volume_music) * slider_width - circle_size / 2,
                                  slider_bar_music.y - (circle_size - slider_height) / 2,
                                  circle_size, circle_size };

    Rectangle slider_knob_effects = { slider_bar_effects.x + (*volume_effects) * slider_width - circle_size / 2,
                                    slider_bar_effects.y - (circle_size - slider_height) / 2,
                                    circle_size, circle_size };

    int icon_size = 50;
    Rectangle icon_music_rect = { slider_bar_music.x - icon_size - 30, slider_bar_music.y + (slider_height - icon_size) / 2, icon_size, icon_size };
    Rectangle icon_effects_rect = { slider_bar_effects.x - icon_size - 30, slider_bar_effects.y + (slider_height - icon_size) / 2, icon_size, icon_size };

    Vector2 mouse = GetMousePosition();

    slider_knob_music.x = slider_bar_music.x + (*volume_music) * slider_width - circle_size / 2;
    slider_knob_effects.x = slider_bar_effects.x + (*volume_effects) * slider_width - circle_size / 2;

    float corner_radius = 0.8f;
    int segments = 10;

    Rectangle filled_bar_music = { slider_bar_music.x, slider_bar_music.y, (*volume_music) * slider_width, slider_height };
    Rectangle filled_bar_effects = { slider_bar_effects.x, slider_bar_effects.y, (*volume_effects) * slider_width, slider_height };

    DrawRectangleRounded(slider_bar_music, corner_radius, segments, WHITE);
    DrawRectangleRounded(filled_bar_music, corner_radius, segments, custom_colors.music_color);
    DrawCircleV((Vector2){slider_knob_music.x + circle_size / 2, slider_knob_music.y + circle_size / 2}, circle_size * 0.65, custom_colors.slider_color);
    DrawRectangleRounded(slider_bar_effects, corner_radius, segments, WHITE);
    DrawRectangleRounded(filled_bar_effects, corner_radius, segments, custom_colors.music_color);
    DrawCircleV((Vector2){slider_knob_effects.x + circle_size / 2, slider_knob_effects.y + circle_size / 2}, circle_size * 0.65, custom_colors.slider_color);

    if (slider_knob_music.x <= slider_bar_music.x) {
        DrawTexturePro(textures->music_off, (Rectangle){0, 0, textures->music_off.width, textures->music_off.height}, icon_music_rect, (Vector2){0, 0}, 0.0f, WHITE);
    } else {
        DrawTexturePro(textures->music_on, (Rectangle){0, 0, textures->music_on.width, textures->music_on.height}, icon_music_rect, (Vector2){0, 0}, 0.0f, WHITE);
    }

    if (slider_knob_effects.x <= slider_bar_effects.x) {
        DrawTexturePro(textures->volume_off, (Rectangle){0, 0, textures->volume_off.width, textures->volume_off.height}, icon_effects_rect, (Vector2){0, 0}, 0.0f,WHITE);
    } else if (slider_knob_effects.x <= slider_bar_effects.x + (slider_width / 2)) {
        DrawTexturePro(textures->volume_on2, (Rectangle){0, 0, textures->volume_on2.width, textures->volume_on2.height}, icon_effects_rect, (Vector2){0, 0}, 0.0f, WHITE);
    } else {
        DrawTexturePro(textures->volume_on, (Rectangle){0, 0, textures->volume_on.width, textures->volume_on.height}, icon_effects_rect, (Vector2){0, 0}, 0.0f, WHITE);
    }

    float text_width_music = MeasureText("Music Volume", 40);
    float text_width_effects = MeasureText("Effects Volume", 40);
    Vector2 text_pos_music = {(GetScreenWidth() - text_width_music) / 2, slider_bar_music.y - 70};
    DrawTextEx(mx_get_custom_font(), "Music Volume", text_pos_music, 40, 3, WHITE);
    Vector2 text_pos_effects = {(GetScreenWidth() - text_width_effects) / 2, slider_bar_effects.y - 70};
    DrawTextEx(mx_get_custom_font(), "Effects Volume", text_pos_effects, 40, 3, WHITE);

    const char* button_text = "GUIDE";
    icon_size += 40;
    int button_x1 = (GetScreenWidth() - (MeasureText(button_text, 120) + icon_size )) / 2 - 20;
    int button_y11 = 150;
    int text_width2 = MeasureText(button_text, 65);
    int button_width2 = icon_size + text_width2 + 190;
    int text_offset_x = button_x1 + icon_size + 10;
    Rectangle guide_button = { button_x1, button_y11, button_width2, 90 };
    Rectangle guide_icon_rect = { button_x1, button_y11 + (50 - icon_size) / 2 + 20, icon_size, icon_size };
    Rectangle guide_text_rect = { text_offset_x, 167, text_width2, 50 };
    DrawTexturePro(textures->guide, (Rectangle){0, 0, textures->guide.width, textures->guide.height}, guide_icon_rect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 text_pos2 = { guide_text_rect.x, guide_text_rect.y - 40 };
    DrawTextEx(mx_get_custom_font(), button_text, text_pos2, 120, 3, WHITE);

    int button_width3 = 220;
    int button_height3 = 70;
    int button_spacing = 90;
    int total_buttons_width = button_width3 * 2 + button_spacing;
    int button_x2 = center_x - total_buttons_width / 2;
    int button_y12 = slider_bar_effects.y + slider_height + 100;
    Rectangle resume_button = { button_x2, button_y12, button_width3, button_height3 };
    Rectangle quit_button = { button_x2 + button_width3 + button_spacing, button_y12, button_width3, button_height3 };
    float corner_radius1 = 0.5f;
    DrawRectangleRounded(resume_button, corner_radius1, segments, custom_colors.music_color);
    DrawRectangleRounded(quit_button, corner_radius1, segments, custom_colors.music_color);
    int font_size1 = 40;
    Vector2 text_pos_resume = {
        resume_button.x + (resume_button.width - MeasureText("RESUME", font_size1)) / 2 - 10,
        resume_button.y + (resume_button.height - font_size1) / 2
    };
    DrawTextEx(mx_get_custom_font(), "RESUME", text_pos_resume, font_size1, 3, WHITE);
    Vector2 text_pos_quit = {
        quit_button.x + (quit_button.width - MeasureText("QUIT", font_size1)) / 2,
        quit_button.y + (quit_button.height - font_size1) / 2
    };
    DrawTextEx(mx_get_custom_font(), "QUIT", text_pos_quit, font_size1, 3, WHITE);

    bool cursor_changed = false;
    if (!(*is_exit_popup_open)) {
        if (CheckCollisionPointRec(mouse, slider_knob_music) || CheckCollisionPointRec(mouse, slider_knob_effects)) {
            cursor_changed = true;
            SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(mouse, slider_bar_music)) {
                cursor_changed = true;
                *volume_music = (mouse.x - slider_bar_music.x) / slider_width;
                if (*volume_music < 0.0f) {
                    *volume_music = 0.0f;
                }
                if (*volume_music > 1.0f) {
                    *volume_music = 1.0f;
                }
                mx_update_music_volume(*volume_music);
            }
            if (CheckCollisionPointRec(mouse, slider_bar_effects)) {
                cursor_changed = true;
                *volume_effects = (mouse.x - slider_bar_effects.x) / slider_width;
                if (*volume_effects < 0.0f) {
                    *volume_effects = 0.0f;
                }
                if (*volume_effects > 1.0f) {
                    *volume_effects = 1.0f;
                }
                mx_set_effects_volume(*volume_effects);
            }
        }
        if (CheckCollisionPointRec(mouse, resume_button)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursor_changed = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mx_play_sound_effect(button_click);
                mx_resume_game_timer();
                current_state = GAMEPLAY;
            }
        }
        if (CheckCollisionPointRec(mouse, guide_button)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursor_changed = true;
            previous_guide_state = current_state;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mx_play_sound_effect(button_click);
                current_state = GUIDE_PAGE1;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
        if (CheckCollisionPointRec(mouse, quit_button)) {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            cursor_changed = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mx_play_sound_effect(button_click);
                *is_exit_popup_open = true;
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }
        }
    }
    if (*is_exit_popup_open) {
        draw_exit_confirmation(is_exit_popup_open, counter, &cursor_changed);
    }
    if (!cursor_changed) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}
