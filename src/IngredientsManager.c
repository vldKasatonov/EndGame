#include "../inc/header.h"

Item* allocateItemMemory() {
	Item* item = (Item*)malloc(sizeof(Item));

	if (!item)
		return NULL;

	return item;
}

void deleteItem(Item** item) {
	if (item && *item) {
		free(*item);
		*item = NULL;
	}
}

Item* getDirtyItem(Ingredient type) {
	Item* item = allocateItemMemory();

	if (!item)
		return NULL;

	item->type = type;
	item->state = DIRTY;

	return item;
}

void updateItem(Item* item, IngredientState state) {
	if (item) {
		item->state = state;
	}
}

Item* getSalad() {
	Item* item = allocateItemMemory();

	if (!item)
		return NULL;

	item->type = SALAD;
	item->state = MIXED;

	return item;
}
//Item* mixIngredients(Inventory* inventory, int index1, int index2) {
//	Item* item = (Item*)malloc(sizeof(Item));
//
//	if (!item)
//		return NULL;
//
//	item->type = SALAD;
//	item->state = MIXED;
//
//	deleteItem(&i1);
//	deleteItem(&i2);
//
//	return item;
//}
