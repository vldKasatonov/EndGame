#include "../inc/header.h"

GameScreen currentState = MAIN_MENU;
GameScreen previousState = MAIN_MENU;
GameScreen previousGuideState = SETTINGS;

Inventory hotbar;
Queue queue;
Level level;
int surfaceCount;
Surface surfaces[34];

