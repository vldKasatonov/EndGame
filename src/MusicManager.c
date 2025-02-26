#include "../inc/header.h"

static Music menuMusic;
static Music gameplayMusic;
static bool musicLoaded = false;
static bool musicPlaying = false;
static bool gameplayMusicPlaying = false;

void InitGameAudio(void) {
    InitAudioDevice();
    menuMusic = LoadMusicStream("resource/audio/music/menu_music.wav");
    gameplayMusic = LoadMusicStream("resource/audio/music/gameplay_music.mp3");  
    SetMusicVolume(menuMusic, 0.5f);
    SetMusicVolume(gameplayMusic, 0.5f);
    musicLoaded = true;
}

void UpdateGameAudio(void) {
    if (musicLoaded) {
        if (musicPlaying) UpdateMusicStream(menuMusic);
        if (gameplayMusicPlaying) UpdateMusicStream(gameplayMusic);
    }
}

void UpdateMenuMusic(void) {
    if (!musicLoaded) return;

    if (currentState == MAIN_MENU ||
        currentState == DEVELOPERS ||
        currentState == LEVEL_MENU ||
        currentState == LEVEL_MENU2 ||
        currentState == SETTINGS || 
        currentState == GUIDE_PAGE1 ||
        currentState == GUIDE_PAGE2 ||
        currentState == GUIDE_PAGE3 || 
        currentState == SELECT_PLAYER) {

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

void UpdateGameplayMusic(void) {
    if (!musicLoaded) return;

    if (currentState == GAMEPLAY || currentState == GAMEPLAY_SETTINGS) {
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

void UpdateMusicVolume(float volume) {
    if (musicLoaded) {
        SetMusicVolume(menuMusic, volume);
        SetMusicVolume(gameplayMusic, volume); 
    }
}

void UnloadGameAudio(void) {
    if (musicLoaded) {
        StopMusicStream(menuMusic);
        StopMusicStream(gameplayMusic);
        UnloadMusicStream(menuMusic);
        UnloadMusicStream(gameplayMusic);
        CloseAudioDevice();
        musicLoaded = false;
    }
}
