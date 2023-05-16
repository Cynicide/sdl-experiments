#pragma once
#include <SDL2/SDL.h>

class Powerup {

public:
    Powerup(SDL_Texture* powerupSprite, float parentXPos, float parentYPos, int parentWidth);
    ~Powerup(){};
    void update(double dt);
    void render();

    SDL_FRect powerupRect;

private:
    void SliceSpriteSheet();
    void move(double dt);
    
    SDL_Texture* powerupSprite;
    static const int numSprites = 10;
    static const int lastFrame = 9;
    SDL_Rect powerupSpriteClips[numSprites];
    float currentFrame = 0.f;
    int powerupHeight = 0;
    int powerupWidth = 0;

    float yVel = 250.0f;
};