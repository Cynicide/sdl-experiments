#include <globals.h>

#include <Powerup.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

Powerup::Powerup(SDL_Texture* powerupSprite, float xPos, float yPos) {
    this->powerupSprite = powerupSprite;

    bool bQuery = SDL_QueryTexture(powerupSprite, NULL, NULL, &powerupWidth, &powerupHeight);
    if (bQuery == 1) {
        spdlog::error("Issue querying Powerup Texture: ");
        spdlog::error(SDL_GetError());
    }

    powerupRect= {xPos, yPos,((float)powerupWidth / (float)numSprites), (float)powerupHeight};
    SliceSpriteSheet();
}

void Powerup::update(double dt) {
    currentFrame = currentFrame + (30 * dt);
    if ((int)currentFrame > (float)lastFrame) {
        currentFrame = 0.0f;
        }
    
    move(dt);
}

void Powerup::render() {
        int frame = (int)currentFrame;
        SDL_Rect solidSprite = {powerupSpriteClips[frame].x, powerupSpriteClips[frame].y, powerupSpriteClips[frame].w, powerupSpriteClips[frame].h};
        SDL_RenderCopyF(gRenderer, powerupSprite, &solidSprite, &powerupRect );
}

void Powerup::move(double dt) {
    powerupRect.y = powerupRect.y + (yVel * dt);
}

void Powerup::SliceSpriteSheet() {
    for( int i = 0; i <= numSprites - 1; i++ ) {
        powerupSpriteClips[ i ].x =   i * (powerupWidth / numSprites);
        powerupSpriteClips[ i ].y =   0;
        powerupSpriteClips[ i ].w =  (powerupWidth / numSprites);
        powerupSpriteClips[ i ].h = powerupHeight;
        }
}