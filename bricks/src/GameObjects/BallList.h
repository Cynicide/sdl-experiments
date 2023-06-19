#pragma once

#include <SDL2/SDL.h>
#include <Ball.h>
#include <SpriteManager.h>
#include <AudioManager.h>
#include <memory>

class BallList {
public:
        BallList(SpriteManager* spriteManager, AudioManager* audioManager);
        ~BallList();

        void add();
        void fillAtLocation(float x, float y, float currentVel);
        void remove(int index);
        void clear();
        std::shared_ptr<Ball> get(int index);
        void update(double dt, SDL_FRect paddleRect);
        void render();
        void updateServing(double dt, SDL_FRect paddleRect);

        void unstickAll();
        void setSpeed(int speed);

        const static int MAXBALLS = 3;

private:
        std::shared_ptr<Ball> ballList[MAXBALLS];

        SpriteManager* spriteManager;
        AudioManager* audioManager;
};