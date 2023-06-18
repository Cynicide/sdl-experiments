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

void Level::update(double dt, SDL_FRect paddleRect) {
    for (auto &i : brickList) {
        if (i.brickStatus != Definitions::BrickStatus::BrickDestroyed) {
            i.update(dt);
        }
    }

    for (auto &t : turretList) {
            t.update(dt, paddleRect);
    }
}

void Level::updatePreServe(double dt) {
    for (auto &i : brickList) {
            i.updatePreServe(dt);
    }

    for (auto &t : turretList) {
            t.update(dt);
    }
}

void Level::updateServe(double dt, SDL_FRect paddleRect) {
    for (auto &i : brickList) {
            i.updatePreServe(dt);
    }

    for (auto &t : turretList) {
            t.updateServe(dt, paddleRect);
    }
}


void Level::render() 
{
    for (auto &i : brickList) {
        if (i.brickStatus != Definitions::BrickStatus::BrickDestroyed) {
            i.render();
        }
    }

    for (auto &t : turretList) {
            t.renderBase();
    }

    // Turret Sprites should rendered seperately from their bases stop the turret rendering under the base next to it/
    for (auto &t : turretList) {
            t.renderTurret();
    }
}

void Level::renderPreServe() {
    for (auto &i : brickList) {
            i.renderPreServe();
    }
    for (auto &t : turretList) {
            t.renderBase();
    }
    // Turret Sprites should rendered seperately from their bases stop the turret rendering under the base next to it/
    for (auto &t : turretList) {
            t.renderTurret();
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
    for (auto &i : brickList) {
        if (i.brickStatus != Definitions::BrickStatus::BrickDestroyed && i.brickType != Definitions::BrickType::Indestructable) {
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

/*void Level::LoadLevel() {
    auto logger = spdlog::get("fileLogger");
    std::string line;
    int word;

    std::ifstream inFile(*levelIterator);
    turretList.clear();
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
        logger->error("Error loading level. File cannot be opened");
    }
    
    inFile.close();
}*/

void Level::CreateLevel() {

    auto logger = spdlog::get("fileLogger");

    float posX = startX;
    float posY = startY;

    brickList.clear();

    for(std::vector<char> &newvec: level)
        {
        for(const char &elem: newvec)
        {
            if (elem != '0') 
            {
                // ToDo: Maybe look at making all these std::unique_ptr
                switch (elem) {
                    case '1': {
                        Brick tmpBrick(posX, posY, Definitions::BrickType::Red, spriteManager->brickRed);
                        brickList.push_back(tmpBrick);
                        break;  
                    }
                    case '2': {
                        Brick tmpBrick(posX, posY, Definitions::BrickType::Blue, spriteManager->brickBlue);
                        brickList.push_back(tmpBrick);
                        break;  
                    }
                    case '3': {
                        Brick tmpBrick(posX, posY, Definitions::BrickType::Yellow, spriteManager->brickYellow);
                        brickList.push_back(tmpBrick);
                        break;  
                    }
                    case '4': {
                        Brick tmpBrick(posX, posY, Definitions::BrickType::Tough, spriteManager->brickTough);
                        brickList.push_back(tmpBrick);
                        break;  
                    }
                    case '5': {
                        Brick tmpBrick(posX, posY, Definitions::BrickType::Indestructable, spriteManager->brickIndestructable);
                        brickList.push_back(tmpBrick);
                        break; 
                    }
                    case '6': {
                        Brick tmpBrick(posX, posY, Definitions::BrickType::Orange, spriteManager->brickOrange);
                        brickList.push_back(tmpBrick);
                        break; 
                    }
                    case '7': {
                        Brick tmpBrick(posX, posY, Definitions::BrickType::Green, spriteManager->brickGreen);
                        brickList.push_back(tmpBrick);
                        break; 
                    }
                    case '8': {
                        Brick tmpBrick(posX, posY, Definitions::BrickType::Purple, spriteManager->brickPurple);
                        brickList.push_back(tmpBrick);
                        break;
                    }
                    case '9': {
                        Turret tmpTurret(posX, posY, spriteManager, audioManager);
                        turretList.push_back(tmpTurret);
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

        // Assign neighbour pointers for all bricks
        // ToDo: Do Remove all this
        findNeighbours();
}

/*void Level::CreateLevel() {

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
                        Brick tmpBrick(posX, posY, type, sprite);
                        brickList.push_back(tmpBrick);
                        break;  
                    }
                    case 2: {
                        type = Definitions::BrickType::Blue;
                        sprite = spriteManager->brickBlue;
                        Brick tmpBrick(posX, posY, type, sprite);
                        brickList.push_back(tmpBrick);
                        break;  
                    }
                    case 3: {
                        type = Definitions::BrickType::Yellow;
                        sprite = spriteManager->brickYellow;
                        Brick tmpBrick(posX, posY, type, sprite);
                        brickList.push_back(tmpBrick);
                        break;  
                    }
                    case 4: {
                        type = Definitions::BrickType::Tough;
                        sprite = spriteManager->brickTough;
                        Brick tmpBrick(posX, posY, type, sprite);
                        brickList.push_back(tmpBrick);
                        break;  
                    }
                    case 5: {
                        type = Definitions::BrickType::Indestructable;
                        sprite = spriteManager->brickIndestructable;
                        Brick tmpBrick(posX, posY, type, sprite);
                        brickList.push_back(tmpBrick);
                        break; 
                    }
                    case 6: {
                        type = Definitions::BrickType::Orange;
                        sprite = spriteManager->brickOrange;
                        Brick tmpBrick(posX, posY, type, sprite);
                        brickList.push_back(tmpBrick);
                        break; 
                    }
                    case 7: {
                        type = Definitions::BrickType::Green;
                        sprite = spriteManager->brickGreen;
                        Brick tmpBrick(posX, posY, type, sprite);
                        brickList.push_back(tmpBrick);
                        break; 
                    }
                    case 8: {
                        type = Definitions::BrickType::Purple;
                        sprite = spriteManager->brickPurple;
                        Brick tmpBrick(posX, posY, type, sprite);
                        brickList.push_back(tmpBrick);
                        break;
                    }
                    case 9: {
                        Turret tmpTurret(posX, posY, spriteManager, audioManager);
                        turretList.push_back(tmpTurret);
                        break;
                    }
                    default: {
                        type = Definitions::BrickType::Red;
                        sprite = spriteManager->brickRed;
                        break;  
                    }
                }
                //Brick tmpBrick(posX, posY, type, sprite, audioManager->ping);
                //brickList.push_back(tmpBrick);
            }
            posX = posX + brickSizeX;
        }
        posX = startX;
        posY = posY + brickSizeY;
        }

        // Assign neighbour pointers for all bricks
        findNeighbours();
}*/

void Level::findNeighbours() {
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

void Level::clearTurretBullets() {
    for (auto &t : turretList) {
        t.deleteBullet();
    }
}