#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SDL2/SDL.h>

//Game state base class
class GameState
{
public:
    //State transitions
    virtual bool enter() = 0;
    virtual bool exit() = 0;

    //Main loop functions
    virtual void handleEvent( SDL_Event& e ) = 0;
    virtual void update(double dt) = 0;
    virtual void render() = 0;

    //Make sure to call child destructors
    virtual ~GameState(){};

};

#endif