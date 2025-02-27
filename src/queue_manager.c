#include "../inc/header.h"

t_queue_config queue_config = {
    30, // register x
    725, // register y
    {{30, 120}, {30, 315}, {30, 510}}, // spots
};

void mx_initialize_queue(t_queue* queue) {
    queue->queue_size = 0;
    queue->at_register = NULL;
    queue->out_of_queue = NULL;
    for (int i = 0; i < MX_MAX_QUEUE; i++) {
        queue->queue[i] = NULL;
    }
}

bool mx_has_queue_space(t_queue* queue) {
    return queue->queue_size < MX_MAX_QUEUE;
}

bool mx_accept_order(t_queue* queue) {
    // no one to accept or queue is full
    if (queue->at_register == NULL || !mx_has_queue_space(queue)) {
        return false;
    }

    queue->at_register->target_x = queue_config.spots[queue->queue_size].x;
    queue->at_register->target_y = queue_config.spots[queue->queue_size].y;

    queue->queue[queue->queue_size] = queue->at_register;
    queue->queue_size++;
    queue->at_register = NULL;
    return true;
}

void mx_serve_guest_at_index(t_queue* queue, int index) {
    if (index < 0 || index >= queue->queue_size || !queue->queue[index] || !queue->queue[index]->order) {
        return;
    }

    queue->out_of_queue = queue->queue[index];
    queue->out_of_queue->target_x = -100;
    queue->queue[index] = NULL;

    // shift queue
    for (int i = index; i < queue->queue_size - 1; i++) {
        queue->queue[i] = queue->queue[i + 1];
        queue->queue[i]->target_y -= 200;
    }

    queue->queue[queue->queue_size - 1] = NULL;
    queue->queue_size--;
}

void clear_queue(t_queue* queue) {
    queue->queue_size = 0;
    queue->at_register = NULL;
    queue->out_of_queue = NULL;
    for (int i = 0; i < MX_MAX_QUEUE; i++) {
        queue->queue[i] = NULL;
    }
}
