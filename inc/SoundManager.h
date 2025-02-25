#pragma once

#include <raylib.h>

void InitSoundEffects();       
void UnloadSoundEffects();      
void PlaySoundEffect(Sound sound); 
void SetEffectsVolume(float volume); 

extern Sound buttonClick;  
extern Sound itemPickup;
extern Sound completeOrder;
extern Sound cutting;
extern Sound frying;
extern Sound leaves;
extern Sound peeling;
extern Sound washing;
extern Sound wrongOrder;
extern Sound pouring;   
extern Sound levelComplete; 

