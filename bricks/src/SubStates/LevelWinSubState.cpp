#include <LevelWinSubState.h>
//#include <Definitions.h>

LevelWinSubState::LevelWinSubState(GameContext* gameContext, SubState*& sNextState) : 
    gameContext(gameContext),
    sNextState(sNextState) {
}

void LevelWinSubState::setLoadLevelSubState(SubState* loadLevelSubState) {
    this->loadLevelSubState = loadLevelSubState;
}

bool LevelWinSubState::enter() {

    return true;
}
bool LevelWinSubState::exit() {
    return true;
}

//Main loop functions
void LevelWinSubState::handleEvent( SDL_Event& e ) {

}
void LevelWinSubState::update(double dt) {

    if ( gameContext->brickManager.lastLevelCheck()) {
        // We need to handle ending the game
    } else {
        gameContext->brickManager.nextLevel();
        sNextState = loadLevelSubState;
    }

}
void LevelWinSubState::render() {
        gameContext->tiledBackground.render();
        gameContext->lightning.render();

        gameContext->borderL.render();
        gameContext->borderR.render();
        gameContext->borderT.render();
        gameContext->borderTL.render();
        gameContext->borderTR.render();
}