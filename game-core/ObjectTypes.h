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
	Track,
	Wwod,
	Adrenaline,
};

enum class GAMECOREDLL CollisionPriorities {
	Track,
	Object
};