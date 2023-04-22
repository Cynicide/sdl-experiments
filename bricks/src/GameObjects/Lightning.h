#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <random>

class Lightning
{
public:
    void render();
    void update(double dt);
    void destroy();

    SDL_FRect bBorder;

    Lightning();

    ~Lightning(){};

private:
    // Background Sprite
    SDL_Texture* lightningSprite;
    SDL_Rect lightningRect;

    int borderHeight = 16;
    int borderWidth = 32;
};