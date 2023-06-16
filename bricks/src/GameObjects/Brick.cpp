#include <Brick.h>
//#include <iostream>
#include <algorithm>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


Brick::Brick(float _xpos, float _ypos, Definitions::BrickType type, SDL_Texture* sprite) {
    
    brickType = type;

    switch (brickType) {
        case Definitions::BrickType::Red:
        {
            brickSprite = sprite;
            health = 1;
            break;
        }
        case Definitions::BrickType::Blue: {
            brickSprite = sprite;
            health = 1;
            break;
        }
        case Definitions::BrickType::Yellow: {
            brickSprite = sprite;
            health = 1;
            break;
        }
        case Definitions::BrickType::Orange: {
            brickSprite = sprite;
            health = 1;
            break;
        }
        case Definitions::BrickType::Green: {
            brickSprite = sprite;
            health = 1;
            break;
        }
        case Definitions::BrickType::Purple: {
            brickSprite = sprite;
            health = 1;
            break;
        }  
        case Definitions::BrickType::Tough: {
            brickSprite = sprite;
            health = 2;
            break;
        }
        case Definitions::BrickType::Indestructable: {
            destructable = false;
            brickSprite = sprite;
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
    for( int i = 0; i <= numSprites - 1; i++ ) {
        brickSpriteClips[ i ].x =   i * brickWidth;
        brickSpriteClips[ i ].y =   0;
        brickSpriteClips[ i ].w =  brickWidth;
        brickSpriteClips[ i ].h = brickHeight;
        }
}

void Brick::render() 
{
    if (brickStatus == Definitions::BrickStatus::BrickExploding) {
            int frame = (int)currentdestructionFrame;
            SDL_Rect solidSprite = {brickSpriteClips[frame].x, brickSpriteClips[frame].y, brickSpriteClips[frame].w, brickSpriteClips[frame].h};
            SDL_RenderCopyF(gRenderer, brickSprite, &solidSprite, &brickRect );
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

void Brick::renderPreServe() {
    if (shineAnimDone == false) {
        int frame = (int)currentShineFrame;
        SDL_Rect solidSprite = {brickSpriteClips[frame].x, brickSpriteClips[frame].y, brickSpriteClips[frame].w, brickSpriteClips[frame].h};
        SDL_RenderCopyF(gRenderer, brickSprite, &solidSprite, &brickRect );
    } else {
        render();
    }
}

Definitions::BrickStatus Brick::hit() {
    if (destructable == true) {
        health = health - 1;

        if (health == 0) {
            spdlog::info("Brick at: " + std::to_string(xpos) + "," + std::to_string(ypos) + " has been marked as destroyed.");
            brickStatus = Definitions::BrickStatus::BrickExploding;      
        }
    }
    return brickStatus;
}

void Brick::update(double dt) {
    if (brickStatus == Definitions::BrickStatus::BrickExploding) {
        currentdestructionFrame = currentdestructionFrame + (60 * dt);
        if ((int)currentdestructionFrame == destructionEndFrame) {
            brickStatus = Definitions::BrickStatus::BrickDestroyed;
        }
    }
}

void Brick::updatePreServe(double dt) {
    currentShineFrame = currentShineFrame + (20 * dt);
    if ((int)currentShineFrame == shineEndFrame) {
        currentShineFrame = shineStartFrame;
        shineAnimDone = true;
    }
}