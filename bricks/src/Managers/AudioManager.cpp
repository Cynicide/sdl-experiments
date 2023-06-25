#include <AudioManager.h>
#include "spdlog/spdlog.h"

AudioManager::AudioManager() {
    auto logger = spdlog::get("fileLogger");
    logger->info("Creating Audio Manager");
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
    ping = loadSound("assets\\audio\\ping.wav"); // 1
    pong = loadSound("assets\\audio\\pong.wav"); // 3
    explosion = loadSound("assets\\audio\\explosion.wav"); // 2 
    laser = loadSound("assets\\audio\\laser.wav"); // 4
    turretExplosion = loadSound("assets\\audio\\turret-explosion.wav"); // 5
    letsGo = loadMusic("assets\\audio\\letsgo.mp3"); // Music
    levelEnd = loadMusic("assets\\audio\\levelend.mp3"); // Music
    gameOver = loadMusic("assets\\audio\\gameover.mp3"); // Music
    titleTrack = loadMusic("assets\\audio\\title-track.mp3"); // Music
}