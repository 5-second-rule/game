#pragma once

#include "game-media.h"
#include "game-core\GameObjectCtorTable.h"

class GAMEMEDIADLL RenderableGameObjectCtorTable : public GameObjectCtorTable
{
public:
	int modelIndexes[GameObjectCtorTable::OBJECT_TYPE_COUNT];
	int textureIndexes[GameObjectCtorTable::OBJECT_TYPE_COUNT];
	int bumpIndexes[GameObjectCtorTable::OBJECT_TYPE_COUNT];
	int vertexShaderIndexes[GameObjectCtorTable::OBJECT_TYPE_COUNT];			// sic  ... I'd like to point out that it is indices
	int pixelShaderIndexes[GameObjectCtorTable::OBJECT_TYPE_COUNT];

	RenderableGameObjectCtorTable();
	~RenderableGameObjectCtorTable();

	virtual void initCtors();
};

