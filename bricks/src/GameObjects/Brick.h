#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> 

#include <SpriteManager.h>
#include <AudioManager.h>

#include <Definitions.h>
#include <vector>

class Brick
{
public:

    Brick(float _xpos, float _ypos, Definitions::BrickType type, SDL_Texture* sprite, Mix_Chunk* collisionSound);
    ~Brick(){};

    void updatePreServe(double dt);
    void renderPreServe();
    
    void update(double dt);
    void render();

    SDL_FRect brickRect;
    Definitions::BrickStatus brickStatus = Definitions::BrickStatus::BrickGood;
    Definitions::BrickType brickType;
    Definitions::BrickStatus hit();
    
    Brick* topNeighbour = nullptr;
    Brick* bottomNeighbour = nullptr;
    Brick* leftNeighbour = nullptr;
    Brick* rightNeighbour = nullptr;

private:

    float xpos; 
    float ypos;
    

    static const int numSprites = 21;
    static const int destructionStartFrame = 3;
    static const int destructionEndFrame = 10;
    float currentdestructionFrame = destructionStartFrame;
    
    static const int shineStartFrame = 10;
    static const int shineEndFrame = 20;
    float currentShineFrame = shineStartFrame;
    bool shineAnimDone = false;


    SDL_Texture* brickSprite;
    SDL_Rect brickSpriteClips[numSprites];

    Mix_Chunk* collisionSound;

    float brickHeight = 32.f;
    float brickWidth = 64.f;

    int type = 0;
    int health = 0;
    bool destructable = true;

    void SliceSpriteSheet();
};