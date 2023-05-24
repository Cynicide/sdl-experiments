#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <random>

class Lightning
{
public:

    Lightning(SpriteManager *spriteManager);
    ~Lightning(){};

    void render();

    SDL_FRect bBorder;

private:
    SDL_Texture* lightningSprite;

    int borderHeight = 0;
    int borderWidth = 0;
};