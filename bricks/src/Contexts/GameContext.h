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
        Ball ball;
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

        // Logos
        SDL_Texture* logoSprite;

        //Fonts
        TTF_Font* publicPixel12;
        TTF_Font* publicPixel24;

    private:
        constexpr static float borderWidthV = 32.f;
        constexpr static float borderWidthC = 32.f;
};