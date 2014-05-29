#pragma once

#include "game-media.h"
#include "game-core\GameObjectCtorTable.h"
#include "SelectionScreenData.h"
#include "SignallingGameState.h"

class GAMEMEDIADLL RenderableGameObjectCtorTable : public GameObjectCtorTable
{
private:
	void prepSelectionScreenData();
public:
	SelectionScreenData *selectionScreenData;
	int modelIndexes[GameObjectCtorTable::OBJECT_TYPE_COUNT];
	int textureIndexes[GameObjectCtorTable::OBJECT_TYPE_COUNT];
	int bumpIndexes[GameObjectCtorTable::OBJECT_TYPE_COUNT];
	int vertexShaderIndexes[GameObjectCtorTable::OBJECT_TYPE_COUNT];			// sic  ... I'd like to point out that it is indices
	int pixelShaderIndexes[GameObjectCtorTable::OBJECT_TYPE_COUNT];

	RenderableGameObjectCtorTable();
	~RenderableGameObjectCtorTable();

	virtual void initCtors();
};

