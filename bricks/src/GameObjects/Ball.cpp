#include <Ball.h>
#include <iostream>
Ball::Ball() {
    ballSprite = SpriteManager::get()->ball;
}


void Ball::update(float dt) {
        int textureHeight = 0;
        int textureWidth = 0;

        bool bQuery = SDL_QueryTexture(ballSprite, NULL, NULL, &textureWidth, &textureHeight);
        if (bQuery == 1) {
            SDL_Log( SDL_GetError());
        }


        ballRect.x = SCREEN_WIDTH / 2 - textureWidth / 2;
        ballRect.y = SCREEN_HEIGHT / 2  - textureHeight / 2;
        ballRect.w = textureWidth;
        ballRect.h = textureHeight;

}

void Ball::render() 
{

    SDL_RenderCopy(gRenderer, ballSprite, NULL, &ballRect );
}

void Ball::destroy() {

}
