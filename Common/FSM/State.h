#ifndef STATE_H
#define STATE_H
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

  //this will execute when the state is entered
  virtual void enter(entity_type*)=0;

  //this is the states normal update function
  virtual void execute(entity_type*)=0;

  //this will execute when the state is exited. 
  virtual void exit(entity_type*)=0;

  //this executes if the agent receives a message from the 
  //message dispatcher
  virtual bool onMessage(entity_type*, const Event&)=0;
};

#endif