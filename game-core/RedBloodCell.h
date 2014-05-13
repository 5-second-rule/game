#pragma once

#include "game-core.h"
#include "MovingObject.h"
#include "ObjectTypes.h"

class GAMECOREDLL RedBloodCell : public MovingObject
{
	StateMachine<RedBloodCell> *m_state_machine;
public:
	RedBloodCell();
	~RedBloodCell();
	bool handleEvent(Event* msg);
	void update(float dt);
};

