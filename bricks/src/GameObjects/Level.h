#pragma once
#include <vector>

#include <AudioManager.h>
#include <SpriteManager.h>
#include <Brick.h>
#include <Turret.h>
#include <Powerup.h>

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


    void LoadLevel();
    void CreateLevel();
    void restartGame();
    void clearLevel();

    void clearTurretBullets();

    Level(SpriteManager* spriteManager, AudioManager* audioManager);

    ~Level(){};

    std::vector<Brick> brickList;
    std::vector<Turret> turretList;

private:

    SpriteManager* spriteManager;
    AudioManager* audioManager;

    std::string path = "assets\\levels\\";
    std::string ext = ".level";
    std::vector<std::string> levelFiles;
    std::vector<std::string>::iterator levelIterator;
    std::vector<std::string>::iterator lastLevel;

    std::vector<std::vector<int>> level;
    
    float startX = PLAYFIELD_STARTX + 32;
    float startY = 116;

    float brickSizeX = 64;
    float brickSizeY = 32;

    float turretSizeX = 64;
    float turretizeY = 64;

    void findNeighbours();

};