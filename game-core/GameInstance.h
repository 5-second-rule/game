#pragma once

#include "game-core.h"
#include "engine-core/Engine.h"
#include "engine-core/World.h"
#include "GameObjectCtorTable.h"

GAMECOREDLL enum class ActionType {
	MOVE,
	USE,
	SHOOT
};

class GAMECOREDLL GameInstance : public IEngineInstanceDelegate
{
private:
	static GameInstance *globalInstance;
	Engine *engineInstance;
	bool initHasRun;

protected:
	virtual GameObjectCtorTable * makeCtorTable();
	virtual Engine * makeEngineInstance(GameObjectCtorTable *ctors) = 0;

public:
	GameInstance();
	~GameInstance();

	static void setGlobalInstance(GameInstance *instance);
	static GameInstance * getGlobalInstance();

	void init();
	void run();
	Engine * getEngineInstance();

	// IEngineInstanceDelegate Methods
	virtual void HandleAction( ActionEvent* evt );
	virtual ActionEvent* MakeActionEvent( int actionType, unsigned int playerGuid, size_t index, const char* data );

};

