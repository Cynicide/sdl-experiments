#include <Ball.h>
#include <cmath>
#include "spdlog/spdlog.h"
#include <Sign.h>

Ball::Ball(SpriteManager* spriteManager, AudioManager* audioManager) {
    this->ballSprite = spriteManager->ball;
    this->audioPaddleHit = audioManager->pong;
    this->audioBrickHit = audioManager->ping;
    currentVel = startingVel;
    vel.x = currentVel;
    vel.y = currentVel;

    spriteManager->getTextureDimensions(ballSprite, ballWidth, ballHeight);
}

Ball::Ball(SpriteManager* spriteManager, float x, float y, float currentVel, AudioManager* audioManager) {
    this->currentVel = currentVel;
    this->ballSprite = spriteManager->ball;
    this->audioPaddleHit = audioManager->pong;
    this->audioBrickHit = audioManager->ping;
    
    spriteManager->getTextureDimensions(ballSprite, ballWidth, ballHeight);

    vel.x = currentVel;
    vel.y = -currentVel;

    ballRect = {x, y, (float)ballWidth, (float)ballHeight};
}

// Regular Ball Movement
void Ball::update(double dt) {
        move(dt);
}

void Ball::revertUpdate(double dt) {
    ballRect.x -= vel.x * dt;
    ballRect.y -= vel.y * dt;
}

void Ball::moveAbovePaddle(SDL_FRect paddleRect) {
    ballRect.y = paddleRect.y - ballRect.h ;
}

// Moves the ball in lock step with the paddle
void Ball::update(double dt, SDL_FRect paddleRect) {
    ballRect.x = (paddleRect.x + (paddleRect.w / 2)) - (ballWidth / 2);
    ballRect.y = paddleRect.y - paddleRect.h;
    ballRect.w = ballWidth;
    ballRect.h = ballHeight;
}

// Moves the ball when the Magnetic Powerup is active
void Ball::updateStuck(double dt, SDL_FRect paddleRect) {
    ballRect.x = paddleRect.x + stuckOffset;
    ballRect.y = paddleRect.y - ballRect.h;
}


// Reset the ball's position and velocity
void Ball::reset() {
    currentVel = startingVel;
    vel.x = currentVel;
    vel.y = -currentVel;

    ballRect.x = SCREEN_WIDTH / 2 - ballWidth / 2;
    ballRect.y = SCREEN_HEIGHT / 2  - ballHeight / 2;
    ballRect.w = ballWidth;
    ballRect.h = ballHeight;
}


// Wall Collision
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

void Ball::hitLightning() {
    flipY();
}

// Collision with the Player
void Ball::hitPaddle(Vector2d normals, SDL_FRect paddleRect){

    // If we collide on the side fo the paddle
    if (abs(normals.x) > 0.0001f) {
        flipX();
    } 

    // If we collide on the top
    if (abs(normals.y) > 0.0001f) {
        // Get the middle of the ball and the paddle
        int ball_mid = ballRect.x + (ballRect.w / 2);
        int paddle_mid = paddleRect.x + (paddleRect.w / 2);

        // Get the hitlocation. Left of paddle_mid will be a positive number. Right of paddle_mid will be a negative number
        int hitLocation = paddle_mid - ball_mid;
        changeAngle(hitLocation, paddleRect.w);
        flipY();
    }

    speedUp();

    // Play Collision Sound
    if (Mix_Playing(1)) {
        Mix_HaltChannel(1);
        Mix_PlayChannel(1, audioPaddleHit, 0);
    } else {
        Mix_PlayChannel(1, audioPaddleHit, 0);
    }   

}

//Collision with a brick or turret
void Ball::hitBrick(Vector2d normals){
    if (abs(normals.x) > 0.0001f) {
        flipX();
    } 
    
    if (abs(normals.y) > 0.0001f) {
        flipY();
    }

    if (Mix_Playing(3)) {
        Mix_HaltChannel(3);
        Mix_PlayChannel(3, audioBrickHit, 0);
    } else {
        Mix_PlayChannel(3, audioBrickHit, 0);
    } 
}

// Speed the ball up
void Ball::speedUp() {
    auto logger = spdlog::get("fileLogger");
    if (currentVel < maxVel ) {
        currentVel = currentVel + speedUpAmount;
        logger->debug("Speedup:" + std::to_string(currentVel));
    }
}

// Get the current Velocity
float Ball::getCurrentVel() {
    return currentVel;
}

void Ball::setSpeed(int ballSpeed) {
    // Based on the direction of the ball on an axis (Sign) unapply the base speed and apply the new base speed.
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

    // Update the base speed
    currentVel = ballSpeed;
}

// Magnetic Powerup
void Ball::setStuckOffset(int offset) {
    this->stuckOffset = offset;
}

void Ball::resetStuckOffset(){
    stuckOffset = 0;
}

void Ball::stickToPaddle() {
    stuckToPaddle = true;
}

void Ball::releaseFromPaddle(){
    stuckToPaddle = false;
}

void Ball::render() {
    SDL_RenderCopyF(gRenderer, ballSprite, NULL, &ballRect );
    // DEBUG: Bounding Boxes
    //SDL_SetRenderDrawColor(gRenderer, 255,255,0, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &ballRect);
}

void Ball::changeAngle(int hitLocation, int paddleSize) {
     auto logger = spdlog::get("fileLogger");   
    // Hit Location should be between paddleSize and -paddleSize
    // Smaller numbers are generated closer to the center
    logger->info("HitLocation: " + std::to_string(hitLocation));
    logger->info("PaddleSize / 2: " + std::to_string(paddleSize / 2 ));

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

    logger->info("Bounce Resolved: VX: " + std::to_string(vel.x) + " VY: " + std::to_string(vel.y));
}



// Private Methods
void Ball::flipX() {
    vel.x = vel.x * -1;
}

void Ball::flipY() {
    vel.y = vel.y * -1;
}

void Ball::move(double dt) {
    ballRect.x += vel.x * dt;
    ballRect.y += vel.y * dt;
}