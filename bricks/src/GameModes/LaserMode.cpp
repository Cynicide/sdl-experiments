#include <LaserMode.h>

LaserMode::LaserMode(GameContext *gameContext, GameMode*& sNextMode) : 
    gameContext(gameContext),
    sNextMode(sNextMode)
    {

    }

bool LaserMode::enter() {
    gameContext->paddle.setLaserPaddle();
    currentDuration = 0;
    return true;
}

bool LaserMode::exit() {
    return true;
}

void LaserMode::setNormalMode(GameMode* normalGameMode) {
    this->normalGameMode = normalGameMode;
}

void LaserMode::handleEvent( SDL_Event& e ) {

}

void LaserMode::update(double dt) {
    //These are not if/else as I want to handle decrementing and firing on the same update.
    //Decrement the cooldown if it's running
    if (currentCooldown > 0) {
        currentCooldown = currentCooldown - (60 * dt);
    }

    // If the cooldown has gone below 0 reset it
    if (currentCooldown < 0) {
        currentCooldown = 0;
    }
    
    // Fire the laser if the cooldown has ended
    if (currentCooldown == 0) {
        int mx, my;
        Uint32 mouseState = SDL_GetMouseState(&mx, &my);
        if (mouseState == SDL_BUTTON(1)) 
        {
            gameContext->AddBullets(gameContext->paddle.paddleRect);
            currentCooldown = maxCooldown;
        }
    }

    currentDuration = currentDuration + (60 * dt);
    spdlog::debug("LaserMode: " + std::to_string(currentDuration));
    if (currentDuration >= (double)powerupDuration) {
        sNextMode = normalGameMode;
        currentDuration = 0;
    } 

}

void LaserMode::render() {

}