#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <SDL2/SDL.h>
#include <GameState.h>



class PlayState : public GameState
{
public:
    //Static accessor
    static PlayState* get();

    //Transitions
    bool enter();
    bool exit();

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update(float dt);
    void render();

private:
    //Static instance
    static PlayState sPlayState;

    //Private constructor
    PlayState();

};
#endif
