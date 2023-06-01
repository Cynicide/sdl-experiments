#include <MagneticMode.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

MagneticMode::MagneticMode(GameContext *gameContext, GameMode*& sNextMode) : 
    gameContext(gameContext),
    sNextMode(sNextMode)
    {

    }

bool MagneticMode::enter() {
    currentDuration = 0;
    return true;
}

bool MagneticMode::exit() {
    return true;
}

void MagneticMode::setNormalMode(GameMode* normalGameMode) {
    this->normalGameMode = normalGameMode;
}

void MagneticMode::handleEvent( SDL_Event& e ) {

}

void MagneticMode::update(double dt) {
    currentDuration = currentDuration + (60 * dt);
    spdlog::debug("MagneticTime: " + std::to_string(currentDuration));
    if (currentDuration >= (double)powerupDuration) {
        sNextMode = normalGameMode;
        currentDuration = 0;
    } 

}

void MagneticMode::render() {

}