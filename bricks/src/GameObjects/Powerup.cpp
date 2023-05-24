#include <globals.h>
#include <Powerup.h>


Powerup::Powerup(SpriteManager *spriteManager, float parentXPos, float parentYPos, int parentWidth) {
    this->powerupSprite = spriteManager->capsuleLaser;

    spriteManager->getTextureDimensions(powerupSprite, powerupWidth, powerupHeight);

    float parentMid = parentXPos + (parentWidth / 2);
    float powerupMid = (((float)powerupWidth / (float)numSprites) / 2);
    float powerupXpos = parentMid - powerupMid;


    powerupRect= {powerupXpos, parentYPos,((float)powerupWidth / (float)numSprites), (float)powerupHeight};
    SliceSpriteSheet();
}

void Powerup::update(double dt) {
    currentFrame = currentFrame + (30 * dt);
    if ((int)currentFrame > (float)lastFrame) {
        currentFrame = 0.0f;
        }
    
    move(dt);
}

void Powerup::render() {
        int frame = (int)currentFrame;
        SDL_Rect solidSprite = {powerupSpriteClips[frame].x, powerupSpriteClips[frame].y, powerupSpriteClips[frame].w, powerupSpriteClips[frame].h};
        SDL_RenderCopyF(gRenderer, powerupSprite, &solidSprite, &powerupRect );
}

void Powerup::move(double dt) {
    powerupRect.y = powerupRect.y + (yVel * dt);
}

void Powerup::SliceSpriteSheet() {
    for( int i = 0; i <= numSprites - 1; i++ ) {
        powerupSpriteClips[ i ].x =   i * (powerupWidth / numSprites);
        powerupSpriteClips[ i ].y =   0;
        powerupSpriteClips[ i ].w =  (powerupWidth / numSprites);
        powerupSpriteClips[ i ].h = powerupHeight;
        }
}