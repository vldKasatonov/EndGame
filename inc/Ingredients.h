#pragma once

#include "header.h"
#include "Inventory.h"

// state of ingredient
typedef enum {
	DIRTY,
	CLEAN,
	PEELED,
	JUICED,
	FRIED,
	SLICED,
	MIXED
} IngredientState;

// type of ingredient
typedef enum {
	APPLE,
	POTATO,
	CUCUMBER,
	TOMATO,
	SALAD
} Ingredient;

typedef struct {
	IngredientState state;
	Ingredient type;
} Item;

bool canFry(Item*);
bool canWash(Item*);
bool canPeel(Item*);
bool canJuice(Item*);
bool canSlice(Item*);
bool canServe(Item*);
bool canThrowAway(Item* item);

Item* getDirtyItem(Ingredient);
void updateItem(Item*, IngredientState);
//Item* mixIngredients(Inventory*, int, int); // UNCOMENT THEN
void deleteItem(Item** item);
Item* getSalad();


