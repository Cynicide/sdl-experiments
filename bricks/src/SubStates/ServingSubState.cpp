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
    gameContext->cleanup();
    gameContext->ballList.add();
    for (int b = 0; b < 3; ++b) {
        if (gameContext->ballList.get(b) != nullptr) {
            gameContext->ballList.get(b)->reset();
        }
    }
    return true;
}
bool ServingSubState::exit() {
    return true;
}

//Main loop functions
void ServingSubState::handleEvent( SDL_Event& e ) {

}
void ServingSubState::update(double dt) {
    gameContext->paddle.updateServing(dt);
    gameContext->levelManager.updateServe(dt, gameContext->paddle.paddleRect);
    gameContext->ballList.updateServing(dt, gameContext->paddle.paddleRect);

    int mx, my;
    Uint32 mouseState = SDL_GetMouseState(&mx, &my);
    if (mouseState == SDL_BUTTON(1)) 
    {
        sNextState = playingSubState;
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
    gameContext->lifeCounter.render(gameContext->lives);
    gameContext->paddle.renderServing();
    gameContext->levelManager.render();
    gameContext->ballList.render();
}