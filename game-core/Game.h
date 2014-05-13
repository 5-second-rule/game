#pragma once

#include "game-core.h"
#include "GameObjectCtorTable.h"
#include "engine-core/Engine.h"
#include "engine-core/World.h"

class GAMECOREDLL Game
{
private:
	static Game *globalInstance;
	Engine *engineInstance;

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
};