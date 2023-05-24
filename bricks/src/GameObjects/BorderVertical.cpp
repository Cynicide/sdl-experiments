#include <BorderVertical.h>
//#include <iostream>
BorderVertical::BorderVertical(float startX, bool flipX, SpriteManager *spriteManager) {

    this->borderStartX = startX;
    this->borderSprite = spriteManager->techBorder;
    
    spriteManager->getTextureDimensions(borderSprite, borderWidth, borderSpriteHeight);
    borderHeight = SCREEN_HEIGHT;
    
    if (flipX == true) {
        angle = -180;
    }

    borderRect = {borderStartX, borderStartY, (float)borderWidth, borderHeight};
}

void BorderVertical::render() 
{
    // Vertical Borders 
    for (float s = borderRect.y; s < borderRect.h; s = s + borderSpriteHeight) {
        SDL_FRect tempRect = {borderRect.x, s, (float)borderWidth, (float)borderSpriteHeight};
        SDL_RenderCopyExF(gRenderer, borderSprite, NULL, &tempRect, angle, NULL, SDL_FLIP_NONE);
    }

    // DEBUG: Collision Rects
    //SDL_SetRenderDrawColor(gRenderer, 255,0,0, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &borderRect);
}