#pragma once
#include <GameState.h>
#include <PlayState.h>
#include <ExitState.h>


#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <statemanagers.h>

#include <ScrollingBackground.h>
#include <BorderVertical.h>

#include <SDL2/SDL.h>

class StartState : public GameState
{
public:
    //Static accessor
    static StartState* get();

    //Transitions
    bool enter();
    bool exit();

    //Game loop functions
    void handleEvent( SDL_Event& e );
    void update(double dt);
    void render();

private:
    //Static instance
    static StartState sStartState;

    BorderVertical borderL;
    BorderVertical borderR;
    float borderWidthV = 32.f;
    float borderHeightV = 128.f;
    
    // Resources
    SDL_Texture* logoSprite = NULL;
    int logoX = 1024;
    int logoY = 1024;
    ScrollingBackground background;

    TTF_Font* font;
    Text spaceToStart;
    Text qToQuit;
    Text clickToLaunch;
    Text instructions;

    //Private constructor
    StartState();
};