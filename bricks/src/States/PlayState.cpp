#include <PlayState.h>
#include <TextManager.h>
#include <sstream>

PlayState::PlayState(GameContext* gameContext) :
    gameContext(gameContext),
    servingSubState(gameContext, sNextState),
    loadLevelSubState(gameContext, sNextState),
    dyingSubState(gameContext, sNextState),
    playingSubState(gameContext, sNextState),
    levelWinSubState(gameContext, sNextState) {
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
    loadLevelSubState.setServingSubState(&servingSubState);
    levelWinSubState.setLoadLevelSubState(&loadLevelSubState);

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
    //gameContext->tiledBackground.render();
    //gameContext->lightning.render();

   //gameContext->borderL.render();
    //gameContext->borderR.render();
    //gameContext->borderT.render();
    //gameContext->borderTL.render();
    //gameContext->borderTR.render();

    // Move the rest of these into the substates themselves
    //gameContext->paddle.render(subState);
    //gameContext->levelManager.render();
    //gameContext->ball.render();
    sCurrentState->render();



}