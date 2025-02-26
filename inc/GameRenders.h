#pragma once

#include "Inventory.h"
#include "Objects.h"

void renderTimer(void);

void renderLevelMenu(GameTextures *textures, Level_stars *level_star, Player*);

void renderLevelMenu2(GameTextures*);

void renderDevelopers(GameTextures *textures);

void drawStars(int, int, GameTextures*, Vector2);

void drawText(int, Rectangle, Vector2, char*, char* time);

void drawLevel(int, int, GameTextures*, Texture2D, Vector2);

void tonedRect(int);

void renderMainMenu(GameTextures*, bool*);

void renderGameplaySettings(GameTextures*, float*, float*, bool*, int*);

void renderGuidePage1(GameTextures *textures);

void renderGuidePage2(GameTextures *textures);

void renderGuidePage3(GameTextures *textures);

void renderSelectPlayer(GameTextures*);

void renderSettings(GameTextures *textures, float *volumeMusic, float *volumeEffects, Level_stars *gameState);

void renderHotbar(GameTextures*);

void renderQueue(Rectangle, bool*, int*, GameTextures*);

void renderGameplay(Player*, GameTextures*, bool*, int *servedCounter, int maxServed);

void drawStars_gameplay(int, double, GameTextures*, Vector2);

void DisableGameplayInput(bool);

void DrawLevelSucsses(bool *isExitPopupOpen, GameTextures *textures, int*);

void updateLevelStars(Level_stars*, int, int);

int calculateStarsForLevel(void);
