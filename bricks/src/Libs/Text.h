#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <globals.h>
#include <string>

class Text {
    public:
        Text();
        Text(TTF_Font * font, std::string text, float x_loc, float y_loc, SDL_Renderer* gRenderer);

        void destroy();
        void render();

        int getXLocation();
        int getYLocation();
        void setVerticalOffset( int offset);
        void setHorizontalOffset( int offset);

        void padLeft(int padding);

        void setPos(int x, int y);
        void centerHorizontally(int screen_width);
        void centerVetically(int screen_height);
        void center(int screen_width, int screen_height);
        void moveTopQuarter(int screen_height);
        void moveBottomQuarter(int screen_height);

        void moveBottomLeft(int screen_height, int screen_width, int* playfield_start_x);
        void offsetAboveVertically(int offsetObjectY, int offsetObjectX);


    private:
        SDL_Texture * texture;
        SDL_FRect textRect;
        SDL_Surface * surface;

        int verticalOffset = 10;
        int horizontalOffset = 10;

        int textW;
        int textH;
};