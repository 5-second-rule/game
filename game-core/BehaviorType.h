#pragma once

#include "game-core.h"

enum GAMECOREDLL BehaviorType{
	none = 0x00,
	seek = 0x01,
	flee = 0x02,
	arrive = 0x04,
	wander = 0x08,
	pursuit = 0x10,
	evade = 0x20,
	follow_path = 0x40,
	offset_pursuit = 0x80
};
