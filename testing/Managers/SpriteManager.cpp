#include <SpriteManager.h>

#include <SDL2/SDL_image.h>

SpriteManager SpriteManager::sSpriteManager;

SpriteManager::SpriteManager() {

    background = loadTexture("assets\\images\\background2.png");

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
        SDL_Log( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        if( optimizedSurface == NULL )
        {
            SDL_Log( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
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