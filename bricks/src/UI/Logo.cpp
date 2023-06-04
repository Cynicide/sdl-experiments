#include <Logo.h>

Logo::Logo(SpriteManager* spriteManager) {
    this->logoTexture = spriteManager->logo;

    spriteManager->getTextureDimensions(logoTexture, logoWidth, logoHeight);

    logoXPos = (SCREEN_WIDTH / 2 - logoWidth / 2); 
    logoYPos =  (SCREEN_HEIGHT / 4) - (logoHeight / 2);

    logoRect = {logoXPos, logoYPos, (float)logoWidth, (float)logoHeight};
}

void Logo::render() {
    SDL_RenderCopyF(gRenderer, logoTexture, NULL, &logoRect );
}

void Logo::update(double dt) {

}