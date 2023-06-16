#include <Paddle.h>
//#include <iostream>
#include <Vector2d.h>

Paddle::Paddle(SpriteManager* spriteManager, Mix_Chunk* collisionSound, Mix_Chunk* explosionSound) : 
    paddleSprite(spriteManager->paddle),
    explosionSprite(spriteManager->shipExplosion),
    longPaddle(spriteManager->longPaddle),
    laserPaddle(spriteManager->laserPaddle),
    collisionSound(collisionSound),
    explosionSound(explosionSound) {

    spriteManager->getTextureDimensions(paddleSprite, paddleWidth, paddleHeight);
    spriteManager->getTextureDimensions(explosionSprite, explosionWidth, explosionHeight);
    spriteManager->getTextureDimensions(longPaddle, longPaddleWidth, longPaddleHeight);
    spriteManager->getTextureDimensions(laserPaddle, laserPaddleWidth, laserPaddleHeight);

    currentTextureWidth = &paddleWidth;
    currentTextureHeight = &paddleHeight;
    currentTexture = paddleSprite;

    sliceExplosionSheet();
}


void Paddle::updateServing(double dt) {
    move();
}

void Paddle::updatePlaying(double dt) {
    move();
}

void Paddle::updateDying(double dt) {
    if (explosionSoundPlayed == false) {
        explode();
        explosionSoundPlayed = true;
    }
    currentdestructionFrame = currentdestructionFrame + (60 * dt);
}


void Paddle::renderServing() {
    SDL_RenderCopyF(gRenderer, currentTexture, NULL, &paddleRect );
    //SDL_SetRenderDrawColor(gRenderer, 255,0,0, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &paddleRect);
}

void Paddle::renderPlaying() {
    SDL_RenderCopyF(gRenderer, currentTexture, NULL, &paddleRect );
    //SDL_SetRenderDrawColor(gRenderer, 255,0,0, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &paddleRect);
}

void Paddle::renderDying() {
    spdlog::debug("Rendering Explosion");
    int frame = (int)currentdestructionFrame;

    if (frame < destructionEndFrame) {
        SDL_FRect explosionRect;
        float paddleMidX = paddleRect.x + (paddleRect.w / 2);
        float paddleMidY = paddleRect.y + (paddleRect.h /2 );

        explosionRect.x = paddleMidX - ((explosionWidth / numExplosionSprites) / 2);
        explosionRect.y = paddleMidY - (explosionHeight / 2);
        explosionRect.w = explosionWidth / numExplosionSprites;
        explosionRect.h = explosionHeight;

        SDL_Rect solidSprite = {explosionSpriteClips[frame].x, explosionSpriteClips[frame].y, explosionSpriteClips[frame].w, explosionSpriteClips[frame].h};
        SDL_RenderCopyF(gRenderer, explosionSprite, &solidSprite, &explosionRect);               
    }
}

void Paddle::destroy() {

}

void Paddle::setNormalPaddle() {
    currentTextureWidth = &paddleWidth;
    currentTextureHeight = &paddleHeight;
    currentTexture = paddleSprite;
}

void Paddle::setLongPaddle() {
    currentTextureWidth = &longPaddleWidth;
    currentTextureHeight = &longPaddleHeight;
    currentTexture = longPaddle;
}

void Paddle::setLaserPaddle() {
    currentTextureWidth = &laserPaddleWidth;
    currentTextureHeight = &laserPaddleHeight;
    currentTexture = laserPaddle;
}

void Paddle::move() {
    // Hmmm... This looks bad. How do we replace this?
    int borderHeight = 16;
    int borderWidth = 32;      

    int x, y;
    SDL_GetMouseState(&x, &y);

    float scaleX = static_cast<float>(LOGICAL_SCREEN_WIDTH) / SCREEN_WIDTH;

    int paddleX = static_cast<int>(x / scaleX);

    paddleRect.w = static_cast<float>(*currentTextureWidth);
    paddleRect.h = static_cast<float>(*currentTextureHeight);

    paddleRect.x = paddleX - (paddleRect.w / 2);

    if (paddleRect.x < PLAYFIELD_STARTX + borderWidth) {
        paddleRect.x = PLAYFIELD_STARTX + borderWidth;
    } 

    if (paddleRect.x > PLAYFIELD_STARTX + PLAYFIELD_WIDTH - paddleRect.w - borderWidth) {
        paddleRect.x = PLAYFIELD_STARTX + PLAYFIELD_WIDTH - paddleRect.w - borderWidth;
    }
    paddleRect.y = SCREEN_HEIGHT - paddleRect.h - borderHeight;

}

void Paddle::reset() {
    currentdestructionFrame = destructionStartFrame;
    innerExplosionTimer = 0;
    explosionSoundPlayed = false;
    currentTexture = paddleSprite;
}

void Paddle::hit() {
    /*if (Mix_Playing(1)) {
        Mix_HaltChannel(1);
        Mix_PlayChannel(1, collisionSound, 0);
    } else {
        Mix_PlayChannel(1, collisionSound, 0);
    }*/     
}

void Paddle::explode() {
    if (Mix_Playing(2)) {
        Mix_HaltChannel(2);
        Mix_PlayChannel(2, explosionSound, 0);
    } else {
        Mix_PlayChannel(2, explosionSound, 0);
    }
}

void Paddle::sliceExplosionSheet() {

        for( int i = 0; i <= numExplosionSprites - 1; i++ ) 
        {
        explosionSpriteClips[ i ].x =   i * (explosionWidth / numExplosionSprites);
        explosionSpriteClips[ i ].y =   0;
        explosionSpriteClips[ i ].w =  (explosionWidth / numExplosionSprites);
        explosionSpriteClips[ i ].h = explosionHeight;
        }
        spdlog::info("Slicing paddle Sprite Sheet");
}