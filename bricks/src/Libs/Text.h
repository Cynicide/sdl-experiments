#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <globals.h>
#include <string>

// ToDo: Turn this into a Manager Class

class Text {
    public:
        SDL_Texture * texture;
        SDL_Rect textRect;
        SDL_Surface * surface;
        int textW;
        int textH;
        Text();
        Text(TTF_Font * font, std::string text, int x_loc, int y_loc, SDL_Renderer* gRenderer);
        void SetPos(int x, int y);
        void Destroy();
        void Render();
};


#endif