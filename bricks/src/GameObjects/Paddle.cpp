#include <Paddle.h>
//#include <iostream>
#include <Vector2d.h>

Paddle::Paddle(SDL_Texture* paddleSprite, SDL_Texture* explosionSprite, Mix_Chunk* collisionSound, Mix_Chunk* explosionSound) {
    this->paddleSprite = paddleSprite;
    this->explosionSprite = explosionSprite;
    this->collisionSound = collisionSound;
    this->explosionSound = explosionSound;

    paddleSpeed = 5.f;

    /*bool bQuery = SDL_QueryTexture(paddleSprite, NULL, NULL, &textureWidth, &textureHeight);
    if (bQuery == 1) {
        spdlog::error("Error querying paddle sprite.");
        spdlog::error( SDL_GetError());
    }  

    bQuery = SDL_QueryTexture(explosionSprite, NULL, NULL, &explosionWidth, &explosionHeight);
    if (bQuery == 1) {
        spdlog::error("Error querying paddle explosion sprite.");
        spdlog::error(SDL_GetError());
    }*/ 

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

        explosionRect.x = paddleMidX - (explosionWidth / 2);
        explosionRect.y = paddleMidY - (explosionHeight / 2);
        explosionRect.w = explosionWidth;
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
    Uint32 mouseState = SDL_GetMouseState(&x, &y);

    paddleRect.x = x;

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
        explosionSpriteClips[ i ].x =   i * explosionWidth;
        explosionSpriteClips[ i ].y =   0;
        explosionSpriteClips[ i ].w =  explosionWidth;
        explosionSpriteClips[ i ].h = explosionHeight;
        }
        spdlog::info("Slicing paddle Sprite Sheet");
}