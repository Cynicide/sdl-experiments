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
    return true;
}
bool DyingSubState::exit() {
    return true;
}

//Main loop functions
void DyingSubState::handleEvent( SDL_Event& e ) {
            if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_SPACE ) )
            {
                //gameContext->paddle.reset();
                sNextState = servingSubState;
            }
}
void DyingSubState::update(double dt) {
    gameContext->paddle.updateDying(dt);

}
void DyingSubState::render() {
        gameContext->tiledBackground.render();
        gameContext->lightning.render();

        gameContext->borderL.render();
        gameContext->borderR.render();
        gameContext->borderT.render();
        gameContext->borderTL.render();
        gameContext->borderTR.render();
        gameContext->paddle.renderDying();
        gameContext->brickManager.render();
        gameContext->ball.render();
}