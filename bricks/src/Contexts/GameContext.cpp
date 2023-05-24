#include <GameContext.h>
#include <globals.h>

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

void GameContext::AddBallAtLocation(float x, float y) {
    for (int b = 0; b < 3; ++b) {
        if (ballList[b] == nullptr) {
            ballList[b] = new Ball(&spriteManager, x, y);
            break;
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
            powerupList[p] = new Powerup(&spriteManager, x, y, parentWidth);
            break;
        }
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