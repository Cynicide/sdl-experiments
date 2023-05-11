#pragma once
#include <SDL2/SDL_mixer.h> 

class AudioManager
{
public:
    //Private constructor
    AudioManager();

    // PrivateDestructor
    ~AudioManager(){};

    Mix_Chunk * ping;
    Mix_Chunk * pong;
    Mix_Chunk * explosion;

    Mix_Chunk * loadSound(const char * filename);
    Mix_Music* loadMusic(const char * filename);
    void loadAudio();

private:

};