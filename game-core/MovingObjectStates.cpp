#include "MovingObjectStates.h"

Move::Move(){}

Move* Move::instance(){
	static Move moveState;
	return &moveState;
}

bool Move::handleEvent(MovingObject* object, Event *evt){
	MoveMessage* move;
	float forceModule;
	Vector4 force, forceToApply;


	ActionEvent *actionEvt = dynamic_cast<ActionEvent *>(evt);
	if (actionEvt == nullptr)
		return false;

	switch (ActionType(actionEvt->actionType)) {
	case ActionType::MOVE: {
		MoveEvent *moveEvent = dynamic_cast<MoveEvent *>(evt);
		if (moveEvent == nullptr)
			return false;
		assert(configInstance()->getValue("move_force", forceModule));
		force.set(moveEvent->direction.x * forceModule,
			      moveEvent->direction.y * forceModule,
			      moveEvent->direction.z * forceModule);

		if (object->getWorld()->isTick(30)){
			cout << "Before: " << force.toString();
		}
		forceToApply = force; Transformation::pointToWorldSpace(force,
			object->front(),
			object->side(),
			object->top(),
			Vector4(0,0,0));
		if (object->getWorld()->isTick(30)){
			cout << "After: " << forceToApply.toString();
		}
		object->applyForce(forceToApply);
		return true;
		break;
	}
	case ActionType::SHOOT: {
		// create projectile and set it in motion
		break;
	}
	default:
			
		break;
	}
	return false;
}

void Move::enter(MovingObject* object){

}

void Move::execute(MovingObject* object){

}

void Move::exit(MovingObject* object){

}