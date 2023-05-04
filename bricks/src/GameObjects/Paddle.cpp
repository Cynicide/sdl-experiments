#include <Paddle.h>
#include <iostream>
#include <Vector2d.h>

Paddle::Paddle() {
    paddleSprite = SpriteManager::get()->paddle;
    explosionSprite = SpriteManager::get()->shipExplosion;
    collisionSound = AudioManager::get()->pong;

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


void Paddle::update(double dt) {
        int borderHeight = 16;
        int borderWidth = 32;      

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

void Paddle::render(Definitions::SubState subState) 
{

    switch (subState) {
        case Definitions::SubState::SERVING: {
            SDL_RenderCopyF(gRenderer, paddleSprite, NULL, &paddleRect );
            //SDL_SetRenderDrawColor(gRenderer, 255,0,0, SDL_ALPHA_OPAQUE);
            //SDL_RenderDrawRectF(gRenderer, &paddleRect);
            break;
        }
        case Definitions::SubState::PLAYING: {
            SDL_RenderCopyF(gRenderer, paddleSprite, NULL, &paddleRect );
            //SDL_SetRenderDrawColor(gRenderer, 255,0,0, SDL_ALPHA_OPAQUE);
            //SDL_RenderDrawRectF(gRenderer, &paddleRect);
            break;
        }
        case Definitions::SubState::DYING: {
            spdlog::debug("Rendering Explosion");

            SDL_FRect explosionRect;
            float paddleMidX = paddleRect.x + (paddleRect.w / 2);
            float paddleMidY = paddleRect.y + (paddleRect.h /2 );

            explosionRect.x = paddleMidX - (explosionWidth / 2);
            explosionRect.y = paddleMidY - (explosionHeight / 2);
            explosionRect.w = explosionWidth;
            explosionRect.h = explosionHeight;

            SDL_Rect solidSprite = {explosionSpriteClips[currentdestructionFrame].x, explosionSpriteClips[currentdestructionFrame].y, explosionSpriteClips[currentdestructionFrame].w, explosionSpriteClips[currentdestructionFrame].h};
            SDL_RenderCopyF(gRenderer, explosionSprite, &solidSprite, &explosionRect);
            currentdestructionFrame = currentdestructionFrame + 1;
            if (currentdestructionFrame == destructionEndFrame) {
                currentdestructionFrame = 1;
            }
            break;
        }
        case Definitions::SubState::GAMEOVER: {
            break;
        }
    }

}

void Paddle::destroy() {

}

void Paddle::hit() {
    Mix_PlayChannel( -1, collisionSound, 0 );
}

void Paddle::sliceExplosionSheet() {

        for( int i = 0; i <= numExplosionSprites - 1; i++ ) 
        {
        explosionSpriteClips[ i ].x =   i * explosionWidth;
        explosionSpriteClips[ i ].y =   0;
        explosionSpriteClips[ i ].w =  explosionWidth;
        explosionSpriteClips[ i ].h = explosionHeight;
        }
}