#pragma once
#include <GameMode.h>
#include <GameContext.h>

//Game Mode base class
class AddLifeMode: public GameMode
{
public:
    AddLifeMode(GameContext *gameContext, GameMode*& sNextMode);
    ~AddLifeMode(){};

    //Game Mode transitions
    bool enter();
    bool exit();

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update(double dt);
    void render();
    void setNormalMode(GameMode* normalGameMode);

private:
    GameContext *gameContext;
    GameMode*& sNextMode;
    GameMode* normalGameMode;
};