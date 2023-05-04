#include <StartState.h>
#include <SpriteManager.h>

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
    spdlog::info("Entered StartState.");

    background = ScrollingBackground(SpriteManager::get()->stars); 
    logoSprite = SpriteManager::get()->logo;

    bool bQuery = SDL_QueryTexture(logoSprite, NULL, NULL, &logoX, &logoY);
    if (bQuery == 1) {
        SDL_Log( SDL_GetError());
    }

    return success;
}

bool StartState::exit()
{
    spdlog::info("Exited StartState");
    return true;
}

void StartState::handleEvent( SDL_Event& e )
{
    //If the user pressed space move onto play state
    if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_SPACE ) )
    {
        setNextState( PlayState::get() );
    }
}

void StartState::update(double dt)
{
    background.update(dt);
}

void StartState::render()
{
    background.render();
    SDL_Rect logoRect = {(SCREEN_WIDTH / 2 - logoX / 2), (SCREEN_HEIGHT / 2) - (logoY / 2), logoX, logoY };
    SDL_RenderCopy(gRenderer, logoSprite, NULL, &logoRect );
}