#include <LoadLevelSubState.h>
//#include <Definitions.h>

LoadLevelSubState::LoadLevelSubState(GameContext* gameContext, SubState*& sNextState) : 
    gameContext(gameContext),
    sNextState(sNextState) {
}

void LoadLevelSubState::setServingSubState( SubState* servingSubState) {
    this->servingSubState = servingSubState;
}

bool LoadLevelSubState::enter() {
    gameContext->brickManager.LoadLevel();
    gameContext->brickManager.CreateLevel();
    sNextState = servingSubState;
    return true;
}
bool LoadLevelSubState::exit() {
    return true;
}

//Main loop functions
void LoadLevelSubState::handleEvent( SDL_Event& e ) {

}
void LoadLevelSubState::update(double dt) {

}
void LoadLevelSubState::render() {
        gameContext->tiledBackground.render();
        gameContext->lightning.render();

        gameContext->borderL.render();
        gameContext->borderR.render();
        gameContext->borderT.render();
        gameContext->borderTL.render();
        gameContext->borderTR.render();
}