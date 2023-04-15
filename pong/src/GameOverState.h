#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H
#include <GameState.h>
#include <ExitState.h>
#include <StartState.h>

#include <Text.h>
#include <globals.h>
#include <statemanagers.h>
#include <string>

#include <SDL2/SDL.h>

class GameOverState : public GameState
{
public:
    //Static accessor
    static GameOverState* get();

    //Transitions
    bool enter();
    bool exit();

    std::string winner;

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update(float dt);
    void render();

private:
    //Static instance
    static GameOverState sGameOverState;

    Text gameOverText;
    Text playAgainText;
    Text winnerText;

    //Private constructor
    GameOverState();

};
#endif