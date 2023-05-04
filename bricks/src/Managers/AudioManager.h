#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

//#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> 

class AudioManager
{
public:
    //Static accessor
    static AudioManager* get();

    Mix_Chunk * ping;
    Mix_Chunk * pong;

    Mix_Chunk * loadSound(const char * filename);
    Mix_Music* loadMusic(const char * filename);
    void loadAudio();

private:
    //Static instance
    static AudioManager sAudioManager;


    //Private constructor
    AudioManager();

    // PrivateDestructor
    ~AudioManager(){};

};
#endif