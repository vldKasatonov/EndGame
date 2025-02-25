#include "../inc/header.h"

QueueConfig queueConfig = {
    30, // register x
    725, // register y
    {{30, 120}, {30, 315}, {30, 510}}, // spots
};

void initializeQueue(Queue* queue) {
    queue->queueSize = 0;
    queue->atRegister = NULL;
    queue->outOfQueue = NULL;
    for (int i = 0; i < MAX_QUEUE; i++) {
        queue->queue[i] = NULL;
    }
}

bool hasQueueSpace(Queue* queue) {
    return queue->queueSize < MAX_QUEUE;
}

bool acceptOrder(Queue* queue) {
    // no one to accept or queue is full
    if (queue->atRegister == NULL || !hasQueueSpace(queue)) {
        return false;
    }

    queue->atRegister->targetX = queueConfig.spots[queue->queueSize].x;
    queue->atRegister->targetY = queueConfig.spots[queue->queueSize].y;

    queue->queue[queue->queueSize] = queue->atRegister;
    queue->queueSize++;
    queue->atRegister = NULL;
    return true;
}

void serveGuestAtIndex(Queue* queue, int index) {
    if (index < 0 || index >= queue->queueSize || !queue->queue[index] || !queue->queue[index]->order) {
        return;
    }

    queue->outOfQueue = queue->queue[index];
    queue->outOfQueue->targetX = -100;
    queue->queue[index] = NULL;

    // shift queue
    for (int i = index; i < queue->queueSize - 1; i++) {
        queue->queue[i] = queue->queue[i + 1];
        queue->queue[i]->targetY -= 200;
    }

    queue->queue[queue->queueSize - 1] = NULL;
    queue->queueSize--;
}

void clearQueue(Queue* queue) {
    queue->queueSize = 0;
    queue->atRegister = NULL;
    queue->outOfQueue = NULL;
    for (int i = 0; i < MAX_QUEUE; i++) {
        queue->queue[i] = NULL;
    }
}
