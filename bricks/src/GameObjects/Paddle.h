#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>

class Paddle
{
public:
    void render();
    void update(float dt);
    void destroy();

    Paddle();

    ~Paddle(){};

private:
    // Background Sprite
    SDL_Texture* paddleSprite;
    SDL_Rect paddleRect;

};