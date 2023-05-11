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

    // Sprites
    SDL_Texture* stars;
    SDL_Texture* logo;
    SDL_Texture* background;
    SDL_Texture* paddle;
    SDL_Texture* ball;
    SDL_Texture* lightning;
    SDL_Texture* brickRed;
    SDL_Texture* brickBlue;
    SDL_Texture* brickYellow;
    SDL_Texture* brickTough;
    SDL_Texture* brickIndestructable;
    SDL_Texture* brickGreen;
    SDL_Texture* brickPurple;
    SDL_Texture* brickOrange;
    SDL_Texture* shipExplosion;
    SDL_Texture* techBorder;
    SDL_Texture* techCorner;
    SDL_Texture* techTopBorder;

    void loadSprites();

private:
    SDL_Surface* loadSurface(std::string path);
    SDL_Texture* loadAlphaTexture(std::string path);
    SDL_Texture* loadTexture(std::string path);
};