#include <TurretBullet.h>
#include <cmath>

TurretBullet::TurretBullet(SpriteManager* spriteManager, SDL_FRect position, double angle) {
    this->turretBulletSprite = spriteManager->turretBullet;
    this->turretBulletRect = position;
    this->angle = angle;

    spriteManager->getTextureDimensions(turretBulletSprite, turretBulletWidth, turretBulletHeight);
    //turretBulletRect = {0, 0, (float)(turretBulletWidth / numSprites), (float)turretBulletHeight};
    SliceSpriteSheet();
}

void TurretBullet::SliceSpriteSheet() {
    for( int i = 0; i <= numSprites - 1; i++ ) {
        turretBulletSpriteClips[ i ].x =   i * (turretBulletWidth / numSprites);
        turretBulletSpriteClips[ i ].y =   0;
        turretBulletSpriteClips[ i ].w =  (turretBulletWidth / numSprites);
        turretBulletSpriteClips[ i ].h = turretBulletHeight;
        }
}

void TurretBullet::update(double dt) {
    moveBullet(dt);
}

void TurretBullet::render() {
    SDL_Rect solidSprite = {turretBulletSpriteClips[0].x, turretBulletSpriteClips[0].y, turretBulletSpriteClips[0].w, turretBulletSpriteClips[0].h};
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
    turretBulletRect.y += deltaY * dt;
}