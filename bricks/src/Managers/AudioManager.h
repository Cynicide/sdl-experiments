#pragma once
#include <SDL2/SDL_mixer.h> 

class AudioManager
{
public:
    //Private constructor
    AudioManager();

    // PrivateDestructor
    ~AudioManager(){};

    Mix_Chunk* ping;
    Mix_Chunk* pong;
    Mix_Chunk* explosion;
    Mix_Chunk* laser;
    Mix_Chunk* turretExplosion;

    Mix_Music* letsGo;
    Mix_Music* levelEnd;
    Mix_Music* gameOver;

    Mix_Chunk * loadSound(const char * filename);
    Mix_Music* loadMusic(const char * filename);
    void loadAudio();

private:

};