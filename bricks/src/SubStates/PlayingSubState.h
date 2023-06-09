#pragma once

#include <SubState.h>
#include <DyingSubState.h>
#include <LevelWinSubState.h>

#include <GameContext.h>

#include <GameMode.h>
#include <NormalMode.h>
#include <LongMode.h>
#include <SlowMode.h>
#include <LaserMode.h>
#include <LevelWarp.h>
#include <MagneticMode.h>

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

    // ToDo: Is there a better way to do this sNextState?
    SubState*& sNextState;
    SubState* dyingSubState;
    SubState* levelWinSubState;

    GameMode* sCurrentMode = NULL;
    GameMode* sNextMode = NULL;

    NormalMode normalGameMode;
    LongMode longGameMode;
    SlowMode slowGameMode;
    LaserMode laserMode;
    MagneticMode magneticMode;
};