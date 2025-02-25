#pragma once

#include "header.h"
#include "Ingredients.h"
#include "GameConfig.h"

typedef struct {
	Item* items[INVENTORY_SIZE];
	int activeItem;
} Inventory;

void initializeInventory(Inventory*);
int findFreeCell(Inventory*);
int addItem(Inventory*, Item*);
Item* removeActiveItem(Inventory*);
void clearInventory(Inventory*);
void setActiveItem(Inventory*, int);
void reloadInventory(Inventory*);
