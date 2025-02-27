#include "../inc/header.h"

#define MAX_LEVELS 10  
#define BEST_TIME_FORMAT "resource/best_time_level_%d.txt"  

static double startTime = 0.0;
static double pausedTime = 0.0;
static double bestTimes[MAX_LEVELS] = { -1.0 };  
static bool timerRunning = false;
static bool timerPaused = false;
extern int currentLevel;

void mx_start_game_timer(void) {
    if (currentLevel < 0 || currentLevel >= MAX_LEVELS) {
        printf("Error: Invalid level (%d) in mx_start_game_timer()\n", currentLevel);
        return;
    }
    startTime = GetTime();
    timerRunning = true;
    timerPaused = false;
}

void mx_pause_game_timer(void) {
    if (timerRunning && !timerPaused) {
        pausedTime = GetTime() - startTime;
        timerPaused = true;
    }
}

void mx_resume_game_timer(void) {
    if (timerRunning && timerPaused) {
        startTime = GetTime() - pausedTime;
        timerPaused = false;
    }
}

double mx_get_elapsed_time(void) {
    if (!timerRunning) return 0.0;
    return timerPaused ? pausedTime : (GetTime() - startTime);
}

void mx_load_best_time(void) {
    if (currentLevel < 0 || currentLevel >= MAX_LEVELS) {
        printf("Error: Invalid level (%d) in mx_load_best_time()\n", currentLevel);
        return;
    }

    char filename[50];
    snprintf(filename, sizeof(filename), BEST_TIME_FORMAT, currentLevel);

    FILE *file = fopen(filename, "r");
    if (file) {
        if (fscanf(file, "%lf", &bestTimes[currentLevel]) != 1) {
            bestTimes[currentLevel] = -1.0;
        }
        fclose(file);
    } else {
        bestTimes[currentLevel] = -1.0;
    }
}

void mx_save_best_time(void) {
    if (!timerRunning) return;

    if (currentLevel < 0 || currentLevel >= MAX_LEVELS) {
        printf("Error: Invalid level (%d) in mx_save_best_time()\n", currentLevel);
        return;
    }

    double elapsedTime = mx_get_elapsed_time();
    timerRunning = false;

    if (bestTimes[currentLevel] < 0 || elapsedTime < bestTimes[currentLevel]) {
        bestTimes[currentLevel] = elapsedTime;

        char filename[50];
        snprintf(filename, sizeof(filename), BEST_TIME_FORMAT, currentLevel);

        FILE *file = fopen(filename, "w");
        if (file) {
            fprintf(file, "%.2f\n", bestTimes[currentLevel]);
            fclose(file);
        } else {
            printf("Error: Cannot save best time!\n");
        }
    }
}

void mx_reset_game_timer(void) {
    timerRunning = false;
    timerPaused = false;
}

double mx_get_best_time(void) {
    if (currentLevel < 0 || currentLevel >= MAX_LEVELS) return -1.0;
    return bestTimes[currentLevel];
}


