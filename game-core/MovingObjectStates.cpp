#include "MovingObjectStates.h"

Move::Move(){}

Move* Move::instance(){
	static Move moveState;
	return &moveState;
}

bool Move::onMessage(MovingObject* object, const Telegram &msg){
	MoveMessage* move;
	float forceModule;
	Vector4 force, forceToApply;

	switch (msg.Type)
	{
	case Game::MessageType::move_command:
		assert(msg.ExtraInfo);
		move = (MoveMessage*)msg.ExtraInfo;
		configInstance()->getValue("move_force", forceModule);
		
		switch (move->dir)
		{
		case Game::Direction::up:
			force.set(0, 0, forceModule);
			break;
		case Game::Direction::down:
			force.set(0, 0, -forceModule);
			break;
		case Game::Direction::left:
			force.set(0, -forceModule, 0);
			break;
		case Game::Direction::right:
			force.set(0, forceModule, 0);
			break;
		default:
			break;
		}
		forceToApply = Transformation::pointToWorldSpace(force,
			object->heading(),
			object->side(),
			object->top(),
			object->getBody()->m_position);
		object->applyForce(forceToApply);
		return true;
		break;
	default:
		return false;
		break;
	}	
}

void Move::enter(MovingObject* object){

}

void Move::execute(MovingObject* object){

}

void Move::exit(MovingObject* object){

}