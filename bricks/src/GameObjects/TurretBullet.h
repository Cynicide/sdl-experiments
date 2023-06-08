#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Vector2d.h>

class TurretBullet {
    public:
        TurretBullet(SpriteManager* spriteManager, SDL_FRect position, SDL_FRect paddleRect);
        ~TurretBullet(){};

        void render();    
        void update(double dt);

        SDL_FRect turretBulletRect;

    private:
        void sliceSpriteSheet();
        void moveBullet(double dt);
        void setAngle(SDL_FRect paddleRect);

        // Sprite
        SDL_Texture* turretBulletSprite;
        int turretBulletHeight = 0;
        int turretBulletWidth = 0;

        // Sprite Animation
        static const int numSprites = 3;
        static const int lastSprite = 2;
        float currentFrame = 0.f;
        SDL_Rect turretBulletSpriteClips[numSprites];

        // Movement
        Vector2d vel = {0,0};

        double angle = 0.f;
        int speed = 100;

        double deltaX = 0.f;
        double deltaY = 0.f;
};