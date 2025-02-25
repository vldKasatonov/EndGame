#pragma once

#define MAX_LEVEL_GUESTS 6

typedef struct LevelData {
	int guestCount;
	Item levelMenu[MAX_LEVEL_GUESTS];
	Surface surfaces[34];
	int surfaceCount;
} LevelData;

extern LevelData levelData[];
