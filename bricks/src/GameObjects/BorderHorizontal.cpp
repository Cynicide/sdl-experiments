#include <BorderHorizontal.h>
//#include <iostream>
BorderHorizontal::BorderHorizontal(float startX, bool flipX, SDL_Texture* borderSprite) {

    this->borderStartX = startX;
    this->borderSprite = borderSprite;

    int w, h;
    bool bQuery = SDL_QueryTexture(borderSprite, NULL, NULL, &w, &h);
    if (bQuery == 1) {
        spdlog::error("Issue querying Horizontal Wall Texture: ");
        spdlog::error(SDL_GetError());
    }

    borderSpriteWidth = (float)w;
    borderHeight = (float)h;
    borderWidth = PLAYFIELD_WIDTH;

    if (flipX == true) {
        angle = -180;
    }

    borderRect = {borderStartX, borderStartY, borderWidth, borderHeight};
}

void BorderHorizontal::render() 
{
    for (float s = borderRect.x; s < borderRect.x + borderRect.w; s = s + borderSpriteWidth) {
        SDL_FRect tempRect = {s, borderRect.y, borderSpriteWidth, borderHeight};
        SDL_RenderCopyExF(gRenderer, borderSprite, NULL, &tempRect, 0, NULL, SDL_FLIP_NONE);
    }

    // DEBUG: Collision Rects
    //SDL_SetRenderDrawColor(gRenderer, 255,0,0, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &borderRect);
}
