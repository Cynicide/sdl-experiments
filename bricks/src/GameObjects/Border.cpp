#include <Border.h>
#include <iostream>
Border::Border() {
    borderSprite = SpriteManager::get()->border;
    SliceSpriteSheet();
    lBorder = {0.f, 0.f, (float)borderWidth, (float)SCREEN_HEIGHT};
    rBorder = {(float)(SCREEN_WIDTH - borderWidth), 0.f, (float)borderWidth, (float)SCREEN_HEIGHT};
    tBorder = {(float)borderWidth, 0.f, (float)(SCREEN_WIDTH - borderWidth * 2), (float)borderHeight};
}


void Border::SliceSpriteSheet() {

for( int i = 0; i <= numSprites - 1; i++ ) 
    {

    borderSpriteClips[ i ].x =   i * borderWidth;
    borderSpriteClips[ i ].y =   0;
    borderSpriteClips[ i ].w =  borderWidth;
    borderSpriteClips[ i ].h = borderHeight;
    }
}

void Border::update(double dt) {


}

void Border::render() 
{

    SDL_Rect wallSprite = {borderSpriteClips[0].x, borderSpriteClips[0].y, borderSpriteClips[0].w, borderSpriteClips[0].h};
    SDL_Rect cornerSprite = {borderSpriteClips[1].x, borderSpriteClips[1].y, borderSpriteClips[1].w, borderSpriteClips[1].h};

    // Draw Walls

    for (int s = 0; s < SCREEN_HEIGHT; s = s + borderHeight) 
    {
        SDL_Rect location_l = {0, s, borderWidth, borderHeight};
        SDL_Rect location_r = {SCREEN_WIDTH - borderWidth, s, borderWidth, borderHeight};
        SDL_RenderCopyEx(gRenderer, borderSprite, &wallSprite, &location_l, -90, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(gRenderer, borderSprite, &wallSprite, &location_r, 90, NULL, SDL_FLIP_NONE);
    }

    for (int t = 0; t < SCREEN_WIDTH; t = t + borderWidth) 
    {
        SDL_Rect location_t = {t, 0, borderWidth, borderHeight};
        SDL_RenderCopyEx(gRenderer, borderSprite, &wallSprite, &location_t, 0, NULL, SDL_FLIP_NONE);
    }

    // Draw Corners

    SDL_Rect location_tl = {0, 0, borderWidth, borderHeight};
    SDL_Rect location_tr = {SCREEN_WIDTH - borderWidth, 0, borderWidth, borderHeight};
    SDL_RenderCopyEx(gRenderer, borderSprite, &cornerSprite, &location_tr, 90, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer, borderSprite, &cornerSprite, &location_tl, 0, NULL, SDL_FLIP_NONE);

    SDL_SetRenderDrawColor(gRenderer, 0,255,0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRectF(gRenderer, &rBorder);
    SDL_RenderDrawRectF(gRenderer, &lBorder);
    SDL_SetRenderDrawColor(gRenderer, 255,0,0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRectF(gRenderer, &tBorder);

}

void Border::destroy() {

}
