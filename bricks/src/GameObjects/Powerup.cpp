#include <globals.h>
#include <Powerup.h>
#include <random>
#include "spdlog/spdlog.h"

Powerup::Powerup(SpriteManager* spriteManager, float parentXPos, float parentYPos, int parentWidth) {
     auto logger = spdlog::get("fileLogger");   
    //this->powerupType = powerupType;
    randomizePowerup();

    switch (this->powerupType) {
        case Definitions::PowerUpType::Laser: {
            logger->info("Setting sprite for Laser");
            this->powerupSprite = spriteManager->capsuleLaser;
            break;
        }
        case Definitions::PowerUpType::ExtraLife: {
            logger->info("Setting sprite for Extra Life");
            this->powerupSprite = spriteManager->capsuleExtraLife;
            break;
        }
        case Definitions::PowerUpType::SlowBall: {
            logger->info("Setting sprite for Slow");
            this->powerupSprite = spriteManager->capsuleSlow;
            break;
        }
        case Definitions::PowerUpType::TripleBall: {
            logger->info("Setting sprite for Triple");
            this->powerupSprite = spriteManager->capsuleTriple;
            break;
        }
        case Definitions::PowerUpType::Wide: {
            logger->info("Setting sprite for Wide");
            this->powerupSprite = spriteManager->capsuleWide;
            break;
        }
        case Definitions::PowerUpType::LevelSkip: {
            logger->info("Setting sprite for Level Skip");
            this->powerupSprite = spriteManager->capsuleJump;
            break;
        }
        case Definitions::PowerUpType::Magnetic: {
            logger->info("Setting sprite for Magnetic");
            this->powerupSprite = spriteManager->capsuleMagnetic;
            break;
        }
    };

    spriteManager->getTextureDimensions(powerupSprite, powerupWidth, powerupHeight);

    float parentMid = parentXPos + (parentWidth / 2);
    float powerupMid = (((float)powerupWidth / (float)numSprites) / 2);
    float powerupXpos = parentMid - powerupMid;


    powerupRect= {powerupXpos, parentYPos,((float)powerupWidth / (float)numSprites), (float)powerupHeight};
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

void Powerup::randomizePowerup() {
        auto logger = spdlog::get("fileLogger");
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    logger->info("Randomizing Powerup");

    int randomNumber = distribution(engine);
    if (randomNumber < extraLifeChance) {
        logger->info("Generating Extra Life Powerup");
        powerupType = Definitions::PowerUpType::ExtraLife;
    } else if (randomNumber < slowBallChance) {
        logger->info("Generating Slow Powerup");
        powerupType = Definitions::PowerUpType::SlowBall;
    } else if (randomNumber < wideChance) {
        logger->info("Generating Wide Powerup");
        powerupType = Definitions::PowerUpType::Wide;
    } else if (randomNumber <= tripleBallChance) {
        logger->info("Generating Triple Powerup");
        powerupType = Definitions::PowerUpType::TripleBall;
    } else if (randomNumber <= laserChance) {
        logger->info("Generating Laser Powerup");
        powerupType = Definitions::PowerUpType::Laser;
    } else if (randomNumber <= levelSkipChance) {
        logger->info("Generating Level Skip Powerup");
        powerupType = Definitions::PowerUpType::LevelSkip;
    } else if (randomNumber <= magneticChance){
        logger->info("Generating Magnetic Powerup");
        powerupType = Definitions::PowerUpType::Magnetic; 
    } else {
        logger->info("Generating Laser Powerup");
        powerupType = Definitions::PowerUpType::Laser;         
    }
}