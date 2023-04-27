#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Vector2d.h>

class Ball
{
public:
    void render();
    void update(double dt, SDL_FRect paddleRect);
    void update(double dt);
    void destroy();

    void reset();
    void randomizeXDirection();
    void flipY();
    void flipX();

    Ball();
    ~Ball(){};

    Vector2d vel;
    SDL_FRect ballRect;

private:
    SDL_Texture* ballSprite;
    
    int height = 0;
    int width = 0;
    
    Vector2d startingVel = {9, -9};
    
    void move();
};