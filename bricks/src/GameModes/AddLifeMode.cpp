#include <AddLifeMode.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

AddLifeMode::AddLifeMode(GameContext *gameContext, GameMode*& sNextMode) : 
    gameContext(gameContext),
    sNextMode(sNextMode)
    {

    }

bool AddLifeMode::enter() {

    return true;
}

bool AddLifeMode::exit() {
    return true;
}

void AddLifeMode::setNormalMode(GameMode* normalGameMode) {
    this->normalGameMode = normalGameMode;
}

void AddLifeMode::handleEvent( SDL_Event& e ) {

}

void AddLifeMode::update(double dt) {
    gameContext->AddLife();
    sNextMode = normalGameMode;
}

void AddLifeMode::render() {

}