#include "../inc/header.h"

static void reset_game_progress(t_level_stars *game_state) {
    char filename[50];
    for (int i = 0; i < 3; i++) {  
        snprintf(filename, sizeof(filename),
                 "resource/best_time_level_%d.txt", i);
        remove(filename); 
    }
    printf("INFO: All best time files deleted\n");
    for (int i = 0; i < 3; i++) { 
        game_state->level_stars[i] = 0;
    }
    printf("INFO: Deleting progress and resetting stars\n");
}

void mx_render_settings(t_game_textures *textures, float *volume_music, float *volume_effects, t_level_stars *game_state) {
    int slider_width = 500;
    int slider_height = 30;
    int circle_size = 30;
    int center_x = game_config.screen_width / 2;
    int center_y = game_config.screen_height / 2;
    Rectangle slider_bar_music = { center_x - slider_width / 2, center_y - 100 - 50, slider_width, slider_height };
    Rectangle slider_bar_effects = { center_x - slider_width / 2, center_y + 40 - 30, slider_width, slider_height };
    Rectangle slider_knob_music = { slider_bar_music.x + (*volume_music) * slider_width - circle_size / 2,
                                  slider_bar_music.y - (circle_size - slider_height) / 2,
                                  circle_size, circle_size };

    Rectangle slider_knob_effects = { slider_bar_effects.x + (*volume_effects) * slider_width - circle_size / 2,
                                    slider_bar_effects.y - (circle_size - slider_height) / 2,
                                    circle_size, circle_size };
    int icon_size = 60;
    Rectangle icon_music_rect = { slider_bar_music.x - icon_size - 35, slider_bar_music.y + (slider_height - icon_size) / 2, icon_size, icon_size };
    Rectangle icon_effects_rect = { slider_bar_effects.x - icon_size - 30, slider_bar_effects.y + (slider_height - icon_size) / 2, icon_size, icon_size };
    Vector2 mouse = GetMousePosition();
    bool cursor_changed = false;

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

    float text_width_music = MeasureText("Music Volume", game_config.font_size_paragraph + 20);
    float text_width_effects = MeasureText("Effects Volume", game_config.font_size_paragraph + 20);
    Vector2 text_pos_music = {(GetScreenWidth() - text_width_music) / 2 - 80, slider_bar_music.y - 80};
    DrawTextEx(mx_get_custom_font(), "Music Volume", text_pos_music, game_config.font_size_paragraph + 40, 3, WHITE);
    Vector2 text_pos_effects = {(GetScreenWidth() - text_width_effects) / 2 - 80, slider_bar_effects.y - 80};
    DrawTextEx(mx_get_custom_font(), "Effects Volume", text_pos_effects, game_config.font_size_paragraph + 40, 3, WHITE);

    Rectangle back_button = mx_draw_back_button(textures);

    int button_x2 = (1600 - (MeasureText("DELETE PROGRESS", game_config.font_size_paragraph + 20) + icon_size + 10)) / 2 - 90;
    int button_y12 = slider_bar_effects.y + 150;
    int text_offset_x2 = button_x2 + icon_size + 10;
    Rectangle delete_button = { button_x2, button_y12, MeasureText("DELETE PROGRESS", game_config.font_size_paragraph + 31) + icon_size + 10, 50 };
    Rectangle delete_icon_rect = { button_x2, button_y12 + (50 - icon_size) / 2 + 10, icon_size, icon_size };
    Rectangle delete_text_rect = { text_offset_x2, button_y12 + (50 - game_config.font_size_paragraph + 15) / 2 - 5, MeasureText("DELETE PROGRESS", game_config.font_size_paragraph + 20), 50 };
    DrawTexturePro(textures->del_texture, (Rectangle){0, 0, textures->del_texture.width, textures->del_texture.height}, delete_icon_rect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 text_pos3 = {
        delete_text_rect.x,
        delete_text_rect.y - 10
    };
    DrawTextEx(mx_get_custom_font(), "DELETE PROGRESS", text_pos3, game_config.font_size_paragraph + 30, 3, custom_colors.red_color);

    int button_x1 = 1200;
    int button_y11 = 780;
    icon_size += 20;
    const char* button_text = "GUIDE";
    int text_width2 = MeasureText(button_text, game_config.font_size_header2 + 30) + 45;
    int button_width2 = icon_size + text_width2 + 55;
    int text_offset_x = button_x1 + icon_size + 10;
    Rectangle guide_button = { button_x1, button_y11, button_width2, 50 };
    Rectangle guide_icon_rect = { button_x1, button_y11 + (50 - icon_size) / 2 + 20, icon_size, icon_size };
    Rectangle guide_text_rect = { text_offset_x, button_y11 + (50 - game_config.font_size_header2 + 30) / 2 - 5, text_width2, 50 };
    DrawTexturePro(textures->guide, (Rectangle){0, 0, textures->guide.width, textures->guide.height}, guide_icon_rect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 text_pos2 = { guide_text_rect.x, guide_text_rect.y - 20 };
    DrawTextEx(mx_get_custom_font(), button_text, text_pos2, game_config.font_size_paragraph + 70, 3, WHITE);

    check_collision(mouse, &cursor_changed, back_button, previous_state);
    if (CheckCollisionPointRec(mouse, delete_button)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursor_changed = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            reset_game_progress(game_state);
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
    if (!cursor_changed) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}
