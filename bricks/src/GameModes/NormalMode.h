#pragma once
#include <GameMode.h>
#include <GameContext.h>

//Game Mode base class
class NormalMode: public GameMode
{
public:
    NormalMode(GameContext *gameContext);
    ~NormalMode(){};

    //Game Mode transitions
    bool enter();
    bool exit();

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update(double dt);
    void render();

private:
    GameContext *gameContext;
};