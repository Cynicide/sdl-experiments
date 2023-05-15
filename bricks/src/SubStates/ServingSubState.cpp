#include <ServingSubState.h>

ServingSubState::ServingSubState(GameContext* gameContext, SubState*& sNextState) : 
    gameContext(gameContext),
    sNextState(sNextState)
    {

    }

void ServingSubState::setPlayingSubState(SubState* playingSubState) {
    this->playingSubState = playingSubState;
}

bool ServingSubState::enter() {
    gameContext->paddle.reset();
    return true;
}
bool ServingSubState::exit() {
    return true;
}

//Main loop functions
void ServingSubState::handleEvent( SDL_Event& e ) {

}
void ServingSubState::update(double dt) {


    gameContext->ball.reset();
    gameContext->paddle.updateServing(dt);
    gameContext->ball.update(dt, gameContext->paddle.paddleRect);
    int mx, my;
    Uint32 mouseState = SDL_GetMouseState(&mx, &my);
    if (mouseState == SDL_BUTTON(1)) 
    {
        gameContext->ball.randomizeXDirection();
        sNextState = playingSubState;
        //subState = Definitions::SubState::PLAYING;
    }

}
void ServingSubState::render() {
    gameContext->tiledBackground.render();
    gameContext->lightning.render();

    gameContext->borderL.render();
    gameContext->borderR.render();
    gameContext->borderT.render();
    gameContext->borderTL.render();
    gameContext->borderTR.render();
    gameContext->paddle.renderServing();
    gameContext->brickManager.render();
    gameContext->ball.render();
}