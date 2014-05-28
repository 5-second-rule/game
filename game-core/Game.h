#pragma once

#include "game-core.h"
#include "GameObjectCtorTable.h"
#include "ObjectTypes.h"
#include "engine-core/Engine.h"
#include "engine-core/World.h"
#include "TrackPath.h"

#define m_getEngine() ((Game::getGlobalInstance())->getEngineInstance())
#define m_getWorld() (m_getEngine()->getWorld())
#define m_getObject(handle) ((m_getWorld())->get(handle))
#define m_createObject(object_type) ((Game::getGlobalInstance())->invoke(object_type))

class GAMECOREDLL Game
{
private:
	static Game *globalInstance;
	Engine *engineInstance;
	TrackPath *track;

	bool initialized;

protected:
	GameObjectCtorTable *objectCtors;
	virtual Engine * makeEngineInstance(ConstructorTable<BaseObject> *objectCtors, ConstructorTable<ActionEvent>* eventCtors) = 0;

public:
	Game();
	~Game();

	static void setGlobalInstance(Game *instance);
	static Game * getGlobalInstance();

	virtual GameObjectCtorTable * makeCtorTable();

	virtual void init();
	void run();
	Engine * getEngineInstance();
	TrackPath * getTrackPath();
	BaseObject *invoke(ObjectTypes object_type);
};