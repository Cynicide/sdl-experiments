#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Definitions.h>

class Powerup {

public:
    Powerup(SpriteManager* spriteManager, float parentXPos, float parentYPos, int parentWidth);
    ~Powerup(){};
    void update(double dt);
    void render();
    void randomizePowerup();

    SDL_FRect powerupRect;
    Definitions::PowerUpType powerupType;

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

        /*
    Powerup Ranges

    Extra Life  0 - 5    5%
    Slow        6 - 28   22%
    Wide        29 - 52  23%
    Triple      53 - 69  16%
    Laser       70 - 79  10% 
    LevelSkip:  80 - 85  5%    
    Magnetic:   86 - 100 15%
    */
    
    /*int extraLifeChance = 1;
    int slowBallChance = 2;
    int wideChance = 3;
    int tripleBallChance = 4;
    int laserChance = 54;
    int levelSkipChance = 55;
    int magneticChance = 100;*/

    int extraLifeChance = 5;
    int slowBallChance = 28;
    int wideChance = 52;
    int tripleBallChance = 69;
    int laserChance = 79;
    int levelSkipChance = 85;
    int magneticChance = 100;
};