#include <Ball.h>
#include <iostream>
#include <random>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <Sign.h>

Ball::Ball() {
    ballSprite = SpriteManager::get()->ball;

    startingVel = {6, -6};
    currentVel = startingVel;

    vel.x = currentVel.x;
    vel.y = currentVel.y;

    bool bQuery = SDL_QueryTexture(ballSprite, NULL, NULL, &height, &width);
    if (bQuery == 1) {
        spdlog::error("Issue querying Ball Texture: ", SDL_GetError());
    }
}

void Ball::reset() {
    vel.x = startingVel.x;
    vel.y = startingVel.y;

    ballRect.x = SCREEN_WIDTH / 2 - width / 2;
    ballRect.y = SCREEN_HEIGHT / 2  - height / 2;
    ballRect.w = width;
    ballRect.h = height;
}

void Ball::update(double dt) {
    move();
}

void Ball::update(double dt, SDL_FRect paddleRect) {
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

void Ball::move() {
    ballRect.x += vel.x;
    ballRect.y += vel.y;
}

void Ball::flipY() {
    vel.y = vel.y * -1;
}

void Ball::flipX() {
    vel.x = vel.x * -1;
}

void Ball::randomizeXDirection() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> direction(0, 1);
    if (direction(gen) == 1) {
        vel.x = vel.x * -1;
    }
}

void Ball::render() {
    SDL_RenderCopyF(gRenderer, ballSprite, NULL, &ballRect );
    //SDL_SetRenderDrawColor(gRenderer, 255,255,0, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &ballRect);
}

void Ball::ChangeAngle(int hitLocation, int paddleSize) {
    
    // Hit Location should be between paddleSize and -paddleSize
    // Smaller numbers are generated closer to the center
    spdlog::info("HitLocation: " + std::to_string(hitLocation));
    spdlog::info("PaddleSize / 2: " + std::to_string(paddleSize / 2 ));

    float paddleHalf = paddleSize / 2;

    // No divide by zero errors
    if (hitLocation == 0) {
        hitLocation = 1;
    }

    float angle = 0.f;

    if (sgn(hitLocation) == 1) {
        angle = (float)hitLocation / (float)paddleHalf;
        spdlog::info( std::to_string((float)hitLocation) + " / " + std::to_string((float)paddleHalf) +  " = " + std::to_string(angle));
        if ( angle > 1.0f ) {
            angle = 1.0f;
        }

        if ( angle < 0.01f ) {
            angle = 0.01f;
        } 
    } else {
        angle = (float)hitLocation / (float)paddleHalf;
        spdlog::info( std::to_string((float)hitLocation) + " / " + std::to_string((float)paddleHalf) +  " = " + std::to_string(angle));
        spdlog::info("Angle: " + std::to_string(angle));

        if ( angle < -1.0f ) {
            angle = -1.0f;
        }

        if ( angle > -0.01f ) {
            angle = -0.01f;
        } 
    }
    vel.x = currentVel.x * -(angle * 1.5);

    spdlog::info("Bounce Resolved: VX: " + std::to_string(vel.x) + " VY: " + std::to_string(vel.y));
}

    void Ball::hitTopWall(SDL_FRect border) {
        ballRect.y = border.y + border.h ;
        flipY();
    }

    void Ball::hitRightWall(SDL_FRect border) {
        ballRect.x = border.x - ballRect.w ;
        flipX();
    }

    void Ball::hitLeftWall(SDL_FRect border) {
        ballRect.x = border.x + border.w ;
        flipX();
    }

    void Ball::hitPaddle(Vector2d normals, SDL_FRect paddleRect){
        int ball_mid = ballRect.x + (ballRect.w / 2);
        int paddle_mid = paddleRect.x + (paddleRect.w / 2);
        int hitLocation = paddle_mid - ball_mid;

         ChangeAngle(hitLocation, paddleRect.w);
        
        if (abs(normals.x) > 0.0001f) {
            flipX();
        } 
        
        if (abs(normals.y) > 0.0001f) {
            flipY();
        }
    }

    void Ball::hitBrick(Vector2d normals){
        if (abs(normals.x) > 0.0001f) {
            flipX();
        } 
        
        if (abs(normals.y) > 0.0001f) {
            flipY();
        }
    }

    void Ball::hitLightning() {
        flipY();
    }