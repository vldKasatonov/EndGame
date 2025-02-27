#include "../inc/header.h"

static Font custom_font;
static bool font_loaded = false;

Font mx_get_custom_font(void) {
    if (!font_loaded) {
        custom_font = LoadFont("resource/fonts/Gyrochrome-ExtraBold.otf");
        font_loaded = true;
    }
    return custom_font;
}

void mx_unload_custom_font(void) {
    if (font_loaded) {
        UnloadFont(custom_font);
        font_loaded = false;
    }
}
