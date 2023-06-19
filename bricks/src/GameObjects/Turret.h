#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> 
#include <SpriteManager.h>
#include <Audiomanager.h>
#include <Definitions.h>
#include <TurretBullet.h>

class Turret {
    public:
        Turret(float _xpos, float _ypos, SpriteManager* spriteManager, AudioManager* audioManager);
        ~Turret();

        void renderBase();
        void renderTurret();
        void update(double dt);
        void update(double dt, SDL_FRect paddleRect);
        void updateServe(double dt, SDL_FRect paddleRect);

        void deleteBullet();
        void hitTurret();
        bool isGood();

        SDL_FRect turretRect;
        SDL_FRect collisionRect;
        SDL_FRect explosionRect;

        TurretBullet* turretBullet = nullptr;
        Definitions::TurretStatus turretStatus = Definitions::TurretStatus::TurretGood;

    private:
        void sliceSpriteSheet();
        void sliceExplosionSpriteSheet();
        double calculateRotationAngle(SDL_FRect paddleRect);
        void explode();

        SDL_FRect calculateBulletPosition();

        SpriteManager *spriteManager;

        Mix_Chunk* explosionSound;

        SDL_FPoint rotationPoint = {0, 0};
        float angle = 0.f;

        int bulletWidth = 8;
        int bulletHeight = 8;

        SDL_Texture* turretSprite;
        SDL_Texture* turretBase;
        SDL_Texture* turretExplosion;

        int turretHeight = 0;
        int turretWidth = 0;

        static const int numSprites = 3;
        static const int lastSprite = 2;
        SDL_Rect turretSpriteClips[numSprites];
        float currentSprite = 0.f;

        int turretGunHeight = 0;
        int turretGunWidth = 0;

        static const int numExplosionSprites = 8;
        static const int lastExplosionSprite = 7;
        SDL_Rect turretExplosionSpriteClips[numExplosionSprites];
        float currentExplosionSprite = 0.f;
        int explosionSpriteWidth = 0;
        int explosionSpriteHeight = 0;

        // ToDo: How do I make a float a static const
        float baseShotTimer = 400.f;
        float shotTimer = 0.f;
        float currentShotTimer = 0.f;

        int bulletTimeVariance = 50;

        bool explosionSoundPlayed = false;
};