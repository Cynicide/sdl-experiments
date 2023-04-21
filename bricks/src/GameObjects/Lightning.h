#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <random>

class Lightning
{
public:
    void render();
    void update(float dt);
    void destroy();

    SDL_Rect bBorder;

    Lightning();

    ~Lightning(){};

private:
    // Background Sprite
    SDL_Texture* lightningSprite;
    SDL_Rect lightningRect;
};