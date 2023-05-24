#pragma once

#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Definitions.h>

class BorderVertical
{
public:
    void render();

    SDL_FRect borderRect;

    BorderVertical(float startX, bool flipX, SpriteManager *spriteManager);
    ~BorderVertical(){};

private:
    // Sprites
    float borderStartX = 0.f;
    float borderStartY = 0.f;
    float borderHeight = 0.f;
    int borderWidth = 0;
    int borderSpriteHeight = 0;

    SDL_Texture* borderSprite;

    int angle = 0;
};