#include <LevelWarp.h>
#include <globals.h>
#include "spdlog/spdlog.h"

LevelWarp::LevelWarp(SpriteManager* spriteManager){

    this->warpArrowSprite = spriteManager->levelWarpArrow;
    this->warpPortalSprite = spriteManager->levelWarpPortal;

    spriteManager->getTextureDimensions(warpPortalSprite, warpPortalWidth, warpPortalHeight);
    spriteManager->getTextureDimensions(warpArrowSprite, warpArrowWidth, warpArrowHeight);

    warpPortalRect = {(float)PLAYFIELD_STARTX + (float)(PLAYFIELD_WIDTH - (warpPortalWidth / numSprites)), (float)(SCREEN_HEIGHT - warpPortalHeight), (float)warpPortalWidth  / numSprites, (float)warpPortalHeight};
    warpArrowRect = {(float)(warpPortalRect.x - warpArrowWidth), (float)warpPortalRect.y, (float)warpArrowWidth, (float)warpArrowHeight};

    //Offset the collision out of the wall so the paddle can collide with it
    warpPortalCollisionRect = warpPortalRect;
    warpPortalCollisionRect.x = warpPortalCollisionRect.x - xCollisionOffset;


    sliceSpriteSheet();
}

void LevelWarp::update(double dt) {
    auto logger = spdlog::get("fileLogger");
    currentPortalFrame = currentPortalFrame + (30 * dt);
    if ((int)currentPortalFrame > (float)lastFrame) {
        currentPortalFrame = 0.0f;
    }

    currentArrowBlinkTimer = currentArrowBlinkTimer + (30 * dt);
    
    logger->info("ArrowBlink: " + std::to_string(currentArrowBlinkTimer));
    if ((int)currentArrowBlinkTimer > arrowBlinkTimer)
    {
        arrowBlink = !arrowBlink;
        currentArrowBlinkTimer = 0.f;
    }
    
}

void LevelWarp::sliceSpriteSheet() {
    for( int i = 0; i <= numSprites - 1; i++ ) {
        warpPortalSpriteClips[ i ].x =   i * (warpPortalWidth / numSprites);
        warpPortalSpriteClips[ i ].y =   0;
        warpPortalSpriteClips[ i ].w =  (warpPortalWidth / numSprites);
        warpPortalSpriteClips[ i ].h = warpPortalHeight;
    }
}

void LevelWarp::render() {
    int frame = (int)currentPortalFrame;
    SDL_Rect solidSprite = {warpPortalSpriteClips[frame].x, warpPortalSpriteClips[frame].y, warpPortalSpriteClips[frame].w, warpPortalSpriteClips[frame].h};
    SDL_RenderCopyF(gRenderer, warpPortalSprite, &solidSprite, &warpPortalRect );
    
    if (arrowBlink) {
        SDL_RenderCopyF(gRenderer, warpArrowSprite, NULL, &warpArrowRect);
    }
    
}