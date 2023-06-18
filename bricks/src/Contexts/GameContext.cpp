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
    logoSprite(&spriteManager),
    powerupList(&spriteManager),
    bulletList(&spriteManager, &audioManager),
    ballList(&spriteManager, &audioManager)
{
    this->publicPixel12 = textManager.publicPixel12;
    this->publicPixel24 = textManager.publicPixel24;

    levelManager.getLevelFiles();
}

void GameContext::addLife() {
    if (lives < maxLives) {
        lives = lives + 1;
    }
}

void GameContext::resetGame() {
    levelManager.clearLevel();
    levelManager.restartGame();
    cleanup();
    lives = startingLives;
}

void GameContext::cleanup() {
    levelManager.clearTurretBullets();
    ballList.clear();
    powerupList.clear();
    bulletList.clear();
}