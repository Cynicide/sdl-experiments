    #include <GameState.h>
    #include <globals.h>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_mixer.h> 

    // Keyboard Events
    int NumKeys;
    const Uint8* keyboardState = SDL_GetKeyboardState(&NumKeys);
    
    // Fonts
    TTF_Font * font = NULL;
    TTF_Font * bigfont = NULL;

    // Window and Renderer
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    SDL_Surface* gScreenSurface = NULL;

    // State Pointers
    GameState* gCurrentState = NULL;
    GameState* gNextState = NULL;

    Mix_Music* peppatheme = NULL;
    Mix_Chunk* puddles = NULL;


