#pragma once

#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Definitions.h>

class BorderCorner
{
public:
    void render();

    SDL_FRect borderRect;

    BorderCorner(float startX, bool flipX, SDL_Texture* borderSprite);
    ~BorderCorner(){};

private:
    float borderStartX = 0.f;
    float borderStartY = 0.f;
    float borderHeight = 0.f;
    float borderWidth = 0.f;

    SDL_Texture* borderSprite;

    int angle = 0;
};