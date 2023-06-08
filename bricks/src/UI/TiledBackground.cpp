#include <TiledBackground.h>

TiledBackground::TiledBackground(SpriteManager* spriteManager) {
    this->backgroundSprite = spriteManager->background;
    spriteManager->getTextureDimensions(backgroundSprite, textureWidth, textureHeight);
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