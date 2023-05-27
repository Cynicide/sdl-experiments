#include <LifeCounter.h>
//#include <iostream>
LifeCounter::LifeCounter(float startX, SpriteManager* spriteManager) {
    this->lifeCounterSprite = spriteManager->lifeCounter;
    this->lifeIconSprite = spriteManager->lifeIcon;

    //int lcW, lcH;

    spriteManager->getTextureDimensions(lifeCounterSprite, lifeCounterW, lifeCounterH);
    spriteManager->getTextureDimensions(lifeIconSprite, lifeIconW, lifeIconH);

    lifeCounterRect = {(float)startX, 0.f, (float)lifeCounterW, (float)lifeCounterH};

}

void LifeCounter::render(int lives) 
{
    SDL_RenderCopyF(gRenderer, lifeCounterSprite, NULL, &lifeCounterRect);
    float counterOffset = lifeCounterRect.x;
    for (int l = 0; l < lives; ++l) {
        SDL_FRect lifeIcon = {counterOffset, (float)0, (float)lifeIconW, (float)lifeIconH};
        SDL_RenderCopyF(gRenderer, lifeIconSprite, NULL, &lifeIcon);
        counterOffset = counterOffset + lifeIconW;
    }
}