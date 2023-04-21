#include <Paddle.h>
#include <iostream>
Paddle::Paddle() {
    paddleSprite = SpriteManager::get()->paddle;
}


void Paddle::update(float dt) {
        int textureHeight = 0;
        int textureWidth = 0;
        int borderHeight = 16;
        int borderWidth = 16;

        bool bQuery = SDL_QueryTexture(paddleSprite, NULL, NULL, &textureWidth, &textureHeight);
        if (bQuery == 1) {
            SDL_Log( SDL_GetError());
        }        

        int x, y;
        Uint32 mouseState = SDL_GetMouseState(&x, &y);

        paddleRect.x = x;

        if (paddleRect.x < borderWidth) {
            paddleRect.x = borderWidth;
        } 

        if (paddleRect.x > SCREEN_WIDTH - textureWidth - borderWidth) {
            paddleRect.x = SCREEN_WIDTH - textureWidth - borderWidth;
        }
        paddleRect.y = SCREEN_HEIGHT - textureHeight - borderHeight;
        paddleRect.w = textureWidth;
        paddleRect.h = textureHeight;
}

void Paddle::render() 
{

    SDL_RenderCopy(gRenderer, paddleSprite, NULL, &paddleRect );
}

void Paddle::destroy() {

}
