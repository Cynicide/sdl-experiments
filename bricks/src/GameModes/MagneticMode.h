#pragma once
#include <GameMode.h>
#include <GameContext.h>

//Game Mode base class
class MagneticMode: public GameMode
{
public:
    MagneticMode(GameContext *gameContext, GameMode*& sNextMode);
    ~MagneticMode(){};

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

    const int powerupDuration = 600;
    double currentDuration = 0;
};