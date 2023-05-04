#include <Brick.h>
#include <iostream>
#include <algorithm>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


Brick::Brick(float _xpos, float _ypos, Definitions::BrickType type) {
    
    collisionSound = AudioManager::get()->ping;

    brickType = type;

    switch (brickType) {
        case Definitions::BrickType::Red:
        {
            brickSprite = SpriteManager::get()->brickRed;
            health = 1;
            break;
        }
        case Definitions::BrickType::Blue: {
            brickSprite = SpriteManager::get()->brickBlue;
            health = 1;
            break;
        }
        case Definitions::BrickType::Yellow: {
            brickSprite = SpriteManager::get()->brickYellow;
            health = 1;
            break;
        }
        case Definitions::BrickType::Orange: {
            brickSprite = SpriteManager::get()->brickOrange;
            health = 1;
            break;
        }
        case Definitions::BrickType::Green: {
            brickSprite = SpriteManager::get()->brickGreen;
            health = 1;
            break;
        }
        case Definitions::BrickType::Purple: {
            brickSprite = SpriteManager::get()->brickPurple;
            health = 1;
            break;
        }  
        case Definitions::BrickType::Tough: {
            brickSprite = SpriteManager::get()->brickTough;
            health = 2;
            break;
        }
        case Definitions::BrickType::Indestructable: {
            destructable = false;
            brickSprite = SpriteManager::get()->brickIndestructable;
            health = -1;
            break;
        }
    }
    SliceSpriteSheet();
    xpos = _xpos;
    ypos = _ypos;
    brickRect = {xpos, ypos, brickWidth, brickHeight};
}


void Brick::SliceSpriteSheet() {

    for( int i = 0; i <= numSprites - 1; i++ ) 
        {
        brickSpriteClips[ i ].x =   i * brickWidth;
        brickSpriteClips[ i ].y =   0;
        brickSpriteClips[ i ].w =  brickWidth;
        brickSpriteClips[ i ].h = brickHeight;
        }
}

void Brick::update(double dt) {
}

void Brick::render() 
{
    if (brickStatus == Definitions::BrickStatus::Exploding) {
            SDL_Rect solidSprite = {brickSpriteClips[currentdestructionFrame].x, brickSpriteClips[currentdestructionFrame].y, brickSpriteClips[currentdestructionFrame].w, brickSpriteClips[currentdestructionFrame].h};
            SDL_RenderCopyF(gRenderer, brickSprite, &solidSprite, &brickRect );
            currentdestructionFrame = currentdestructionFrame + 1;
            if (currentdestructionFrame == destructionEndFrame) {
                brickStatus = Definitions::BrickStatus::Destroyed;
            }

    } else {
        if (brickType == Definitions::BrickType::Tough) {
            if (health == 2) {
                SDL_Rect solidSprite = {brickSpriteClips[0].x, brickSpriteClips[0].y, brickSpriteClips[0].w, brickSpriteClips[0].h};
                SDL_RenderCopyF(gRenderer, brickSprite, &solidSprite, &brickRect );
            } else if (health == 1) {
                SDL_Rect solidSprite = {brickSpriteClips[1].x, brickSpriteClips[1].y, brickSpriteClips[1].w, brickSpriteClips[1].h};
                SDL_RenderCopyF(gRenderer, brickSprite, &solidSprite, &brickRect );
            }
        } else {
            SDL_Rect solidSprite = {brickSpriteClips[0].x, brickSpriteClips[0].y, brickSpriteClips[0].w, brickSpriteClips[0].h};
            SDL_RenderCopyF(gRenderer, brickSprite, &solidSprite, &brickRect );
        }

    }
    
    //SDL_SetRenderDrawColor(gRenderer, 255,255,255, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &brickRect);
}

void Brick::hit() {
    
    Mix_PlayChannel( -1, collisionSound, 0 );
    
    if (destructable == true) {
        health = health - 1;

        if (health == 0) {
            spdlog::info("Brick at: " + std::to_string(xpos) + "," + std::to_string(ypos) + " has been marked as destroyed.");
            brickStatus = Definitions::BrickStatus::Exploding;      
        }
    }
}