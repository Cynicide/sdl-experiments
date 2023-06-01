#pragma once

#include <TiledBackground.h>
#include <Paddle.h>
#include <Ball.h>
#include <Bullet.h>
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
#include <Definitions.h>

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
        Bullet* bulletList[2] = {};

        //Game Concepts
        const static int startingLives = 3;
        const static int maxLives = 5;
        int lives = startingLives;


        void AddBall();
        void AddBallsAtLocation(float x, float y, float currentVal);        
        void ClearBalls();

        void AddLife();

        void AddPowerUp(float xPos, float yPos, int parentWidth);
        Definitions::PowerUpType randomizePowerUp();
        void ClearPowerups();

        void AddBullets(SDL_FRect paddleRect);
        void ClearBullets();

    private:
        constexpr static float borderWidthV = 32.f;
        constexpr static float borderWidthC = 32.f;

        /*
        
        Extra Life  0 - 5    5%
        Slow        6 - 28   22%
        Wide        29 - 52  23%
        Triple      53 - 69  16%
        Laser       70 - 79  10% 
        LevelSkip:  80 - 85  5%    
        Magnetic:   86 - 100 15%


        */

        int extraLifeChance = 5;
        int slowBallChance = 28;
        int wideChance = 52;
        int tripleBallChance = 69;
        int laserChance = 79;
        int levelSkipChance = 85;
        int magneticChance = 100;
};