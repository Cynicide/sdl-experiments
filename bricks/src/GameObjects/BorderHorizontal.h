#pragma once

#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Definitions.h>

class BorderHorizontal
{
public:
    void render();

    SDL_FRect borderRect;

    BorderHorizontal(float startX, bool flipX, SDL_Texture* borderSprite);
    ~BorderHorizontal(){};

private:
    // Sprites
    float borderStartX = 0.f;
    float borderStartY = 0.f;
    float borderHeight = 0.f;
    float borderWidth = 0.f;
    float borderSpriteWidth = 0.f;

    SDL_Texture* borderSprite;

    int angle = 0;
};