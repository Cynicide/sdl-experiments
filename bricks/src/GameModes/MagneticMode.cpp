#include <MagneticMode.h>

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
    gameContext->ballList.unstickAll();
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
        gameContext->ballList.unstickAll();
    }

    currentDuration = currentDuration + (60 * dt);
    if (currentDuration >= (double)powerupDuration) {
        sNextMode = normalGameMode;
        currentDuration = 0;
    } 

}

void MagneticMode::render() {

}