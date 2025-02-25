#pragma once

#include <stdio.h>
#include <raylib.h>
#include <float.h>

void StartGameTimer();
void PauseGameTimer();    
void ResumeGameTimer();   
void ResetGameTimer();    
double GetElapsedTime();
void LoadBestTime();
void SaveBestTime();
double GetBestTime();


