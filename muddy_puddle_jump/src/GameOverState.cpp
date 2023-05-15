#include <GameOverState.h>

GameOverState GameOverState::sGameOverState;

GameOverState::GameOverState() {

}

GameOverState* GameOverState::get(int _score)
{
    //Get static instance
    sGameOverState.score = _score;
    return &sGameOverState;
}

bool GameOverState::enter()
{
    //Loading success flag
    bool success = true;
    SDL_Log("Entered StartState\n");
    backgroundTexture = ImageLib::get()->loadTexture("assets\\images\\background1080.png");

    gameOver = Text(bigfont, ("Game Over! Your score is " + std::to_string(score)).c_str(), 0, 0, gRenderer);
    gameOver.SetPos((SCREEN_WIDTH / 2) - (gameOver.textRect.w / 2 ), SCREEN_HEIGHT / 2 - (gameOver.textRect.h / 2 ) - 100); 
    
    playAgain = Text(font, "Do you want to play again? Y/N", 0, 0, gRenderer);
    playAgain.SetPos((SCREEN_WIDTH / 2) - (playAgain.textRect.w / 2 ), SCREEN_HEIGHT / 2 - (playAgain.textRect.h / 2 ) + 100); 
    
    return success;
}

bool GameOverState::exit()
{
    SDL_Log("Exited StartState\n");
    gameOver.Destroy();
    playAgain.Destroy();

    return true;
}

void GameOverState::handleEvent( SDL_Event& e )
{
    //If the user pressed space
    if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_y ) )
    {
        //Move onto play state
        setNextState( PlayState::get() );
    }

    if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_n ) )
    {
        //Move onto exit state
        setNextState( ExitState::get() );
    }

    if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_q ) )
    {
        //Move onto exit state
        setNextState( ExitState::get() );
    }
}

void GameOverState::update(float dt)
{

}

void GameOverState::render()
{
    SDL_RenderCopy(gRenderer, backgroundTexture, NULL, NULL);
    gameOver.Render();
    playAgain.Render();
}

