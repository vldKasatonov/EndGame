#pragma once

#include "header.h"

typedef struct GameTextures {
    Texture2D gearTexture;
    Texture2D volume_on;
    Texture2D volume_on2;
    Texture2D music_on;
    Texture2D volume_off;
    Texture2D music_off;
    Texture2D arrow;
    Texture2D del_texture;
    Texture2D guide;
    Texture2D exit;
    Texture2D pause;
    Texture2D background;
    Texture2D play_button;
    Texture2D star;
    Texture2D one_player;
    Texture2D two_players;
    Texture2D chef;
    Texture2D right_arrow;
    Texture2D left_arrow;
    Texture2D map3;
    Texture2D image3;
    Texture2D level_preview;
    Texture2D served_icon;
    Texture2D guest;
    Texture2D reversedGuest;
    Texture2D dirtyApple;
    Texture2D washedApple;
    Texture2D slicedApple;
    Texture2D juice;
    Texture2D dirtyPotato;
    Texture2D washedPotato;
    Texture2D slicedPotato;
    Texture2D peeledPotato;
    Texture2D friedPotato;
    Texture2D dirtyCucumber;
    Texture2D washedCucumber;
    Texture2D slicedCucumber;
    Texture2D dirtyTomato;
    Texture2D washedTomato;
    Texture2D slicedTomato;
    Texture2D salad;
    Texture2D guideJuice;
    Texture2D guidePotato;
    Texture2D guideSalad;
    Texture2D image1;
    Texture2D image2;
    Texture2D map1;
    Texture2D map2;
    Texture2D cloud;
    Texture2D fButton;
} GameTextures;

void LoadTextures(GameTextures *textures);
void UnloadTextures(GameTextures *textures);

