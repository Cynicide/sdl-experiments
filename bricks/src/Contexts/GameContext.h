#pragma once

#include <BallList.h>
#include <PlayerBulletList.h>
#include <PowerupList.h>

#include <BorderHorizontal.h>
#include <BorderVertical.h>
#include <BorderCorner.h>

#include <Paddle.h>
#include <Lightning.h>
#include <Level.h>
#include <ScrollingBackground.h>
#include <TiledBackground.h>

#include <LifeCounter.h>
#include <Logo.h>
#include <Definitions.h>

#include <TextManager.h>
#include <AudioManager.h>
#include <SpriteManager.h>

class GameContext {
    public:

        GameContext();
        ~GameContext(){};

        //Lives
        const static int startingLives = 3;
        const static int maxLives = 5;
        int lives = startingLives;

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

        PowerupList powerupList;
        PlayerBulletList bulletList;
        BallList ballList;

        // Life Methods
        void addLife();
        void cleanup();
        void resetGame();

    private:
        //ToDo: Can we remove these?
        constexpr static float borderWidthV = 32.f;
        constexpr static float borderWidthC = 32.f;

};