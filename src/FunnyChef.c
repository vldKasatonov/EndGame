#include "../inc/header.h"

void move_background(GameTextures* textures, float speed_scrolling, Vector2* position) {
	position->x += speed_scrolling;
	position->y += speed_scrolling;

	if (position->x >= gameConfig.screenWidth) position->x = -textures->background.width;
	if (position->y >= gameConfig.screenHeight) position->y = -textures->background.height;
}

void draw_moving_background(GameTextures* textures, Vector2 pos_background) {
	for (float x = pos_background.x; x < gameConfig.screenWidth; x += textures->background.width) {
		for (float y = pos_background.y; y < gameConfig.screenHeight; y += textures->background.height) {
			DrawTexture(textures->background, (int)x, (int)y, WHITE);
		}
	}
}

static void drawCustomerCount(GameTextures *textures, int servedCounter, int maxServed) {
    Rectangle srcIcon = { 0, 0, textures->served_icon.width, textures->served_icon.height };
    Vector2 servedCounterPos = { gameConfig.screenWidth / 5 + 15, 85 };
    Vector2 textSize = MeasureTextEx(GetCustomFont(), "0/5", 50, 2);
    DrawTexturePro(textures->served_icon, srcIcon, (Rectangle){ servedCounterPos.x - textSize.x / 2 - 15,
                   servedCounterPos.y, 50, 50 }, (Vector2){0, 0}, 0.0f, WHITE);
    char counterText[6];
    snprintf(counterText, sizeof(counterText), "%d/%d", servedCounter, maxServed);
    DrawTextEx(GetCustomFont(), counterText, servedCounterPos, 50, 2, WHITE);
}

static bool timerStarted = false;

int main(void)
{
	InitWindow(gameConfig.screenWidth, gameConfig.screenHeight, "Funny Chef");
	InitGameAudio();
	InitSoundEffects();

	GameTextures textures;
	LoadTextures(&textures);
	
	SetTargetFPS(60);

	//    int levelProgress = 0;

	Player playerData;
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

	Level_stars gameState = { {0, 0, 0} };

	while (!WindowShouldClose())
	{
		UpdateGameAudio();
		UpdateMenuMusic();
		UpdateGameplayMusic();

		switch (currentState)
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
			PauseGameTimer();
		} break;
		case GAMEPLAY:
		{
			if (GetElapsedTime() == 0)
			{
				StartGameTimer();
				timerStarted = true;
			}
			else
			{
				ResumeGameTimer();
			}
		}break;
		}

		BeginDrawing();
		ClearBackground(customColors.menuBackgroundColor);

		switch (currentState) {
		case MAIN_MENU:
		{
			draw_moving_background(&textures, pos_background);
			renderMainMenu(&textures, &isExitPopupOpen);
		} break;
		case DEVELOPERS:
		{
			draw_moving_background(&textures, pos_background);
			renderDevelopers(&textures);
		} break;
		case SELECT_PLAYER:
		{
			draw_moving_background(&textures, pos_background);
			renderSelectPlayer(&textures);
		} break;
		case LEVEL_MENU:
		{
			draw_moving_background(&textures, pos_background);
			renderLevelMenu(&textures, &gameState, &playerData);
		} break;
		case LEVEL_MENU2:
		{
			draw_moving_background(&textures, pos_background);
			renderLevelMenu2(&textures);
		} break;
		case SETTINGS:
		{
			draw_moving_background(&textures, pos_background);
			renderSettings(&textures, &volumeMusic, &volumeEffects, &gameState);
			UpdateMusicVolume(volumeMusic);
		} break;
		case GAMEPLAY_SETTINGS:
		{
			draw_moving_background(&textures, pos_background);
			renderGameplaySettings(&textures, &volumeMusic, &volumeEffects, &isExitPopupOpen, &servedCounter);
			UpdateMusicVolume(volumeMusic);
		} break;
		case GUIDE_PAGE1:
		{
			draw_moving_background(&textures, pos_background);
			renderGuidePage1(&textures);
		} break;
		case GUIDE_PAGE2:
		{
			draw_moving_background(&textures, pos_background);
			renderGuidePage2(&textures);
		} break;
		case GUIDE_PAGE3:
		{
			draw_moving_background(&textures, pos_background);
			renderGuidePage3(&textures);
		} break;
		case GAMEPLAY:
		{
			if (!timerStarted) {
				StartGameTimer();
				timerStarted = true;
			}

			renderGameplay(&playerData, &textures, &isPopupOpen, &servedCounter, maxServed);
			renderHotbar(&textures);
			renderTimer();
			drawCustomerCount(&textures, servedCounter, maxServed);

		} break;
		}
		EndDrawing();
	}
	SaveBestTime();
	UnloadGameAudio();
	UnloadSoundEffects();
    UnloadTextures(&textures);
	CloseWindow();
	printf("INFO: Closing the Funny Chef\n");
	return 0;
}
