#include <BorderCorner.h>
//#include <iostream>
BorderCorner::BorderCorner(float startX, bool flipX, SpriteManager* spriteManager) {
    this->borderStartX = startX;
    this->borderSprite = spriteManager->techCorner;

    spriteManager->getTextureDimensions(borderSprite, textureWidth, textureHeight);
    
    if (flipX == true) {
        angle = 90;
    }

    borderRect = {borderStartX, borderStartY, (float)textureWidth, (float)textureHeight};
}

void BorderCorner::render() 
{
    SDL_RenderCopyExF(gRenderer, borderSprite, NULL, &borderRect, angle, NULL, SDL_FLIP_NONE);
}