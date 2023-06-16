#include <LoadLevelSubState.h>
//#include <Definitions.h>

LoadLevelSubState::LoadLevelSubState(GameContext* gameContext, SubState*& sNextState) : 
    gameContext(gameContext),
    sNextState(sNextState) {
}

void LoadLevelSubState::setPreServeSubState(SubState* letsGoSubState) {
    this->letsGoSubState = letsGoSubState;
}
bool LoadLevelSubState::enter() {
    gameContext->clearBalls();
    gameContext->bulletList.clear();
    gameContext->powerupList.clear();
    gameContext->levelManager.LoadLevel();
    gameContext->levelManager.CreateLevel();
    gameContext->addBall();
    
    sNextState = letsGoSubState;
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