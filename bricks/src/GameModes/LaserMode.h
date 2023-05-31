#pragma once
#include <GameMode.h>
#include <GameContext.h>

//Game Mode base class
class LaserMode: public GameMode
{
public:
    LaserMode(GameContext *gameContext, GameMode*& sNextMode);
    ~LaserMode(){};

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

    const int maxCooldown = 3;
    const int powerupDuration = 400;
    double currentDuration = 0;
    float currentCooldown = 0;
};