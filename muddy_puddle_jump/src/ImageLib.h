#ifndef IMAGELIB_H
#define IMAGELIB_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <globals.h>

class ImageLib
{
public:
    //Static accessor
    static ImageLib* get();

    SDL_Surface* loadSurface(std::string path);
    SDL_Texture* loadTexture(std::string path);

private:
    //Static instance
    static ImageLib sImageLib;

    //Private constructor
    ImageLib();

};
#endif
