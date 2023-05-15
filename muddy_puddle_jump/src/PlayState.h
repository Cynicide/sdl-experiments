#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include <GameState.h>
#include <GameOverState.h>
#include <ExitState.h>
#include <ImageLib.h>
#include <iostream>
#include <string>

#include <audio.h>

#include <Text.h>
#include <globals.h>
#include <statemanagers.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h> 
#include <random>

class PlayState : public GameState
{
public:
    //Static accessor
    static PlayState* get();

    //Transitions
    bool enter();
    bool exit();

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update(float dt);
    void render();

private:
    //Static instance
    static PlayState sPlayState;

    enum SubState {
        PREPARING,
        PLAYING,
        JUMPING,
        WAITING
    };

    enum JumpDirection {
        UP,
        DOWN
    };

    SubState substate;
    JumpDirection jumpdirection;

    SDL_Texture* backgroundTexture;
    SDL_Texture* peppaTexture;
    SDL_Texture* puddleTexture;

    SDL_FRect peppa_offset;
    SDL_FRect puddle_offset;
    int peppaYmax;
    int peppaYmin;
    int peppaJumpheight;
    int peppaYvelUp;
    int peppaYvelDown;

    // Peppa Sprites
    SDL_Rect gSpriteClips[3];

    int numOfJumpsMax;
    int numOfJumps;
    int jumpTimerUpMax;
    int jumpTimerDownMax;
    float jumpTimer;
    int score;
    int countdown;
    float timeLeft;

    Text scoreText;
    Text timeText;

    bool AABBCheck(SDL_FRect rPeppa, SDL_FRect rPuddle);
    void SliceSpriteSheet();
    void RunCountDown(float dt);

    //Private constructor
    PlayState();

};
#endif
