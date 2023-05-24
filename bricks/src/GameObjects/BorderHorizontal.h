#pragma once

#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Definitions.h>

class BorderHorizontal
{
public:
    void render();

    SDL_FRect borderRect;

    BorderHorizontal(float startX, bool flipX, SpriteManager *spriteManager);
    ~BorderHorizontal(){};

private:
    // Sprites
    float borderStartX = 0.f;
    float borderStartY = 0.f;
    int borderHeight = 0;
    float borderWidth = 0.f;
    int borderSpriteWidth = 0;

    SDL_Texture* borderSprite;

    int angle = 0;
};