#pragma once
#include <SpriteManager.h>
#include <Definitions.h>

class Bullet {

    public:
        Bullet(SpriteManager* spriteManager, float xLocation, float yLocation);
        ~Bullet(){};
        SDL_FRect bulletRect;

        void update(double dt);
        void render();
        void hit();
        void destroy();
        void move(double dt);

    private:

        SDL_Texture* bulletSprite;

        int bulletWidth = 0;
        int bulletHeight = 0;
        const static int numSprites = 8;
        SDL_Rect bulletSpriteClips[numSprites];

        int maxVel = 1300;
        int startingVel = 1000;
        int speedUpAmount = 200;
        float currentVel = 0;

        Definitions::BulletStatus bulletStatus = Definitions::BulletStatus::BulletGood;

        void sliceSpriteSheet();
};