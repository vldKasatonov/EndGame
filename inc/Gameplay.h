#pragma once

#include "header.h"
#include "stdio.h"
#include "Inventory.h"

typedef enum {
    NONE,
    POTATO_BED,
    TOMATO_BED,
    CUCUMBER_BED,
    APPLE_TREE,
    WASHBASIN,
    PEELING_TABLE,
    SLICING_TABLE,
    GARBAGE_CAN,
    STOVE,
    JUICEMAKER
} InteractableType;

typedef struct {
    Rectangle rect;
    Color color;
    InteractableType type;
} Surface;

void renderGameplay(Vector2*, Surface*, const int, Inventory*, GameTextures*,  bool *isExitPopupOpen);
