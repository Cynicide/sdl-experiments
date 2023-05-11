#include <BrickManager.h>
#include <Definitions.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ranges.h"

#include <sstream>
#include <fstream>


BrickManager::BrickManager(SpriteManager* spriteManager, AudioManager* audioManager) {
    this->spriteManager = spriteManager;
    this->audioManager = audioManager;
}

void BrickManager::update(double dt) {
}

void BrickManager::render() 
{
    for (auto &i : brickList) {
        if (i.brickStatus != Definitions::BrickStatus::Destroyed) {
            i.render();
        }
    }
}

void BrickManager::destroy() {

}

void BrickManager::LoadLevel() {

    std::string line;
    int word;

    std::ifstream inFile("assets\\levels\\01.txt");

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
/*
    // Static Map of all Brick Types to their representation in Level files.

    // Maybe put this in defitions?
    static const std::unordered_map<int, Definitions::BrickType> typeMap {
        {1, Definitions::BrickType::Red},
        {2, Definitions::BrickType::Blue},
        {3, Definitions::BrickType::Yellow},
        {4, Definitions::BrickType::Tough},
        {5, Definitions::BrickType::Indestructable},
        {6, Definitions::BrickType::Orange},
        {7, Definitions::BrickType::Green},
        {8, Definitions::BrickType::Purple},
    };


    for (auto &newvec: level) {
        for(const int &elem: newvec) {
            
            // Find the Brick Type in the Static Map
            auto brickType = typeMap.find(elem);
            Definitions::BrickType type = (brickType != typeMap.end()) ? brickType->second : Definitions::BrickType::Red;

            if (elem != 0) {
                // Create a Brick Object with the constructor parameters
                brickList.emplace_back(posX, posY, type, &brickList);
                //Brick tmpBrick(posX, posY, type, &brickList);
                //brickList.push_back(tmpBrick);
            } 
            posX = posX + brickSizeX;
        }
        posX = startX;
        posY += brickSizeY;
    }*/

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
}   