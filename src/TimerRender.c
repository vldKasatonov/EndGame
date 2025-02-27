#include "../inc/header.h"

void mx_render_timer(void) {
    static bool timerStarted = false;

    if (!timerStarted) {
        mx_start_game_timer();
        timerStarted = true;
    }

    double elapsedTime = mx_get_elapsed_time();
    int minutes = (int)elapsedTime / 60;
    int seconds = (int)elapsedTime % 60;

    int screen_width = GetScreenWidth();
    int textSize = 50; 

    char timeText[10]; 
    snprintf(timeText, sizeof(timeText), "%02d:%02d", minutes, seconds);

    int posX = screen_width / 8 + 80;
    int posY = 20;               

    Vector2 timePos = { posX, posY };

    DrawTextEx(mx_get_custom_font(), timeText, timePos, textSize, 2, WHITE);
}
