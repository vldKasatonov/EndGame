#include "../inc/header.h"

void move_background(t_game_textures* textures, float speed_scrolling, Vector2* position) {
	position->x += speed_scrolling;
	position->y += speed_scrolling;

	if (position->x >= game_config.screen_width) position->x = -textures->background.width;
	if (position->y >= game_config.screen_height) position->y = -textures->background.height;
}

void draw_moving_background(t_game_textures* textures, Vector2 pos_background) {
	for (float x = pos_background.x; x < game_config.screen_width; x += textures->background.width) {
		for (float y = pos_background.y; y < game_config.screen_height; y += textures->background.height) {
			DrawTexture(textures->background, (int)x, (int)y, WHITE);
		}
	}
}

static void drawCustomerCount(t_game_textures *textures, int servedCounter, int maxServed) {
    Rectangle srcIcon = { 0, 0, textures->served_icon.width, textures->served_icon.height };
    Vector2 servedCounterPos = { game_config.screen_width / 5 + 15, 85 };
    Vector2 textSize = MeasureTextEx(mx_get_custom_font(), "0/5", 50, 2);
    DrawTexturePro(textures->served_icon, srcIcon, (Rectangle){ servedCounterPos.x - textSize.x / 2 - 15,
                   servedCounterPos.y, 50, 50 }, (Vector2){0, 0}, 0.0f, WHITE);
    char counterText[6];
    snprintf(counterText, sizeof(counterText), "%d/%d", servedCounter, maxServed);
    DrawTextEx(mx_get_custom_font(), counterText, servedCounterPos, 50, 2, WHITE);
}

static bool timerStarted = false;

int main(void)
{
	InitWindow(game_config.screen_width, game_config.screen_height, "Funny Chef");
	mx_init_game_audio();
	mx_init_sound_effects();

	t_game_textures textures;
	mx_load_textures(&textures);
	
	SetTargetFPS(60);

	//    int levelProgress = 0;

	t_player playerData;
	playerData.position.x = 300;
	playerData.position.y = 350;
	float volumeMusic = 0.5f;
	float volumeEffects = 0.5f;

	float speed_scrolling = -1.5f;
	Vector2 pos_background = { 0.0f, 0.0f };

    int servedCounter = 0;
    int maxServed = 5;

    bool isExitPopupOpen = false;
    bool isPopupOpen = false;

	t_level_stars game_state = { {0, 0, 0} };

	while (!WindowShouldClose())
	{
		mx_updat_game_audio();
		mx_update_menu_music();
		mx_update_gameplay_music();

		switch (current_state)
		{
		case MAIN_MENU:
		{
			move_background(&textures, speed_scrolling, &pos_background);
		} break;
		case DEVELOPERS:
		{
			move_background(&textures, speed_scrolling, &pos_background);
		} break;
		case SELECT_PLAYER:
		{
			move_background(&textures, speed_scrolling, &pos_background);
		} break;
		case LEVEL_MENU:
		{
			move_background(&textures, speed_scrolling, &pos_background);
		} break;
		case LEVEL_MENU2:
		{
			move_background(&textures, speed_scrolling, &pos_background);
		} break;
		case SETTINGS:
		{
			move_background(&textures, speed_scrolling, &pos_background);
		} break;
		case GUIDE_PAGE1:
		{
			move_background(&textures, speed_scrolling, &pos_background);
		} break;
		case GUIDE_PAGE2:
		{
			move_background(&textures, speed_scrolling, &pos_background);
		} break;
		case GUIDE_PAGE3:
		{
			move_background(&textures, speed_scrolling, &pos_background);
		} break;
		case GAMEPLAY_SETTINGS:
		{
			move_background(&textures, speed_scrolling, &pos_background);
			mx_pause_game_timer();
		} break;
		case GAMEPLAY:
		{
			if (mx_get_elapsed_time() == 0)
			{
				mx_start_game_timer();
				timerStarted = true;
			}
			else
			{
				mx_resume_game_timer();
			}
		}break;
		}

		BeginDrawing();
		ClearBackground(custom_colors.menu_background_color);

		switch (current_state) {
		case MAIN_MENU:
		{
			draw_moving_background(&textures, pos_background);
			mx_render_main_menu(&textures, &isExitPopupOpen);
		} break;
		case DEVELOPERS:
		{
			draw_moving_background(&textures, pos_background);
			mx_render_developers(&textures);
		} break;
		case SELECT_PLAYER:
		{
			draw_moving_background(&textures, pos_background);
			mx_render_select_player(&textures);
		} break;
		case LEVEL_MENU:
		{
			draw_moving_background(&textures, pos_background);
			mx_render_level_menu(&textures, &game_state, &playerData);
		} break;
		case LEVEL_MENU2:
		{
			draw_moving_background(&textures, pos_background);
			mx_render_level_menu2(&textures);
		} break;
		case SETTINGS:
		{
			draw_moving_background(&textures, pos_background);
			mx_render_settings(&textures, &volumeMusic, &volumeEffects, &game_state);
			mx_update_music_volume(volumeMusic);
		} break;
		case GAMEPLAY_SETTINGS:
		{
			draw_moving_background(&textures, pos_background);
			mx_render_gameplay_settings(&textures, &volumeMusic, &volumeEffects, &isExitPopupOpen, &servedCounter);
			mx_update_music_volume(volumeMusic);
		} break;
		case GUIDE_PAGE1:
		{
			draw_moving_background(&textures, pos_background);
			mx_render_guide_page1(&textures);
		} break;
		case GUIDE_PAGE2:
		{
			draw_moving_background(&textures, pos_background);
			mx_render_guide_page2(&textures);
		} break;
		case GUIDE_PAGE3:
		{
			draw_moving_background(&textures, pos_background);
			mx_render_guide_page3(&textures);
		} break;
		case GAMEPLAY:
		{
			if (!timerStarted) {
				mx_start_game_timer();
				timerStarted = true;
			}

			mx_render_gameplay(&playerData, &textures, &isPopupOpen, &servedCounter, maxServed);
			mx_render_hotbar(&textures);
			mx_render_timer();
			drawCustomerCount(&textures, servedCounter, maxServed);

		} break;
		}
		EndDrawing();
	}
	mx_save_best_time();
	mx_unload_game_audio();
	mx_unload_sound_effects();
    mx_unload_textures(&textures);
	CloseWindow();
	printf("INFO: Closing the Funny Chef\n");
	return 0;
}
