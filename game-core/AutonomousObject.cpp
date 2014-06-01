#include "AutonomousObject.h"

#include <iostream>
#include <sstream>

AutonomousObject::AutonomousObject(ObjectTypes objectType) : AutonomousObject(objectType, Game::getGlobalInstance()) {}

AutonomousObject::AutonomousObject(ObjectTypes objectType, Game *owner) : MovingObject(objectType, owner)
{
	steering_behavior = new SteeringBehavior(this);
	path = AIPath::instance();
	theWorld.allocateHandle(this, HandleType::GLOBAL);
	theWorld.insert(this);
}

AutonomousObject::~AutonomousObject() {}

void AutonomousObject::update(float dt){
	this->applyForce(this->steering_behavior->calculate());
	MovingObject::update(dt);
}

void AutonomousObject::setPursuit(Handle &pray){
	steering_behavior->pursuitOn(pray);
}

void AutonomousObject::setEvade(Handle &predator){
	steering_behavior->pursuitOn(predator);
}

bool AutonomousObject::setOnSteeringBehavior(BehaviorType behavior){
	return steering_behavior->on(behavior);
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
	steering_behavior->off(behavior);
}


string AutonomousObject::toString() const {
	stringstream buffer;
	//buffer << MovingObject::toString() << endl;
	buffer << steering_behavior->toString() << endl;
	return buffer.str();
}

void AutonomousObject::setCurrentWayPoint(WayPoint p){
	current_way_point = p;
}


WayPoint AutonomousObject::getCurrentWayPoint(){
	return current_way_point;
}


void AutonomousObject::setNextWayPoint(){
	path->setNextWayPoint(this);
}
