#include <BrickManager.h>
#include <iostream>

#include <string>
#include <sstream>
#include <fstream>


BrickManager::BrickManager() {

}

void BrickManager::update(double dt) {
}

void BrickManager::render() 
{
    for (auto i : brickList) {
        i.render();
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
    // Testing
    //spdlog::debug("Level Data");
    //for(std::vector<int> &newvec: level)
    //{
    //    spdlog::debug("{}", newvec);
    //}
}

void BrickManager::CreateLevel() {

    float posX = startX;
    float posY = startY;

    for(std::vector<int> &newvec: level)
        {
        for(const int &elem: newvec)
        {
            if (elem == 1) 
            {
                
                Brick tmpBrick(posX, posY);
                brickList.push_back(tmpBrick);
                tmpBrick.setVectorRef(brickList);
            }
            posX = posX + brickSizeX;
        }
        posX = startX;
        posY = posY + brickSizeY;
        }
}   