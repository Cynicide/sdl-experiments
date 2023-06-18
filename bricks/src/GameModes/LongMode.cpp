#include <LongMode.h>

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
    gameContext->paddle.setNormalPaddle();
    currentDuration = 0;
    return true;
}

void LongMode::setNormalMode(GameMode* normalGameMode) {
    this->normalGameMode = normalGameMode;
}

void LongMode::handleEvent( SDL_Event& e ) {

}

void LongMode::update(double dt) {
    currentDuration = currentDuration + (60 * dt);
    if (currentDuration >= (double)powerupDuration) {
        sNextMode = normalGameMode;
        currentDuration = 0;
    } 

}

void LongMode::render() {

}