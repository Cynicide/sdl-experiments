#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H
#include <GameState.h>
#include <PlayState.h>
#include <ExitState.h>
#include <ImageLib.h>
#include <Text.h>
#include <globals.h>
#include <statemanagers.h>
#include <Vector2d.h>
#include <string>

#include <SDL2/SDL.h>

class GameOverState : public GameState
{
public:
    //Static accessor
    static GameOverState* get(int _score);
    //Transitions
    bool enter();
    bool exit();

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update(float dt);
    void render();

    int score;

private:
    //Static instance
    static GameOverState sGameOverState;



    SDL_Surface* background;
    SDL_Texture* backgroundTexture;

    Text gameOver;
    Text playAgain;

    //Private constructor
    GameOverState();

};
#endif