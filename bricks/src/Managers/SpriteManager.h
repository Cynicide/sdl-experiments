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
    SDL_Texture* paddle;
    SDL_Texture* ball;
    SDL_Texture* border;
    SDL_Texture* lightning;
    SDL_Texture* brickRed;
    SDL_Texture* brickBlue;
    SDL_Texture* brickYellow;
    SDL_Texture* brickTough;
    SDL_Texture* brickIndestructable;

    SDL_Surface* loadSurface(std::string path);
    SDL_Texture* loadAlphaTexture(std::string path);
    SDL_Texture* loadTexture(std::string path);

    void loadSprites();

private:
    //Static instance
    static SpriteManager sSpriteManager;


    //Private constructor
    SpriteManager();

    // PrivateDestructor
    ~SpriteManager(){};

};
#endif