#include <Turret.h>
#include <random>
#include <globals.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

Turret::Turret(float _xpos, float _ypos, SpriteManager* spriteManager, AudioManager* audioManager)
{
    this->turretSprite = spriteManager->turret;
    this->turretBase = spriteManager->turretBase;
    this->turretExplosion = spriteManager->turretExplosion;
    this->spriteManager = spriteManager;
    this->explosionSound = audioManager->turretExplosion;

    spriteManager->getTextureDimensions(turretSprite, turretGunWidth, turretGunHeight);
    spriteManager->getTextureDimensions(turretBase, turretWidth, turretHeight);
    spriteManager->getTextureDimensions(turretExplosion, explosionSpriteWidth, explosionSpriteHeight);

    // Slightly randomize the time between shots
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distribution(-bulletTimeVariance, bulletTimeVariance);
    int randomNumber = distribution(engine);
    shotTimer = baseShotTimer + randomNumber;

    rotationPoint = {(float)(turretWidth / 2), (float)(turretHeight * 0.25f)};
    
    turretRect = {_xpos, _ypos, (float)turretGunWidth / numSprites, (float)turretGunHeight};
    collisionRect = {_xpos, _ypos, (float)turretWidth, (float)turretHeight / 2};
    explosionRect = {_xpos, _ypos, (float)turretWidth / numExplosionSprites, (float)turretHeight};
    
    sliceSpriteSheet();
    sliceExplosionSpriteSheet();

}

Turret::~Turret() {
    if (turretBullet != nullptr) {
        delete turretBullet;
        turretBullet = nullptr;
    }
}

void Turret::sliceSpriteSheet() {
    for( int i = 0; i <= numSprites - 1; i++ ) {
        turretSpriteClips[ i ].x =   i * (turretGunWidth / numSprites);
        turretSpriteClips[ i ].y =   0;
        turretSpriteClips[ i ].w =  (turretGunWidth / numSprites);
        turretSpriteClips[ i ].h = turretGunHeight;
        }
}

void Turret::sliceExplosionSpriteSheet() {
    for( int i = 0; i <= numExplosionSprites - 1; i++ ) {
        turretExplosionSpriteClips[ i ].x =   i * (explosionSpriteWidth / numExplosionSprites);
        turretExplosionSpriteClips[ i ].y =   0;
        turretExplosionSpriteClips[ i ].w =  (explosionSpriteWidth / numExplosionSprites);
        turretExplosionSpriteClips[ i ].h = explosionSpriteHeight;
        }
}

void Turret::update(double dt) {

    if (angle != 0.f) {
        angle = 0.f;
    }
    currentSprite = currentSprite + (15 * dt);
    if ((int)currentSprite > (float)lastSprite) {
        currentSprite = 0.0f;
    }
}

void Turret::updateServe(double dt, SDL_FRect paddleRect) {
    angle = calculateRotationAngle(paddleRect);
    currentSprite = currentSprite + (15 * dt);
    if ((int)currentSprite > (float)lastSprite) {
        currentSprite = 0.0f;
    }
}

void Turret::hitTurret() {
    turretStatus = Definitions::TurretStatus::TurretExploding;
    currentShotTimer = 0.f;
    if (explosionSoundPlayed == false) {
        explode();
        explosionSoundPlayed = true;
    }
}

void Turret::explode() {
    if (Mix_Playing(5)) {
        Mix_HaltChannel(5);
        Mix_PlayChannel(5, explosionSound, 0);
    } else {
        Mix_PlayChannel(5, explosionSound, 0);
    }
}

void Turret::update(double dt, SDL_FRect paddleRect) {
    
    switch (turretStatus) {
        case Definitions::TurretStatus::TurretGood: {
            angle = calculateRotationAngle(paddleRect);

            currentShotTimer = currentShotTimer + (60 * dt);
            spdlog::debug("Current Shot Timer: " + std::to_string(currentShotTimer));
            if (currentShotTimer > shotTimer) {
                if (turretBullet == nullptr) {
                    spdlog::info("Firing");
                    turretBullet = new TurretBullet(spriteManager, calculateBulletPosition(), paddleRect);
                }
                currentShotTimer = 0.f;
            }

            currentSprite = currentSprite + (15 * dt);
            if ((int)currentSprite > (float)lastSprite) {
                currentSprite = 0.0f;
            }

            break;
        }

        case Definitions::TurretStatus::TurretExploding: {
            currentExplosionSprite = currentExplosionSprite + (60 * dt);
            break;
        }
        case Definitions::TurretStatus::TurretDead: {
            break;
        }        
    }
    
    // Does this Turret have an active Bullet?
    if (turretBullet != nullptr) {
        turretBullet->update(dt);

        // Remove the bullet if it falls off the bottom of the screen
        if (turretBullet->turretBulletRect.y > SCREEN_HEIGHT) {
            deleteBullet();
        }
    }
}

void Turret::renderBase() {
    switch(turretStatus) {
        case Definitions::TurretStatus::TurretGood: {
            SDL_RenderCopyF(gRenderer, turretBase, NULL, &turretRect );
            break;
        }
        case Definitions::TurretStatus::TurretExploding: {
            break;
        }
        case Definitions::TurretStatus::TurretDead: {
            break;
        }
    }
}

void Turret::renderTurret() {
switch(turretStatus) {
        case Definitions::TurretStatus::TurretGood: {
            //SDL_RenderCopyExF(gRenderer, turretSprite, NULL, &turretRect, angle, &rotationPoint,  SDL_FLIP_NONE);
            int frame = (int)currentSprite;
            SDL_Rect solidSprite = {turretSpriteClips[frame].x, turretSpriteClips[frame].y, turretSpriteClips[frame].w, turretSpriteClips[frame].h};
            SDL_RenderCopyExF(gRenderer, turretSprite, &solidSprite, &turretRect, angle, NULL, SDL_FLIP_NONE);
            break;
        }
        case Definitions::TurretStatus::TurretExploding: {
            
            int frame = (int)currentExplosionSprite;

            if (frame < lastExplosionSprite) {
                SDL_FRect explosionRect;
                float turretMidX = turretRect.x + (turretRect.w / 2);
                float turretMidY = turretRect.y + (turretRect.h /2 );

                explosionRect.x = turretMidX - ((explosionSpriteWidth / numExplosionSprites) / 2);
                explosionRect.y = turretMidY - (explosionSpriteHeight / 2);
                explosionRect.w = explosionSpriteWidth / numExplosionSprites;
                explosionRect.h = explosionSpriteHeight;

                SDL_Rect solidSprite = {turretExplosionSpriteClips[frame].x, turretExplosionSpriteClips[frame].y, turretExplosionSpriteClips[frame].w, turretExplosionSpriteClips[frame].h};
                SDL_RenderCopyF(gRenderer, turretExplosion, &solidSprite, &explosionRect);               
            } else {
                turretStatus = Definitions::TurretStatus::TurretDead;
                currentShotTimer = 0.f;
            }
            break;
        }
        case Definitions::TurretStatus::TurretDead: {
            break;
        }
    }
    if (turretBullet != nullptr) {
        turretBullet->render();
    }
}

void Turret::deleteBullet() {
    if (turretBullet != nullptr) {
        delete turretBullet;
        turretBullet = nullptr;
    }

}

double Turret::calculateRotationAngle(SDL_FRect paddleRect)
{
    // Calculate the angle between the two sprite rects
    double deltaX = (turretRect.x + (turretRect.w / 2)) - (paddleRect.x + (paddleRect.w / 2));
    double deltaY = (turretRect.y + (turretRect.h / 2)) - (paddleRect.y + (paddleRect.h / 2));
    
    double angle = std::atan2(deltaY, deltaX) * 180.0 / M_PI;

    // Adjust the angle to make the bottom of turret point at the paddle
    angle += 90.0;

    return angle;
}

SDL_FRect Turret::calculateBulletPosition()
{
    SDL_FRect bullet;
    
    // Calculate the center position of the sprite
    int spriteCenterX = turretRect.x + (turretRect.w / 2);                                               
    int spriteCenterY = turretRect.y + (turretRect.h * 0.25);

    // Calculate the offset from the center of the sprite to the bottom
    int offsetX = (int)(turretWidth / 2 * -std::sin(angle * M_PI / 180.0));
    int offsetY = (int)(turretHeight / 2 * std::cos(angle * M_PI / 180.0));

    // Calculate the position of the object
    bullet.x = spriteCenterX - (bulletWidth / 2) + offsetX;
    bullet.y = spriteCenterY - (bulletHeight / 2) + offsetY;
    bullet.w = bulletWidth;
    bullet.h = bulletHeight;

    return bullet;
}