#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <SDL2/SDL.h>
#include <GameState.h>

#include <TiledBackground.h>
#include <Paddle.h>
#include <Ball.h>
#include <Border.h>
#include <Brick.h>
#include <Lightning.h>
#include <BrickManager.h>
#include <Sign.h>
#include <Text.h>

#include <Definitions.h>

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

    TiledBackground background;
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

    TTF_Font * font;

    Definitions::SubState subState = Definitions::SubState::SERVING;

    //Private constructor
    PlayState();

};
#endif
