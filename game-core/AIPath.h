#pragma once
#include "game-core.h"

#include "AutonomousObject.h"

class GAMECOREDLL AutonomousObject;

class GAMECOREDLL AIPath
{
private:
	PathContainer m_path;
	bool m_looped;

	AIPath();


	void set(PathContainer new_path);
	void set(const AIPath& path);
	void clear();

public:
	~AIPath();


	static AIPath* instance();


	WayPoint begin();
	Common::Vector4 currentWayPoint(AutonomousObject*);
	void setNextWayPoint(AutonomousObject*);
	void loopOn();
	void loopOff();
	bool finished(AutonomousObject*);


	string toString();
	void print();
};
