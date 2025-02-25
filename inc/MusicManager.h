#pragma once

#include <raylib.h>
#include "header.h"

void InitGameAudio();
void UpdateGameAudio();
void UnloadGameAudio();
void SetMusicVolumeLevel(float volume);
void UpdateMenuMusic();
void UpdateGameplayMusic();
void UpdateMusicVolume(float volume);

