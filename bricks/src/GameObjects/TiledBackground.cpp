#include <TiledBackground.h>
TiledBackground::TiledBackground() {

}

TiledBackground::TiledBackground(SDL_Texture* sprite) {
    backgroundSprite = sprite;
    bool bQuery = SDL_QueryTexture(backgroundSprite, NULL, NULL, &textureWidth, &textureHeight);
    if (bQuery == 1) {
        SDL_Log( SDL_GetError());
    }
}

void TiledBackground::render() {
    // Tile the texture over the screen
    for (int c = 0; c < SCREEN_HEIGHT; c = c + textureHeight) {
        for (int r = PLAYFIELD_STARTX; r < PLAYFIELD_STARTX + PLAYFIELD_WIDTH; r = r + textureWidth) {
            SDL_Rect tile = {r, c, textureWidth, textureHeight};
            SDL_RenderCopy(gRenderer, backgroundSprite, NULL, &tile );
        }
    }
}