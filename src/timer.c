#include "../inc/header.h"

#define MX_MAX_LEVELS 10  
#define MX_BEST_TIME_FORMAT "resource/best_time_level_%d.txt"  

static double start_time = 0.0;
static double paused_time = 0.0;
static double best_times[MX_MAX_LEVELS] = { -1.0 };  
static bool timer_running = false;
static bool timer_paused = false;
extern int current_level;

void mx_start_game_timer(void) {
    if (current_level < 0 || current_level >= MX_MAX_LEVELS) {
        printf("Error: Invalid level (%d) in mx_start_game_timer()\n", current_level);
        return;
    }
    start_time = GetTime();
    timer_running = true;
    timer_paused = false;
}

void mx_pause_game_timer(void) {
    if (timer_running && !timer_paused) {
        paused_time = GetTime() - start_time;
        timer_paused = true;
    }
}

void mx_resume_game_timer(void) {
    if (timer_running && timer_paused) {
        start_time = GetTime() - paused_time;
        timer_paused = false;
    }
}

double mx_get_elapsed_time(void) {
    if (!timer_running) return 0.0;
    return timer_paused ? paused_time : (GetTime() - start_time);
}

void mx_load_best_time(void) {
    if (current_level < 0 || current_level >= MX_MAX_LEVELS) {
        printf("Error: Invalid level (%d) in mx_load_best_time()\n", current_level);
        return;
    }

    char filename[50];
    snprintf(filename, sizeof(filename), MX_BEST_TIME_FORMAT, current_level);

    FILE *file = fopen(filename, "r");
    if (file) {
        if (fscanf(file, "%lf", &best_times[current_level]) != 1) {
            best_times[current_level] = -1.0;
        }
        fclose(file);
    } else {
        best_times[current_level] = -1.0;
    }
}

void mx_save_best_time(void) {
    if (!timer_running) return;

    if (current_level < 0 || current_level >= MX_MAX_LEVELS) {
        printf("Error: Invalid level (%d) in mx_save_best_time()\n", current_level);
        return;
    }

    double elapsed_time = mx_get_elapsed_time();
    timer_running = false;

    if (best_times[current_level] < 0 || elapsed_time < best_times[current_level]) {
        best_times[current_level] = elapsed_time;

        char filename[50];
        snprintf(filename, sizeof(filename), MX_BEST_TIME_FORMAT, current_level);

        FILE *file = fopen(filename, "w");
        if (file) {
            fprintf(file, "%.2f\n", best_times[current_level]);
            fclose(file);
        } else {
            printf("Error: Cannot save best time!\n");
        }
    }
}

void mx_reset_game_timer(void) {
    timer_running = false;
    timer_paused = false;
}

double mx_get_best_time(void) {
    if (current_level < 0 || current_level >= MX_MAX_LEVELS) return -1.0;
    return best_times[current_level];
}


