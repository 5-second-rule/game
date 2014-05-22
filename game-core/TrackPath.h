#pragma once

#include <vector>

#include "game-core.h"
#include "common/Vector4.h"

struct GAMECOREDLL PathNode {
	Common::Vector4 point;
	Common::Vector4 normal;

	Common::Vector4 getPlane() {
		return this->point + this->normal;
	};
};

class TrackPath
{
public:
	std::vector<PathNode> nodes;

	TrackPath();
	~TrackPath();

	int locateIndex(Common::Vector4 realPosition, int lastIndex);

	static TrackPath * fromFile(char *file);
};

