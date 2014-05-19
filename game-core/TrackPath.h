#pragma once

#include <vector>

#include "game-core.h"
#include "common/Vector4.h"

struct GAMECOREDLL PathNode {
	Common::Vector4 point;
	Common::Vector4 normal;
};

class TrackPath
{
public:
	std::vector<PathNode> nodes;

	TrackPath();
	~TrackPath();

	static TrackPath * fromFile(char *file);
};

