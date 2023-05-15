#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>

class ScrollingBackground
{
public:
    void render();
    void update(double dt);
    void destroy();

    ScrollingBackground(SDL_Texture* sprite);
    ~ScrollingBackground(){};

private:
    // Background Sprite
    SDL_Texture* backgroundSprite;
    float scrollingOffset = 0.f;
    int textureHeight;
    int textureWidth;
};