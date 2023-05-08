#include <BorderCorner.h>
#include <iostream>
BorderCorner::BorderCorner(float startX, float startY, float borderWidth, float borderHeight, bool flipX) {

    if (flipX == true) {
        angle = 90;
    }

    borderSprite = SpriteManager::get()->techCorner;
    borderRect = {startX, startY, borderWidth, borderHeight};
}

BorderCorner::BorderCorner() {

}

void BorderCorner::update(double dt) {

}

void BorderCorner::render() 
{

    SDL_RenderCopyExF(gRenderer, borderSprite, NULL, &borderRect, angle, NULL, SDL_FLIP_NONE);
    /*
    SDL_Rect location_tl = {PLAYFIELD_STARTX, 0, techCornerWidth, techCornerHeight};
    SDL_Rect location_tr = {PLAYFIELD_STARTX + PLAYFIELD_WIDTH - techCornerWidth, 0, techCornerWidth, techCornerHeight};
    */
}

void BorderCorner::destroy() {

}
