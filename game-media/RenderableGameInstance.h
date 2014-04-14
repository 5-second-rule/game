#pragma once

#include "game-media.h"
#include "game-core/GameInstance.h"
#include "engine-core/World.h"
#include "engine-core/ObjectCtorTable.h"

class GAMEMEDIADLL RenderableGameInstance : public GameInstance
{
protected:
	virtual World * makeWorld();
	virtual ObjectCtorTable * makeCtorTable();

public:
	RenderableGameInstance();
	~RenderableGameInstance();
};

