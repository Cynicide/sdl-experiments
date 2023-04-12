
#ifndef EXITSTATE_H
#define EXITSTATE_H

#include <GameState.h>
#include <globals.h>
#include <statemanagers.h>

#include <SDL2/SDL.h>
class ExitState : public GameState
{
public:
	//Static accessor
	static ExitState* get();

	//Transitions
	bool enter();
	bool exit();

	//Main loop functions
	void handleEvent( SDL_Event& e );
	void update();
	void render();

private:
	//Static instance
	static ExitState sExitState;

	//Private constructor
	ExitState();
};
#endif