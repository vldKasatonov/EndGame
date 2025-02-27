#include "../inc/header.h"

int mx_get_nearby_interactable(Rectangle player, t_surface* surfaces, int surface_count) {
    for (int i = 0; i < surface_count; i++) {
        if (CheckCollisionRecs(player, surfaces[i].rect)) {
            return i;
        }
    }
    return -1;
}

static void updateActiveItemState(t_inventory* inventory, t_ingredient_state state) {
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
        t_item* removedItem = mx_remove_active_item(inventory);
        if (removedItem) {
            mx_delete_item(&removedItem);
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
            updateActiveItemState(inventory, CLEAN);
        }
        break;
    case PEELING_TABLE:
        if (mx_can_peel(inventory->items[inventory->active_item])) {
            mx_play_sound_effect(peeling);
            updateActiveItemState(inventory, PEELED);
        }
        break;
    case SLICING_TABLE:
        if (mx_can_slice(inventory->items[inventory->active_item])) {
            mx_play_sound_effect(cutting);
            updateActiveItemState(inventory, SLICED);
        }
        break;
    case JUICEMAKER:
        if (mx_can_juice(inventory->items[inventory->active_item])) {
            mx_play_sound_effect(pouring);
            updateActiveItemState(inventory, JUICED);
        }
        break;
    case STOVE:
        if (mx_can_fry(inventory->items[inventory->active_item])) {
            mx_play_sound_effect(frying);
            updateActiveItemState(inventory, FRIED);
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
      	bool haveSlicedCucumber = false;
        int indexSlicedCucumber = 0;
        bool haveSlicedTomato = false;
        int indexSlicedTomato = 0;
        for (int i = 0; i < MX_INVENTORY_SIZE; i++) {
    		if (inventory->items[i]) {
      			if (inventory->items[i]->state == SLICED && inventory->items[i]->type == CUCUMBER) {
                	haveSlicedCucumber = true;
                	indexSlicedCucumber = i;
            	}
            	if (inventory->items[i]->state == SLICED && inventory->items[i]->type == TOMATO) {
                	haveSlicedTomato = true;
                	indexSlicedTomato = i;
            	}
    		}
		}
        if (haveSlicedCucumber && haveSlicedTomato) {
            mx_set_active_item(inventory, indexSlicedCucumber);
            t_item* item = mx_remove_active_item(inventory);
            if (item != NULL) {
                mx_delete_item(&item);
            }
            mx_set_active_item(inventory, indexSlicedTomato);
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
