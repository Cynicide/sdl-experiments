#include <SlowMode.h>

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
    gameContext->ballList.setSpeed(ballSpeed);
    sNextMode = normalGameMode;
}

void SlowMode::render() {

}