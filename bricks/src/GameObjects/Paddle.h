#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> 

#include <SpriteManager.h>
#include <AudioManager.h>

#include <Definitions.h>

#include <Ball.h>

class Paddle
{
public:
    void render(Definitions::SubState subState);
    void update(double dt);
    void destroy();
    void hit();
    void reset();

    SDL_FRect paddleRect;

    Paddle();

    ~Paddle(){};

private:
    // Background Sprite
    SDL_Texture* paddleSprite;
    SDL_Texture* explosionSprite;
    Mix_Chunk *collisionSound;

    float paddleSpeed;
    int textureWidth = 144;
    int textureHeight = 24;

    static const int numExplosionSprites = 8;
    SDL_Rect explosionSpriteClips[numExplosionSprites];
    int explosionWidth = 208;
    int explosionHeight = 72;
    static const int destructionStartFrame = 1;
    static const int destructionEndFrame = 8;
    int currentdestructionFrame = destructionStartFrame;
    int innerExplosionTimer = 0;
    int innerExplosionTimerMax = 2;

    void sliceExplosionSheet();
};