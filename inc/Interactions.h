#pragma once

#include "Objects.h"
#include "Inventory.h"
//
//InteractableType getNearbyInteractable(Rectangle, Surface*, int);

void interactWithGuest(Inventory* inventory, Queue* queue, int index, InteractableType type);

//int getNearbySurfaceIndex(Rectangle guest, Surface* surfaces, int surfaceCount);

int getNearbyInteractable(Rectangle player, Surface* surfaces, int surfaceCount);

void interactWithObject(Inventory*, InteractableType);
