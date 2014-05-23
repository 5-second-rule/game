#pragma once
//------------------------------------------------------------------------
//
//  Name:   StateMachine.h
//
//  Desc:   State machine class. Inherit from this class and create some 
//          states to give your agents FSM functionality
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <cassert>
#include <string>

#include "engine-core/Event.h"

#include "State.h"

template <class entity_type>
class StateMachine
{
private:
	entity_type *m_owner;
	State<entity_type> *m_current_state;
	State<entity_type> *m_previous_state;
	State<entity_type> *m_global_state;

public:

	StateMachine(entity_type *p_owner);
	virtual ~StateMachine();

	// Set methods
	void setCurrentState(State<entity_type>* s);
	void setGlobalState(State<entity_type>* s);
	void setPreviousState(State<entity_type>* s);

	// Get methods
	State<entity_type>* getCurrentState() const;
	State<entity_type>* getGlobalState() const;
	State<entity_type>* getPreviousState() const;

	void  update() const;
	bool  handleEvent(Event* evt) const;
	void  changeState(State<entity_type>* pNewState);
	void  revertToPreviousState();
	bool  isInState(const State<entity_type>& st) const;


	// Debug method that returns the name of the state
	std::string getNameOfCurrentState() const;
};

template <class entity_type>
StateMachine<entity_type>::StateMachine(entity_type *p_owner) :m_owner(p_owner),
m_current_state(nullptr),
m_previous_state(nullptr),
m_global_state(nullptr) {}

template <class entity_type>
StateMachine<entity_type>::~StateMachine() {}

template <class entity_type>
void StateMachine<entity_type>::setCurrentState(State<entity_type>* s){
	m_current_state = s;
}

template <class entity_type>
void StateMachine<entity_type>::setGlobalState(State<entity_type>* s){
	m_global_state = s;
}

template <class entity_type>
void StateMachine<entity_type>::setPreviousState(State<entity_type>* s){
	m_previous_state = s;
}

template <class entity_type>
State<entity_type>* StateMachine<entity_type>::getCurrentState() const{
	return m_current_state;
}

template <class entity_type>
State<entity_type>* StateMachine<entity_type>::getGlobalState() const{
	return m_global_state;
}

template <class entity_type>
State<entity_type>* StateMachine<entity_type>::getPreviousState() const{
	return m_previous_state;
}

template <class entity_type>
void StateMachine<entity_type>::update() const
{
	if (m_global_state)
		m_global_state->execute(m_owner);

	if (m_current_state)
		m_current_state->execute(m_owner);
}

template <class entity_type>
bool StateMachine<entity_type>::handleEvent(Event* evt)const
{
	// See if current state is valid and if it can handle the event
	if (m_current_state && m_current_state->handleEvent(m_owner, evt)) {
		return true;
	}

	// Otherwise see if there is a global state that can handle the event
	if (m_global_state && m_global_state->handleEvent(m_owner, evt)) {
		return true;
	}
	return false;
}

template <class entity_type>
void StateMachine<entity_type>::changeState(State<entity_type>* p_new_state)
{
	if (p_new_state == nullptr)
		throw "Trying to change to a null pointer state";

	m_previous_state = m_current_state;

	// call the exit method of the existing state
	m_current_state->exit(m_owner);

	// change state to the new state
	m_current_state = p_new_state;

	// call the entry method of the new state
	m_current_state->enter(m_owner);
}

template <class entity_type>
void StateMachine<entity_type>::revertToPreviousState()
{
	changeState(m_previous_state);
}

template <class entity_type>
bool StateMachine<entity_type>::isInState(const State<entity_type>& st) const
{
	if (typeid(*m_current_state) == typeid(st)) return true;
	return false;
}

template <class entity_type>
std::string StateMachine<entity_type>::getNameOfCurrentState() const
{
	std::string s(typeid(*m_current_state).name());

	// Remove the 'class ' part from the front of the string
	if (s.size() > 5)
	{
		s.erase(0, 6);
	}

	return s;
}
