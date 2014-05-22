#pragma once
//------------------------------------------------------------------------
//
//  Name:   State.h
//
//  Desc:   abstract base class to define an interface for a state
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "engine-core/Event.h"

template <class entity_type>
class State
{
public:

	virtual ~State(){}

	// This executes when the state is entered
	virtual void enter(entity_type*) = 0;

	// State update function
	virtual void execute(entity_type*) = 0;

	// This executes when the state is exited. 
	virtual void exit(entity_type*) = 0;

	// This executes if the agent receives a message from the 
	// message dispatcher
	virtual bool handleEvent(entity_type*, Event*) = 0;
};