#include <statemanagers.h>

void setNextState( GameState* newState )
{
    //If the user doesn't want to exit
    if( !(dynamic_cast<ExitState*>(gNextState)))
    {
        //Set the next state
        gNextState = newState;
    }
}

void changeState()
{
    //If the state needs to be changed
    if( gNextState != nullptr )
    {
		gCurrentState->exit();
		gNextState->enter();

        //Change the current state ID
        gCurrentState = gNextState;
        gNextState = nullptr;
    }
}