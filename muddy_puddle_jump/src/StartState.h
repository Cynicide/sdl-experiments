#ifndef STARTSTATE_H
#define STARTSTATE_H
#include <GameState.h>
#include <PlayState.h>
#include <ExitState.h>
#include <ImageLib.h>
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

    SDL_Surface* background;
    SDL_Texture* backgroundTexture;

    Text title;
    Text pressSpace;

    //Private constructor
    StartState();

};
#endif