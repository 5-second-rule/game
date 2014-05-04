#include "RedBloodCell.h"


RedBloodCell::RedBloodCell()
{
	m_state_machine = new StateMachine<RedBloodCell>(this);
}


RedBloodCell::~RedBloodCell()
{
}

bool RedBloodCell::onMessage(Event* evt) {
	if (m_state_machine->HandleMessage(*evt))
		return true;
	return MovingObject::onMessage(evt);
}

void RedBloodCell::update(float dt){

	MovingObject::update(dt);
}