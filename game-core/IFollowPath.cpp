#include "IFollowPath.h"

void IFollowPath::setCurrentWayPoint(WayPoint p){
	current_way_point = p;
}

WayPoint IFollowPath::getCurrentWayPoint(){
	return current_way_point;
}

void IFollowPath::setNextWayPoint(){
	path->setNextWayPoint(this);
}
