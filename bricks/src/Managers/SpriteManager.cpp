#include <SpriteManager.h>

#include <SDL2/SDL_image.h>
#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

SpriteManager SpriteManager::sSpriteManager;

SpriteManager::SpriteManager() {


}

SpriteManager* SpriteManager::get()
{
    //Get static instance
    return &sSpriteManager;
}

SDL_Surface* SpriteManager::loadSurface( std::string path) {
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        spdlog::error( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    return loadedSurface;
}

SDL_Texture* SpriteManager::loadAlphaTexture(std::string path) {
    SDL_Surface* surface = loadSurface(path);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);

    bool bQuery = SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    if (bQuery == 1) {
        spdlog::info("Error setting Texture Blend Mode: ");
        spdlog::info(SDL_GetError());
    }
    SDL_FreeSurface(surface);
    return texture;
    
}

SDL_Texture* SpriteManager::loadTexture(std::string path) {
    SDL_Surface* surface = loadSurface(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_FreeSurface(surface);
    return texture;

}

void SpriteManager::loadSprites() {
    stars = loadAlphaTexture("assets\\images\\stars.png");
    logo = loadAlphaTexture("assets\\images\\logo.png");
    background = loadAlphaTexture("assets\\images\\background.png");
    paddle = loadAlphaTexture("assets\\images\\paddle.png");
    ball = loadAlphaTexture("assets\\images\\ball.png");
    border = loadTexture("assets\\images\\border-sheet.png");
    lightning = loadAlphaTexture("assets\\images\\lightning.png");
    brickRed = loadAlphaTexture("assets\\images\\brick-red-sheet.png");
    brickBlue = loadAlphaTexture("assets\\images\\brick-blue-sheet.png");
    brickYellow = loadAlphaTexture("assets\\images\\brick-yellow-sheet.png");
    brickGreen = loadAlphaTexture("assets\\images\\brick-green-sheet.png");
    brickPurple = loadAlphaTexture("assets\\images\\brick-purple-sheet.png");
    brickOrange = loadAlphaTexture("assets\\images\\brick-orange-sheet.png");
    brickTough = loadAlphaTexture("assets\\images\\brick-tough-sheet.png");
    brickIndestructable = loadAlphaTexture("assets\\images\\brick-indestructable-sheet.png");
    shipExplosion = loadAlphaTexture("assets\\images\\explosion-sheet.png");
}