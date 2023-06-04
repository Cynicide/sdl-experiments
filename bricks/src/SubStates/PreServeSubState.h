#pragma once

#include <SubState.h>
#include <GameContext.h>
#include <ServingSubState.h>
#include <Paddle.h>

#include <LetsGoUIElement.h>

class PreServeSubState : public SubState
{
public:

    PreServeSubState(GameContext* gameContext, SubState*& sNextState);
    ~PreServeSubState(){};

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

    LetsGoUIElement letsGoElement;
};