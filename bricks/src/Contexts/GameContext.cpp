#include <GameContext.h>
#include <globals.h>

GameContext::GameContext() :
    spriteManager(),
    audioManager(),
    textManager(),
    ball(spriteManager.ball),
    paddle(spriteManager.paddle, spriteManager.shipExplosion, audioManager.pong, audioManager.explosion),
    levelManager(&spriteManager, &audioManager),
    lightning(spriteManager.lightning),
    tiledBackground(spriteManager.background),
    scrollingBackground(spriteManager.stars),
    borderL(PLAYFIELD_STARTX, false, spriteManager.techBorder),
    borderR(PLAYFIELD_STARTX + PLAYFIELD_WIDTH - borderWidthV,  true, spriteManager.techBorder),
    borderT(PLAYFIELD_STARTX, false, spriteManager.techTopBorder),
    borderTR(PLAYFIELD_STARTX + PLAYFIELD_WIDTH - borderWidthC, true, spriteManager.techCorner),
    borderTL(PLAYFIELD_STARTX, false, spriteManager.techCorner)
{
    this->logoSprite = spriteManager.logo;
    this->publicPixel12 = textManager.publicPixel12;
    this->publicPixel24 = textManager.publicPixel24;
    levelManager.getLevelFiles();
}