#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>

class Powerup {

public:
    Powerup(SpriteManager *spriteManager, float parentXPos, float parentYPos, int parentWidth);
    ~Powerup(){};
    void update(double dt);
    void render();

    SDL_FRect powerupRect;

private:
    void SliceSpriteSheet();
    void move(double dt);
    
    SDL_Texture* powerupSprite;
    static const int numSprites = 11;
    static const int lastFrame = 10;
    SDL_Rect powerupSpriteClips[numSprites];
    float currentFrame = 0.f;
    int powerupHeight = 0;
    int powerupWidth = 0;

    float yVel = 250.0f;
};