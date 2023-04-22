#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>

class Background
{
public:
    void render();
    void update(double dt);
    void destroy();

    Background();

    ~Background(){};

private:
    // Background Sprite
    SDL_Texture* backgroundSprite;

};