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
	TitleScreen,
	State,
	Wwod,
	Adrenaline,
};

enum class GAMECOREDLL CollisionPriorities {
	Track,
	Object
};