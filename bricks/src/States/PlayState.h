#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <SDL2/SDL.h>
#include <GameState.h>

#include <Background.h>
#include <Paddle.h>
#include <Ball.h>
#include <Border.h>
#include <Brick.h>
#include <Lightning.h>
#include <BrickManager.h>
#include <Sign.h>
#include <Text.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <Physics.h>

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
    void update(double dt);
    void render();

private:
    //Static instance
    static PlayState sPlayState;

    Background background;
    Paddle paddle;
    Ball ball;
    Border border;
    Lightning lightning;
    BrickManager brickManager;

    SDL_FRect bpb;
    Physics physics;

    Text ballCoord;
    Text bpbCoord;
    Text ballVel;

    bool gPause = false;
    int UpdateLoop = 0;
    int RenderLoop = 0;

    enum SubState {
        SERVING,
        PLAYING,
        DYING,
        GAMEOVER
    };

    SubState subState = SERVING;

    //Private constructor
    PlayState();

};
#endif
