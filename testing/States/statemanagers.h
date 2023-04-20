#ifndef STATEMANAGERS_H
#define STATEMANAGERS_H

#include <ExitState.h>
#include <GameState.h>

#include <globals.h>

//State managers
void setNextState( GameState* nextState );
void changeState();
#endif