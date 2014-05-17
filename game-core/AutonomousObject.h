#pragma once

#include "game-core.h"
#include "MovingObject.h"

class AutonomousObject : public MovingObject
{
private:
	SteeringBehavior* steering_behavior;
public:
	AutonomousObject(int objectType);
	~AutonomousObject();

	// Steering Behavior methods
	void setOnSteeringBehavior(BehaviorType);
	void setOffSteeringBehavior(BehaviorType);
	void setPursuit(Handle &pray);
	void setEvade(Handle &predator);
};

