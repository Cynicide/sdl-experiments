#include <SlowMode.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

SlowMode::SlowMode(GameContext *gameContext, GameMode*& sNextMode) : 
    gameContext(gameContext),
    sNextMode(sNextMode)
    {

    }

bool SlowMode::enter() {

    return true;
}

bool SlowMode::exit() {
    return true;
}

void SlowMode::setNormalMode(GameMode* normalGameMode) {
    this->normalGameMode = normalGameMode;
}

void SlowMode::handleEvent( SDL_Event& e ) {

}

void SlowMode::update(double dt) {
    for (int b = 0; b < 3; ++b) {
        if (gameContext->ballList[b] != nullptr) {
            gameContext->ballList[b]->setSpeed(ballSpeed);
        }
    }
    sNextMode = normalGameMode;
}

void SlowMode::render() {

}