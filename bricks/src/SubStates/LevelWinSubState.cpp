#include <LevelWinSubState.h>
//#include <Definitions.h>

LevelWinSubState::LevelWinSubState(GameContext* gameContext, SubState*& sNextState) : 
    gameContext(gameContext),
    sNextState(sNextState),
    levelEndElement(&gameContext->spriteManager, gameContext->spriteManager.levelCompleteTop, gameContext->spriteManager.levelCompleteBottom,  gameContext->audioManager.levelEnd) {
}

void LevelWinSubState::setLoadLevelSubState(SubState* loadLevelSubState) {
    this->loadLevelSubState = loadLevelSubState;
}

bool LevelWinSubState::enter() {
    gameContext->paddle.reset();
    gameContext->powerupList.clear();
    return true;
}
bool LevelWinSubState::exit() {
    levelEndElement.reset();
    return true;
}

//Main loop functions
void LevelWinSubState::handleEvent( SDL_Event& e ) {

}
void LevelWinSubState::update(double dt) {

    levelEndElement.update(dt);
    if (levelEndElement.done() == true) {
        if ( gameContext->levelManager.lastLevelCheck()) {
            // ToDo: We need to handle ending the game
            gameContext->cleanup();
        } else {
            gameContext->levelManager.nextLevel();
            gameContext->cleanup();
            sNextState = loadLevelSubState;
        }
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
        
        gameContext->levelManager.render();
        gameContext->paddle.renderServing();
        
        levelEndElement.render();
}