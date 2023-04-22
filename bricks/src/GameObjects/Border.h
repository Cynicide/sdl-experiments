#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>

class Border
{
public:
    void render();
    void update(double dt);
    void destroy();

    SDL_FRect lBorder;
    SDL_FRect rBorder;
    SDL_FRect tBorder;

    Border();

    ~Border(){};

private:
    // Background Sprite
    SDL_Texture* borderSprite;
    SDL_Rect borderRect;

    int borderHeight = 32;
    int borderWidth = 32;

    int numSprites = 2;
    SDL_Rect borderSpriteClips[2];

    void SliceSpriteSheet();

};