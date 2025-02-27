#include "../inc/header.h"

static Music menuMusic;
static Music gameplayMusic;
static bool musicLoaded = false;
static bool musicPlaying = false;
static bool gameplayMusicPlaying = false;

void mx_init_game_audio(void) {
    InitAudioDevice();
    menuMusic = LoadMusicStream("resource/audio/music/menu_music.wav");
    gameplayMusic = LoadMusicStream("resource/audio/music/gameplay_music.mp3");  
    SetMusicVolume(menuMusic, 0.5f);
    SetMusicVolume(gameplayMusic, 0.5f);
    musicLoaded = true;
}

void mx_updat_game_audio(void) {
    if (musicLoaded) {
        if (musicPlaying) UpdateMusicStream(menuMusic);
        if (gameplayMusicPlaying) UpdateMusicStream(gameplayMusic);
    }
}

void mx_update_menu_music(void) {
    if (!musicLoaded) return;

    if (current_state == MAIN_MENU ||
        current_state == DEVELOPERS ||
        current_state == LEVEL_MENU ||
        current_state == LEVEL_MENU2 ||
        current_state == SETTINGS || 
        current_state == GUIDE_PAGE1 ||
        current_state == GUIDE_PAGE2 ||
        current_state == GUIDE_PAGE3 || 
        current_state == SELECT_PLAYER) {

        if (!musicPlaying) {
            StopMusicStream(gameplayMusic);
            gameplayMusicPlaying = false;

            PlayMusicStream(menuMusic);
            musicPlaying = true;
        }
    } else {
        if (musicPlaying) {
            StopMusicStream(menuMusic);
            musicPlaying = false;
        }
    }
}

void mx_update_gameplay_music(void) {
    if (!musicLoaded) return;

    if (current_state == GAMEPLAY || current_state == GAMEPLAY_SETTINGS) {
        if (!gameplayMusicPlaying) {
            StopMusicStream(menuMusic);
            musicPlaying = false;

            PlayMusicStream(gameplayMusic);
            gameplayMusicPlaying = true;
        }
    } else {
        if (gameplayMusicPlaying) {
            StopMusicStream(gameplayMusic);
            gameplayMusicPlaying = false;
        }
    }
}

void mx_update_music_volume(float volume) {
    if (musicLoaded) {
        SetMusicVolume(menuMusic, volume);
        SetMusicVolume(gameplayMusic, volume); 
    }
}

void mx_unload_game_audio(void) {
    if (musicLoaded) {
        StopMusicStream(menuMusic);
        StopMusicStream(gameplayMusic);
        UnloadMusicStream(menuMusic);
        UnloadMusicStream(gameplayMusic);
        CloseAudioDevice();
        musicLoaded = false;
    }
}
