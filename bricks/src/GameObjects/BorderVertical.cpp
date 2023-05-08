#include <BorderVertical.h>
#include <iostream>
BorderVertical::BorderVertical(float startX, float startY, float borderWidth, float borderHeight, bool flipX) {

    if (flipX == true) {
        angle = -180;
    }

    borderSprite = SpriteManager::get()->techBorder;
    borderRect = {startX, startY, borderWidth, borderHeight};
}

BorderVertical::BorderVertical() {

}

void BorderVertical::update(double dt) {

}

void BorderVertical::render() 
{
    // Vertical Borders 

        for (float s = borderRect.y; s < borderRect.h; s = s + (float)borderHeight) {
            SDL_FRect tempRect = {borderRect.x, s, (float)borderWidth, (float)borderHeight};
            SDL_RenderCopyExF(gRenderer, borderSprite, NULL, &tempRect, angle, NULL, SDL_FLIP_NONE);
        }


    // DEBUG: Collision Rects
    //SDL_SetRenderDrawColor(gRenderer, 255,0,0, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &borderRect);

    /*
    // Draw Corners

    SDL_Rect location_tl = {PLAYFIELD_STARTX, 0, techCornerWidth, techCornerHeight};
    SDL_Rect location_tr = {PLAYFIELD_STARTX + PLAYFIELD_WIDTH - techCornerWidth, 0, techCornerWidth, techCornerHeight};
    SDL_RenderCopyEx(gRenderer, techCornerSprite, NULL, &location_tr, 90, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer, techCornerSprite, NULL, &location_tl, 0, NULL, SDL_FLIP_NONE);

    // DEBUG: Collision Boxes
    //SDL_SetRenderDrawColor(gRenderer, 0,255,0, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &rBorder);
    //SDL_RenderDrawRectF(gRenderer, &lBorder);
    //SDL_SetRenderDrawColor(gRenderer, 255,0,0, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &tBorder);
*/
}

void BorderVertical::destroy() {

}
