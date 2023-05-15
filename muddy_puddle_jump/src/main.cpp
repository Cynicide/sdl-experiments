#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL_image.h>
#include <iostream>

#include <globals.h>
#include <statemanagers.h>

#include <GameState.h>
#include <StartState.h>
#include <PlayState.h>
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
    font = TTF_OpenFont("assets\\fonts\\PeppaPig.ttf", 40);
    bigfont = TTF_OpenFont("assets\\fonts\\PeppaPig.ttf", 60);

    SDL_Log("Creating Window.\n");
    gWindow = SDL_CreateWindow("Mouse Training", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    peppatheme = loadMusic("assets\\sounds\\theme-instrumental.mp3");

    puddles = loadAudio("assets\\sounds\\puddles.wav");

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
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
    SDL_DestroyWindow( gWindow );
    TTF_Quit();
    Mix_FreeMusic(peppatheme);
    Mix_FreeChunk(puddles);
    Mix_CloseAudio();
    
    gWindow = NULL;
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

    SDL_ShowCursor(SDL_DISABLE);

    SDL_Event e;

    SDL_Log("Getting Start State.\n");
	gCurrentState = StartState::get();
	gCurrentState->enter();

    //While the user hasn't quit
    SDL_Log("Starting Game Loop.\n");
    Mix_PlayMusic(peppatheme, -1);
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

        float dt = Timer::get()->GetDeltaTime();
        //std::cout << dt << "\n";
        
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