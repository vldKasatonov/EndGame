#pragma once

#include "header.h"
#include "Ingredients.h"
#include "GameConfig.h"
#include "Levels.h"

typedef struct {
	int id;
    int arrivalTime;
	Item* order;
    int x;
    int y;
    int targetX;
    int targetY;
} Guest;

typedef struct {
    Guest* queue[MAX_QUEUE];
    int queueSize;
    Guest* atRegister;
    Guest* outOfQueue;
} Queue;

typedef struct {
    Guest* allGuests;
    int nextGuestIndex;
    int guestCount;
} Level;

void initializeQueue(Queue*);
bool hasQueueSpace(Queue*);
bool acceptOrder(Queue*);
void serveGuestAtIndex(Queue*, int);
void initializeLevel(LevelData*, Level*);
void loadLevel(LevelData*, Level*);
void clearLevel(Level*);
void tryAddGuestToRegister(Level*, Queue*, int);

// move then
void initializeSurfaces(LevelData*);
