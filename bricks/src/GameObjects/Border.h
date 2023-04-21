#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>

class Border
{
public:
    void render();
    void update(float dt);
    void destroy();

    SDL_Rect lBorder;
    SDL_Rect rBorder;
    SDL_Rect tBorder;

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