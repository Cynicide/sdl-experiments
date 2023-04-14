#include <GameOverState.h>

GameOverState GameOverState::sGameOverState;

GameOverState::GameOverState() {

}

GameOverState* GameOverState::get()
{
    //Get static instance
    return &sGameOverState;
}
 
bool GameOverState::enter()
{
    //Loading success flag
    bool success = true;
    gameOverText = Text(font, "Game Over!", 0, 0, gRenderer);
    playAgainText = Text(smallfont, "Press Space to try again!", 0, 30, gRenderer);
    return success;
}

bool GameOverState::exit()
{
    return true;
}

void GameOverState::handleEvent( SDL_Event& e )
{
    //If the user pressed space
    if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_SPACE ) )
    {
        //Move onto title state
        setNextState( StartState::get() );
    }
}

void GameOverState::update(float dt)
{

}

void GameOverState::render()
{
    SDL_RenderCopy(gRenderer, gameOverText.texture, NULL, &gameOverText.textRect);
    SDL_RenderCopy(gRenderer, playAgainText.texture, NULL, &playAgainText.textRect);
}