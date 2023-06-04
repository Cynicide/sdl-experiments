#pragma once

#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Definitions.h>

class BorderCorner
{
public:
    void render();

    SDL_FRect borderRect;

    BorderCorner(float startX, bool flipX, SpriteManager* spriteManager);
    ~BorderCorner(){};

private:
    float borderStartX = 0.f;
    float borderStartY = 0.f;

    SDL_Texture* borderSprite;
    int textureWidth = 0;
    int textureHeight = 0;

    int angle = 0;
};