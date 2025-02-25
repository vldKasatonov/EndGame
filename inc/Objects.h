#pragma once

#include "header.h"
#include "stdio.h"
#include "Inventory.h"

typedef struct {
    int x;
    int y;
} Position;

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
    JUICEMAKER,
    PICK_UP,
    CASHBOX,
    PLATE
} InteractableType;

typedef struct {
    Rectangle rect;
    Color color;
    InteractableType type;
} Surface;
