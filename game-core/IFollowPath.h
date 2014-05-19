#pragma once

#include "game-core.h"
#include "Path.h"
class GAMECOREDLL Path;

class GAMECOREDLL IFollowPath{
	friend class SteeringBehavior;
protected:
	Path* path;
	WayPoint current_way_point;
public:
	virtual WayPoint getCurrentWayPoint();
	virtual void setCurrentWayPoint(WayPoint);
	virtual void setNextWayPoint();
};
