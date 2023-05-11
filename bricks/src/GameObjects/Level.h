#pragma once

#include <vector>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ranges.h"

#include <Brick.h>

class Level {
    public:

    void render();
    void destroy();

    void LoadLevel();
    void CreateLevel();

    Level();

    ~Level(){};

    private: 
        
        std::vector<std::vector<int>> level;
    
        float startX = PLAYFIELD_STARTX + 32;
        float startY = 116;
        float brickSizeX = 64;
        float brickSizeY = 32;
};