#include <GameOverState.h>

    GameOverState::GameOverState(GameContext* gameContext, GameState* startState) :
    gameOverElement(&gameContext->spriteManager, gameContext->spriteManager.gameOverTop, gameContext->spriteManager.gameOverBottom, gameContext->audioManager.gameOver)
    {
        this->gameContext = gameContext;
        this->startState = startState;
    }
    
    //Transitions
    bool GameOverState::enter() {
        gameContext->resetGame();
        return true;
    }
    bool GameOverState::exit() {
        gameOverElement.reset();
        return true;
    }

    //Game loop functions
    void GameOverState::handleEvent( SDL_Event& e ) {
    //If the user pressed space move onto start state
        if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_SPACE ) ) {
            setNextState(startState);
        }
    }
    void GameOverState::update(double dt) {

        gameOverElement.update(dt);

    }

    void GameOverState::render() {
        gameContext->tiledBackground.render();
        gameContext->lightning.render();

        gameContext->borderL.render();
        gameContext->borderR.render();
        gameContext->borderT.render();
        gameContext->borderTL.render();
        gameContext->borderTR.render();
        gameContext->lifeCounter.render(gameContext->lives);
        gameContext->levelManager.render();
        gameOverElement.render();
    }