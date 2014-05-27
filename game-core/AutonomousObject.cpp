#include "AutonomousObject.h"

#include <iostream>

AutonomousObject::AutonomousObject(int objectType) : MovingObject(objectType)
{
	steering_behavior = new SteeringBehavior(this);
	path = Path::instance();
	setCurrentWayPoint(path->begin());
	path->loopOn();
	init();
}

AutonomousObject::~AutonomousObject()
{
}

void AutonomousObject::init(){
	MovingObject::init();
	steering_behavior->init();
}

void AutonomousObject::update(float dt){
	tick_force += this->steering_behavior->calculate();
	MovingObject::update(dt);
}

void AutonomousObject::setPursuit(Handle &pray){
	steering_behavior->pursuitOn(pray);
}

void AutonomousObject::setEvade(Handle &predator){
	steering_behavior->pursuitOn(predator);
}

bool AutonomousObject::setOnSteeringBehavior(BehaviorType behavior){
	if (behavior == BehaviorType::arrive)
		steering_behavior->arriveOn();
	else if (behavior == BehaviorType::flee)
		steering_behavior->fleeOn();
	else if (behavior == BehaviorType::seek)
		steering_behavior->seekOn();
	else if (behavior == BehaviorType::wander)
		steering_behavior->wanderOn();
	else
		return false;
	return true;
}

bool AutonomousObject::setOnSteeringBehavior(BehaviorType behavior, Handle handle){
	if (behavior == BehaviorType::pursuit)
		steering_behavior->pursuitOn(handle);
	else if (behavior == BehaviorType::evade)
		steering_behavior->evadeOn(handle);
	else
		return false;
	return true;
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

string AutonomousObject::toString(){
	stringstream buffer;
	buffer << MovingObject::toString() << endl;
	buffer << steering_behavior->toString() << endl;
	return buffer.str();
}