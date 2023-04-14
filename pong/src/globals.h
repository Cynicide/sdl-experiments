#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <GameState.h>
#include <SDL2/SDL_mixer.h> 

// Screen Dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Keyboard Input
extern int NumKeys;
extern const Uint8* keyboardState;

// Window and Renderer
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

// State Pointers
extern GameState* gCurrentState;
extern GameState* gNextState;

// Fonts
extern TTF_Font * font;
extern TTF_Font * smallfont;

// Sounds

extern Mix_Chunk *gPing;
extern Mix_Chunk *gPong;

#endif