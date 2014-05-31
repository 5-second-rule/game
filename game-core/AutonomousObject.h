#pragma once

#include <string>

#include "game-core.h"
#include "MovingObject.h"
#include "SteeringBehavior.h"
#include "BehaviorType.h"
#include "Path.h"

class GAMECOREDLL SteeringBehavior;

class GAMECOREDLL AutonomousObject : public MovingObject, public IFollowPath
{
private:
	SteeringBehavior* steering_behavior;
	bool tagged;
public:
	Path *path;
	AutonomousObject(ObjectTypes objectType);
	AutonomousObject(ObjectTypes objectType, Game *owner);
	~AutonomousObject();
	virtual void init();

	virtual void update(float dt);

	// Steering Behavior methods
	bool setOnSteeringBehavior(BehaviorType behavior);
	bool setOnSteeringBehavior(BehaviorType behavior, Handle handle);
	void setOffSteeringBehavior(BehaviorType);
	void setPursuit(Handle &pray);
	void setEvade(Handle &predator);
	void setOffsetPursuit(Handle &handle, Vector4 &vect);

	bool isTagged();
	void setTag(bool tag);
	
	virtual std::string toString();
};

