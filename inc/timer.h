#pragma once

#include <stdio.h>
#include <raylib.h>
#include <float.h>

void StartGameTimer(void);
void PauseGameTimer(void);
void ResumeGameTimer(void);
void ResetGameTimer(void);
double GetElapsedTime(void);
void LoadBestTime(void);
void SaveBestTime(void);
double GetBestTime(void);


