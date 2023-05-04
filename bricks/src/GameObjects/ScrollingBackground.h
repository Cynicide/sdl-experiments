#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>

class ScrollingBackground
{
public:
    void render();
    void update(double dt);
    void destroy();

    ScrollingBackground();
    ScrollingBackground(SDL_Texture* sprite);

    ~ScrollingBackground(){};

private:
    // Background Sprite
    SDL_Texture* backgroundSprite;
    int scrollingOffset = 0;
    int textureHeight;
    int textureWidth;
};