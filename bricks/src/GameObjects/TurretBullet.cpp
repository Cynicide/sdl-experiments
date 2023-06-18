#include <TurretBullet.h>
#include <cmath>

TurretBullet::TurretBullet(SpriteManager* spriteManager, SDL_FRect position, SDL_FRect paddleRect) {
    this->turretBulletSprite = spriteManager->turretBullet;
    this->turretBulletRect = position;
    
    spriteManager->getTextureDimensions(turretBulletSprite, turretBulletWidth, turretBulletHeight);
    setAngle(paddleRect);
    sliceSpriteSheet();
}

void TurretBullet::setAngle(SDL_FRect paddleRect) {
    double deltaX = (turretBulletRect.x + (turretBulletRect.w / 2)) - (paddleRect.x + (paddleRect.w / 2));
    double deltaY = (turretBulletRect.y + (turretBulletRect.h / 2)) - (paddleRect.y + (paddleRect.h / 2));
    angle = std::atan2(deltaY, deltaX) * 180.0 / M_PI;
}

void TurretBullet::sliceSpriteSheet() {
    for( int i = 0; i <= numSprites - 1; i++ ) {
        turretBulletSpriteClips[ i ].x =   i * (turretBulletWidth / numSprites);
        turretBulletSpriteClips[ i ].y =   0;
        turretBulletSpriteClips[ i ].w =  (turretBulletWidth / numSprites);
        turretBulletSpriteClips[ i ].h = turretBulletHeight;
        }
}

void TurretBullet::update(double dt) {
    currentFrame = currentFrame + (30 * dt);
        if ((int)currentFrame > (float)lastSprite) {
            currentFrame = 0.0f;
        }
    moveBullet(dt);
}

void TurretBullet::render() {
    int frame = (int)currentFrame;
    // What is causing this segfault
    SDL_Rect solidSprite = {turretBulletSpriteClips[frame].x, turretBulletSpriteClips[frame].y, turretBulletSpriteClips[frame].w, turretBulletSpriteClips[frame].h};
    SDL_RenderCopyF(gRenderer, turretBulletSprite, &solidSprite, &turretBulletRect );
}

void TurretBullet::moveBullet(double dt) {
    // Convert the angle from degrees to radians
    double angleRad = angle * M_PI / 180.0;

    // Calculate the horizontal and vertical components of the movement
    double deltaX = speed * std::cos(angleRad);
    double deltaY = speed * std::sin(angleRad);

    // Update the object's position
    turretBulletRect.x += -deltaX * dt;
    turretBulletRect.y += -deltaY * dt;
}