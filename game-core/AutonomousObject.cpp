#include "AutonomousObject.h"


AutonomousObject::AutonomousObject(int objectType) : MovingObject(objectType)
{
	steering_behavior = nullptr;
	path = Path::instance();
	setCurrentWayPoint(path->begin());
	path->loopOn();
}


AutonomousObject::~AutonomousObject()
{
}


void AutonomousObject::setPursuit(Handle &pray){
	steering_behavior->pursuitOn(pray);
}

void AutonomousObject::setEvade(Handle &predator){
	steering_behavior->pursuitOn(predator);
}

void AutonomousObject::setOnSteeringBehavior(BehaviorType behavior){
	if (behavior == BehaviorType::arrive)
		steering_behavior->arriveOn();
	else if (behavior == BehaviorType::flee)
		steering_behavior->fleeOn();
	else if (behavior == BehaviorType::seek)
		steering_behavior->seekOn();
	else if (behavior == BehaviorType::wander)
		steering_behavior->wanderOn();
}

void AutonomousObject::setOffSteeringBehavior(BehaviorType behavior){
	if (behavior == BehaviorType::arrive)
		steering_behavior->arriveOff();
	else if (behavior == BehaviorType::flee)
		steering_behavior->fleeOff();
	else if (behavior == BehaviorType::seek)
		steering_behavior->seekOff();
	else if (behavior == BehaviorType::wander)
		steering_behavior->wanderOff();
}
