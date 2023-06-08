#include <PreServeSubState.h>

PreServeSubState::PreServeSubState(GameContext* gameContext, SubState*& sNextState) : 
    gameContext(gameContext),
    sNextState(sNextState),
    letsGoElement(&gameContext->spriteManager, &gameContext->audioManager) 
    {
}

void PreServeSubState::setServingSubState( SubState* servingSubState) {
    this->servingSubState = servingSubState;
}

bool PreServeSubState::enter() {
    gameContext->paddle.reset();
    gameContext->ClearPowerups();
    return true;
}
bool PreServeSubState::exit() {
    letsGoElement.reset();
    return true;
}

//Main loop functions
void PreServeSubState::handleEvent( SDL_Event& e ) {

}
void PreServeSubState::update(double dt) {
    letsGoElement.update(dt);
    if (letsGoElement.done() == true) {
        sNextState = servingSubState;
    }
    gameContext->levelManager.updatePreServe(dt);
    gameContext->paddle.updateServing(dt);
}

void PreServeSubState::render() {
        gameContext->tiledBackground.render();
        gameContext->lightning.render();

        gameContext->borderL.render();
        gameContext->borderR.render();
        gameContext->borderT.render();
        gameContext->borderTL.render();
        gameContext->borderTR.render();
        gameContext->levelManager.renderPreServe();
        gameContext->paddle.renderServing();
        letsGoElement.render();
}