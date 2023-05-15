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
    backgroundTexture = ImageLib::get()->loadTexture("assets\\images\\background1080.png");

    title = Text(bigfont, "Peppa Pig's Muddy Puddle Jump", 0, 0, gRenderer);
    title.SetPos((SCREEN_WIDTH / 2) - (title.textRect.w / 2 ), SCREEN_HEIGHT / 2 - (title.textRect.h / 2 ) - 100); 
    
    pressSpace = Text(font, "Press Space to Start", 0, 0, gRenderer);
    pressSpace.SetPos((SCREEN_WIDTH / 2) - (pressSpace.textRect.w / 2 ), SCREEN_HEIGHT / 2 - (pressSpace.textRect.h / 2 ) + 100); 
    
    return success;
}

bool StartState::exit()
{
    SDL_Log("Exited StartState\n");
    title.Destroy();
    pressSpace.Destroy();

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
    SDL_RenderCopy(gRenderer, backgroundTexture, NULL, NULL);
    title.Render();
    pressSpace.Render();
}

