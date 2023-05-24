#pragma once

#include <TiledBackground.h>
#include <Paddle.h>
#include <Ball.h>
#include <BorderHorizontal.h>
#include <BorderVertical.h>
#include <BorderCorner.h>
#include <Brick.h>
#include <Lightning.h>
#include <Level.h>
#include <ScrollingBackground.h>
#include <Powerup.h>
#include <LifeCounter.h>
#include <Logo.h>

#include <TextManager.h>
#include <AudioManager.h>
#include <SpriteManager.h>

#include <vector>

#include <Text.h>

class GameContext {
    public:

        GameContext();
        ~GameContext(){};

        // Managers
        SpriteManager spriteManager;
        AudioManager audioManager;
        TextManager textManager;

        // Play Elements
        Paddle paddle;
        Level levelManager;
        Lightning lightning;

        // BackGrounds
        TiledBackground tiledBackground;
        ScrollingBackground scrollingBackground;

        // Borders
        BorderVertical borderL;
        BorderVertical borderR;
        BorderHorizontal borderT;
        BorderCorner borderTR;
        BorderCorner borderTL;

        //UI Elements
        LifeCounter lifeCounter;

        // Logos
        Logo logoSprite;

        //Fonts
        TTF_Font* publicPixel12;
        TTF_Font* publicPixel24;

        //Lists
        Ball* ballList[3] = {};
        Powerup* powerupList[5] = {};

        //Game Concepts
        const static int startingLives = 3;
        const static int maxLives = 5;
        int lives = startingLives;


        void AddBall();
        void AddBallAtLocation(float x, float y);        
        void ClearBalls();

        void AddPowerUp(float xPos, float yPos, int parentWidth);
        void ClearPowerups();

    private:
        constexpr static float borderWidthV = 32.f;
        constexpr static float borderWidthC = 32.f;
};