#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Vector2d.h>

class Ball
{
public:

    Ball(SpriteManager* spriteManager);
    Ball(SpriteManager* spriteManager, float x, float y, float currentVel);
    ~Ball(){};

    // State Methods
    void update(double dt);
    void update(double dt, SDL_FRect paddleRect);
    void updateStuck(double dt, SDL_FRect paddleRect);
    void render();
    void reset();

    // Collision
    void hitTopWall(SDL_FRect border);
    void hitRightWall(SDL_FRect border);
    void hitLeftWall(SDL_FRect border);    
    void hitLightning();
    void hitPaddle(Vector2d normals, SDL_FRect paddleRect);
    void hitBrick(Vector2d normals);

 
    // Movement
    void speedUp();
    float getCurrentVel();
    void setSpeed(int ballSpeed);
    void changeAngle(int hitLocation, int paddleSize);
    Vector2d vel;
    SDL_FRect ballRect;

    // Magnetic Powerup
    void setStuckOffset(int offset);
    void resetStuckOffset();
    void stickToPaddle();
    void releaseFromPaddle();

    bool stuckToPaddle = false; // Is the ball stuck to the paddle?
    int stuckOffset = 0; // The offset from the center when stuck.

private:
    // Sprite 
    SDL_Texture* ballSprite = NULL;
    int ballHeight = 0;
    int ballWidth = 0;

    // Velocity    
    int maxVel = 500;
    int startingVel = 400;
    int speedUpAmount = 20;
    float currentVel = 0;

    void flipY();
    void flipX();
    void move(double dt);
};