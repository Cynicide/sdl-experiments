#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Vector2d.h>

class Ball
{
public:

    Ball(SDL_Texture* ballSprite);
    ~Ball(){};

    // State Methods
    void render();
    void update(double dt, SDL_FRect paddleRect);
    void update(double dt); 

    // Collision
    void hitTopWall(SDL_FRect border);
    void hitRightWall(SDL_FRect border);
    void hitLeftWall(SDL_FRect border);    
    void hitPaddle(Vector2d normals, SDL_FRect paddleRect);
    void hitBrick(Vector2d normals);
    void hitLightning();

    // Other
    void changeAngle(int hitLocation, int paddleSize);
    void reset();
    void randomizeXDirection();

    // Velocity and Dimensions
    Vector2d vel;
    SDL_FRect ballRect;

private:
    // Sprite 
    SDL_Texture* ballSprite = NULL;
    int ballHeight = 0;
    int ballWidth = 0;

    // Velocity    
    Vector2d startingVel;
    Vector2d currentVel;

    void flipY();
    void flipX();
    void move();
};