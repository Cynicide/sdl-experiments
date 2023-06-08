#include <PlayState.h>
#include <TextManager.h>
#include <sstream>

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
    spdlog::info("Entered PlayState");
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

    // This seems like a bit of a hack. You're not supposed to call these methods.
    loadLevelSubState.enter();
    sCurrentState = &loadLevelSubState;
    
    return success;
}

bool PlayState::exit()
{
    
    sCurrentState->exit();
    spdlog::info("Exited PlayState");
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
}

void PlayState::render()
{
    sCurrentState->render();
}