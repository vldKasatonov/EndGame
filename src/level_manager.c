#include "../inc/header.h"

int current_level = 0;

void mx_initialize_level(t_level_data* level_data, t_level* level) {
    level->next_guest_index = 0;
    level->guest_count = level_data->guest_count;

    level->all_guests = malloc(level->guest_count * sizeof(t_guest));
    if (!level->all_guests) {
        return;
    }

    for (int i = 0; i < level->guest_count; i++) {
        level->all_guests[i].id = i + 1;
        level->all_guests[i].arrival_time = i * 15;
        level->all_guests[i].order = &level_data->level_menu[i];

        level->all_guests[i].x = queue_config.register_x;
        level->all_guests[i].y = queue_config.register_y + 200;
        level->all_guests[i].target_x = queue_config.register_x;
        level->all_guests[i].target_y = queue_config.register_y;
    }
}

void loadLevel(t_level_data* level_data, t_level* level) {
    mx_clear_level(level);
    mx_initialize_level(level_data, level);
}

void mx_clear_level(t_level* level) {
    if (level->all_guests) {
        free(level->all_guests);
        level->all_guests = NULL;
    }

    level->next_guest_index = 0;
    level->guest_count = 0;
}

void mx_try_add_guest_to_register(t_level* level, t_queue* queue, int current_time) {
    if (queue->at_register != NULL || !mx_has_queue_space(queue)) {
        return;
    }

    if (level->next_guest_index >= level->guest_count) {
        return;
    }

    t_guest* nextGuest = &level->all_guests[level->next_guest_index];
    nextGuest->target_x = queue_config.register_x;
    nextGuest->target_y = queue_config.register_y;

    if (nextGuest->arrival_time <= current_time) {
        queue->at_register = nextGuest;
        level->next_guest_index++;
    }
}
