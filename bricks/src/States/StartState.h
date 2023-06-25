#pragma once
#include <GameState.h>
#include <PlayState.h>
#include <ExitState.h>

#include <statemanagers.h>
#include <GameContext.h>
#include <Logo.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> 

class StartState : public GameState
{
public:
    //Private constructor
    StartState(GameContext* gameContext, PlayState* playState);
    ~StartState(){};

    //Transitions
    bool enter();
    bool exit();

    //Game loop functions
    void handleEvent( SDL_Event& e );
    void update(double dt);
    void render();

private:
    GameContext* gameContext;
    GameState* playState;

    TTF_Font* font;
    Text spaceToStart;
    Text qToQuit;
    Text clickToLaunch;
    Text instructions;

    Mix_Music* titleTrack;
};