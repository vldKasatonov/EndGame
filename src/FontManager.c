#include "../inc/header.h"

static Font customFont;
static bool fontLoaded = false;

Font mx_get_custom_font(void) {
    if (!fontLoaded) {
        customFont = LoadFont("resource/fonts/Gyrochrome-ExtraBold.otf");
        fontLoaded = true;
    }
    return customFont;
}

void mx_unload_custom_font(void) {
    if (fontLoaded) {
        UnloadFont(customFont);
        fontLoaded = false;
    }
}
