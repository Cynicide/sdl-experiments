#pragma once
#include <vector>

#include <AudioManager.h>
#include <SpriteManager.h>
#include <Brick.h>

class BrickManager
{
public:
    void render();
    void update(double dt);
    void destroy();

    void LoadLevel();
    void CreateLevel();

    BrickManager(SpriteManager* spriteManager, AudioManager* audioManager);

    ~BrickManager(){};

    std::vector<Brick> brickList;

private:

    SpriteManager* spriteManager;
    AudioManager* audioManager;

    std::vector<std::vector<int>> level;
    
    float startX = PLAYFIELD_STARTX + 32;
    float startY = 116;
    float brickSizeX = 64;
    float brickSizeY = 32;
};