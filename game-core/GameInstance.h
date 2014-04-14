#pragma once

#include "game-core.h"
#include "engine-core/EngineInstance.h"
#include "engine-core/World.h"
#include "engine-core/ObjectCtorTable.h"

class GAMECOREDLL GameInstance
{
private:
	EngineInstance *engineInstance;
	bool initHasRun;

protected:
	virtual World * makeWorld();
	virtual ObjectCtorTable * makeCtorTable();

public:
	GameInstance();
	~GameInstance();

	void init();
};

