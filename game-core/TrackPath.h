#pragma once

#include <vector>

#include "game-core.h"
#include "common/Vector4.h"

struct GAMECOREDLL PathNode {
	Common::Vector4 point;
	Common::Vector4 normal;

	float distanceTo(Common::Vector4 otherPoint) {
		return this->normal.dot(otherPoint - this->point);
	};
};

class GAMECOREDLL TrackPath
{
public:
	std::vector<PathNode> nodes;

	TrackPath();
	~TrackPath();

	int locateIndex(Common::Vector4 realPosition, int lastIndex);

	PathNode interpolateNode(Common::Vector4 realPosition, int closestIndex);

	static TrackPath * fromFile(char *file);
};

