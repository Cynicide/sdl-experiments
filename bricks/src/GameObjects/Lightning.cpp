#include <Lightning.h>
//#include <iostream>


Lightning::Lightning(SpriteManager* spriteManager) {
    this->lightningSprite = spriteManager->lightning;

    spriteManager->getTextureDimensions(lightningSprite, borderWidth, borderHeight);

    bBorder = {(float)borderWidth, (float)(SCREEN_HEIGHT - borderHeight), (float)(SCREEN_WIDTH - borderWidth * 2), (float)borderHeight};
}

void Lightning::render() 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> direction(0, 1);

    // Draw Bottom
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    for (int b = PLAYFIELD_STARTX; b < PLAYFIELD_STARTX + PLAYFIELD_WIDTH; b = b + borderWidth) 
    {
        if (direction(gen) == 1) {
            flip = SDL_FLIP_HORIZONTAL;
        }
        SDL_Rect location_b = {b, SCREEN_HEIGHT - borderHeight, borderWidth, borderHeight};
        SDL_RenderCopyEx(gRenderer, lightningSprite, NULL, &location_b, 0, NULL, flip);
        flip = SDL_FLIP_NONE;
    }
    
    // Draw Collision Boxes
    //SDL_SetRenderDrawColor(gRenderer, 255,0,0, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &bBorder);
}
