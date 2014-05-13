#pragma once

#include "game-core.h"
#include "IFollowPath.h"

class GAMECOREDLL IFollowPath;

class GAMECOREDLL Path
{
	PathContainer m_path;
	bool m_looped;


	Path();

	PathContainer createRandomPath(int NumWaypoints,
		float MinX,
		float MinY,
		float MinZ,
		float MaxX,
		float MaxY,
		float MaxZ);
	void set(PathContainer new_path);
	void set(const Path& path);
	void clear();
public:
	~Path();

	static Path* instance();

	WayPoint begin();
	Vector4 currentWayPoint(IFollowPath*);
	void setNextWayPoint(IFollowPath*);
	void loopOn();
	void loopOff();
	bool finished(IFollowPath*);

	string toString();
	void print();
};

