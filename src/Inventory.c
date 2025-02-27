#include "../inc/header.h"

void mx_initialize_inventory(t_inventory* inventory) {
	for (int i = 0; i < MX_INVENTORY_SIZE; i++) {
		inventory->items[i] = NULL;
	}
	inventory->active_item = 0;
}

int mx_find_free_cell(t_inventory* inventory) {
	for (int i = 0; i < MX_INVENTORY_SIZE; i++) {
		if (inventory->items[i] == NULL)
			return i;
	}
	return -1;
}

int mx_add_item(t_inventory* inventory, t_item* item) {
	int free_cell = mx_find_free_cell(inventory);
	
	if (free_cell != -1) {
		inventory->items[free_cell] = item;
		inventory->active_item = free_cell;
		return free_cell;
	}
	
	return -1;
}

t_item* mx_remove_active_item(t_inventory* inventory) {
	t_item* removed_item = inventory->items[inventory->active_item];

	inventory->items[inventory->active_item] = NULL;
	return removed_item;
}

void mx_clear_inventory(t_inventory* inventory) {
	for (int i = 0; i < MX_INVENTORY_SIZE; i++) {
		inventory->items[i] = NULL;
	}
}

void mx_set_active_item(t_inventory* inventory, int index) {
	inventory->active_item = index;
}

void mx_reload_inventory(t_inventory* inventory) {
	mx_clear_inventory(inventory);
	inventory->active_item = 0;
}
