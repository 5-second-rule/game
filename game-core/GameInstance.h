#pragma once

#include "engine-core/Engine.h"
#include "engine-core/World.h"

#include "game-core.h"
#include "MovingObject.h"
#include "ObjectTypes.h"
#include "GameObjectCtorTable.h"

#define getWorld() (((GameInstance::getGlobalInstance())->getEngineInstance())->world)
#define getObject(handle) ((getWorld())->get(handle))

class GAMECOREDLL GameInstance : public IEngineInstanceDelegate
{
private:
	static GameInstance *globalInstance;
	bool initHasRun;
	
protected:
	Engine *engineInstance;
	virtual GameObjectCtorTable * makeCtorTable();
	virtual Engine * makeEngineInstance(GameObjectCtorTable *ctors) = 0;

public:
	float m_fluid_density;

	GameInstance();
	~GameInstance();

	static void setGlobalInstance(GameInstance *instance);
	static GameInstance * getGlobalInstance();

	virtual void init();
	void run();
	Engine * getEngineInstance();

	// IEngineInstanceDelegate Methods
	virtual ActionEvent* MakeActionEvent( int actionType, unsigned int playerGuid, const char* data );
};