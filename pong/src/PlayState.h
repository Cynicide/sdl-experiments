#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include <GameState.h>
#include <ExitState.h>
#include <GameOverState.h>

#include <Vector2d.h>
#include <Physics.h>

#include <Ball.h>
#include <Paddle.h>

#include <Text.h>
#include <globals.h>
#include <templates.h>
#include <statemanagers.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> 

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
    void update();
    void render();

private:
    //Static instance
    static PlayState sPlayState;

    Ball ball;
    Ball bpb;
    Paddle paddle_p1;
    Paddle paddle_p2;

    Mix_Chunk *gPing;
    Mix_Chunk *gPong;

    Physics physics;

    enum SubState {
    PLAYING,
    SERVE
    };

    SubState substate = SERVE;

    const float starting_vel = 3.f;
    const float speedup_val = 1.07f;

    //Private constructor
    PlayState();

};
#endif
