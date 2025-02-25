#include "../inc/header.h"

static Font customFont;
static bool fontLoaded = false;

Font GetCustomFont() {
    if (!fontLoaded) {
        customFont = LoadFont("resource/fonts/Gyrochrome-ExtraBold.otf");
        fontLoaded = true;
    }
    return customFont;
}

void UnloadCustomFont() {
    if (fontLoaded) {
        UnloadFont(customFont);
        fontLoaded = false;
    }
}
