#include "RedBloodCell.h"


RedBloodCell::RedBloodCell()
{
	m_state_machine = new StateMachine<RedBloodCell>(this);
}


RedBloodCell::~RedBloodCell()
{
}

bool RedBloodCell::onMessage(Telegram msg){
	if (m_state_machine->HandleMessage(msg))
		return true;
	return MovingObject::onMessage(msg);
}

void RedBloodCell::update(float dt){

	MovingObject::update(dt);
}