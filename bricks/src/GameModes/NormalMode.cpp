#include <NormalMode.h>

NormalMode::NormalMode(GameContext *gameContext) : 
    gameContext(gameContext)
    {

    }

bool NormalMode::enter() {
    gameContext->paddle.setNormalPaddle();
    return true;
}

bool NormalMode::exit() {
    return true;
}

void NormalMode::handleEvent( SDL_Event& e ) {

}

void NormalMode::update(double dt) {

}

void NormalMode::render() {

}