#include <Brick.h>
#include <iostream>
#include <algorithm>

Brick::Brick(int _xpos, int _ypos) {
    brickLightSprite = SpriteManager::get()->brickLight;
    brickDarkSprite = SpriteManager::get()->brickDark;
    SliceSpriteSheet();
    xpos = _xpos;
    ypos = _ypos;

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

void Brick::update(float dt) {
}

void Brick::render() 
{
    SDL_Rect solidSprite = {brickSpriteClips[0].x, brickSpriteClips[0].y, brickSpriteClips[0].w, brickSpriteClips[0].h};
    SDL_Rect tile = {xpos, ypos, brickWidth, brickHeight};
    SDL_RenderCopy(gRenderer, brickLightSprite, &solidSprite, &tile );
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