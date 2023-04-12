    #include <GameState.h>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>

    // Keyboard Events
    int NumKeys;
    const Uint8* keyboardState = SDL_GetKeyboardState(&NumKeys);
    
    // Fonts
    TTF_Font * font = NULL;
    TTF_Font * smallfont = NULL;
    
    // Window and Renderer
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;

    // State Pointers
    GameState* gCurrentState = NULL;
    GameState* gNextState = NULL;