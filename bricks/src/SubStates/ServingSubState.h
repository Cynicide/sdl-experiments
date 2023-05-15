#pragma once

#include <SubState.h>

#include <GameContext.h>

#include <PlayingSubState.h>

class ServingSubState : public SubState
{
public:

    ServingSubState(GameContext* gameContext, SubState*& sNextState);
    ~ServingSubState(){};

    void setPlayingSubState(SubState* playingSubState);
    void setNextStatePointer(SubState* sNextState);

    //State transitions
    bool enter();
    bool exit();

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update(double dt);
    void render();

private:
    GameContext* gameContext;
    SubState*& sNextState;
    SubState* playingSubState;
};