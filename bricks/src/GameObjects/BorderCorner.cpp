#include <BorderCorner.h>
//#include <iostream>
BorderCorner::BorderCorner(float startX, bool flipX, SDL_Texture* borderSprite) {
    this->borderStartX = startX;
    this->borderSprite = borderSprite;

    if (flipX == true) {
        angle = 90;
    }

    int w, h;
    bool bQuery = SDL_QueryTexture(borderSprite, NULL, NULL, &w, &h);
    if (bQuery == 1) {
        spdlog::error("Issue querying Vertical Wall Texture: ");
        spdlog::error(SDL_GetError());
    }

    borderWidth = (float)w;
    borderHeight = (float)h;

    borderRect = {borderStartX, borderStartY, borderWidth, borderHeight};
}

void BorderCorner::render() 
{
    SDL_RenderCopyExF(gRenderer, borderSprite, NULL, &borderRect, angle, NULL, SDL_FLIP_NONE);
}