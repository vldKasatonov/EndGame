#include "../inc/header.h"

int currentLevel = 0;

void initializeLevel(LevelData* levelData, Level* level) {
    level->nextGuestIndex = 0;
    level->guestCount = levelData->guestCount;

    level->allGuests = malloc(level->guestCount * sizeof(Guest));
    if (!level->allGuests) {
        return;
    }

    for (int i = 0; i < level->guestCount; i++) {
        level->allGuests[i].id = i + 1;
        level->allGuests[i].arrivalTime = i * 15;
        level->allGuests[i].order = &levelData->levelMenu[i];

        level->allGuests[i].x = queueConfig.registerX;
        level->allGuests[i].y = queueConfig.registerY + 200;
        level->allGuests[i].targetX = queueConfig.registerX;
        level->allGuests[i].targetY = queueConfig.registerY;
    }
}

void loadLevel(LevelData* levelData, Level* level) {
    clearLevel(level);
    initializeLevel(levelData, level);
}

void clearLevel(Level* level) {
    if (level->allGuests) {
        free(level->allGuests);
        level->allGuests = NULL;
    }

    level->nextGuestIndex = 0;
    level->guestCount = 0;
}

void tryAddGuestToRegister(Level* level, Queue* queue, int currentTime) {
    if (queue->atRegister != NULL || !hasQueueSpace(queue)) {
        return;
    }

    if (level->nextGuestIndex >= level->guestCount) {
        return;
    }

    Guest* nextGuest = &level->allGuests[level->nextGuestIndex];
    nextGuest->targetX = queueConfig.registerX;
    nextGuest->targetY = queueConfig.registerY;

    if (nextGuest->arrivalTime <= currentTime) {
        queue->atRegister = nextGuest;
        level->nextGuestIndex++;
    }
}
