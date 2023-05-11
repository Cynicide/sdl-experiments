#include <ExitState.h>

//Hollow exit state

ExitState::ExitState()
{

}

bool ExitState::enter()
{
	return true;
}
	
bool ExitState::exit()
{
	return true;
}

void ExitState::handleEvent( SDL_Event& e )
{

}

void ExitState::update(double dt)
{

}

void ExitState::render()
{

}

