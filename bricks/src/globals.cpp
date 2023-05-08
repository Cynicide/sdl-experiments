    #include <globals.h>

    // Default Screen dimensions to be overidden
    int SCREEN_WIDTH = 1280;
    int SCREEN_HEIGHT = 960;
    
    // Width of the Virtual Playfield, starting point will change based on screen width.
    int PLAYFIELD_STARTX = 0;
    const int PLAYFIELD_WIDTH = 1280;

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