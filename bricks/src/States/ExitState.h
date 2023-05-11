#pragma once

#include <GameState.h>
#include <SDL2/SDL.h>
class ExitState : public GameState
{
public:

	ExitState();
	~ExitState(){};

	//Transitions
	bool enter();
	bool exit();

	//Main loop functions
	void handleEvent( SDL_Event& e );
	void update(double dt);
	void render();

private:

};