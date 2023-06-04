#include <Ball.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <cmath>

#include <Sign.h>

Ball::Ball(SpriteManager* spriteManager) {
    this->ballSprite = spriteManager->ball;

    currentVel = startingVel;
    vel.x = currentVel;
    vel.y = currentVel;

    spriteManager->getTextureDimensions(ballSprite, ballWidth, ballHeight);
}

Ball::Ball(SpriteManager* spriteManager, float x, float y, float currentVel) {
    this->currentVel = currentVel;
    this->ballSprite = spriteManager->ball;
    spriteManager->getTextureDimensions(ballSprite, ballWidth, ballHeight);

    vel.x = currentVel;
    vel.y = -currentVel;

    ballRect = {x, y, (float)ballWidth, (float)ballHeight};
}


float Ball::getCurrentVel() {
    return currentVel;
}

void Ball::setSpeed(int ballSpeed) {
    // Based on the direction of the ball on an axis (Sign) unapply the base speed and apply the new speed.
    if (sgn(vel.x) == 1) {
        vel.x = vel.x - currentVel;
        vel.x = vel.x + ballSpeed;
    } else {
        vel.x = vel.x + currentVel;
        vel.x = vel.x - ballSpeed;
    }

    if (sgn(vel.y) == 1) {
        vel.y = vel.y - currentVel;
        vel.y = vel.y + ballSpeed;
    } else {
        vel.y = vel.y + currentVel;
        vel.y = vel.y - ballSpeed;
    }

    currentVel = ballSpeed;

}

void Ball::speedUp() {
    // Need to make sure this is being called every time the speed is changed. ie flipx. I think it's not always being used when we just update ball.vel we don't reference currentvel
    // when we bounce we should always reference currentvel
    // Check what direction the ball is moving on X
    if (currentVel < maxVel ) {
        currentVel = currentVel + speedUpAmount;
        spdlog::info("Speedup:" + std::to_string(currentVel));
    }
}

void Ball::reset() {
    currentVel = startingVel;
    vel.x = currentVel;
    vel.y = -currentVel;

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

void Ball::updateStuck(double dt, SDL_FRect paddleRect) {
    ballRect.x = paddleRect.x + stuckOffset;
    ballRect.y = paddleRect.y - paddleRect.h;
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

void Ball::setStuckOffset(int offset) {
    this->stuckOffset = offset;
}

void Ball::resetStuckOffset(){
    stuckOffset = 0;
}

void Ball::stickToPaddle() {
    stuckToPaddle = true;
}

void Ball::freeFromPaddle(){
    stuckToPaddle = false;
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

    // If the ball hit exactly in the middle move it one pixel to the right.
    if (hitLocation == 0) {
        hitLocation = 1;
    }

    // Divide the Location by half the size of the paddle resulting in a float between 0 and 1
    float angle = (float)hitLocation / (float)paddleHalf;
    
    // Remove sign
    angle = abs(angle);

    // Sometimes there can be a hit location greater than one due to the ball impacting with the middle of the ball past the end of the paddle. This is considered a 1.0/-1.0 angle.
    if ( angle > 1.0f ) {
        angle = 1.0f;
    }

    if ( angle < 0.01f ) {
        angle = 0.01f;
    } 

    float newXSpeed = 0;

    // Not happy with this. Was looking for a formula that would do the same thing.
    if (angle >= 0.75) {
        newXSpeed = currentVel + (currentVel * 0.75);
    } else if (angle < 0.75 && angle >= 0.51) {
        newXSpeed = currentVel + (currentVel * 0.50);
    } else if (angle < 0.51 && angle >= 0.26) {
        newXSpeed = currentVel + (currentVel * 0.25);
    } else if (angle <= 0.25) {
        newXSpeed = currentVel;
    }
    
    // Set the new X Axis Speed
    // Negative Hit Locations - to the right the paddle generate a positive velocity
    // Positive Hit Locations - to the left the paddle generate a negative velocity 

    if (sgn(hitLocation) == 1) {
        vel.x = -newXSpeed;
    } else {
        vel.x = newXSpeed;
    }

    // Set the new Y Axis Speed as speedup has occured due to paddle collision.
    if (sgn(vel.y) == 1) {
        vel.y = currentVel;
    } else {
        vel.y = -currentVel;
    }

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

        speedUp();

        if (abs(normals.x) > 0.0001f) {
            flipX();
        } 
        
        if (abs(normals.y) > 0.0001f) {
            // Get the middle of the ball and the paddle
            int ball_mid = ballRect.x + (ballRect.w / 2);
            int paddle_mid = paddleRect.x + (paddleRect.w / 2);

            // Get the hitlocation. Left of paddle_mid will be a positive number. Right of paddle_mid will be a negative number
            int hitLocation = paddle_mid - ball_mid;
            changeAngle(hitLocation, paddleRect.w);
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