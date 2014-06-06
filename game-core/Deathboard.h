#pragma once

#include "game-core.h"

struct DeathboardEntry {
	int playerIndex;
	int numDeaths;
	int deathOrder;
	bool winner;
};
