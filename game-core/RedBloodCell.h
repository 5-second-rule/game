#pragma once
#include "MovingObject.h"
#include "StateMachine.h"

class RedBloodCell : public MovingObject
{
	StateMachine<RedBloodCell> *m_state_machine;
public:
	RedBloodCell();
	~RedBloodCell();
	bool onEvent(Event event);
	void update(float dt);
};

