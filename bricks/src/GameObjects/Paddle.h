#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>

class Paddle
{
public:
    void render();
    void update(double dt);
    void destroy();

    SDL_FRect paddleRect;

    Paddle();

    ~Paddle(){};

private:
    // Background Sprite
    SDL_Texture* paddleSprite;


};