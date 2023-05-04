#include <ScrollingBackground.h>

ScrollingBackground::ScrollingBackground() {

}

ScrollingBackground::ScrollingBackground(SDL_Texture* sprite) {
    backgroundSprite = sprite;
    bool bQuery = SDL_QueryTexture(backgroundSprite, NULL, NULL, &textureWidth, &textureHeight);
    if (bQuery == 1) {
        SDL_Log( SDL_GetError());
    }
}

void ScrollingBackground::update(double dt) {

    scrollingOffset = scrollingOffset - 5;

    if( scrollingOffset < -textureHeight )
    {
        scrollingOffset = 0;
    }
}

void ScrollingBackground::render() {

    SDL_Rect upperBackground = {0, scrollingOffset, textureWidth, textureHeight};
    SDL_Rect lowerBackground = {0, scrollingOffset + textureHeight, textureWidth, textureHeight};
    SDL_RenderCopy(gRenderer, backgroundSprite, NULL, &upperBackground );
    SDL_RenderCopy(gRenderer, backgroundSprite, NULL, &lowerBackground );
}

void ScrollingBackground::destroy() {
}