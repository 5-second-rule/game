#include "MovingObjectStates.h"
#include "MoveEvent.h"
#include "ActionType.h"

Move::Move(){}

Move* Move::instance(){
	static Move moveState;
	return &moveState;
}

bool Move::handleEvent(MovingObject* object, Event *evt){
	float forceModule;
	Vector4 force, forceToApply;

	ActionEvent *actionEvt = dynamic_cast<ActionEvent *>(evt);
	if (actionEvt == nullptr)
		return false;

	switch (ActionType(actionEvt->getActionType())) {
	case ActionType::MOVE: {
		MoveEvent *moveEvent = dynamic_cast<MoveEvent *>(evt);
		if (moveEvent == nullptr)
			return false;
		assert(ConfigSettings::configInstance()->getValue("move_force", forceModule));
		force.set(moveEvent->direction.x * forceModule,
			      moveEvent->direction.y * forceModule,
			      moveEvent->direction.z * forceModule);
		forceToApply = force; Transformation::vectorToWorldSpace(force,
			object->getSide(),
			object->getTop(),
			object->getFront());
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
	object->setForce(0, 0, 0);
	object->setTickForce(0, 0, 0);
}

void Move::execute(MovingObject* object){



}

void Move::exit(MovingObject* object){

}