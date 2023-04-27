#ifndef GLOBALS_H
#define GLOBALS_H

#include <GameState.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// App Details

extern const char * appName;

// Screen Dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

// Keyboard Input
extern int NumKeys;
extern const Uint8* keyboardState;

// Window and Renderer
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Surface* gScreenSurface;

// State Pointers
extern GameState* gCurrentState;
extern GameState* gNextState;

// Fonts
extern TTF_Font * font;

#endif