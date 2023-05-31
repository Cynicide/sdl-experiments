#pragma once

#include <globals.h>
#include <string>
#include <SDL2/SDL.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class SpriteManager
{
public:

    SpriteManager();
    ~SpriteManager();

    bool getTextureDimensions(SDL_Texture* texture, int& width, int& height);

    // Sprites
    SDL_Texture* stars;
    SDL_Texture* logo;
    SDL_Texture* background;

    SDL_Texture* paddle;
    SDL_Texture* longPaddle;
    SDL_Texture* laserPaddle;
    SDL_Texture* shipExplosion;

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

    void loadSprites();


private:
    SDL_Surface* loadSurface(std::string path);
    SDL_Texture* loadAlphaTexture(std::string path);
    SDL_Texture* loadTexture(std::string path);
};