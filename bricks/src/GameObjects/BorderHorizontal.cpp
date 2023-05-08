#include <BorderHorizontal.h>
#include <iostream>
BorderHorizontal::BorderHorizontal(float startX, float startY, float borderWidth, float borderHeight, bool flipX) {

    if (flipX == true) {
        angle = -180;
    }

    borderSprite = SpriteManager::get()->techTopBorder;
    borderRect = {startX, startY, borderWidth, borderHeight};
}

BorderHorizontal::BorderHorizontal() {

}

void BorderHorizontal::update(double dt) {

}

void BorderHorizontal::render() 
{
    // Vertical Borders 
    //if (orientation == Definitions::BorderOrientation::HORIZONTAL) {
    //    for (float s = borderRect.y; s < borderRect.h; s = s + (float)techBorderHeightV) {
    //        SDL_FRect tempRect = {borderRect.x, s, (float)techBorderWidthV, (float)techBorderHeightV};
    //        SDL_RenderCopyExF(gRenderer, techBorderSprite, NULL, &tempRect, angle, NULL, SDL_FLIP_NONE);
    //    }
    //} else {
        // Horizontal Borders 
        spdlog::info("---- drawing top border ---");
        for (float s = borderRect.x; s < borderRect.x + borderRect.w; s = s + (float)borderWidth) {
            SDL_FRect tempRect = {s, borderRect.y, (float)borderWidth, (float)borderHeight};
            spdlog::info("x:" + std::to_string(tempRect.x) + "y:" + std::to_string(tempRect.y) + "w:" + std::to_string(tempRect.w) + "h:" + std::to_string(tempRect.h)); 
            SDL_RenderCopyExF(gRenderer, borderSprite, NULL, &tempRect, 0, NULL, SDL_FLIP_NONE);
        }
    //}

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

void BorderHorizontal::destroy() {

}
