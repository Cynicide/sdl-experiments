#ifndef PHYSICS_H
#define PHYSICS_H

#include <Vector2d.h>
#include <SDL2/SDL.h>

class Physics { 
    public:
        Physics();
        float SweptAABB(SDL_FRect rectA, SDL_FRect rectB, Vector2d rectAVel, float &normalx, float &normaly);
        void ProcessCollision(SDL_FRect &rectA, SDL_FRect rectB, Vector2d rectAVel);
        SDL_FRect GetSweptBroadphaseBox(SDL_FRect object, int velx, int vely);
        bool AABBCheck(SDL_FRect rectA, SDL_FRect rectB);
        void Render();
};

#endif