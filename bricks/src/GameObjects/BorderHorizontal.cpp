#include <BorderHorizontal.h>
//#include <iostream>
BorderHorizontal::BorderHorizontal(float startX, bool flipX, SpriteManager *spriteManager) {

    this->borderStartX = startX;
    this->borderSprite = spriteManager->techTopBorder;

    spriteManager->getTextureDimensions(borderSprite, borderSpriteWidth, borderHeight);
    borderWidth = PLAYFIELD_WIDTH;

    if (flipX == true) {
        angle = -180;
    }

    borderRect = {borderStartX, borderStartY, borderWidth, (float)borderHeight};
}

void BorderHorizontal::render() 
{
    for (float s = borderRect.x; s < borderRect.x + borderRect.w; s = s + (float)borderSpriteWidth) {
        SDL_FRect tempRect = {s, borderRect.y, (float)borderSpriteWidth, (float)borderHeight};
        SDL_RenderCopyExF(gRenderer, borderSprite, NULL, &tempRect, 0, NULL, SDL_FLIP_NONE);
    }

    // DEBUG: Collision Rects
    //SDL_SetRenderDrawColor(gRenderer, 255,0,0, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &borderRect);
}
