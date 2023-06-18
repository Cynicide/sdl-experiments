#pragma once
#include <PlayerBullet.h>
#include <SpriteManager.h>
#include <AudioManager.h>
#include <SDL2/SDL.h>

class PlayerBulletList {
    public:
        PlayerBulletList(SpriteManager* spriteManager, AudioManager* audioManager);
        ~PlayerBulletList();

        void shoot(SDL_FRect paddleRect);
        void remove(int index);
        void clear();
        PlayerBullet* get(int index);
        void update(double dt);
        void render();

        const static int MAXBULLETS = 2;

    private:
        PlayerBullet* bulletList[MAXBULLETS] = {};

        SpriteManager* spriteManager;
        AudioManager* audioManager;
};