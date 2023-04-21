#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>

class Ball
{
public:
    void render();
    void update(float dt);
    void destroy();

    Ball();

    ~Ball(){};

private:
    // Background Sprite
    SDL_Texture* ballSprite;
    SDL_Rect ballRect;

};