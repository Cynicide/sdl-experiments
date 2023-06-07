#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>

#include <TurretBullet.h>

class Turret {
    public:
        Turret(float _xpos, float _ypos, SpriteManager* spriteManager);
        ~Turret();

        void renderBase();
        void renderTurret();
        void update(double dt);
        void update(double dt, SDL_FRect paddleRect);

        SDL_FRect turretRect;
        SDL_FRect collisionRect;

        TurretBullet* turretBullet = nullptr;

    private:
        void SliceSpriteSheet();
        double calculateRotationAngle(SDL_FRect paddleRect);
        SDL_FRect calculateBulletPosition();

        SpriteManager *spriteManager;

        SDL_FPoint rotationPoint = {0, 0};
        float angle = 0.f;

        int bulletWidth = 8;
        int bulletHeight = 8;

        SDL_Texture* turretSprite;
        SDL_Texture* turretBase;

        static const int numSprites = 3;
        SDL_Rect turretSpriteClips[numSprites];
        int turretHeight = 0;
        int turretWidth = 0;

        // ToDo: How do I make a float a static const
        float baseShotTimer = 200.f;
        float shotTimer = 0.f;
        float currentShotTimer = 0.f;
};