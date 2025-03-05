#include "../inc/header.h"

static void move_background(t_game_textures* textures, float speed_scrolling, Vector2* position) {
	position->x += speed_scrolling;
	position->y += speed_scrolling;

	if (position->x >= game_config.screen_width) position->x = -textures->background.width;
	if (position->y >= game_config.screen_height) position->y = -textures->background.height;
}

static void draw_moving_background(t_game_textures* textures, Vector2 pos_background) {
	for (float x = pos_background.x; x < game_config.screen_width; x += textures->background.width) {
		for (float y = pos_background.y; y < game_config.screen_height; y += textures->background.height) {
			DrawTexture(textures->background, (int)x, (int)y, WHITE);
		}
	}
}

static void draw_customer_count(t_game_textures *textures, int served_counter, int max_served) {
    Rectangle src_icon = { 0, 0, textures->served_icon.width, textures->served_icon.height };
    Vector2 served_counter_pos = { game_config.screen_width / 5 - 290, 20 };
    Vector2 text_size = MeasureTextEx(mx_get_custom_font(), "0/5", 50, 2);
    DrawTexturePro(textures->served_icon, src_icon, (Rectangle){ served_counter_pos.x - text_size.x / 2 + 45,
                   served_counter_pos.y - 45, 50, 50 }, (Vector2){0, 0}, 0.0f, BLANK);
    char counter_text[6];
    snprintf(counter_text, sizeof(counter_text), "%d/%d", served_counter, max_served);
    DrawTextEx(mx_get_custom_font(), counter_text, served_counter_pos, 50, 2, WHITE);
}

int main(void)
{
	InitWindow(game_config.screen_width, game_config.screen_height, "Funny Chef");
	SetTargetFPS(60);
	mx_init_game_audio();
	mx_init_sound_effects();
	t_game_textures textures;
	mx_load_textures(&textures);

	t_player player_data;
	player_data.position.x = 300;
	player_data.position.y = 350;
	float volume_music = 0.5f;
	float volume_effects = 0.5f;

	float speed_scrolling = -1.5f;
	Vector2 pos_background = { 0.0f, 0.0f };

    int served_counter = 0;
    int max_served = 5;

    bool is_exit_popup_open = false;
    bool is_popup_open = false;

	t_level_stars game_state = { {0, 0, 0} };

	while (!WindowShouldClose()) {
		mx_updat_game_audio();
		mx_update_menu_music();
		mx_update_gameplay_music();

		switch (current_state) {
		case MAIN_MENU:
			move_background(&textures, speed_scrolling, &pos_background);
            break;
		case DEVELOPERS:
			move_background(&textures, speed_scrolling, &pos_background);
			break;
		case SELECT_PLAYER:
			move_background(&textures, speed_scrolling, &pos_background);
			break;
		case LEVEL_MENU:
			move_background(&textures, speed_scrolling, &pos_background);
			break;
		case LEVEL_MENU2:
			move_background(&textures, speed_scrolling, &pos_background);
			break;
		case SETTINGS:
			move_background(&textures, speed_scrolling, &pos_background);
			break;
		case GUIDE_PAGE1:
			move_background(&textures, speed_scrolling, &pos_background);
			break;
		case GUIDE_PAGE2:
			move_background(&textures, speed_scrolling, &pos_background);
			break;
		case GUIDE_PAGE3:
			move_background(&textures, speed_scrolling, &pos_background);
			break;
		case GAMEPLAY_SETTINGS:
			move_background(&textures, speed_scrolling, &pos_background);
			mx_pause_game_timer();
			break;
		case GAMEPLAY:
			break;
		}

		BeginDrawing();
		ClearBackground(custom_colors.menu_background_color);

		switch (current_state) {
		case MAIN_MENU:
			draw_moving_background(&textures, pos_background);
			mx_render_main_menu(&textures, &is_exit_popup_open);
			break;
		case DEVELOPERS:
			draw_moving_background(&textures, pos_background);
			mx_render_developers(&textures);
			break;
		case SELECT_PLAYER:
			draw_moving_background(&textures, pos_background);
			mx_render_select_player(&textures);
			break;
		case LEVEL_MENU:
			draw_moving_background(&textures, pos_background);
			mx_render_level_menu(&textures, &game_state, &player_data);
			break;
		case LEVEL_MENU2:
			draw_moving_background(&textures, pos_background);
			mx_render_level_menu2(&textures);
			break;
		case SETTINGS:
			draw_moving_background(&textures, pos_background);
			mx_render_settings(&textures, &volume_music, &volume_effects, &game_state);
			mx_update_music_volume(volume_music);
			break;
		case GAMEPLAY_SETTINGS:
			draw_moving_background(&textures, pos_background);
			mx_render_gameplay_settings(&textures, &volume_music, &volume_effects, &is_exit_popup_open, &served_counter);
			mx_update_music_volume(volume_music);
			break;
		case GUIDE_PAGE1:
			draw_moving_background(&textures, pos_background);
			mx_render_guide_page1(&textures);
			break;
		case GUIDE_PAGE2:
			draw_moving_background(&textures, pos_background);
			mx_render_guide_page2(&textures);
			break;
		case GUIDE_PAGE3:
			draw_moving_background(&textures, pos_background);
			mx_render_guide_page3(&textures);
			break;
		case GAMEPLAY:
			mx_render_gameplay(&player_data, &textures, &is_popup_open, &served_counter, max_served);
			mx_render_hotbar(&textures);
			mx_render_timer();
			draw_customer_count(&textures, served_counter, max_served);
			break;
		}
		EndDrawing();
	}
	mx_unload_game_audio();
	mx_unload_sound_effects();
    mx_unload_textures(&textures);
	CloseWindow();
	printf("INFO: Closing the Funny Chef\n");
	return 0;
}
