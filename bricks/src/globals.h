#pragma once

#include <GameState.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// App Details

extern const char * appName;

// Screen Dimensions
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int PLAYFIELD_STARTX;
extern const int PLAYFIELD_WIDTH;

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