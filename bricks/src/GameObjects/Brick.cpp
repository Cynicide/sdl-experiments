#include <Brick.h>
#include <iostream>
#include <algorithm>

Brick::Brick(float _xpos, float _ypos) {
    brickLightSprite = SpriteManager::get()->brickLight;
    brickDarkSprite = SpriteManager::get()->brickDark;
    SliceSpriteSheet();
    xpos = _xpos;
    ypos = _ypos;
    brickRect = {xpos, ypos, brickWidth, brickHeight};
}


void Brick::SliceSpriteSheet() {

    for( int i = 0; i <= numSprites - 1; i++ ) 
        {

        brickSpriteClips[ i ].x =   i * brickWidth;
        brickSpriteClips[ i ].y =   0;
        brickSpriteClips[ i ].w =  brickWidth;
        brickSpriteClips[ i ].h = brickHeight;
        }
}

void Brick::update(double dt) {
}

void Brick::render() 
{
    SDL_Rect solidSprite = {brickSpriteClips[0].x, brickSpriteClips[0].y, brickSpriteClips[0].w, brickSpriteClips[0].h};
    
    SDL_RenderCopyF(gRenderer, brickLightSprite, &solidSprite, &brickRect );
    SDL_SetRenderDrawColor(gRenderer, 255,255,255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRectF(gRenderer, &brickRect);
}

void Brick::destroy() {
    // This will become important later on. We will need to trigger destruction and render the appropriate frame
}

void Brick::setVectorRef(std::vector<Brick>& _vectorRef) {
    vectorRef = &_vectorRef;
}

void Brick::removeFromVector() {
    // Ensure the vector is still valid
    if (vectorRef) {
        // Find this object in the vector and remove it
        auto it = std::find(vectorRef->begin(), vectorRef->end(), *this);
        if (it != vectorRef->end()) {
            vectorRef->erase(it);
        }
    }
}