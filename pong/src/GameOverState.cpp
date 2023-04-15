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
    gameOverText.SetPos((SCREEN_WIDTH / 2) - (gameOverText.textRect.w / 2 ), SCREEN_HEIGHT / 2 - (gameOverText.textRect.h / 2 )); 

    playAgainText = Text(smallfont, "Press Space to try again!", 0, 0, gRenderer);
    playAgainText.SetPos((SCREEN_WIDTH / 2) - (playAgainText.textRect.w / 2 ), SCREEN_HEIGHT / 2 - (playAgainText.textRect.h / 2 ) + 60); 

    std::string wtext = winner + " wins.";
    winnerText = Text(font, wtext.c_str(), 0, 0, gRenderer);
    winnerText.SetPos((SCREEN_WIDTH / 2) - (winnerText.textRect.w / 2 ), SCREEN_HEIGHT / 2 - (winnerText.textRect.h / 2 ) + 20); 

    return success;
}

bool GameOverState::exit()
{
    gameOverText.Destroy();
    playAgainText.Destroy();
    winnerText.Destroy();
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
    gameOverText.Render();
    playAgainText.Render();
    winnerText.Render();
}