#include <PlayState.h>
#include <statemanagers.h>
#include "spdlog/spdlog.h"

PlayState::PlayState(GameContext* gameContext) :
    gameContext(gameContext),
    servingSubState(gameContext, sNextState),
    loadLevelSubState(gameContext, sNextState),
    dyingSubState(gameContext, sNextState),
    playingSubState(gameContext, sNextState),
    levelWinSubState(gameContext, sNextState),
    preServeSubState(gameContext, sNextState) {
    }

bool PlayState::enter()
{
    auto logger = spdlog::get("fileLogger");
    logger->info("Entered PlayState");
    //Loading success flag
    bool success = true;
 
    font = gameContext->publicPixel12;

    playingSubState.setDyingSubState(&dyingSubState);
    playingSubState.setLevelWinSubState(&levelWinSubState);
    dyingSubState.setServingSubState(&servingSubState);
    servingSubState.setPlayingSubState(&playingSubState);
    loadLevelSubState.setPreServeSubState(&preServeSubState);
    levelWinSubState.setLoadLevelSubState(&loadLevelSubState);
    preServeSubState.setServingSubState(&servingSubState);

    gameContext->lives = gameContext->startingLives;

    // This seems like a bit of a hack. You're not supposed to call these methods.
    loadLevelSubState.enter();
    sCurrentState = &loadLevelSubState;
    
    return success;
}

bool PlayState::exit()
{
    auto logger = spdlog::get("fileLogger");
    sCurrentState->exit();
    logger->info("Exited PlayState");
    return true;
}

void PlayState::handleEvent( SDL_Event& e )
{  
    sCurrentState->handleEvent( e );
                    //Exit on quit
    if( ( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_r ) ))
    {
        gameContext->resetGame();
        sNextState = &loadLevelSubState;
    }
}

void PlayState::update(double dt)
{
    sCurrentState->update(dt);

    if( sNextState != nullptr )
    {
		sCurrentState->exit();
		sNextState->enter();

        //Change the current state ID
        sCurrentState = sNextState;
        sNextState = nullptr;
    }

    if (gameContext->lives == 0) {
        setNextState(gameOverState);
    }
}

void PlayState::render()
{
    sCurrentState->render();
}

void PlayState::setGameOverState(GameState* gameOverState) {
    this->gameOverState = gameOverState;
}