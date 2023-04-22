#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>

class Ball
{
public:
    void render();
    void update(double dt, SDL_Rect paddleRect);
    void update(double dt);
    void destroy();

    void reset();
    void randomizeXDirection();
    void flipY();
    void flipX();

    Ball();

    ~Ball(){};

    float yVel = -150.f;
    float xVel = 150.f;
    SDL_FRect ballRect;

private:
    // Background Sprite
    SDL_Texture* ballSprite;
    int height = 0;
    int width = 0;

    void move(double dt);
};