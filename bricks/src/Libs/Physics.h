#ifndef PHYSICS_H
#define PHYSICS_H

#include <Vector2d.h>
#include <SDL2/SDL.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <iostream>
#include <string>
#include <fstream>

class Physics { 
    public:
        Physics();
        float SweptAABB(SDL_FRect rectA, SDL_FRect rectB, Vector2d rectAVel, float &normalx, float &normaly);
        Vector2d ProcessCollision(SDL_FRect &rectA, SDL_FRect rectB, Vector2d &rectAVel, double dt);
        SDL_FRect GetSweptBroadphaseBox(SDL_FRect object, float velx, float vely);
        bool AABBCheck(SDL_FRect rectA, SDL_FRect rectB);
        void Render();

    private:

        inline void Logger( std::string logMsg ){
            using namespace std;
            
            string filePath = "./game.txt";

            ofstream ofs(filePath.c_str(), std::ios_base::out | std::ios_base::app );
            ofs << logMsg << '\n';
            ofs.close();
        }
};

#endif