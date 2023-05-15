#pragma once

#include <SubState.h>
#include <DyingSubState.h>
#include <LevelWinSubState.h>

#include <GameContext.h>


#include <Text.h>
#include <Physics.h>
#include <SDL2/SDL.h>

class PlayingSubState : public SubState
{
public:

    PlayingSubState(GameContext* gameContext, SubState*& sNextState);
    ~PlayingSubState(){};

    //State transitions
    bool enter();
    bool exit();

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update(double dt);
    void render();
    void setDyingSubState(SubState* dyingSubState);
    void setLevelWinSubState(SubState* levelWinSubState);

private:
    GameContext* gameContext;

    SDL_FRect bpb;
    Physics physics;

    SubState*& sNextState;
    SubState* dyingSubState;
    SubState* levelWinSubState;

};