#pragma once

#include "game-core.h"
#include "engine-core/ConstructorTable.h"
#include "engine-core/IHasHandle.h"

class GAMECOREDLL GameObjectCtorTable : public ConstructorTable<IHasHandle>
{
public:
	static const int OBJECT_TYPE_COUNT = 10;

	GameObjectCtorTable();
	~GameObjectCtorTable();

	virtual void initCtors();
};

