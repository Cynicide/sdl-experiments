#pragma once

#include <SDL2/SDL.h>
#include <GameState.h>

#include <TiledBackground.h>
#include <Paddle.h>
#include <Ball.h>
#include <BorderHorizontal.h>
#include <BorderVertical.h>
#include <BorderCorner.h>
#include <Brick.h>
#include <Lightning.h>
#include <BrickManager.h>
#include <TextManager.h>
#include <Sign.h>
#include <Text.h>

#include <Definitions.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <Physics.h>

class PlayState : public GameState
{
public:
    //Private constructor
    PlayState(SpriteManager* spriteManager, AudioManager* audioManager, TextManager* textManager);
    ~PlayState(){};

    //Transitions
    bool enter();
    bool exit();

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update(double dt);
    void render();

private:

    float borderWidthV = 32.f;
    float borderWidthC = 32.f;


    SpriteManager* spriteManager;
    AudioManager* audioManager;
    TextManager* textManager;

    TiledBackground background;
    Paddle paddle;
    Ball ball;

    BorderVertical borderL;
    BorderVertical borderR;
    BorderHorizontal borderT;
    BorderCorner borderTR;
    BorderCorner borderTL;
    
    Lightning lightning;
    BrickManager brickManager;

    SDL_FRect bpb;
    Physics physics;

    Text ballCoord;
    Text bpbCoord;
    Text ballVel;

    TTF_Font * font;

    Definitions::SubState subState = Definitions::SubState::SERVING;
};