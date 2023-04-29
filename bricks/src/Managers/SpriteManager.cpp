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
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        spdlog::error( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        if( optimizedSurface == NULL )
        {
            spdlog::error( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

SDL_Texture* SpriteManager::loadAlphaTexture(std::string path) {
    SDL_Surface* surface = loadSurface(path);

    Uint32 bgcolorkey = SDL_MapRGB(surface->format, 0, 0, 0);
    SDL_SetColorKey(surface, SDL_TRUE, bgcolorkey);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
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
    background = loadTexture("assets\\images\\background.png");
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
}