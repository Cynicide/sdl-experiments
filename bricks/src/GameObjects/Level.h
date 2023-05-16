#pragma once
#include <vector>

#include <AudioManager.h>
#include <SpriteManager.h>
#include <Brick.h>
#include <Powerup.h>

class Level
{
public:
    void render();
    void update(double dt);
    void destroy();
    void getLevelFiles();
    void nextLevel();
    bool lastLevelCheck();


    void LoadLevel();
    void CreateLevel();
    void CreatePowerUp(float xPos, float yPos);
    void RemoveAllPowerups();


    Level(SpriteManager* spriteManager, AudioManager* audioManager);

    ~Level(){};

    std::vector<Brick> brickList;

private:

    SpriteManager* spriteManager;
    AudioManager* audioManager;

    std::string path = "assets\\levels\\";
    std::string ext = ".level";
    std::vector<std::string> levelFiles;
    std::vector<std::string>::iterator levelIterator;
    std::vector<std::string>::iterator lastLevel;

    std::vector<std::vector<int>> level;
    
    std::vector<Powerup> powerupList; 

    float startX = PLAYFIELD_STARTX + 32;
    float startY = 116;
    float brickSizeX = 64;
    float brickSizeY = 32;

    void findNeighbours();

};