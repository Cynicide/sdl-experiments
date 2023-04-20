#include <Background.h>

Background::Background() {
    background = SpriteManager::get()->background;
}


void Background::render() {

    int textureHeight;
    int textureWidth;

    SDL_QueryTexture(background, NULL, NULL, &textureWidth, &textureHeight);

    for (int c = 0; c < SCREEN_HEIGHT; c = c + textureHeight) {
        for (int r = 0; r < SCREEN_WIDTH; r = r + textureWidth) {
            SDL_Rect tile = {r, c, textureWidth, textureHeight};
            SDL_RenderCopy(gRenderer, background, NULL, &tile );
        }
    }


}

void Background::destroy() {

}
