#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL_image.h>

#include <globals.h>
#include <statemanagers.h>

#include <StartState.h>
#include <ExitState.h>
#include <Timer.h>

// Method  Definitions
bool initSDL();
void closeSDL();

// Methods
bool initSDL () {

    SDL_Log("Initializing SDL.\n");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        SDL_LogError(1, "SDL Could not be initialized! SDL_Error: %s\n", SDL_GetError());
        return false;
    } 
    
    SDL_Log("Initializing SDL TTF.\n");
    if (TTF_Init() < 0)
    {
        SDL_LogError(1, "SDL TTF Could not be initialized! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_Log("Initializing Fonts.\n");
    font = TTF_OpenFont("assets\\fonts\\PublicPixel.ttf", 40);

    SDL_Log("Creating Window.\n");
    gWindow = SDL_CreateWindow("Calamity", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) 
    {
        SDL_LogError(1, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    } 

   SDL_Log("Creating Audio Mixer.\n");
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_LogError(1,"SDL Mixer cannot be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        SDL_Log( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }
    else
    {
        //Get window surface
        gScreenSurface = SDL_GetWindowSurface( gWindow );
    }

    SDL_Log("Creating Renderer.\n");
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    return true;
}

void closeSDL() 
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow( gWindow );
    TTF_Quit();
    Mix_CloseAudio();
    
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Quit();
}

// Main
int main (int argc, char* args[]) 
{

    SDL_Log("SDL starting...\n");
    if( !initSDL()) 
    {
        SDL_LogError(1, "Failed to Initialize!\n");
        closeSDL();
        return 1;
    }

    SpriteManager::get()->loadSprites();

    SDL_Event e;

    double before_time = (double)SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();

    SDL_Log("Getting Start State.\n");
	gCurrentState = StartState::get();
	gCurrentState->enter();

    //While the user hasn't quit
    SDL_Log("Starting Game Loop.\n");
    while( gCurrentState != ExitState::get() )
    {
        //Do state event handling
        while( SDL_PollEvent( &e ) != 0 )
        {
            //Handle state events
            gCurrentState->handleEvent( e );

            //Exit on quit
            if( e.type == SDL_QUIT )
            {
                setNextState( ExitState::get() );
            }

            if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_q ) )
            {
                setNextState( ExitState::get() );
            }
        }

        //float dt = Timer::get()->GetDeltaTime();

        double current_time = (double)SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();
        // How long it's been since the last frame in seconds.
        double dt = static_cast<double>(current_time - before_time);
        // Prime beforeTime for the next frame.
        before_time = current_time;

        //Do state logic
        gCurrentState->update(dt);

        //Change state if needed
        changeState();

        SDL_RenderClear(gRenderer);

        //Do state rendering
        gCurrentState->render();

        //Update screen
        SDL_RenderPresent( gRenderer );

        Timer::get()->Tick();
		}
    SDL_Log("Quitting SDL\n");
    closeSDL();
    return 0;
}