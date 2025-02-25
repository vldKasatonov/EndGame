#include "../inc/header.h"

void initializeInventory(Inventory* inventory) {
	for (int i = 0; i < INVENTORY_SIZE; i++) {
		inventory->items[i] = NULL;
	}
	inventory->activeItem = 0;
}

int findFreeCell(Inventory* inventory) {
	for (int i = 0; i < INVENTORY_SIZE; i++) {
		if (inventory->items[i] == NULL)
			return i;
	}
	return -1;
}

int addItem(Inventory* inventory, Item* item) {
	int freeCell = findFreeCell(inventory);
	
	if (freeCell != -1) {
		inventory->items[freeCell] = item;
		inventory->activeItem = freeCell;
		return freeCell;
	}
	
	return -1;
}

Item* removeActiveItem(Inventory* inventory) {
	Item* removedItem = inventory->items[inventory->activeItem];

	inventory->items[inventory->activeItem] = NULL;
	return removedItem;
}

void clearInventory(Inventory* inventory) {
	for (int i = 0; i < INVENTORY_SIZE; i++) {
		inventory->items[i] = NULL;
	}
}

void setActiveItem(Inventory* inventory, int index) {
	inventory->activeItem = index;
}

void reloadInventory(Inventory* inventory) {
	clearInventory(inventory);
	inventory->activeItem = 0;
}
