#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL_image.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <GameContext.h>

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

    // Get the Display mode on Display 0 and use it to set the resolution and virtual playfield    
    SDL_DisplayMode mode; 
    SDL_GetCurrentDisplayMode(0, &mode);

    SCREEN_HEIGHT = mode.h;
    SCREEN_WIDTH = mode.w;
    
    // Make sure the virtual playfield is centered on the screen
    int screenWidthMidpoint = SCREEN_WIDTH / 2;
    PLAYFIELD_STARTX = screenWidthMidpoint - (PLAYFIELD_WIDTH /2);

    // Initialize SDL Mixer
    spdlog::info("Creating Audio Mixer.");
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        spdlog::error("SDL Mixer cannot be created! SDL_Error: ", SDL_GetError());
        return false;
    }

    // Initialize SDL TTF
    spdlog::info("Initializing SDL TTF.");
    if (TTF_Init() < 0)
    {
        spdlog::error("SDL TTF Could not be initialized! SDL_Error: ", SDL_GetError());
        return false;
    }

    //Initialize SDL Image to enable loading PNG
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        spdlog::error( "SDL_image could not initialize! SDL_image Error: ", IMG_GetError() );
        return false;
    }
    else
    {
        gScreenSurface = SDL_GetWindowSurface( gWindow );
    }

    // Create SDL Window
    spdlog::info("Creating Window.");
    gWindow = SDL_CreateWindow(appName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) 
    {
        spdlog::error("Window could not be created! SDL_Error: ", SDL_GetError());
        return false;
    } 

    spdlog::info("Creating Renderer.");
    //gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // Here we go again:
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    // Capture the Mouse to the Window
    //SDL_SetRelativeMouseMode(SDL_TRUE);

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
    
    // Starting SDL    
    spdlog::info("SDL starting...");
    if( !initSDL()) 
    {
        spdlog::error("Failed to Initialize!");
        //closeSDL();
        return 1;
    }

    // Loading Resources
    GameContext gameContext;

    // Get Event Structure
    SDL_Event e;

    // Instantiate Game States
    PlayState playState(&gameContext);
    StartState startState(&gameContext, &playState);
    ExitState exitState;

    spdlog::info("Getting Start State.");
	gCurrentState = &startState;
	gCurrentState->enter();

    // Getting timestep
    double t = 0.0;
    double dt = 1 / 60.0;
    double currentTime = (double)SDL_GetPerformanceCounter() / (double)SDL_GetPerformanceFrequency();

    //While the user hasn't quit
    spdlog::info("Starting Game Loop.");
    while( !(dynamic_cast<ExitState*>(gCurrentState)))
    {
        
        double newTime = (double)SDL_GetPerformanceCounter() / (double)SDL_GetPerformanceFrequency();
        spdlog::debug ("Time: " + std::to_string(newTime));
        double frameTime = newTime - currentTime;
        spdlog::debug ("FrameTime: " + std::to_string(frameTime));
        currentTime = newTime;
        
        while (frameTime > 0.0) {

            float deltaTime = std::min(frameTime, dt);

            //Do state event handling
            while( SDL_PollEvent( &e ) != 0 )
            {
                //Handle events for the current state
                gCurrentState->handleEvent( e );

                //Exit on quit
                if( (e.type == SDL_QUIT) ||  ( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_q ) ))
                {
                    setNextState( &exitState );
                }
            }

            //Do state logic
            gCurrentState->update(deltaTime);

            //Change state if needed
            changeState();

            frameTime -= deltaTime;
            t += deltaTime;
        }

        SDL_SetRenderDrawColor(gRenderer, 0,0,0, SDL_ALPHA_OPAQUE);
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