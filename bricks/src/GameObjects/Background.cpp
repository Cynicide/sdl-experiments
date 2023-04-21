#include <Background.h>

Background::Background() {
    backgroundSprite = SpriteManager::get()->background;
}


void Background::update(float dt) {
}

void Background::render() {

    int textureHeight = 0;
    int textureWidth = 0;

    bool bQuery = SDL_QueryTexture(backgroundSprite, NULL, NULL, &textureWidth, &textureHeight);
    if (bQuery == 1) {
        SDL_Log( SDL_GetError());
    }

    for (int c = 0; c < SCREEN_HEIGHT; c = c + textureHeight) {
        for (int r = 0; r < SCREEN_WIDTH; r = r + textureWidth) {
            SDL_Rect tile = {r, c, textureWidth, textureHeight};
            SDL_RenderCopy(gRenderer, backgroundSprite, NULL, &tile );
        }
    }
}

void Background::destroy() {
}