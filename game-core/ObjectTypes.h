#pragma once
#include "game-core.h"

enum GAMECOREDLL ObjectTypes
{
	Ecoli,
	ChickenPox,
	Syphillis,
	Malaria,
	WhiteBlood,
	RedBlood,
	MagicSchoolBus,
	Cmd,
	AIManager,
	Track
};

enum class GAMECOREDLL CollisionPriorities {
	Track,
	Object
};