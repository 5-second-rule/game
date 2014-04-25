#pragma once

#include "game-core.h"
#include "engine-core/ObjectCtorTable.h"

class GAMECOREDLL GameObjectCtorTable : public ObjectCtorTable
{
public:
	static const int OBJECT_TYPE_COUNT = 10;

	GameObjectCtorTable();
	~GameObjectCtorTable();

	virtual void initCtors();
};

