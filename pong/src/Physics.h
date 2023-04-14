#ifndef PHYSICS_H
#define PHYSICS_H

#include <Vector2d.h>
#include <Ball.h>
#include <Paddle.h>
#include <iostream>

class Physics { 
    public:
        float pxEntry, pyEntry;
        float pxExit, pyExit;

        Physics();
        bool BallVsPaddleCollision(Ball &ball, Paddle paddle);
        float SweptAABB(Ball ball, Paddle paddle, float &normalx, float &normaly);
        void ProcessCollision(Ball &ball, Paddle paddle);
        Ball GetSweptBroadphaseBox(Ball b);
        bool AABBCheck(Ball ball, Paddle paddle);
        void Render();
};

#endif