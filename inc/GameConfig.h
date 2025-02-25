#pragma once

#include "Objects.h"

#define INVENTORY_SIZE 7
#define MAX_QUEUE 3

typedef struct PlayerConfig {
	float speed;
	float playerWidth;
	float playerHeight;
} PlayerConfig;

typedef struct QueueConfig {
	int registerX;
	int registerY;
	Position spots[MAX_QUEUE];
} QueueConfig;

typedef struct GameConfig {
	double screenWidth;
	double screenHeight;
	double buttonWidth;
	double buttonHeight;
	double fontSizeHeader1;
	double fontSizeHeader2;
	double fontSizeHeader3;
	double fontSizeParagraph;
} GameConfig;

typedef struct HotbarConfig {
	int cellWidth;
	int cellHeight;
	int margin;
	Color cellColor;
	Color cellBorderColor;
	Color cellBorderColorActive;
} HotbarConfig;

typedef struct CustomColors {
	Color buttonBackgroundColor;
	Color menuBackgroundColor;
	Color musicColor;
	Color sliderColor;
	Color redColor;
	Color levelRectangleColor;
	Color circleColor;
	Color circleStrokeColor;
	Color nonactiveStarColor;
	Color activeStarColor;
	Color noneColor;
	Color nonactiveLevelColor;
	Color tonedPreviewColor;
} CustomColors;

extern GameConfig gameConfig;
extern CustomColors customColors;
extern QueueConfig queueConfig;
extern HotbarConfig hotbarConfig;
extern PlayerConfig playerConfig;

extern int levelNumber;
