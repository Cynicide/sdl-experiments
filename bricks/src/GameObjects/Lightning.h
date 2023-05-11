#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <random>

class Lightning
{
public:

    Lightning(SDL_Texture* lightningSprite);
    ~Lightning(){};

    void render();

    SDL_FRect bBorder;

private:
    SDL_Texture* lightningSprite;

    float borderHeight = 16;
    float borderWidth = 32;
};