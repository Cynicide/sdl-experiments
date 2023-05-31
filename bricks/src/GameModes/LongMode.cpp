#include <LongMode.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

LongMode::LongMode(GameContext *gameContext, GameMode*& sNextMode) : 
    gameContext(gameContext),
    sNextMode(sNextMode)
    {

    }

bool LongMode::enter() {
    gameContext->paddle.setLongPaddle();
    currentDuration = 0;
    return true;
}

bool LongMode::exit() {
    return true;
}

void LongMode::setNormalMode(GameMode* normalGameMode) {
    this->normalGameMode = normalGameMode;
}

void LongMode::handleEvent( SDL_Event& e ) {

}

void LongMode::update(double dt) {
    currentDuration = currentDuration + (60 * dt);
    spdlog::debug("LongTime: " + std::to_string(currentDuration));
    if (currentDuration >= (double)powerupDuration) {
        sNextMode = normalGameMode;
        currentDuration = 0;
    } 

}

void LongMode::render() {

}