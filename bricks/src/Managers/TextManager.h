#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class TextManager
{
public:
    //Static accessor
    static TextManager* get();
    TTF_Font* publicPixel12 = TTF_OpenFont("assets\\fonts\\PublicPixel.ttf", 12);
    void loadFonts();

private:
    //Static instance
    static TextManager sTextManager;


    //Private constructor
    TextManager();

    // PrivateDestructor
    ~TextManager(){};

};
#endif