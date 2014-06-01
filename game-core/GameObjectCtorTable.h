#pragma once

#include "game-core.h"
#include "engine-core/ConstructorTable.h"
#include "engine-core/BaseObject.h"

class GAMECOREDLL GameObjectCtorTable : public ConstructorTable<BaseObject>
{
public:
	static const int OBJECT_TYPE_COUNT = 11;

	GameObjectCtorTable();
	~GameObjectCtorTable();

	virtual void initCtors();
};

