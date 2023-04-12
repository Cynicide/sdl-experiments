#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>
#include <Vector2d.h>
#include <Text.h>
#include <globals.h>

class Paddle {
    public:
        Vector2d pos;
        Vector2d vel;
        int width;
        int height;
        int score;
        
        SDL_FRect rect;

        Text scoreText;
        Paddle();
        Paddle(int px, int py, int vx, int vy, int _width, int _height, int _score);
        void Destroy();
        void ResetPos(int sHeight);
        void ResetScore();
        void MoveUp();
        void MoveDown(int sHeight);
        void UpdateRect();
        void Render();
};

#endif