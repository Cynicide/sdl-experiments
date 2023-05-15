#include <audio.h>

Mix_Chunk * loadAudio(const char * filename) {
    Mix_Chunk * audio;
    audio = Mix_LoadWAV( filename );
    return audio;
}

Mix_Music* loadMusic(const char * filename) {
    Mix_Music* music;
    music = Mix_LoadMUS(filename);
    return music;
}