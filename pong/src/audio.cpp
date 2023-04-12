#include <audio.h>

Mix_Chunk * loadAudio(const char * filename) {
    Mix_Chunk * audio;
    audio = Mix_LoadWAV( filename );
    return audio;
}