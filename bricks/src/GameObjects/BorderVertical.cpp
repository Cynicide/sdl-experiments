#include <BorderVertical.h>
#include <iostream>
BorderVertical::BorderVertical(float startX, bool flipX, SDL_Texture* borderSprite) {

    this->borderStartX = startX;
    this->borderSprite = borderSprite;
    
    int w, h;
    bool bQuery = SDL_QueryTexture(borderSprite, NULL, NULL, &w, &h);
    if (bQuery == 1) {
        spdlog::error("Issue querying Vertical Wall Texture: ");
        spdlog::error(SDL_GetError());
    }

    borderWidth = (float)w;
    borderSpriteHeight = (float)h;
    borderHeight = SCREEN_HEIGHT;
    
    if (flipX == true) {
        angle = -180;
    }

    borderRect = {borderStartX, borderStartY, borderWidth, borderHeight};
}

void BorderVertical::render() 
{
    // Vertical Borders 
    for (float s = borderRect.y; s < borderRect.h; s = s + borderSpriteHeight) {
        SDL_FRect tempRect = {borderRect.x, s, borderWidth, borderSpriteHeight};
        SDL_RenderCopyExF(gRenderer, borderSprite, NULL, &tempRect, angle, NULL, SDL_FLIP_NONE);
    }

    // DEBUG: Collision Rects
    //SDL_SetRenderDrawColor(gRenderer, 255,0,0, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &borderRect);
}