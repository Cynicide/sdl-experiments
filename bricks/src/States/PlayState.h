#pragma once

#include <SDL2/SDL.h>

#include <GameState.h>

#include <GameContext.h>

#include <SubState.h>
#include <ServingSubState.h>
#include <LoadLevelSubState.h>
#include <PlayingSubState.h>
#include <DyingSubState.h>
#include <LevelWinSubState.h>
#include <PreServeSubState.h>

#include <Definitions.h>

class PlayState : public GameState
{
public:
    //Private constructor
    PlayState(GameContext* gameContext);
    ~PlayState(){};

    //Transitions
    bool enter();
    bool exit();

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update(double dt);
    void render();
    void setGameOverState(GameState* gameOverState);

private:

    GameContext* gameContext;

    TTF_Font * font;

    // State Pointers
    GameState* gameOverState;

    // SubState Pointers
    SubState* sCurrentState = NULL;
    SubState* sNextState = NULL;

    ServingSubState servingSubState;
    LoadLevelSubState loadLevelSubState;
    DyingSubState dyingSubState;
    PlayingSubState playingSubState;
    LevelWinSubState levelWinSubState;
    PreServeSubState preServeSubState;
};