#include "../inc/header.h"

int getNearbyInteractable(Rectangle player, Surface* surfaces, int surfaceCount) {
    for (int i = 0; i < surfaceCount; i++) {
        if (CheckCollisionRecs(player, surfaces[i].rect)) {
            return i;
        }
    }
    return -1;
}

static void updateActiveItemState(Inventory* inventory, IngredientState state) {
    Item* item = removeActiveItem(inventory);

    if (item) {
        updateItem(item, state);
    }

    addItem(inventory, item);
}

void interactWithGuest(Inventory* inventory, Queue* queue, int index, InteractableType type) {
    switch (type) {
    case PICK_UP:
        serveGuestAtIndex(queue, index);
        PlaySoundEffect(completeOrder);
        Item* removedItem = removeActiveItem(inventory);
        if (removedItem) {
            deleteItem(&removedItem);
        }
        break;
    case CASHBOX:
        acceptOrder(queue);
        break;
    default:
        break;
    }
}

void interactWithObject(Inventory* inventory, InteractableType type) {
    switch (type) {
    case POTATO_BED:
        PlaySoundEffect(leaves);
        addItem(inventory, getDirtyItem(POTATO));
        break;
    case TOMATO_BED:
        PlaySoundEffect(leaves);
        addItem(inventory, getDirtyItem(TOMATO));
        break;
    case CUCUMBER_BED:
        PlaySoundEffect(leaves);
        addItem(inventory, getDirtyItem(CUCUMBER));
        break;
    case APPLE_TREE:
        PlaySoundEffect(leaves);
        addItem(inventory, getDirtyItem(APPLE));
        break;
    case WASHBASIN:
        if (canWash(inventory->items[inventory->activeItem])) {
            PlaySoundEffect(washing);
            updateActiveItemState(inventory, CLEAN);
        }
        break;
    case PEELING_TABLE:
        if (canPeel(inventory->items[inventory->activeItem])) {
            PlaySoundEffect(peeling);
            updateActiveItemState(inventory, PEELED);
        }
        break;
    case SLICING_TABLE:
        if (canSlice(inventory->items[inventory->activeItem])) {
            PlaySoundEffect(cutting);
            updateActiveItemState(inventory, SLICED);
        }
        break;
    case JUICEMAKER:
        if (canJuice(inventory->items[inventory->activeItem])) {
            PlaySoundEffect(pouring);
            updateActiveItemState(inventory, JUICED);
        }
        break;
    case STOVE:
        if (canFry(inventory->items[inventory->activeItem])) {
            PlaySoundEffect(frying);
            updateActiveItemState(inventory, FRIED);
        }
        break;
    case GARBAGE_CAN:
        if (canThrowAway(inventory->items[inventory->activeItem]))
        {
            PlaySoundEffect(itemPickup);
            Item* item = removeActiveItem(inventory);
            deleteItem(&item);
        }
        break;
    case PLATE: {
      	bool haveSlicedCucumber = false;
        int indexSlicedCucumber = 0;
        bool haveSlicedTomato = false;
        int indexSlicedTomato = 0;
        for (int i = 0; i < INVENTORY_SIZE; i++) {
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
            setActiveItem(inventory, indexSlicedCucumber);
            Item* item = removeActiveItem(inventory);
            if (item != NULL) {
                deleteItem(&item);
            }
            setActiveItem(inventory, indexSlicedTomato);
            Item* item2 = removeActiveItem(inventory);
            if (item2 != NULL) {
                deleteItem(&item2);
            }
            addItem(inventory, getSalad());
        }
        break;}
    default:
        break;
    }
}
