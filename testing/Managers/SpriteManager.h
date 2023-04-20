#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <globals.h>
#include <string>
#include <SDL2/SDL.h>

class SpriteManager
{
public:
    //Static accessor
    static SpriteManager* get();

    // Background Sprite

    SDL_Texture* background;

    SDL_Surface* loadSurface(std::string path);
    SDL_Texture* loadAlphaTexture(std::string path);
    SDL_Texture* loadTexture(std::string path);

private:
    //Static instance
    static SpriteManager sSpriteManager;


    //Private constructor
    SpriteManager();

    // PrivateDestructor
    ~SpriteManager(){};

};
#endif