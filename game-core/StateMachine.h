#pragma once
#include <cassert>
#include "State.h"

template< class object_type >
class StateMachine
{
private:
	/* Pointer to the owner of this state machine */
	object_type*          m_Owner;
	State< object_type >* m_CurrentState;
	State< object_type >* m_PreviousState;	/* Record of the previus state */
	State< object_type >* m_GlobalState;	/* A global state of the object always called in a update */

public:

	StateMachine(object_type* owner) : m_Owner(owner),
		m_CurrentState(nullptr),
		m_PreviousState(nullptr),
		m_GlobalState(nullptr)
	{}

	virtual ~StateMachine(){}

	// Use these methods to initialize the Finity State Machine
	void setCurrentState(State<object_type>* s){ m_CurrentState = s; }
	void setGlobalState(State<object_type>* s) { m_GlobalState = s; }
	void setPreviousState(State<object_type>* s){ m_PreviousState = s; }

	// Call this to update the Finity State Machine
	void  Update()const
	{
		// If a global state exists, call its execute method, else do nothing
		if (m_GlobalState)   m_GlobalState->Execute(m_Owner);

		// Same for the current state
		if (m_CurrentState) m_CurrentState->Execute(m_Owner);
	}

	// Change to a new state
	void  ChangeState(State<object_type>* pNewState)
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

	//change state back to the previous state
	void  RevertToPreviousState()
	{
		ChangeState(m_PreviousState);
	}

	//returns true if the current state's type is equal to the type of the
	//class passed as a parameter. 
	bool  isInState(const State<object_type>& st)const
	{
		return typeid(*m_CurrentState) == typeid(st);
	}

	State<object_type>*  CurrentState()  const{ return m_CurrentState; }
	State<object_type>*  GlobalState()   const{ return m_GlobalState; }
	State<object_type>*  PreviousState() const{ return m_PreviousState; }
};