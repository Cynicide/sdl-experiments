#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <Definitions.h>
#include <vector>

class Brick
{
public:
    void render();
    void update(double dt);
    void setVectorRef(std::vector<Brick>& _brickRef);
    void hit();    

    SDL_FRect brickRect;

    // Without this std::find won't work
    bool operator==(const Brick& other) const {
        //return (xpos == other.xpos) && (ypos == other.ypos);
        return this == &other;
    }

    Brick(float _xpos, float _ypos, Definitions::BrickType type);
    Definitions::BrickStatus brickStatus = Definitions::BrickStatus::Good;


    ~Brick(){};

private:


    Definitions::BrickType brickType;

    static const int numSprites = 21;
    static const int destructionStartFrame = 3;
    static const int destructionEndFrame = 10;
    int currentdestructionFrame = destructionStartFrame;
    
    SDL_Texture* brickSprite;
    SDL_Rect brickSpriteClips[numSprites];

    float brickHeight = 32.f;
    float brickWidth = 64.f;
    float xpos, ypos;

    int type = 0;
    bool destructable = true;
    int health = 0;

    std::vector<Brick> *brickRef = nullptr;


    void removeFromVector(std::vector<Brick>* vectorRef);

    void SliceSpriteSheet();

};