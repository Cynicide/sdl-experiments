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

    Paddle(SpriteManager *spriteManager, Mix_Chunk* collisionSound, Mix_Chunk* explosionSound);
    ~Paddle(){};

    void updateServing(double dt);
    void updatePlaying(double dt);
    void updateDying(double dt);

    void renderServing();
    void renderPlaying();
    void renderDying();

    void destroy();
    void hit();
    void explode();
    void reset();
    void move();

    SDL_FRect paddleRect;

private:
    // Background Sprite
    SDL_Texture* paddleSprite;
    SDL_Texture* explosionSprite;
    Mix_Chunk* collisionSound;
    Mix_Chunk* explosionSound;

    float paddleSpeed;

    int textureWidth = 0;
    int textureHeight = 0;

    static const int numExplosionSprites = 8;
    static const int destructionStartFrame = 0;
    static const int destructionEndFrame = 7;
    float currentdestructionFrame = destructionStartFrame;

    int explosionWidth = 0;
    int explosionHeight = 0;

    SDL_Rect explosionSpriteClips[numExplosionSprites];

    int innerExplosionTimer = 0;
    int innerExplosionTimerMax = 2;
    bool explosionSoundPlayed = false;

    void sliceExplosionSheet();
};