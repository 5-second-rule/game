#pragma once

#include "MovingObject.h"
#include "ObjectTypes.h"

class RedBloodCell : public MovingObject
{
	StateMachine<RedBloodCell> *m_state_machine;
public:
	RedBloodCell();
	~RedBloodCell();
	bool handleEvent(Event* msg);
	void update(float dt);
};

