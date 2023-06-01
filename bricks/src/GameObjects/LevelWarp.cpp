#include <LevelWarp.h>
#include <globals.h>


LevelWarp::LevelWarp(SpriteManager* spriteManager){
    this->warpSprite = spriteManager->levelWarp;
    spriteManager->getTextureDimensions(warpSprite, warpWidth, warpHeight);
    warpRect = {(float)PLAYFIELD_STARTX + (float)(PLAYFIELD_WIDTH - (warpWidth / numSprites)), (float)(SCREEN_HEIGHT - warpHeight), (float)warpWidth  / numSprites, (float)warpHeight};
    sliceSpriteSheet();
}

void LevelWarp::update(double dt) {
    currentFrame = currentFrame + (30 * dt);
    if ((int)currentFrame > (float)lastFrame) {
        currentFrame = 0.0f;
        }
    
}

void LevelWarp::sliceSpriteSheet() {
    for( int i = 0; i <= numSprites - 1; i++ ) {
        warpSpriteClips[ i ].x =   i * (warpWidth / numSprites);
        warpSpriteClips[ i ].y =   0;
        warpSpriteClips[ i ].w =  (warpWidth / numSprites);
        warpSpriteClips[ i ].h = warpHeight;
    }
}

void LevelWarp::render() {
    int frame = (int)currentFrame;
    SDL_Rect solidSprite = {warpSpriteClips[frame].x, warpSpriteClips[frame].y, warpSpriteClips[frame].w, warpSpriteClips[frame].h};
    SDL_RenderCopyF(gRenderer, warpSprite, &solidSprite, &warpRect );
}