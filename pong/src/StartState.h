#ifndef STARTSTATE_H
#define STARTSTATE_H
#include <GameState.h>
#include <PlayState.h>
#include <ExitState.h>
#include <Text.h>
#include <globals.h>
#include <statemanagers.h>
#include <Vector2d.h>

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
    void update(float dt);
    void render();

private:
    //Static instance
    static StartState sStartState;

    Text titleText;
    Text attractText;
    Text playeroneControls;
    Text playertwoControls;

    //Private constructor
    StartState();

};
#endif