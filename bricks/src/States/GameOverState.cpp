#include <GameOverState.h>

    GameOverState::GameOverState(GameContext* gameContext) {
        this->gameContext = gameContext;
    }
    
    //Transitions
    bool GameOverState::enter() {
        
        return true;
    }
    bool GameOverState::exit() {

        return true;
    }

    //Game loop functions
    void GameOverState::handleEvent( SDL_Event& e ) {

    }
    void GameOverState::update(double dt) {

    }
    void GameOverState::render() {
        gameContext->tiledBackground.render();
        gameContext->lightning.render();

        gameContext->borderL.render();
        gameContext->borderR.render();
        gameContext->borderT.render();
        gameContext->borderTL.render();
        gameContext->borderTR.render();
    }