#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class TextManager
{
public:
    TextManager();
    ~TextManager(){};

    void loadFonts();

    TTF_Font* publicPixel12;
    TTF_Font* publicPixel24;

private:


};