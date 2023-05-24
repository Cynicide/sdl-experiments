#pragma once

#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Definitions.h>

class LifeCounter
{
public:
    LifeCounter(float startX, SpriteManager *spriteManager);
    ~LifeCounter(){};

    void render(int lives);

    SDL_FRect lifeCounterRect;



private:

    SDL_Texture* lifeCounterSprite;
    SDL_Texture* lifeIconSprite;

    int lifeIconW = 0;
    int lifeIconH = 0;
    int lifeCounterW = 0;
    int lifeCounterH = 0;

    int angle = 0;
};