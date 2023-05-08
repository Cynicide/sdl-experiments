#pragma once

#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Definitions.h>

class BorderVertical
{
public:
    void render();
    void update(double dt);
    void destroy();

    SDL_FRect borderRect;

    BorderVertical(float startX, float startY, float borderWidth, float borderHeight, bool flipX);
    BorderVertical();
    ~BorderVertical(){};

private:
    // Background Sprite
    SDL_Texture* borderSprite;

    int angle = 0;

    // Sprites
    int borderHeight = 128;
    int borderWidth = 32;
};