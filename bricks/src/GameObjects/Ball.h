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

    void reset();
    void randomizeXDirection();


    void hitTopWall(SDL_FRect border);
    void hitRightWall(SDL_FRect border);
    void hitLeftWall(SDL_FRect border);    
    void hitPaddle(Vector2d normals, SDL_FRect paddleRect);
    void hitBrick(Vector2d normals);
    void hitLightning();

    void ChangeAngle(int hitLocation, int paddleSize);

    Ball();
    ~Ball(){};

    Vector2d vel;
    SDL_FRect ballRect;

private:
    SDL_Texture* ballSprite = NULL;
    
    int height = 0;
    int width = 0;
    
    Vector2d startingVel;
    Vector2d currentVel;
    void flipY();
    void flipX();
    
    void move();
};