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
	UI,
	SelectionScreen,
	State,
	Wwod,
	Adrenaline,
	AIManager
};

enum class GAMECOREDLL CollisionPriorities {
	Track,
	Object
};