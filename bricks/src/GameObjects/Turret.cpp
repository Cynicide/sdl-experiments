#include <Turret.h>
#include <random>

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
    std::uniform_int_distribution<int> distribution(-5, 5);
    int randomNumber = distribution(engine);
    shotTimer = baseShotTimer + randomNumber;

    rotationPoint = {(float)(turretWidth / 2), (float)(turretHeight * 0.25f)};
    
    turretRect = {_xpos, _ypos, (float)turretWidth, (float)turretHeight};
    collisionRect = {_xpos, _ypos, (float)turretWidth, (float)turretHeight / 2};
}

Turret::~Turret() {
    if (turretBullet != nullptr) {
        delete turretBullet;
        turretBullet = nullptr;
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

void Turret::update(double dt, SDL_FRect paddleRect) {
    angle = calculateRotationAngle(paddleRect);

    currentShotTimer = currentShotTimer + (60 * dt);
    spdlog::info("Current Shot Timer: " + std::to_string(currentShotTimer));
    if (currentShotTimer > shotTimer) {
        if (turretBullet == nullptr) {
            spdlog::info("Firing");
            turretBullet = new TurretBullet(spriteManager, calculateBulletPosition(), angle);
        }
        currentShotTimer = 0.f;
    }
    if (turretBullet != nullptr) {
        turretBullet->update(dt);
    }
}

void Turret::renderBase() {
    SDL_RenderCopyF(gRenderer, turretBase, NULL, &turretRect );
}

void Turret::renderTurret() {
    SDL_RenderCopyExF(gRenderer, turretSprite, NULL, &turretRect, angle, &rotationPoint,  SDL_FLIP_NONE);
    if (turretBullet != nullptr) {
        turretBullet->render();
    }
}

double Turret::calculateRotationAngle(SDL_FRect paddleRect)
{
    // Calculate the angle between the two sprite rects
    double deltaX = turretRect.x - paddleRect.x;
    double deltaY = turretRect.y - paddleRect.y;
    
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