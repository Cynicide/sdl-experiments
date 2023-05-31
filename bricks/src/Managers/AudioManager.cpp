#include <AudioManager.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

AudioManager::AudioManager() {
    spdlog::info("Creating Audio Manager");
    loadAudio();
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
    explosion = loadSound("assets\\audio\\explosion.wav");
    laser = loadSound("assets\\audio\\laser.wav"); 


}