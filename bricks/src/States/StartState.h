#pragma once
#include <GameState.h>
#include <PlayState.h>
#include <ExitState.h>


#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <statemanagers.h>

#include <ScrollingBackground.h>
#include <BorderVertical.h>
#include <TextManager.h>

#include <SDL2/SDL.h>

class StartState : public GameState
{
public:
    //Private constructor
    StartState(PlayState* playState, SpriteManager* spriteManager, TextManager* textManager);
    ~StartState(){};

    //Transitions
    bool enter();
    bool exit();

    //Game loop functions
    void handleEvent( SDL_Event& e );
    void update(double dt);
    void render();

private:

    float borderWidthV = 32.f;

    SDL_Rect logoRect;

    GameState* playState;
    SpriteManager* spriteManager;
    TextManager* textManager;

    BorderVertical borderL;
    BorderVertical borderR;

    SDL_Texture* logoSprite = NULL;
    ScrollingBackground background;

    TTF_Font* font;
    Text spaceToStart;
    Text qToQuit;
    Text clickToLaunch;
    Text instructions;
};