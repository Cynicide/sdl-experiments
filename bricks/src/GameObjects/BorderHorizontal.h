#pragma once

#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Definitions.h>

class BorderHorizontal
{
public:
    void render();
    void update(double dt);
    void destroy();

    SDL_FRect borderRect;

    BorderHorizontal(float startX, float startY, float borderWidth, float borderHeight, bool flipX);
    BorderHorizontal();
    ~BorderHorizontal(){};

private:
    // Background Sprite
    SDL_Texture* borderSprite;

    int angle = 0;

    // Sprites
    int borderHeight = 32;
    int borderWidth = 128;

//    int techBorderHeightV = 128;
//    int techBorderWidthV = 32;

//    int techCornerHeight = 32;
//    int techCornerWidth = 32;
};