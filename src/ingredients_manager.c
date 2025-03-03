#include "../inc/header.h"

t_item* allocate_item_memory(void) {
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
	t_item* item = allocate_item_memory();

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
	t_item* item = allocate_item_memory();

	if (!item)
		return NULL;

	item->type = SALAD;
	item->state = MIXED;

	return item;
}
