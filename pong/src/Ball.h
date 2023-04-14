#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include <random>
#include <Vector2d.h>
#include <globals.h>
#include <templates.h>

#include <iostream>

class Ball {
    public:
        Vector2d pos;
        Vector2d vel;
        
        int width;
        int height;
        
        float starting_vel;
        float speedup_vel;
        float current_vel;
        float max_vel;
        
        SDL_FRect rect;

        Ball();
        Ball(int px, int py, int vx, int vy, int _width, int _height);
        
        void Move(float dt);

        void RandSetBallVelocity();
        
        void ResetVel();
        
        void ResetPosition(int sWidth, int sHeight);
        
        void SpeedUp();
        
        void Render();

        void UpdateRect();

        void ChangeAngle(int hitLocation);

        void Bounce(int hitLocation);
};

#endif