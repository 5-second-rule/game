#pragma once

#include "game-core.h"
#include "GameObjectCtorTable.h"
#include "ObjectTypes.h"
#include "engine-core/Engine.h"
#include "engine-core/World.h"
#include "TrackPath.h"

#define theWorld (*Game::getGlobalInstance()->getEngineInstance()->getWorld())

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
	void stop();
	Engine * getEngineInstance();
	TrackPath * getTrackPath();
	BaseObject *invoke(ObjectTypes object_type);
};