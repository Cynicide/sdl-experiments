#pragma once
#include <SpriteManager.h>
#include <SDL2/SDL.h>

class Logo {

public:
    Logo(SpriteManager *spriteManager);
    ~Logo(){};
    void render();
    void update(double dt);

private:

    SDL_FRect logoRect;
    SDL_Texture *logoTexture;
    float logoXPos = 0.f;
    float logoYPos = 0.f;
    int logoWidth = 0;
    int logoHeight = 0;
};