#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h> 
#include <iostream>

#include <globals.h>
#include <statemanagers.h>

#include <GameState.h>
#include <StartState.h>
#include <GameOverState.h>
#include <PlayState.h>
#include <ExitState.h>

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
    font = TTF_OpenFont("assets\\fonts\\PublicPixel.ttf", 14);
    smallfont = TTF_OpenFont("assets\\fonts\\PublicPixel.ttf", 12);

    SDL_Log("Creating Window.\n");
    gWindow = SDL_CreateWindow("SDL Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) 
    {
        SDL_LogError(1, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    } 

    std::cout << "Creating Audio Mixer.\n";
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_LogError(1,"SDL Mixer cannot be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_Log("Creating Renderer.\n");
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetVSync(gRenderer, 1);
    return true;
}

void closeSDL() 
{
    SDL_DestroyWindow( gWindow );
    TTF_Quit();
    gWindow = NULL;
    SDL_Quit();
}

// Main
int main (int argc, char* args[]) 
{

    SDL_Log("SDL Pong starting...\n");
    if( !initSDL()) 
    {
        SDL_LogError(1, "Failed to Initialize!\n");
        closeSDL();
        return 1;
    }

    SDL_Event e;

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
        }

        //Do state logic
        gCurrentState->update();

        //Change state if needed
        changeState();

        //Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0,0,0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(gRenderer);
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        //Do state rendering
        gCurrentState->render();

        //Update screen
        SDL_RenderPresent( gRenderer );
		}
    SDL_Log("Quitting SDL Pong.\n");
    closeSDL();
    return 0;
}