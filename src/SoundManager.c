#include "../inc/header.h"

Sound buttonClick;
Sound itemPickup;
Sound completeOrder;
Sound cutting;
Sound frying;
Sound leaves;
Sound peeling;
Sound washing;
Sound wrongOrder;
Sound pouring;
Sound levelComplete;

static float effectsVolume = 0.5f;  

void InitSoundEffects() {
    InitAudioDevice(); 
    buttonClick = LoadSound("resource/audio/effects/button_click.wav");
    itemPickup = LoadSound("resource/audio/effects/item_pickup.wav");
    completeOrder = LoadSound("resource/audio/effects/complete_order.wav");
    cutting = LoadSound("resource/audio/effects/cutting.wav");
    frying = LoadSound("resource/audio/effects/frying.wav");
    leaves = LoadSound("resource/audio/effects/leaves.wav");
    peeling = LoadSound("resource/audio/effects/peeling.wav");
    washing = LoadSound("resource/audio/effects/washing.wav");
    wrongOrder = LoadSound("resource/audio/effects/wrong_order.wav");
    pouring = LoadSound("resource/audio/effects/pouring.wav");
    levelComplete = LoadSound("resource/audio/effects/levelComplete.wav");
    
    SetSoundVolume(buttonClick, effectsVolume);
    SetSoundVolume(itemPickup, effectsVolume);
    SetSoundVolume(completeOrder, effectsVolume);
    SetSoundVolume(cutting, effectsVolume);
    SetSoundVolume(frying, effectsVolume);
    SetSoundVolume(leaves, effectsVolume);
    SetSoundVolume(peeling, effectsVolume);
    SetSoundVolume(washing, effectsVolume);
    SetSoundVolume(wrongOrder, effectsVolume);
    SetSoundVolume(pouring, effectsVolume);
    SetSoundVolume(levelComplete, effectsVolume);
    
    
}

void PlaySoundEffect(Sound sound) {
    PlaySound(sound);
}

void SetEffectsVolume(float volume) {
    effectsVolume = volume;
    SetSoundVolume(buttonClick, volume);
    SetSoundVolume(itemPickup, volume);
    SetSoundVolume(completeOrder, volume);
    SetSoundVolume(cutting, volume);
    SetSoundVolume(frying, volume);
    SetSoundVolume(leaves, volume);
    SetSoundVolume(peeling, volume);
    SetSoundVolume(washing, volume);
    SetSoundVolume(wrongOrder, volume);
    SetSoundVolume(pouring, volume);
    SetSoundVolume(levelComplete, volume);
}

void UnloadSoundEffects() {
    UnloadSound(buttonClick);
    UnloadSound(itemPickup);
    UnloadSound(completeOrder);
    UnloadSound(cutting);
    UnloadSound(frying);
    UnloadSound(leaves);
    UnloadSound(peeling);
    UnloadSound(washing);
    UnloadSound(wrongOrder);
    UnloadSound(pouring);
    UnloadSound(levelComplete);
    CloseAudioDevice();
}
