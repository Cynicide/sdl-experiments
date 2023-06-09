#include <DyingSubState.h>
#include <Definitions.h>

DyingSubState::DyingSubState(GameContext* gameContext, SubState*& sNextState) : 
    gameContext(gameContext),
    sNextState(sNextState) {

}

void DyingSubState::setServingSubState( SubState* servingSubState) {
    this->servingSubState = servingSubState;
}

bool DyingSubState::enter() {
    if (gameContext->lives != 0) {
        gameContext->lives = gameContext->lives - 1;
    }

    gameContext->cleanup();

    return true;
}
bool DyingSubState::exit() {
    return true;
}

//Main loop functions
void DyingSubState::handleEvent( SDL_Event& e ) {
            if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_SPACE ) )
            {
                sNextState = servingSubState;
            }
}
void DyingSubState::update(double dt) {
    gameContext->paddle.updateDying(dt);
    gameContext->levelManager.update(dt, gameContext->paddle.paddleRect);

}
void DyingSubState::render() {
        gameContext->tiledBackground.render();
        gameContext->lightning.render();
        gameContext->borderL.render();
        gameContext->borderR.render();
        gameContext->borderT.render();
        gameContext->borderTL.render();
        gameContext->borderTR.render();
        gameContext->lifeCounter.render(gameContext->lives);
        gameContext->paddle.renderDying();
        gameContext->levelManager.render();
        gameContext->ballList.render();
}