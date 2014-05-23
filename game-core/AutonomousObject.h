#pragma once

#include "game-core.h"
#include "MovingObject.h"
#include "SteeringBehavior.h"

class GAMECOREDLL SteeringBehavior;

class GAMECOREDLL AutonomousObject : public MovingObject
{
private:
	SteeringBehavior* steering_behavior;
public:
	AutonomousObject(int objectType);
	~AutonomousObject();

	virtual void update(float dt);

	// Steering Behavior methods
	void setOnSteeringBehavior(BehaviorType);
	void setOffSteeringBehavior(BehaviorType);
	void setPursuit(Handle &pray);
	void setEvade(Handle &predator);
};

