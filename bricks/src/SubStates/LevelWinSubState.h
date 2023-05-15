#pragma once

#include <SubState.h>
#include <GameContext.h>
#include <LoadLevelSubState.h>

class LevelWinSubState : public SubState
{
public:

    LevelWinSubState(GameContext* gameContext, SubState*& sNextState);
    ~LevelWinSubState(){};

    void setLoadLevelSubState(SubState* loadLevelSubState);

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
    SubState* loadLevelSubState;
};