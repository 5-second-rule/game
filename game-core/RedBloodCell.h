#pragma once

#include "MovingObject.h"

class RedBloodCell : public MovingObject
{
	StateMachine<RedBloodCell> *m_state_machine;
public:
	RedBloodCell();
	~RedBloodCell();
	bool onMessage(Event* msg);
	void update(float dt);
};

