#pragma once

#include "game-core.h"
#include "Path.h"

class GAMECOREDLL IFollowPath{
public:
	virtual WayPoint getCurrentWayPoint() = 0;
	virtual void setCurrentWayPoint(WayPoint) = 0;
};