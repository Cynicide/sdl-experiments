#include <AudioManager.h>

AudioManager AudioManager::sAudioManager;

AudioManager::AudioManager() {

}

AudioManager* AudioManager::get()
{
    //Get static instance
    return &sAudioManager;
}

Mix_Chunk * AudioManager::loadSound(const char * filename) {
    Mix_Chunk * audio;
    audio = Mix_LoadWAV( filename );
    return audio;
}

Mix_Music* AudioManager::loadMusic(const char * filename) {
    Mix_Music* music;
    music = Mix_LoadMUS(filename);
    return music;
}

void AudioManager::loadAudio() {
    ping = loadSound("assets\\audio\\ping.wav");
    pong = loadSound("assets\\audio\\pong.wav"); 

}