#include "../inc/header.h"

bool canWash(Item* item) {
	if (!item) return false;
	return item->state == DIRTY 
		&& (item->type == APPLE || item->type == CUCUMBER || item->type == TOMATO || item->type == POTATO);
}

bool canPeel(Item* item) { 
	if (!item) return false;
	return item->state == CLEAN && item->type == POTATO; 
}

bool canFry(Item* item) { 
	if (!item) return false;
	return item->state == SLICED && item->type == POTATO; 
}

bool canJuice(Item* item) {
	if (!item) return false;
	return item->type == APPLE && item->state == SLICED;
}

bool canSlice(Item* item) {
	if (!item) return false;
	return (item->state == CLEAN
		&& (item->type == CUCUMBER || item->type == TOMATO || item->type == APPLE))
		|| (item->state == PEELED && item->type == POTATO);
}

bool canServe(Item* item) {
	if (!item) return false;
	return item->state == JUICED || item->state == FRIED || item->state == MIXED;
}

bool canThrowAway(Item* item) {
	if (!item) return false;
	return true;
}
