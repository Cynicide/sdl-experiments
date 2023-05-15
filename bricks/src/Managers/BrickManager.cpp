#include <BrickManager.h>
#include <Definitions.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ranges.h"

#include <sstream>
#include <fstream>
#include <filesystem>


BrickManager::BrickManager(SpriteManager* spriteManager, AudioManager* audioManager) {
    this->spriteManager = spriteManager;
    this->audioManager = audioManager;
}

void BrickManager::update(double dt) {
    for (auto &i : brickList) {
        if (i.brickStatus != Definitions::BrickStatus::Destroyed) {
            i.update(dt);
        }
}
}

void BrickManager::render() 
{
    for (auto &i : brickList) {
        if (i.brickStatus != Definitions::BrickStatus::Destroyed) {
            i.render();
        }
    }
}

bool BrickManager::lastLevelCheck() {
    if (levelIterator == std::prev(lastLevel)) {
        return true;
    } else {
        return false;
    }
}

void BrickManager::getLevelFiles() {
    spdlog::info("Getting a list of levels");
    for (auto &p : std::filesystem::recursive_directory_iterator(path)) {
        if (p.path().extension() == ext) {
            levelFiles.push_back(path + p.path().filename().string());
        }
    }
    
    levelIterator = levelFiles.begin();
    lastLevel = levelFiles.end();
    
    //for (auto &i : levelFiles) {
    //    spdlog::info(i);
    //}
}

void BrickManager::destroy() {

}

void BrickManager::nextLevel() {
    ++levelIterator;
}

void BrickManager::LoadLevel() {

    std::string line;
    int word;

    std::ifstream inFile(*levelIterator);
    level.clear();
    if(inFile)
    {
        while(getline(inFile, line, '\n'))        
        {
            //create a temporary vector that will contain all the columns
            std::vector<int> tempVec;    
            std::istringstream ss(line);
            
            //read word by word(or int by int) 
            while(ss >> word)
            {
                //add the word to the temporary vector 
                tempVec.push_back(word);
            }      
            //now all the words from the current line has been added to the temporary vector 
            level.emplace_back(tempVec);
        }    
    }
    else 
    {
        spdlog::error("Error loading level. File cannot be opened");
    }
    
    inFile.close();
}

void BrickManager::CreateLevel() {

    float posX = startX;
    float posY = startY;

    brickList.clear();

    for(std::vector<int> &newvec: level)
        {
        for(const int &elem: newvec)
        {
            if (elem != 0) 
            {
                Definitions::BrickType type = Definitions::BrickType::Red;
                SDL_Texture* sprite = spriteManager->brickRed;
                switch (elem) {
                    case 1: {
                        type = Definitions::BrickType::Red;
                        sprite = spriteManager->brickRed;
                        break;  
                    }
                    case 2: {
                        type = Definitions::BrickType::Blue;
                        sprite = spriteManager->brickBlue;
                        break;  
                    }
                    case 3: {
                        type = Definitions::BrickType::Yellow;
                        sprite = spriteManager->brickYellow;
                        break;  
                    }
                    case 4: {
                        type = Definitions::BrickType::Tough;
                        sprite = spriteManager->brickTough;
                        break;  
                    }
                    case 5: {
                        type = Definitions::BrickType::Indestructable;
                        sprite = spriteManager->brickIndestructable;
                        break; 
                    }
                    case 6: {
                        type = Definitions::BrickType::Orange;
                        sprite = spriteManager->brickOrange;
                        break; 
                    }
                    case 7: {
                        type = Definitions::BrickType::Green;
                        sprite = spriteManager->brickGreen;
                        break; 
                    }
                    case 8: {
                        type = Definitions::BrickType::Purple;
                        sprite = spriteManager->brickPurple;
                        break; 
                    }
                    default: {
                        type = Definitions::BrickType::Red;
                        sprite = spriteManager->brickRed;
                        break;  
                    }
                }
                Brick tmpBrick(posX, posY, type, sprite, audioManager->ping);
                brickList.push_back(tmpBrick);
            }
            posX = posX + brickSizeX;
        }
        posX = startX;
        posY = posY + brickSizeY;
        }

        // Assign neighbour pointers for all bricks
        findNeighbours();
}   

void BrickManager::findNeighbours() {
    for (auto &brick : brickList) {
        for (auto &neighbour : brickList) {
            // Find the Top Neighbour
            if (neighbour.brickRect.x == brick.brickRect.x && neighbour.brickRect.y == brick.brickRect.y - brick.brickRect.h) {
                brick.topNeighbour = &neighbour;
            }
            // Find Bottom Neighbour
            if (neighbour.brickRect.x == brick.brickRect.x && neighbour.brickRect.y == brick.brickRect.y + brick.brickRect.h) {
                brick.bottomNeighbour = &neighbour;
            }

            // Find Right Neighbour
            if (neighbour.brickRect.x == brick.brickRect.x + brick.brickRect.w && neighbour.brickRect.y == brick.brickRect.y) {
                brick.rightNeighbour = &neighbour;
            }

            // Find Left Neighbour
            if (neighbour.brickRect.x == brick.brickRect.x - brick.brickRect.w && neighbour.brickRect.y == brick.brickRect.y) {
                brick.leftNeighbour = &neighbour;
            }
        }     
    }
}