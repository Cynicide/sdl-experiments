#pragma once
#include <GameMode.h>
#include <GameContext.h>

//Game Mode base class
class SlowMode: public GameMode
{
public:
    SlowMode(GameContext *gameContext, GameMode*& sNextMode);
    ~SlowMode(){};

    //Game Mode transitions
    bool enter();
    bool exit();

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update(double dt);
    void render();
    void setNormalMode(GameMode* normalGameMode);

    int ballSpeed = 200;

private:
    GameContext *gameContext;
    GameMode*& sNextMode;
    GameMode* normalGameMode;
};