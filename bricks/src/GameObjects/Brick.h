#pragma once
#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <vector>

class Brick
{
public:
    void render();
    void update(double dt);
    void destroy();
    void setVectorRef(std::vector<Brick>& _vectorRef);
    void removeFromVector();

    // Without this std::find won't work
    bool operator==(const Brick& other) const {
        return (xpos == other.xpos) && (ypos == other.ypos);
    }

    Brick(int _xpos, int _ypos);

    ~Brick(){};

private:
    // Background Sprite
    SDL_Texture* brickLightSprite;
    SDL_Texture* brickDarkSprite;
    SDL_Rect brickRect;

    int brickHeight = 32;
    int brickWidth = 64;

    int xpos, ypos;

    int numSprites = 10;
    SDL_Rect brickSpriteClips[10];

    void SliceSpriteSheet();

    std::vector<Brick>* vectorRef = nullptr;

};