#pragma once
#include <GameState.h>
#include <ExitState.h>
#include <VerticalSplitTextUI.h>
#include <statemanagers.h>
#include <GameContext.h>

#include <SDL2/SDL.h>

class GameOverState : public GameState
{
public:
    //Private constructor
    GameOverState(GameContext* gameContext, GameState* startState);
    ~GameOverState(){};

    //Transitions
    bool enter();
    bool exit();

    //Game loop functions
    void handleEvent( SDL_Event& e );
    void update(double dt);
    void render();
    

private:
    GameContext* gameContext;
    GameState* startState;
    VerticalSplitTextUI gameOverElement;
    TTF_Font* font;
};
