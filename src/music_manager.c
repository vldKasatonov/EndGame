#include "../inc/header.h"

static Music menu_music;
static Music gameplay_music;
static bool music_loaded = false;
static bool music_playing = false;
static bool gameplay_music_playing = false;

void mx_init_game_audio(void) {
    InitAudioDevice();
    menu_music = LoadMusicStream("resource/audio/music/menu_music.wav");
    gameplay_music = LoadMusicStream("resource/audio/music/gameplay_music.mp3");  
    SetMusicVolume(menu_music, 0.5f);
    SetMusicVolume(gameplay_music, 0.5f);
    music_loaded = true;
}

void mx_updat_game_audio(void) {
    if (music_loaded) {
        if (music_playing) UpdateMusicStream(menu_music);
        if (gameplay_music_playing) UpdateMusicStream(gameplay_music);
    }
}

void mx_update_menu_music(void) {
    if (!music_loaded) return;

    if (current_state == MAIN_MENU ||
        current_state == DEVELOPERS ||
        current_state == LEVEL_MENU ||
        current_state == LEVEL_MENU2 ||
        current_state == SETTINGS || 
        current_state == GUIDE_PAGE1 ||
        current_state == GUIDE_PAGE2 ||
        current_state == GUIDE_PAGE3 || 
        current_state == SELECT_PLAYER) {

        if (!music_playing) {
            StopMusicStream(gameplay_music);
            gameplay_music_playing = false;

            PlayMusicStream(menu_music);
            music_playing = true;
        }
    } else {
        if (music_playing) {
            StopMusicStream(menu_music);
            music_playing = false;
        }
    }
}

void mx_update_gameplay_music(void) {
    if (!music_loaded) return;

    if (current_state == GAMEPLAY || current_state == GAMEPLAY_SETTINGS) {
        if (!gameplay_music_playing) {
            StopMusicStream(menu_music);
            music_playing = false;

            PlayMusicStream(gameplay_music);
            gameplay_music_playing = true;
        }
    } else {
        if (gameplay_music_playing) {
            StopMusicStream(gameplay_music);
            gameplay_music_playing = false;
        }
    }
}

void mx_update_music_volume(float volume) {
    if (music_loaded) {
        SetMusicVolume(menu_music, volume);
        SetMusicVolume(gameplay_music, volume); 
    }
}

void mx_unload_game_audio(void) {
    if (music_loaded) {
        StopMusicStream(menu_music);
        StopMusicStream(gameplay_music);
        UnloadMusicStream(menu_music);
        UnloadMusicStream(gameplay_music);
        CloseAudioDevice();
        music_loaded = false;
    }
}
