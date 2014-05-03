#include "RedBloodCell.h"


RedBloodCell::RedBloodCell()
{
	m_state_machine = new StateMachine<RedBloodCell>(this);
}


RedBloodCell::~RedBloodCell()
{
}

bool RedBloodCell::onEvent(Event event){
	//m_state_machine->
	return MovingObject::onEvent(event);
}

void RedBloodCell::update(float dt){

	MovingObject::update(dt);
}