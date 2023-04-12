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
    return success;
}

bool StartState::exit()
{
    SDL_Log("Exited StartState\n");
    attractText.Destroy();
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

void StartState::update()
{

}

void StartState::render()
{
    attractText.Render();
}

