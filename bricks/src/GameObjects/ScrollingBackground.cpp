#include <ScrollingBackground.h>

ScrollingBackground::ScrollingBackground(SDL_Texture* sprite) {
    backgroundSprite = sprite;
    bool bQuery = SDL_QueryTexture(backgroundSprite, NULL, NULL, &textureWidth, &textureHeight);
    if (bQuery == 1) {
        SDL_Log( SDL_GetError());
    }
}

void ScrollingBackground::update(double dt) {

    scrollingOffset = scrollingOffset - (100 * dt);

    if( scrollingOffset < -textureHeight )
    {
        scrollingOffset = 0;
    }
}

void ScrollingBackground::render() {

    SDL_Rect upperBackground = {PLAYFIELD_STARTX, (int)scrollingOffset, textureWidth, textureHeight};
    SDL_Rect lowerBackground = {PLAYFIELD_STARTX, (int)scrollingOffset + textureHeight, textureWidth, textureHeight};
    SDL_Rect bottomBackground = {PLAYFIELD_STARTX, (int)scrollingOffset + (textureHeight * 2), textureWidth, textureHeight};
    SDL_RenderCopy(gRenderer, backgroundSprite, NULL, &upperBackground );
    SDL_RenderCopy(gRenderer, backgroundSprite, NULL, &lowerBackground );
    SDL_RenderCopy(gRenderer, backgroundSprite, NULL, &bottomBackground );
}

void ScrollingBackground::destroy() {
}