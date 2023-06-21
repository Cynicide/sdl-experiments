#include <Level.h>
#include <Definitions.h>

#include <sstream>
#include <fstream>
#include <filesystem>
#include "spdlog/spdlog.h"

Level::Level(SpriteManager* spriteManager, AudioManager* audioManager) {
    this->spriteManager = spriteManager;
    this->audioManager = audioManager;
}

Level::~Level() {
    clearLevel();
}

void Level::update(double dt, SDL_FRect paddleRect) {
    for (auto brick : brickList) {
        if (brick->brickStatus != Definitions::BrickStatus::BrickDestroyed) {
            brick->update(dt);
        }
    }

    for (auto turret : turretList) {
            turret->update(dt, paddleRect);
    }

    if (levelWarp != nullptr) {
        levelWarp->update(dt);
    }
}

void Level::updatePreServe(double dt) {
    for (auto brick : brickList) {
            brick->updatePreServe(dt);
    }

    for (auto turret : turretList) {
            turret->update(dt);
    }
}

void Level::updateServe(double dt, SDL_FRect paddleRect) {
    for (auto brick : brickList) {
            brick->updatePreServe(dt);
    }

    for (auto turret : turretList) {
            turret->updateServe(dt, paddleRect);
    }
}

void Level::createLevelWarp() {
    levelWarp = std::make_unique<LevelWarp>(spriteManager);
}

void Level::destroyLevelWarp() {
    levelWarp.reset();
}

bool Level::warpIsActive() {
    if (levelWarp == nullptr) {
        return false;
    } else {
        return true;
    }
}

SDL_FRect Level::getWarpCollisionRect() {
    return levelWarp->warpPortalCollisionRect;
}

void Level::render() 
{
    for (auto brick : brickList) {
        if (brick->brickStatus != Definitions::BrickStatus::BrickDestroyed) {
            brick->render();
        }
    }

    for (auto turret : turretList) {
            turret->renderBase();
    }

    // Turret Sprites should rendered seperately from their bases stop the turret rendering under the base next to it/
    for (auto turret : turretList) {
            turret->renderTurret();
    }

    if (levelWarp != nullptr) {
        levelWarp->render();
    }
}

void Level::renderPreServe() {
    for (auto brick : brickList) {
            brick->renderPreServe();
    }
    for (auto turret : turretList) {
            turret->renderBase();
    }
    // Turret Sprites should rendered seperately from their bases stop the turret rendering under the base next to it/
    for (auto turret : turretList) {
            turret->renderTurret();
    }
}

bool Level::lastLevelCheck() {
    if (levelIterator == std::prev(lastLevel)) {
        return true;
    } else {
        return false;
    }
}

bool Level::isLevelComplete() {
    for (auto brick : brickList) {
        if (brick->brickStatus != Definitions::BrickStatus::BrickDestroyed && brick->brickType != Definitions::BrickType::Indestructable) {
            // If any bricks remain do not advance to the next level.
            return false;
        }
    }
    return true;
}

void Level::getLevelFiles() {
    auto logger = spdlog::get("fileLogger");
    logger->info("Getting a list of levels");
    for (auto &p : std::filesystem::recursive_directory_iterator(path)) {
        if (p.path().extension() == ext) {
            levelFiles.push_back(path + p.path().filename().string());
        }
    }
    
    levelIterator = levelFiles.begin();
    lastLevel = levelFiles.end();

}

void Level::destroy() {

}

void Level::restartGame() {
    levelIterator = levelFiles.begin();
}

void Level::nextLevel() {
    ++levelIterator;
}

void Level::clearLevel() {
    level.clear();
    clearGameObjects();
}

void Level::clearGameObjects() {    
    brickList.clear();
    turretList.clear();
}

void Level::LoadLevel() {
    auto logger = spdlog::get("fileLogger");
    std::string line;
    char word;

    std::ifstream inFile(*levelIterator);
    turretList.clear();
    level.clear();
    if(inFile)
    {
        while(getline(inFile, line, '\n'))        
        {
            //create a temporary vector that will contain all the columns
            std::vector<char> tempVec;    
            std::istringstream ss(line);
            
            //read word by word(or int by int) 
            while(ss >> word)
            {
                if (word != ' ') {
                    tempVec.push_back(word);
                }
                //add the word to the temporary vector 
            }      
            //now all the words from the current line has been added to the temporary vector 
            level.emplace_back(tempVec);
        }    
    }
    else 
    {
        logger->error("Error loading level. File cannot be opened");
    }
    
    inFile.close();
}

void Level::CreateLevel() {

    auto logger = spdlog::get("fileLogger");

    float posX = startX;
    float posY = startY;

    clearGameObjects();

    for(std::vector<char> &newvec: level)
        {
        for(const char &elem: newvec)
        {
            if (elem != '0') 
            {
                // ToDo: Maybe look at making all these std::unique_ptr
                switch (elem) {
                    case '1': {
                        brickList.push_back(std::make_unique<Brick>(posX, posY, Definitions::BrickType::Red, spriteManager->brickRed));
                        break;  
                    }
                    case '2': {
                        brickList.push_back(std::make_unique<Brick>(posX, posY, Definitions::BrickType::Blue, spriteManager->brickBlue));
                        break;  
                    }
                    case '3': {
                        brickList.push_back(std::make_unique<Brick>(posX, posY, Definitions::BrickType::Yellow, spriteManager->brickYellow));
                        break;  
                    }
                    case '4': {
                        brickList.push_back(std::make_unique<Brick>(posX, posY, Definitions::BrickType::Tough, spriteManager->brickTough));
                        break;  
                    }
                    case '5': {
                        brickList.push_back(std::make_unique<Brick>(posX, posY, Definitions::BrickType::Indestructable, spriteManager->brickIndestructable));
                        break; 
                    }
                    case '6': {
                        brickList.push_back(std::make_unique<Brick>(posX, posY, Definitions::BrickType::Orange, spriteManager->brickOrange));
                        break; 
                    }
                    case '7': {
                        brickList.push_back(std::make_unique<Brick>(posX, posY, Definitions::BrickType::Green, spriteManager->brickGreen));
                        break; 
                    }
                    case '8': {
                        brickList.push_back(std::make_unique<Brick>(posX, posY, Definitions::BrickType::Purple, spriteManager->brickPurple));
                        break;
                    }
                    case '9': {
                        turretList.push_back(std::make_unique<Turret>(posX, posY, spriteManager, audioManager));
                        break;
                    }
                    default: {
                        logger->error("Ended up in default when parsing brick vector. This should not happen.");
                        break;  
                    }
                }
            }
            posX = posX + brickSizeX;
        }
        posX = startX;
        posY = posY + brickSizeY;
        }
}

void Level::clearTurretBullets() {
    for (auto &turret : turretList) {
        turret->deleteBullet();
    }
}