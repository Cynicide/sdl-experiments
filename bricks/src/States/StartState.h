#ifndef STARTSTATE_H
#define STARTSTATE_H
#include <GameState.h>
#include <PlayState.h>
#include <ExitState.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <statemanagers.h>

#include <Background.h> 

#include <SDL2/SDL.h>

class StartState : public GameState
{
public:
    //Static accessor
    static StartState* get();
    //Transitions
    bool enter();
    bool exit();

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update(double dt);
    void render();

private:
    //Static instance
    static StartState sStartState;

    Background background;

    //Private constructor
    StartState();

};
#endif