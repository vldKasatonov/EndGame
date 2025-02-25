#pragma once

#include "header.h"

#define NUM_LEVELS 3

typedef enum GameScreen {
    MAIN_MENU = 0,
    SELECT_PLAYER,
    SETTINGS,
    GUIDE_PAGE1,
    GUIDE_PAGE2,
    GUIDE_PAGE3,
    LEVEL_MENU,
    LEVEL_MENU2,
    GAMEPLAY,
    GAMEPLAY_SETTINGS,
    DEVELOPERS
} GameScreen;

typedef struct {
    int levelStars[NUM_LEVELS];
} Level_stars;

typedef struct {
    Vector2 position;
} Player;

extern GameScreen currentState;
extern GameScreen previousState;
extern GameScreen previousGuideState;
extern Inventory hotbar;
extern Queue queue;
extern Level level;
extern Surface surfaces[];
extern int surfaceCount;
