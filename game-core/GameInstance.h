#pragma once

#include "game-core.h"
#include "engine-core/EngineInstance.h"
#include "engine-core/World.h"
#include "GameObjectCtorTable.h"

class GAMECOREDLL GameInstance
{
private:
	static GameInstance *globalInstance;
	EngineInstance *engineInstance;
	bool initHasRun;

protected:
	virtual GameObjectCtorTable * makeCtorTable();
	virtual EngineInstance * makeEngineInstance(GameObjectCtorTable *ctors) = 0;

public:
	GameInstance();
	~GameInstance();

	static void setGlobalInstance(GameInstance *instance);
	static GameInstance * getGlobalInstance();

	void init();
	void run();
	EngineInstance * getEngineInstance();
};

