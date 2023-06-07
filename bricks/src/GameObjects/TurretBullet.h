#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Vector2d.h>

class TurretBullet {
    public:
        TurretBullet(SpriteManager* spriteManager, SDL_FRect position, double angle);
        ~TurretBullet(){};

        void render();    
        void update(double dt);

        SDL_FRect turretBulletRect;

    private:
        void SliceSpriteSheet();
        void moveBullet(double dt);

        SDL_Texture* turretBulletSprite;

        Vector2d vel = {0,0};

        static const int numSprites = 3;
        static const int lastSprite = 2;
        SDL_Rect turretBulletSpriteClips[numSprites];
        int turretBulletHeight = 0;
        int turretBulletWidth = 0;

        double angle = 0.f;
        int speed = 100;
};