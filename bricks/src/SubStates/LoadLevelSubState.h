#pragma once

#include <SubState.h>
#include <GameContext.h>
#include <ServingSubState.h>
#include <Paddle.h>

class LoadLevelSubState : public SubState
{
public:

    LoadLevelSubState(GameContext* gameContext, SubState*& sNextState);
    ~LoadLevelSubState(){};

    void setPreServeSubState(SubState* letsGoSubState);

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
    SubState* letsGoSubState;
};