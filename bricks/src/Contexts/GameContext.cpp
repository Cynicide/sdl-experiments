#include <GameContext.h>
#include <globals.h>
#include <random>
#include <stack>

GameContext::GameContext() :
    spriteManager(),
    audioManager(),
    textManager(),
    paddle(&spriteManager, audioManager.pong, audioManager.explosion),
    levelManager(&spriteManager, &audioManager),
    lightning(&spriteManager),
    tiledBackground(&spriteManager),
    scrollingBackground(&spriteManager),
    borderL(PLAYFIELD_STARTX, false, &spriteManager),
    borderR(PLAYFIELD_STARTX + PLAYFIELD_WIDTH - borderWidthV,  true, &spriteManager),
    borderT(PLAYFIELD_STARTX, false, &spriteManager),
    borderTR(PLAYFIELD_STARTX + PLAYFIELD_WIDTH - borderWidthC, true, &spriteManager),
    borderTL(PLAYFIELD_STARTX, false, &spriteManager),
    lifeCounter(PLAYFIELD_STARTX + borderWidthC, &spriteManager),
    logoSprite(&spriteManager)
{
    this->publicPixel12 = textManager.publicPixel12;
    this->publicPixel24 = textManager.publicPixel24;

    levelManager.getLevelFiles();
}

void GameContext::AddBall() {
    for (int b = 0; b < 3; ++b) {
        if (ballList[b] == nullptr) {
            ballList[b] = new Ball(&spriteManager);
            break;
        }
    }
}

void GameContext::AddLife() {
    if (lives < maxLives) {
        lives = lives + 1;
    }
}

void GameContext::AddBallsAtLocation(float x, float y, float currentVel) {
    for (int b = 0; b < 3; ++b) {
        if (ballList[b] == nullptr) {
            ballList[b] = new Ball(&spriteManager, x, y, currentVel);
        }
    }
}

void GameContext::ClearBalls() {
    for (int b = 0; b < 3; ++b) {
        if (ballList[b] != nullptr) {
            delete(ballList[b]);
            ballList[b] = nullptr;
        }
    }
}

void GameContext::AddPowerUp(float x, float y, int parentWidth) {
    for (int p = 0; p < 5; ++p) {
        if (powerupList[p] == nullptr) {
            spdlog::info("Adding powerup at: " + p);
            powerupList[p] = new Powerup(&spriteManager, x, y, parentWidth, randomizePowerUp());
            break;
        }
    }
}

Definitions::PowerUpType GameContext::randomizePowerUp() {
    
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    spdlog::info("Randomizing Powerup");

    int randomNumber = distribution(engine);
    if (randomNumber < extraLifeChance) {
        spdlog::info("Generating Extra Life Powerup");
        return Definitions::PowerUpType::ExtraLife;
    } else if (randomNumber < slowBallChance) {
        spdlog::info("Generating Slow Powerup");
        return Definitions::PowerUpType::SlowBall;
    } else if (randomNumber < wideChance) {
        spdlog::info("Generating Wide Powerup");
        return Definitions::PowerUpType::Wide;
    } else if (randomNumber <= tripleBallChance) {
        spdlog::info("Generating Triple Powerup");
        return Definitions::PowerUpType::TripleBall;
    } else if (randomNumber <= laserChance) {
        spdlog::info("Generating Laser Powerup");
        return Definitions::PowerUpType::Laser;
    } else if (randomNumber <= levelSkipChance) {
        spdlog::info("Generating Level Skip Powerup");
        return Definitions::PowerUpType::LevelSkip;
    } else if (randomNumber <= magneticChance){
        spdlog::info("Generating Magnetic Powerup");
        return Definitions::PowerUpType::Magnetic; 
    } else {
        spdlog::info("Generating Laser Powerup");
        return Definitions::PowerUpType::Laser;         
    }
}

void GameContext::ClearPowerups() {
    for (int p = 0; p < 5; ++p) {
        if (powerupList[p] != nullptr) {
            delete(powerupList[p]);
            powerupList[p] = nullptr;
        }
    }
}

void GameContext::AddBullets(SDL_FRect paddleRect) {
    // Don't add any bullets unless two slots are free.
    int freeSlots = 0;
    for (int p = 0; p < 2; ++p) {
        if (bulletList[p] == nullptr) {
            freeSlots = freeSlots + 1;
        }
    }

    if (freeSlots >= 2) {

        // Create a stack to hold the bullets
        std::stack<float> bulletStack;
        
        // Push the location to spawn each bullet above the paddle
        bulletStack.push(paddleRect.x + (paddleRect.w * 0.33));
        bulletStack.push(paddleRect.x + (paddleRect.w * 0.66));

        // Look for empty elements in the bullet array
        for (int p = 0; p < 2; ++p) {
            if (bulletList[p] == nullptr) {
                //Retrieve and pop the bullet xlocation
                float xLoc = bulletStack.top();
                bulletStack.pop();
                bulletList[p] = new Bullet(&spriteManager, xLoc, paddleRect.y + 16);
            }
            // If the stack is empty play the audio break out of the loop
            if (bulletStack.empty()) {
                if (Mix_Playing(4)) {
                    Mix_HaltChannel(4);
                    Mix_PlayChannel(4, audioManager.laser, 0);
                } else {
                    Mix_PlayChannel(4, audioManager.laser, 0);
                }            
                break;
            }
        }  
    }
}

void GameContext::ClearBullets() {
    for (int p = 0; p < 2; ++p) {
        if (bulletList[p] != nullptr) {
            delete(bulletList[p]);
            bulletList[p] = nullptr;
        }
    }    
}

void GameContext::resetGame() {
    levelManager.clearLevel();
    levelManager.restartGame();
    cleanup();
}

void GameContext::cleanup() {
    levelManager.clearTurretBullets();
    ClearBalls();
    ClearBullets();
    ClearPowerups();
}