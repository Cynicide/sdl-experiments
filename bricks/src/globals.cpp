    #include <globals.h>

    // App Details
    const char * appName = "Bricks Dreams";

    // Keyboard Events
    int NumKeys;
    const Uint8* keyboardState = SDL_GetKeyboardState(&NumKeys);

    // Window and Renderer
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    SDL_Surface* gScreenSurface = NULL;

    // State Pointers
    GameState* gCurrentState = NULL;
    GameState* gNextState = NULL;