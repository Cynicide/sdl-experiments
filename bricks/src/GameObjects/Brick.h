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

    SDL_FRect brickRect;

    // Without this std::find won't work
    bool operator==(const Brick& other) const {
        return (xpos == other.xpos) && (ypos == other.ypos);
    }

    Brick(float _xpos, float _ypos);

    ~Brick(){};

private:
    // Background Sprite
    SDL_Texture* brickLightSprite;
    SDL_Texture* brickDarkSprite;

    float brickHeight = 32.f;
    float brickWidth = 64.f;
    float xpos, ypos;

    int numSprites = 10;
    SDL_Rect brickSpriteClips[10];

    std::vector<Brick>* vectorRef = nullptr;

    void SliceSpriteSheet();

};