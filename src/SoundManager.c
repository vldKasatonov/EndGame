#include "../inc/header.h"

Sound button_click;
Sound item_pickup;
Sound complete_order;
Sound cutting;
Sound frying;
Sound leaves;
Sound peeling;
Sound washing;
Sound wrong_order;
Sound pouring;
Sound level_complete;

static float effectsVolume = 0.5f;  

void mx_init_sound_effects(void) {
    InitAudioDevice(); 
    button_click = LoadSound("resource/audio/effects/button_click.wav");
    item_pickup = LoadSound("resource/audio/effects/item_pickup.wav");
    complete_order = LoadSound("resource/audio/effects/complete_order.wav");
    cutting = LoadSound("resource/audio/effects/cutting.wav");
    frying = LoadSound("resource/audio/effects/frying.wav");
    leaves = LoadSound("resource/audio/effects/leaves.wav");
    peeling = LoadSound("resource/audio/effects/peeling.wav");
    washing = LoadSound("resource/audio/effects/washing.wav");
    wrong_order = LoadSound("resource/audio/effects/wrong_order.wav");
    pouring = LoadSound("resource/audio/effects/pouring.wav");
    level_complete = LoadSound("resource/audio/effects/level_complete.wav");
    
    SetSoundVolume(button_click, effectsVolume);
    SetSoundVolume(item_pickup, effectsVolume);
    SetSoundVolume(complete_order, effectsVolume);
    SetSoundVolume(cutting, effectsVolume);
    SetSoundVolume(frying, effectsVolume);
    SetSoundVolume(leaves, effectsVolume);
    SetSoundVolume(peeling, effectsVolume);
    SetSoundVolume(washing, effectsVolume);
    SetSoundVolume(wrong_order, effectsVolume);
    SetSoundVolume(pouring, effectsVolume);
    SetSoundVolume(level_complete, effectsVolume);
    
    
}

void mx_play_sound_effect(Sound sound) {
    PlaySound(sound);
}

void mx_set_effects_volume(float volume) {
    effectsVolume = volume;
    SetSoundVolume(button_click, volume);
    SetSoundVolume(item_pickup, volume);
    SetSoundVolume(complete_order, volume);
    SetSoundVolume(cutting, volume);
    SetSoundVolume(frying, volume);
    SetSoundVolume(leaves, volume);
    SetSoundVolume(peeling, volume);
    SetSoundVolume(washing, volume);
    SetSoundVolume(wrong_order, volume);
    SetSoundVolume(pouring, volume);
    SetSoundVolume(level_complete, volume);
}

void mx_unload_sound_effects(void) {
    UnloadSound(button_click);
    UnloadSound(item_pickup);
    UnloadSound(complete_order);
    UnloadSound(cutting);
    UnloadSound(frying);
    UnloadSound(leaves);
    UnloadSound(peeling);
    UnloadSound(washing);
    UnloadSound(wrong_order);
    UnloadSound(pouring);
    UnloadSound(level_complete);
    CloseAudioDevice();
}
