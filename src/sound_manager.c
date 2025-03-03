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

static float effects_volume = 0.5f;  

void mx_init_sound_effects(void) {
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
    
    SetSoundVolume(button_click, effects_volume);
    SetSoundVolume(item_pickup, effects_volume);
    SetSoundVolume(complete_order, effects_volume);
    SetSoundVolume(cutting, effects_volume);
    SetSoundVolume(frying, effects_volume);
    SetSoundVolume(leaves, effects_volume);
    SetSoundVolume(peeling, effects_volume);
    SetSoundVolume(washing, effects_volume);
    SetSoundVolume(wrong_order, effects_volume);
    SetSoundVolume(pouring, effects_volume);
    SetSoundVolume(level_complete, effects_volume);
}

void mx_play_sound_effect(Sound sound) {
    PlaySound(sound);
}

void mx_set_effects_volume(float volume) {
    effects_volume = volume;
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
}
