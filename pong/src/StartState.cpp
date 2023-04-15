#include <StartState.h>

StartState StartState::sStartState;

StartState::StartState() {

}

StartState* StartState::get()
{
    //Get static instance
    return &sStartState;
}

bool StartState::enter()
{
    //Loading success flag
    bool success = true;
    SDL_Log("Entered StartState\n");

    attractText = Text(font, "Press Space to Start!", 0, 0, gRenderer);
    attractText.SetPos((SCREEN_WIDTH / 2) - (attractText.textRect.w / 2 ), SCREEN_HEIGHT / 2 - (attractText.textRect.h / 2 ) + 10); 

    titleText = Text(bigfont, "SDL PONG", 0, 0, gRenderer);
    titleText.SetPos((SCREEN_WIDTH / 2) - (titleText.textRect.w / 2 ), SCREEN_HEIGHT / 2 - (titleText.textRect.h / 2 ) - 30);

    playeroneControls = Text(smallfont, "Player 1: A - Up.   Z - Down.", 0, 0, gRenderer);
    playeroneControls.SetPos((SCREEN_WIDTH / 2) - (playeroneControls.textRect.w / 2 ), SCREEN_HEIGHT / 2 - (playeroneControls.textRect.h / 2 ) + 40);

    playertwoControls = Text(smallfont, "Player 2: K - Up.   M - Down.", 0, 0, gRenderer);
    playertwoControls.SetPos((SCREEN_WIDTH / 2) - (playertwoControls.textRect.w / 2 ), SCREEN_HEIGHT / 2 - (playertwoControls.textRect.h / 2 ) + 60); 
    return success;
}

bool StartState::exit()
{
    SDL_Log("Exited StartState\n");
    attractText.Destroy();
    titleText.Destroy();
    playeroneControls.Destroy();
    playertwoControls.Destroy();
    return true;
}

void StartState::handleEvent( SDL_Event& e )
{
    //If the user pressed space
    if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_SPACE ) )
    {
        //Move onto title state
        setNextState( PlayState::get() );
    }
}

void StartState::update(float dt)
{

}

void StartState::render()
{
    titleText.Render();
    attractText.Render();
    playeroneControls.Render();
    playertwoControls.Render();
}

