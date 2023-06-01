#include <Bullet.h>

Bullet::Bullet(SpriteManager* spriteManager, float xLocation, float yLocation) {
    this->bulletSprite = spriteManager->bullet;
    currentVel = startingVel;
    spriteManager->getTextureDimensions(bulletSprite, bulletWidth, bulletHeight);
    bulletRect= {xLocation, yLocation,((float)bulletWidth / (float)numSprites), (float)bulletHeight};
    sliceSpriteSheet();
}

void Bullet::update(double dt) {
    if (bulletStatus == Definitions::BulletStatus::BulletGood) {
        move(dt);
        spdlog::debug("Bullet CurrentVel: " + std::to_string(currentVel));
        if (currentVel < maxVel) {
            currentVel = currentVel + speedUpAmount;
        }
    }

    if (bulletStatus == Definitions::BulletStatus::BulletExploding) {
        currentFrame = currentFrame + (30 * dt);
        if ((int)currentFrame > (float)lastFrame) {
            bulletStatus = Definitions::BulletStatus::BulletDead;
        }
    }
}

void Bullet::move(double dt) {
    bulletRect.y = bulletRect.y - (currentVel * dt); 
}

void Bullet::render() {

    if (bulletStatus == Definitions::BulletStatus::BulletGood) {
        SDL_Rect goodBullet = {bulletSpriteClips[0].x, bulletSpriteClips[0].y, bulletSpriteClips[0].w, bulletSpriteClips[0].h};
        SDL_RenderCopyF(gRenderer, bulletSprite, &goodBullet, &bulletRect );
    }

    if (bulletStatus == Definitions::BulletStatus::BulletExploding) {
        int frame = (int)currentFrame;
        SDL_Rect solidSprite = {bulletSpriteClips[frame].x, bulletSpriteClips[frame].y, bulletSpriteClips[frame].w, bulletSpriteClips[frame].h};
        SDL_RenderCopyF(gRenderer, bulletSprite, &solidSprite, &bulletRect );
    }
}



void Bullet::hit() {
    bulletStatus = Definitions::BulletStatus::BulletExploding;
    currentFrame = 1.0f;
}

void Bullet::sliceSpriteSheet() {
    for( int i = 0; i <= numSprites - 1; i++ ) {
        bulletSpriteClips[ i ].x =   i * (bulletWidth / numSprites);
        bulletSpriteClips[ i ].y =   0;
        bulletSpriteClips[ i ].w =  (bulletWidth / numSprites);
        bulletSpriteClips[ i ].h = bulletHeight;
        }
}