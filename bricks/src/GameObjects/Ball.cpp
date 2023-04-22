#include <Ball.h>
#include <iostream>
#include <random>

Ball::Ball() {
    ballSprite = SpriteManager::get()->ball;
    reset();
}


void Ball::reset() {
        height = 0;
        width = 0;

        bool bQuery = SDL_QueryTexture(ballSprite, NULL, NULL, &height, &width);
        if (bQuery == 1) {
            SDL_Log( SDL_GetError());
        }

        ballRect.x = SCREEN_WIDTH / 2 - width / 2;
        ballRect.y = SCREEN_HEIGHT / 2  - height / 2;
        ballRect.w = width;
        ballRect.h = height;
}

void Ball::update(double dt) {
    move(dt);
}

void Ball::move(double dt) {
    ballRect.x += xVel * dt;
    ballRect.y += yVel * dt;
    std::cout << "X: " << ballRect.x << " Y: " << ballRect.y << "\n";
    std::cout << "XVel: " << xVel << " YVel: " << yVel << " DT: " << dt << "\n";
}

void Ball::update(double dt, SDL_Rect paddleRect) {
    height = 0;
    width = 0;

    bool bQuery = SDL_QueryTexture(ballSprite, NULL, NULL, &height, &width);
    if (bQuery == 1) {
        SDL_Log( SDL_GetError());
    }

    ballRect.x = (paddleRect.x + (paddleRect.w / 2)) - (width / 2);
    ballRect.y = paddleRect.y - paddleRect.h;
    ballRect.w = width;
    ballRect.h = height;

}

void Ball::flipY() {
    yVel = yVel * -1;
}

void Ball::flipX() {
    xVel = xVel * -1;
}

void Ball::randomizeXDirection() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> direction(0, 1);
    if (direction(gen) == 1) {
        xVel = xVel * -1;
    }
}

void Ball::render() 
{

    SDL_RenderCopyF(gRenderer, ballSprite, NULL, &ballRect );
    SDL_SetRenderDrawColor(gRenderer, 255,255,0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRectF(gRenderer, &ballRect);
}

void Ball::destroy() {

}
