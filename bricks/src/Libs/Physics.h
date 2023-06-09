#pragma once

#include <Vector2d.h>
#include <SDL2/SDL.h>

class Physics { 
    public:
        Physics();
        double SweptAABB(SDL_FRect rectA, SDL_FRect rectB, Vector2d rectAVel, float &normalx, float &normaly);
        Vector2d ProcessCollision(SDL_FRect &rectA, SDL_FRect rectB, Vector2d &rectAVel, double dt);
        SDL_FRect GetSweptBroadphaseBox(SDL_FRect object, float velx, float vely);
        bool AABBCheck(SDL_FRect rectA, SDL_FRect rectB);
        void Render();

    private:

};
