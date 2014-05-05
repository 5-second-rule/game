#include "RedBloodCell.h"


RedBloodCell::RedBloodCell() : MovingObject(ObjectTypes::RedBlood)
{
	m_state_machine = new StateMachine<RedBloodCell>(this);
}


RedBloodCell::~RedBloodCell()
{
}

bool RedBloodCell::handleEvent(Event* evt) {
	if (m_state_machine->handleEvent(evt))
		return true;
	return MovingObject::handleEvent(evt);
}

void RedBloodCell::update(float dt){

	MovingObject::update(dt);
}