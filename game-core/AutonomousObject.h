#pragma once

#include <string>
#include <vector>

#include "common/Vector4.h"

typedef std::vector<Common::Vector4> PathContainer;
typedef std::vector<Common::Vector4>::iterator WayPoint;

#include "game-core.h"

#include "MovingObject.h"
#include "SteeringBehavior.h"
#include "BehaviorType.h"
#include "AIPath.h"

class GAMECOREDLL AIPath;

class GAMECOREDLL AutonomousObject : public MovingObject
{
	friend class SteeringBehavior;
private:
	SteeringBehavior* steering_behavior;
	
	AIPath* path;
	WayPoint current_way_point;

public:
	AutonomousObject(ObjectTypes objectType);
	AutonomousObject(ObjectTypes objectType, Game *owner);
	~AutonomousObject();

	virtual void update(float dt);

	// Steering Behavior methods
	bool setOnSteeringBehavior(BehaviorType behavior);
	bool setOnSteeringBehavior(BehaviorType behavior, Handle handle);
	void setOffSteeringBehavior(BehaviorType);
	void setPursuit(Handle &pray);
	void setEvade(Handle &predator);

	virtual std::string toString() const;

	virtual WayPoint getCurrentWayPoint();
	virtual void setCurrentWayPoint(WayPoint);
	virtual void setNextWayPoint();

};
