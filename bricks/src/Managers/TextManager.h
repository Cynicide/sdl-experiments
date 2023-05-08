#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class TextManager
{
public:
    //Static accessor
    static TextManager* get();
    TTF_Font* publicPixel12;
    TTF_Font* publicPixel24;
    void loadFonts();

private:
    //Static instance
    static TextManager sTextManager;


    //Private constructor
    TextManager();

    // PrivateDestructor
    ~TextManager(){};

};