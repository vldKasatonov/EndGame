#include "../inc/header.h"

void renderTimer() {
    static bool timerStarted = false;

    if (!timerStarted) {
        StartGameTimer();
        timerStarted = true;
    }

    double elapsedTime = GetElapsedTime();
    int minutes = (int)elapsedTime / 60;
    int seconds = (int)elapsedTime % 60;

    int screenWidth = GetScreenWidth();
    int textSize = 50; 

    char timeText[10]; 
    snprintf(timeText, sizeof(timeText), "%02d:%02d", minutes, seconds);

    int posX = screenWidth / 8 + 80;
    int posY = 20;               

    Vector2 timePos = { posX, posY };

    DrawTextEx(GetCustomFont(), timeText, timePos, textSize, 2, WHITE);
}
