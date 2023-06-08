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
    for (int b = 0; b < 3; ++b) {
        if (gameContext->ballList[b] != nullptr) {
                gameContext->ballList[b]->releaseFromPaddle();
                gameContext->ballList[b]->resetStuckOffset();
        }
    }
    return true;
}

void MagneticMode::setNormalMode(GameMode* normalGameMode) {
    this->normalGameMode = normalGameMode;
}

void MagneticMode::handleEvent( SDL_Event& e ) {

}

void MagneticMode::update(double dt) {

    int mx, my;
    Uint32 mouseState = SDL_GetMouseState(&mx, &my);
    if (mouseState == SDL_BUTTON(1)) 
    {
        for (int b = 0; b < 3; ++b) {
            if (gameContext->ballList[b] != nullptr) {
                gameContext->ballList[b]->releaseFromPaddle();
                gameContext->ballList[b]->resetStuckOffset();
            }
        }
    }

    currentDuration = currentDuration + (60 * dt);
    spdlog::debug("MagneticTime: " + std::to_string(currentDuration));
    if (currentDuration >= (double)powerupDuration) {
        sNextMode = normalGameMode;
        currentDuration = 0;
    } 

}

void MagneticMode::render() {

}