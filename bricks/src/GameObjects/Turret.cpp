#include <Turret.h>
#include <random>
#include <globals.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

Turret::Turret(float _xpos, float _ypos, SpriteManager* spriteManager)
{
    this->turretSprite = spriteManager->turret;
    this->turretBase = spriteManager->turretBase;
    this->spriteManager = spriteManager;

    spriteManager->getTextureDimensions(turretBase, turretWidth, turretHeight);

    // Slightly randomize the time between shots
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distribution(-bulletTimeVariance, bulletTimeVariance);
    int randomNumber = distribution(engine);
    shotTimer = baseShotTimer + randomNumber;

    rotationPoint = {(float)(turretWidth / 2), (float)(turretHeight * 0.25f)};
    
    turretRect = {_xpos, _ypos, (float)turretWidth, (float)turretHeight};
    collisionRect = {_xpos, _ypos, (float)turretWidth, (float)turretHeight / 2};
}

Turret::~Turret() {
    if (turretBullet != nullptr) {
        turretBullet.reset();
    }
}

void Turret::SliceSpriteSheet() {
    for( int i = 0; i <= numSprites - 1; i++ ) {
        turretSpriteClips[ i ].x =   i * (turretWidth / numSprites);
        turretSpriteClips[ i ].y =   0;
        turretSpriteClips[ i ].w =  (turretWidth / numSprites);
        turretSpriteClips[ i ].h = turretHeight;
        }
}

void Turret::update(double dt) {

    if (angle != 0.f) {
        angle = 0.f;
    }
}

void Turret::updateServe(double dt, SDL_FRect paddleRect) {
    angle = calculateRotationAngle(paddleRect);
}

void Turret::hitTurret() {
    turretStatus = Definitions::TurretStatus::TurretDead;
    currentShotTimer = 0.f;
}

void Turret::update(double dt, SDL_FRect paddleRect) {
    
    switch (turretStatus) {
        case Definitions::TurretStatus::TurretGood: {
            angle = calculateRotationAngle(paddleRect);

            currentShotTimer = currentShotTimer + (60 * dt);
            if (currentShotTimer > shotTimer) {
                if (turretBullet == nullptr) {
                    turretBullet = std::make_unique<TurretBullet>(spriteManager, calculateBulletPosition(), paddleRect);
                }
                currentShotTimer = 0.f;
            }
            break;
        }

        case Definitions::TurretStatus::TurretExploding: {
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
            SDL_RenderCopyExF(gRenderer, turretSprite, NULL, &turretRect, angle, &rotationPoint,  SDL_FLIP_NONE);
            break;
        }
        case Definitions::TurretStatus::TurretExploding: {
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
        turretBullet.reset();
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