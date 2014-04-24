#pragma once

#include "game-media.h"
#include "game-core\GameObjectCtorTable.h"

class GAMEMEDIADLL RenderableGameObjectCtorTable : public GameObjectCtorTable
{
public:
	int modelIndexes[GameObjectCtorTable::OBJECT_TYPE_COUNT];
	int textureIndexes[GameObjectCtorTable::OBJECT_TYPE_COUNT];

	RenderableGameObjectCtorTable();
	~RenderableGameObjectCtorTable();

	virtual void initCtors();
};

