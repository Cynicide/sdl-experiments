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
    logoSprite(&spriteManager),
    powerupList(&spriteManager),
    bulletList(&spriteManager, &audioManager)
{
    this->publicPixel12 = textManager.publicPixel12;
    this->publicPixel24 = textManager.publicPixel24;

    levelManager.getLevelFiles();
}

void GameContext::addBall() {
    for (int b = 0; b < MAXBALLS; ++b) {
        if (ballList[b] == nullptr) {
            ballList[b] = new Ball(&spriteManager, &audioManager);
            break;
        }
    }
}

void GameContext::addLife() {
    if (lives < maxLives) {
        lives = lives + 1;
    }
}

void GameContext::addBallsAtLocation(float x, float y, float currentVel) {
    for (int b = 0; b < MAXBALLS; ++b) {
        if (ballList[b] == nullptr) {
            ballList[b] = new Ball(&spriteManager, x, y, currentVel, &audioManager);
        }
    }
}

void GameContext::updateBalls(double dt) {
    // Update each ball. If they are stuck to the paddle treat them as if they are being served.
    for (int b = 0; b < MAXBALLS; ++b) {
        if (ballList[b] != nullptr) {
            if (ballList[b]->stuckToPaddle == true) {
                ballList[b]->updateStuck(dt, paddle.paddleRect);
            } else {
                ballList[b]->update(dt);
            }

        }
    }
}

void GameContext::clearBalls() {
    for (int b = 0; b < MAXBALLS; ++b) {
        if (ballList[b] != nullptr) {
            delete(ballList[b]);
            ballList[b] = nullptr;
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
    clearBalls();
    //clearBullets();
    //clearPowerUps();
    powerupList.clear();
    bulletList.clear();
}