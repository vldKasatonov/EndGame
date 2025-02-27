#include "../inc/header.h"

void mx_render_select_player(t_game_textures *textures) {
    Vector2 circle = { game_config.screen_width / 3,
    		      game_config.screen_height / 2 };
    int radius = 200;
    Color non_acctive = { 0, 0, 0, 100};

    DrawCircleV(circle, radius, custom_colors.button_background_color);
    DrawCircle(game_config.screen_width - circle.x, circle.y,
    	       radius, custom_colors.level_rectangle_color);
    DrawCircle(game_config.screen_width - circle.x, circle.y,
    	       radius, non_acctive);
    
    int player_icon_size = 270;
    int half_size_icon = player_icon_size / 2;
    Rectangle one_player_icon_rect = { circle.x - half_size_icon, circle.y
    				      - half_size_icon, player_icon_size,
    				      player_icon_size };
    DrawTexturePro(textures->one_player, (Rectangle){ 0, 0,
    		   textures->one_player.width, textures->one_player.height },
    		   one_player_icon_rect, (Vector2){0, 0}, 0.0f, WHITE);
    int text_player1 = MeasureText("1 PLAYER", game_config.font_size_paragraph + 40);
    Vector2 textPos_one = {
        circle.x - text_player1 / 2 - 10,
        circle.y + 230
    };
    DrawTextEx(mx_get_custom_font(), "1 PLAYER", textPos_one, game_config.font_size_paragraph + 40, 3, WHITE);
    
    Rectangle two_players_icon_rect = { game_config.screen_width - circle.x -
    				       half_size_icon, circle.y - half_size_icon,
    				       player_icon_size, player_icon_size };
    DrawTexturePro(textures->two_players, (Rectangle){ 0, 0,
    		   textures->two_players.width, textures->two_players.height },
    		   two_players_icon_rect, (Vector2){0, 0}, 0.0f, WHITE);
    
    int text_player2 = MeasureText("2 PLAYERS", game_config.font_size_paragraph + 40);
    Vector2 textPos_two = {
        game_config.screen_width - circle.x - text_player2 / 2 - 2,
        circle.y + 230
    };
    DrawTextEx(mx_get_custom_font(), "2 PLAYERS", textPos_two, game_config.font_size_paragraph + 40, 3, WHITE);
  
    int textWidth = MeasureText("BACK", game_config.font_size_paragraph + 50);
    int button_height = 80;
    int iconWidth = textures->exit.width ;
    int iconHeight = textures->exit.height ;
    int button_width = iconWidth + textWidth + 80;
    Rectangle backButton = { 30, 40, button_width, button_height };
    Rectangle backTextRect = { backButton.x + textures->arrow.width + 5, backButton.y, textWidth, button_height };
    Rectangle backRect = { backButton.x , backButton.y + (button_height - iconHeight) / 2, iconWidth, iconHeight };
    DrawTexturePro(textures->arrow, (Rectangle){0, 0, textures->arrow.width, textures->arrow.height}, backRect, (Vector2){0, 0}, 0.0f, WHITE);
    Vector2 textPos1 = { backTextRect.x, backTextRect.y - 10};
    DrawTextEx(mx_get_custom_font(), "BACK", textPos1, game_config.font_size_paragraph + 70, 3, WHITE);
    
    int gearSize = 115;
    Rectangle gearRect = { game_config.screen_width - gearSize - 30, 20, gearSize, gearSize };
    DrawTexturePro(textures->settings, (Rectangle){ 0, 0, textures->settings.width, textures->settings.height }, gearRect, (Vector2){0, 0}, 0.0f, WHITE);

    bool cursorChanged = false;
    Vector2 mouse = GetMousePosition();
    
    if (CheckCollisionPointRec(mouse, gearRect)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            previous_state = current_state;
            current_state = SETTINGS;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
    
    if (CheckCollisionPointRec(mouse, backButton)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = MAIN_MENU;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }

    if (CheckCollisionPointCircle(mouse, circle, radius)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        cursorChanged = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mx_play_sound_effect(button_click);
            current_state = LEVEL_MENU;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }

    if (!cursorChanged) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

}
