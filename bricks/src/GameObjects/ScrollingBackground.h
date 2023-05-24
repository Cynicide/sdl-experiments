#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <globals.h>

class ScrollingBackground
{
public:
    void render();
    void update(double dt);
    void destroy();

    ScrollingBackground(SpriteManager *spriteManager);
    ~ScrollingBackground(){};

private:
    // Background Sprite
    SDL_Texture *backgroundSprite;
    int textureWidth;
    int textureHeight;
    float scrollingOffset = 0.f;
};