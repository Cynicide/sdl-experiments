#pragma once

#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Definitions.h>

class BorderCorner
{
public:
    void render();
    void update(double dt);
    void destroy();

    SDL_FRect borderRect;

    BorderCorner(float startX, float startY, float borderWidth, float borderHeight, bool flipX);
    BorderCorner();
    ~BorderCorner(){};

private:
    // Background Sprite
    SDL_Texture* borderSprite;

    int angle = 0;

    // Sprites
    int borderHeight = 32;
    int borderWidth = 32;
};