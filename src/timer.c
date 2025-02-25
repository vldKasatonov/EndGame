#include "../inc/timer.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEVELS 10  
#define BEST_TIME_FORMAT "resource/best_time_level_%d.txt"  

static double startTime = 0.0;
static double pausedTime = 0.0;
static double bestTimes[MAX_LEVELS] = { -1.0 };  
static bool timerRunning = false;
static bool timerPaused = false;
extern int currentLevel;  

void StartGameTimer() {
    if (currentLevel < 0 || currentLevel >= MAX_LEVELS) {
        printf("Error: Invalid level (%d) in StartGameTimer()\n", currentLevel);
        return;
    }
    startTime = GetTime();
    timerRunning = true;
    timerPaused = false;
}

void PauseGameTimer() {
    if (timerRunning && !timerPaused) {
        pausedTime = GetTime() - startTime;
        timerPaused = true;
    }
}

void ResumeGameTimer() {
    if (timerRunning && timerPaused) {
        startTime = GetTime() - pausedTime;
        timerPaused = false;
    }
}

double GetElapsedTime() {
    if (!timerRunning) return 0.0;
    return timerPaused ? pausedTime : (GetTime() - startTime);
}

void LoadBestTime() {
    if (currentLevel < 0 || currentLevel >= MAX_LEVELS) {
        printf("Error: Invalid level (%d) in LoadBestTime()\n", currentLevel);
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

void SaveBestTime() {
    if (!timerRunning) return;

    if (currentLevel < 0 || currentLevel >= MAX_LEVELS) {
        printf("Error: Invalid level (%d) in SaveBestTime()\n", currentLevel);
        return;
    }

    double elapsedTime = GetElapsedTime();
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

void ResetGameTimer() {
    timerRunning = false;
    timerPaused = false;
}

double GetBestTime() {
    if (currentLevel < 0 || currentLevel >= MAX_LEVELS) return -1.0;
    return bestTimes[currentLevel];
}


