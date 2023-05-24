#include <Paddle.h>
//#include <iostream>
#include <Vector2d.h>

Paddle::Paddle(SpriteManager *spriteManager, Mix_Chunk* collisionSound, Mix_Chunk* explosionSound) : 
    paddleSprite(spriteManager->paddle),
    explosionSprite(spriteManager->shipExplosion),
    collisionSound(collisionSound),
    explosionSound(explosionSound) {

    paddleSpeed = 5.f;

    spriteManager->getTextureDimensions(paddleSprite, textureWidth, textureHeight);
    spriteManager->getTextureDimensions(explosionSprite, explosionWidth, explosionHeight);

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
    SDL_RenderCopyF(gRenderer, paddleSprite, NULL, &paddleRect );
    //SDL_SetRenderDrawColor(gRenderer, 255,0,0, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &paddleRect);
}

void Paddle::renderPlaying() {
    SDL_RenderCopyF(gRenderer, paddleSprite, NULL, &paddleRect );
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

void Paddle::move() {
  int borderHeight = 16;
    int borderWidth = 32;      

    int x, y;
    SDL_GetMouseState(&x, &y);

    float scaleX = static_cast<float>(LOGICAL_SCREEN_WIDTH) / SCREEN_WIDTH;

    int paddleX = static_cast<int>(x / scaleX);

    paddleRect.x = paddleX - (paddleRect.w / 2);

    if (paddleRect.x < PLAYFIELD_STARTX + borderWidth) {
        paddleRect.x = PLAYFIELD_STARTX + borderWidth;
    } 

    if (paddleRect.x > PLAYFIELD_STARTX + PLAYFIELD_WIDTH - textureWidth - borderWidth) {
        paddleRect.x = PLAYFIELD_STARTX + PLAYFIELD_WIDTH - textureWidth - borderWidth;
    }
    paddleRect.y = SCREEN_HEIGHT - textureHeight - borderHeight;
    paddleRect.w = textureWidth;
    paddleRect.h = textureHeight;
}

void Paddle::reset() {
    currentdestructionFrame = destructionStartFrame;
    innerExplosionTimer = 0;
    explosionSoundPlayed = false;
}

void Paddle::hit() {
    Mix_PlayChannel( -1, collisionSound, 0 );
}

void Paddle::explode() {
    Mix_PlayChannel( -1, explosionSound, 0 );
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