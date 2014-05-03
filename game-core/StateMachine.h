#pragma once
#include <cassert>
#include "State.h"

template< class type >
class StateMachine
{
private:
	/* Pointer to the owner of this state machine */
	type*          m_Owner;
	State< type >* m_CurrentState;
	State< type >* m_PreviousState;	/* Record of the previus state */
	State< type >* m_GlobalState;	/* A global state of the object always called in a update */

public:

	StateMachine(type* owner) : m_Owner(owner),
		m_CurrentState(nullptr),
		m_PreviousState(nullptr),
		m_GlobalState(nullptr)
	{}

	virtual ~StateMachine(){}

	// Use these methods to initialize the Finity State Machine
	void setCurrentState(State<type>* s){ m_CurrentState = s; }
	void setGlobalState(State<type>* s) { m_GlobalState = s; }
	void setPreviousState(State<type>* s){ m_PreviousState = s; }
	void  Update()const; // Call this to update the Finity State Machine
	bool handleMessage(const Telegram& msg)const;
	void  ChangeState(State<type>* pNewState); // Change to a new state
	void  RevertToPreviousState() { //change state back to the previous state
		ChangeState(m_PreviousState); 
	}

	//returns true if the current state's type is equal to the type of the
	//class passed as a parameter. 
	bool  isInState(const State<type>& st)const
	{
		return typeid(*m_CurrentState) == typeid(st);
	}

	State<type>*  CurrentState()  const{ return m_CurrentState; }
	State<type>*  GlobalState()   const{ return m_GlobalState; }
	State<type>*  PreviousState() const{ return m_PreviousState; }
};

template< class type >
void StateMachine<type>::update()const
{
	// If a global state exists, call its execute method, else do nothing
	if (m_GlobalState)   m_GlobalState->Execute(m_Owner);

	// Same for the current state
	if (m_CurrentState) m_CurrentState->Execute(m_Owner);
}

template< class type >
void StateMachine<type>::ChangeState(State<type>* pNewState)
{
	assert(pNewState && "<StateMachine::ChangeState>: trying to change to NULL state");

	//keep a record of the previous state
	m_PreviousState = m_CurrentState;

	//call the exit method of the existing state
	m_CurrentState->Exit(m_Owner);

	//change state to the new state
	m_CurrentState = pNewState;

	//call the entry method of the new state
	m_CurrentState->Enter(m_Owner);
}

template< class type >
bool StateMachine<type>::handleMessage(const Telegram& msg)const
{
	//first see if the current state is valid and that it can handle
	//the message
	if (m_pCurrentState && m_pCurrentState->onMessage(m_pOwner, msg))
	{
		return true;
	}

	//if not, and if a global state has been implemented, send 
	//the message to the global state
	if (m_pGlobalState && m_pGlobalState->onMessage(m_pOwner, msg))
	{
		return true;
	}

	return false;
}
