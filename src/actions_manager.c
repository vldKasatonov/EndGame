#include "../inc/header.h"

bool mx_can_throw_away(t_item* item) {
	if (!item) return false;
	return true;
}

bool mx_can_wash(t_item* item) {
	if (!item) return false;
	return item->state == DIRTY
		&& (item->type == APPLE || item->type == CUCUMBER || item->type == TOMATO || item->type == POTATO);
}

bool mx_can_peel(t_item* item) {
	if (!item) return false;
	return item->state == CLEAN && item->type == POTATO;
}

bool mx_can_slice(t_item* item) {
	if (!item) return false;
	return (item->state == CLEAN
		&& (item->type == CUCUMBER || item->type == TOMATO || item->type == APPLE))
		|| (item->state == PEELED && item->type == POTATO);
}

bool mx_can_juice(t_item* item) {
	if (!item) return false;
	return item->state == SLICED && item->type == APPLE;
}

bool mx_can_fry(t_item* item) { 
	if (!item) return false;
	return item->state == SLICED && item->type == POTATO;
}

bool mx_can_serve(t_item* item) {
	if (!item) return false;
	return item->state == JUICED || item->state == FRIED || item->state == MIXED;
}
