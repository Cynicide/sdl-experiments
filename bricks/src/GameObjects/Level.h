#pragma once
#include <vector>

#include <AudioManager.h>
#include <SpriteManager.h>
#include <Brick.h>
#include <Turret.h>
#include <Powerup.h>
#include <LevelWarp.h>
#include <memory>

class Level
{
public:
    void render();
    void update(double dt, SDL_FRect paddleRect);

    void renderPreServe();
    void updatePreServe(double dt);

    void updateServe(double dt, SDL_FRect paddleRect);

    void destroy();
    void getLevelFiles();
    void nextLevel();
    bool lastLevelCheck();
    bool isLevelComplete();

    void LoadLevel();
    void CreateLevel();
    void restartGame();

    void clearLevel();
    void clearGameObjects();
    void clearTurretBullets();

    bool warpIsActive();
    void createLevelWarp();
    void destroyLevelWarp();
    SDL_FRect getWarpCollisionRect();

    Level(SpriteManager* spriteManager, AudioManager* audioManager);

    ~Level();

    std::vector<std::shared_ptr<Brick>> brickList;
    std::vector<std::shared_ptr<Turret>> turretList;

private:

    SpriteManager* spriteManager;
    AudioManager* audioManager;

    std::string path = "assets\\levels\\";
    std::string ext = ".level";
    std::vector<std::string> levelFiles;
    std::vector<std::string>::iterator levelIterator;
    std::vector<std::string>::iterator lastLevel;

    std::vector<std::vector<char>> level;

    std::unique_ptr<LevelWarp> levelWarp;

    float startX = PLAYFIELD_STARTX + 32;
    float startY = 116;

    float brickSizeX = 64;
    float brickSizeY = 32;

    float turretSizeX = 64;
    float turretizeY = 64;
};