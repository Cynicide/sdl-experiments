#pragma once

#include <SubState.h>
#include <GameContext.h>
#include <ServingSubState.h>
#include <Paddle.h>

class DyingSubState : public SubState
{
public:

    DyingSubState(GameContext* gameContext, SubState*& sNextState);
    ~DyingSubState(){};

    void setServingSubState(SubState* servingSubState);

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
    SubState* servingSubState;
};