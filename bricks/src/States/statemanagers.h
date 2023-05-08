#pragma once

#include <ExitState.h>
#include <GameState.h>

#include <globals.h>

//State managers
void setNextState( GameState* nextState );
void changeState();