#pragma once
#include <vector>
#include <Brick.h>
// Notes

// List of Bricks for Rendering and Collision Detection
// Loading the level
// Clearing the lists
// may need a Level manager too

class BrickManager
{
public:
    void render();
    void update(double dt);
    void destroy();

    void LoadLevel();
    void CreateLevel();

    BrickManager();

    ~BrickManager(){};

private:

    std::vector<std::vector<int>> level;
    std::vector<Brick> brickList;

    int startX = 32;
    int startY = 116;
    int brickSizeX = 64;
    int brickSizeY = 32;

};