#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> 

Mix_Chunk * loadAudio(const char * filename);

Mix_Music* loadMusic(const char * filename);

#endif