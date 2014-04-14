#pragma once

#include "game-core.h"
#include "engine-core/ObjectCtorTable.h"

class GAMECOREDLL GameObjectCtorTable : public ObjectCtorTable
{
protected:
	virtual void initCtors();

public:
	GameObjectCtorTable();
	~GameObjectCtorTable();
};

