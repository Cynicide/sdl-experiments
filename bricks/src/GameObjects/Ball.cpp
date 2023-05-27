#include <Ball.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <Sign.h>

Ball::Ball(SpriteManager* spriteManager) {
    this->ballSprite = spriteManager->ball;

    startingVel = {400, -400};
    currentVel = startingVel;

    vel.x = currentVel.x;
    vel.y = currentVel.y;

    spriteManager->getTextureDimensions(ballSprite, ballWidth, ballHeight);
}

Ball::Ball(SpriteManager* spriteManager, float x, float y) {
    this->ballSprite = spriteManager->ball;
    spriteManager->getTextureDimensions(ballSprite, ballWidth, ballHeight);
    startingVel = {400, -400};
    currentVel = startingVel;

    vel.x = currentVel.x;
    vel.y = currentVel.y;

    ballRect = {x, y, (float)ballWidth, (float)ballHeight};
}

void Ball::reset() {
    vel.x = startingVel.x;
    vel.y = startingVel.y;

    ballRect.x = SCREEN_WIDTH / 2 - ballWidth / 2;
    ballRect.y = SCREEN_HEIGHT / 2  - ballHeight / 2;
    ballRect.w = ballWidth;
    ballRect.h = ballHeight;
}

void Ball::update(double dt) {
    move(dt);
}

void Ball::update(double dt, SDL_FRect paddleRect) {
    ballRect.x = (paddleRect.x + (paddleRect.w / 2)) - (ballWidth / 2);
    ballRect.y = paddleRect.y - paddleRect.h;
    ballRect.w = ballWidth;
    ballRect.h = ballHeight;
}

void Ball::move(double dt) {
    ballRect.x += vel.x * dt;
    ballRect.y += vel.y * dt;
}

void Ball::flipY() {
    vel.y = vel.y * -1;
}

void Ball::flipX() {
    vel.x = vel.x * -1;
}

void Ball::render() {
    SDL_RenderCopyF(gRenderer, ballSprite, NULL, &ballRect );

    // DEBUG: Bounding Boxes
    //SDL_SetRenderDrawColor(gRenderer, 255,255,0, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &ballRect);
}

void Ball::changeAngle(int hitLocation, int paddleSize) {
    
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
        ballRect.y = border.y + border.h;
        flipY();
    }

    void Ball::hitRightWall(SDL_FRect border) {
        ballRect.x = border.x - ballRect.w;
        flipX();
    }

    void Ball::hitLeftWall(SDL_FRect border) {
        ballRect.x = border.x + border.w;
        flipX();
    }

    void Ball::hitPaddle(Vector2d normals, SDL_FRect paddleRect){
        int ball_mid = ballRect.x + (ballRect.w / 2);
        int paddle_mid = paddleRect.x + (paddleRect.w / 2);
        int hitLocation = paddle_mid - ball_mid;

         changeAngle(hitLocation, paddleRect.w);
        
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