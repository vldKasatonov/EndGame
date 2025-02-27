#include "../inc/header.h"

t_item* allocateItemMemory(void) {
	t_item* item = (t_item*)malloc(sizeof(t_item));

	if (!item)
		return NULL;

	return item;
}

void mx_delete_item(t_item** item) {
	if (item && *item) {
		free(*item);
		*item = NULL;
	}
}

t_item* mx_get_dirty_item(t_ingredient type) {
	t_item* item = allocateItemMemory();

	if (!item)
		return NULL;

	item->type = type;
	item->state = DIRTY;

	return item;
}

void mx_update_item(t_item* item, t_ingredient_state state) {
	if (item) {
		item->state = state;
	}
}

t_item* mx_get_salad(void) {
	t_item* item = allocateItemMemory();

	if (!item)
		return NULL;

	item->type = SALAD;
	item->state = MIXED;

	return item;
}
//t_item* mixIngredients(t_inventory* inventory, int index1, int index2) {
//	t_item* item = (t_item*)malloc(sizeof(t_item));
//
//	if (!item)
//		return NULL;
//
//	item->type = SALAD;
//	item->state = MIXED;
//
//	mx_delete_item(&i1);
//	mx_delete_item(&i2);
//
//	return item;
//}
