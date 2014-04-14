#pragma once

#include "game-media.h"
#include "game-core\GameObjectCtorTable.h"

class GAMEMEDIADLL RenderableGameObjectCtorTable : public GameObjectCtorTable
{
protected:
	virtual void initCtors();

public:
	RenderableGameObjectCtorTable();
	~RenderableGameObjectCtorTable();
};

