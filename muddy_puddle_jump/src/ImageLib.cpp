#include <ImageLib.h>

ImageLib ImageLib::sImageLib;

ImageLib::ImageLib() {

}

ImageLib* ImageLib::get()
{
    //Get static instance
    return &sImageLib;
}

SDL_Surface* ImageLib::loadSurface( std::string path) {
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

SDL_Texture* ImageLib::loadTexture(std::string path) {
    SDL_Surface* surface = loadSurface(path);
    Uint32 bgcolorkey = SDL_MapRGBA(surface->format, 0, 0, 0, 0);
    SDL_SetColorKey(surface, SDL_TRUE, bgcolorkey);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
