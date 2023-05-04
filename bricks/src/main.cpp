#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL_image.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <globals.h>
#include <statemanagers.h>

#include <StartState.h>
#include <ExitState.h>
#include <Timer.h>
#include <sstream>

#include <TextManager.h>

// Method  Definitions
bool initSDL();
void closeSDL();

// Methods
bool initSDL () {

    spdlog::info("Initializing SDL.");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        spdlog::error("SDL Could not be initialized! SDL_Error: ",  SDL_GetError());
        return false;
    } 
    
    spdlog::info("Initializing SDL TTF.");
    if (TTF_Init() < 0)
    {
        spdlog::error("SDL TTF Could not be initialized! SDL_Error: ", SDL_GetError());
        return false;
    }

    spdlog::info("Creating Window.");
    gWindow = SDL_CreateWindow(appName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) 
    {
        spdlog::error("Window could not be created! SDL_Error: ", SDL_GetError());
        return false;
    } 

    spdlog::info("Creating Audio Mixer.");
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        spdlog::error("SDL Mixer cannot be created! SDL_Error: ", SDL_GetError());
        return false;
    }

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        spdlog::error( "SDL_image could not initialize! SDL_image Error: ", IMG_GetError() );
        return false;
    }
    else
    {
        //Get window surface
        gScreenSurface = SDL_GetWindowSurface( gWindow );
    }

    spdlog::info("Creating Renderer.");
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    // Capture the Mouse
    SDL_SetRelativeMouseMode(SDL_TRUE);
    
    return true;
}

void closeSDL() 
{
    spdlog::info("Destroying Renderer");

    SDL_DestroyRenderer(gRenderer);
    
    spdlog::info("Destroying Window");
    SDL_DestroyWindow( gWindow );

    spdlog::info("Quitting TTF");
    TTF_Quit();

    spdlog::info("Closing Mixer");
    Mix_CloseAudio();
    
    gWindow = NULL;
    gRenderer = NULL;

    spdlog::info("SDL Quit");
    SDL_Quit();
}

// Main
int main (int argc, char* args[]) 
{
    // Start Logging
    auto console = spdlog::stdout_color_mt("console");  
    spdlog::info("Starting Bricks!");
    
    // Remove old Log Files
    std::remove("./game.txt");

    // Starting SDL    
    spdlog::info("SDL starting...");
    if( !initSDL()) 
    {
        spdlog::error("Failed to Initialize!");
        closeSDL();
        return 1;
    }

    // Loading Resources
    SpriteManager::get()->loadSprites();
    AudioManager::get()->loadAudio();
    TextManager::get()->loadFonts();

    // Get Event Structure
    SDL_Event e;

    // TODO: Deltatime implemtation based on https://gafferongames.com/post/fix_your_timestep/ fix.
    spdlog::info("Getting Start State.");
	gCurrentState = StartState::get();
	gCurrentState->enter();

    //While the user hasn't quit
    spdlog::info("Starting Game Loop.");
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

            //Do state logic
            float dt =1.f;
            gCurrentState->update(dt);

            //Change state if needed
            changeState();

        SDL_RenderClear(gRenderer);

        //Do state rendering
        gCurrentState->render();

        //Update screen
        SDL_RenderPresent( gRenderer );
		}
    spdlog::info("Quitting SDL");
    closeSDL();
    return 0;
}