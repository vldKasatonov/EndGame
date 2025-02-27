#include "../inc/header.h"

int mx_get_nearby_interactable(Rectangle player, t_surface* surfaces, int surface_count) {
    for (int i = 0; i < surface_count; i++) {
        if (CheckCollisionRecs(player, surfaces[i].rect)) {
            return i;
        }
    }
    return -1;
}

static void update_active_item_state(t_inventory* inventory, t_ingredient_state state) {
    t_item* item = mx_remove_active_item(inventory);

    if (item) {
        mx_update_item(item, state);
    }

    mx_add_item(inventory, item);
}

void mx_interact_with_guest(t_inventory* inventory, t_queue* queue, int index, t_interactable_type type) {
    switch (type) {
    case PICK_UP:
        mx_serve_guest_at_index(queue, index);
        mx_play_sound_effect(complete_order);
        t_item* removed_item = mx_remove_active_item(inventory);
        if (removed_item) {
            mx_delete_item(&removed_item);
        }
        break;
    case CASHBOX:
        mx_accept_order(queue);
        break;
    default:
        break;
    }
}

void mx_interact_with_object(t_inventory* inventory, t_interactable_type type) {
    switch (type) {
    case POTATO_BED:
        mx_play_sound_effect(leaves);
        mx_add_item(inventory, mx_get_dirty_item(POTATO));
        break;
    case TOMATO_BED:
        mx_play_sound_effect(leaves);
        mx_add_item(inventory, mx_get_dirty_item(TOMATO));
        break;
    case CUCUMBER_BED:
        mx_play_sound_effect(leaves);
        mx_add_item(inventory, mx_get_dirty_item(CUCUMBER));
        break;
    case APPLE_TREE:
        mx_play_sound_effect(leaves);
        mx_add_item(inventory, mx_get_dirty_item(APPLE));
        break;
    case WASHBASIN:
        if (mx_can_wash(inventory->items[inventory->active_item])) {
            mx_play_sound_effect(washing);
            update_active_item_state(inventory, CLEAN);
        }
        break;
    case PEELING_TABLE:
        if (mx_can_peel(inventory->items[inventory->active_item])) {
            mx_play_sound_effect(peeling);
            update_active_item_state(inventory, PEELED);
        }
        break;
    case SLICING_TABLE:
        if (mx_can_slice(inventory->items[inventory->active_item])) {
            mx_play_sound_effect(cutting);
            update_active_item_state(inventory, SLICED);
        }
        break;
    case JUICEMAKER:
        if (mx_can_juice(inventory->items[inventory->active_item])) {
            mx_play_sound_effect(pouring);
            update_active_item_state(inventory, JUICED);
        }
        break;
    case STOVE:
        if (mx_can_fry(inventory->items[inventory->active_item])) {
            mx_play_sound_effect(frying);
            update_active_item_state(inventory, FRIED);
        }
        break;
    case GARBAGE_CAN:
        if (mx_can_throw_away(inventory->items[inventory->active_item]))
        {
            mx_play_sound_effect(item_pickup);
            t_item* item = mx_remove_active_item(inventory);
            mx_delete_item(&item);
        }
        break;
    case PLATE: {
      	bool have_sliced_cucumber = false;
        int index_sliced_cucumber = 0;
        bool have_sliced_tomato = false;
        int index_sliced_tomato = 0;
        for (int i = 0; i < MX_INVENTORY_SIZE; i++) {
    		if (inventory->items[i]) {
      			if (inventory->items[i]->state == SLICED && inventory->items[i]->type == CUCUMBER) {
                	have_sliced_cucumber = true;
                	index_sliced_cucumber = i;
            	}
            	if (inventory->items[i]->state == SLICED && inventory->items[i]->type == TOMATO) {
                	have_sliced_tomato = true;
                	index_sliced_tomato = i;
            	}
    		}
		}
        if (have_sliced_cucumber && have_sliced_tomato) {
            mx_set_active_item(inventory, index_sliced_cucumber);
            t_item* item = mx_remove_active_item(inventory);
            if (item != NULL) {
                mx_delete_item(&item);
            }
            mx_set_active_item(inventory, index_sliced_tomato);
            t_item* item2 = mx_remove_active_item(inventory);
            if (item2 != NULL) {
                mx_delete_item(&item2);
            }
            mx_add_item(inventory, mx_get_salad());
        }
        break;}
    default:
        break;
    }
}
