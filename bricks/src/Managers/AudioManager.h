#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

//#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> 

class AudioManager
{
public:
    //Static accessor
    static AudioManager* get();

    Mix_Chunk * loadAudio(const char * filename);
    Mix_Music* loadMusic(const char * filename);

private:
    //Static instance
    static AudioManager sAudioManager;


    //Private constructor
    AudioManager();

    // PrivateDestructor
    ~AudioManager(){};

};
#endif