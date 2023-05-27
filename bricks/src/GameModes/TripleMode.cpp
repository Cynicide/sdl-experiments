#include <TripleMode.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

TripleMode::TripleMode(GameContext *gameContext, GameMode*& sNextMode) : 
    gameContext(gameContext),
    sNextMode(sNextMode)
    {

    }

bool TripleMode::enter() {

    return true;
}

bool TripleMode::exit() {
    return true;
}

void TripleMode::setNormalMode(GameMode* normalGameMode) {
    this->normalGameMode = normalGameMode;
}

void TripleMode::handleEvent( SDL_Event& e ) {

}

void TripleMode::update(double dt) {
        // Spawn 3 balls
        for (int b = 0; b < 3; ++b) {
            if (gameContext->ballList[b] != nullptr) {
                gameContext->AddBallsAtLocation(gameContext->ballList[b]->ballRect.x, gameContext->ballList[b]->ballRect.y);
                break;
            }
        }
        sNextMode = normalGameMode;
}

void TripleMode::render() {

}