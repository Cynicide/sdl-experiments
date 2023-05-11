#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>

class TiledBackground
{
public:
    // Constructor/Destructor
    TiledBackground(SDL_Texture* backgroundSprite);
    TiledBackground();
    ~TiledBackground(){};

    //Game loop functions
    void render();

private:
    // Background Sprite Resources
    SDL_Texture* backgroundSprite;
    int textureHeight = 0;
    int textureWidth = 0;
};