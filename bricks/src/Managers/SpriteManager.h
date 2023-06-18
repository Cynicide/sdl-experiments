#pragma once

#include <globals.h>
#include <string>
#include <SDL2/SDL.h>

class SpriteManager
{
public:
    SpriteManager();
    ~SpriteManager();
    void loadSprites();
    bool getTextureDimensions(SDL_Texture* texture, int& width, int& height);

    // Sprites
    SDL_Texture* stars;
    SDL_Texture* logo;
    SDL_Texture* background;
    SDL_Texture* letsGoTop;
    SDL_Texture* letsGoBottom;
    SDL_Texture* levelCompleteTop;
    SDL_Texture* levelCompleteBottom;
    SDL_Texture* gameOverTop;
    SDL_Texture* gameOverBottom;    

    SDL_Texture* paddle;
    SDL_Texture* longPaddle;
    SDL_Texture* laserPaddle;
    SDL_Texture* shipExplosion;
    SDL_Texture* turret;
    SDL_Texture* turretBase;
    SDL_Texture* turretBullet;
    SDL_Texture* turretExplosion;

    SDL_Texture* ball;
    SDL_Texture* bullet;
    
    SDL_Texture* brickRed;
    SDL_Texture* brickBlue;
    SDL_Texture* brickYellow;
    SDL_Texture* brickTough;
    SDL_Texture* brickIndestructable;
    SDL_Texture* brickGreen;
    SDL_Texture* brickPurple;
    SDL_Texture* brickOrange;

    SDL_Texture* techBorder;
    SDL_Texture* techCorner;
    SDL_Texture* techTopBorder;
    SDL_Texture* lightning;
    
    SDL_Texture* lifeCounter;
    SDL_Texture* lifeIcon;

    SDL_Texture* capsuleLaser;
    SDL_Texture* capsuleExtraLife;
    SDL_Texture* capsuleSlow;    
    SDL_Texture* capsuleTriple;
    SDL_Texture* capsuleWide;
    SDL_Texture* capsuleJump;
    SDL_Texture* capsuleMagnetic;

    SDL_Texture* levelWarpPortal;
    SDL_Texture* levelWarpArrow;
    
private:
    SDL_Surface* loadSurface(std::string path);
    SDL_Texture* loadAlphaTexture(std::string path);
    SDL_Texture* loadTexture(std::string path);
};