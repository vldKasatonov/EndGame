#include "../inc/header.h"

void mx_render_timer(void) {
    static bool timer_started = false;

    if (!timer_started) {
        mx_start_game_timer();
        timer_started = true;
    }

    double elapsed_time = mx_get_elapsed_time();
    int minutes = (int)elapsed_time / 60;
    int seconds = (int)elapsed_time % 60;

    int screen_width = GetScreenWidth();
    int text_size = 50; 

    char timeText[10]; 
    snprintf(timeText, sizeof(timeText), "%02d:%02d", minutes, seconds);

    Vector2 time_pos = {280, 20};

    DrawTextEx(mx_get_custom_font(), timeText, time_pos, text_size, 2, WHITE);
}
