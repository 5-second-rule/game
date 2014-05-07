#pragma once

#include "game-core.h"
#include "engine-core/Engine.h"
#include "engine-core/World.h"
#include "GameObjectCtorTable.h"

class GAMECOREDLL Game : public IEngineInstanceDelegate
{
private:
	static Game *globalInstance;
	Engine *engineInstance;

	bool initialized;

protected:
	virtual GameObjectCtorTable * makeCtorTable();
	virtual Engine * makeEngineInstance(GameObjectCtorTable *ctors) = 0;

public:
	Game();
	~Game();

	static void setGlobalInstance(Game *instance);
	static Game * getGlobalInstance();

	virtual void init();
	void run();
	Engine * getEngineInstance();

	// IEngineInstanceDelegate Methods
	virtual ActionEvent* MakeActionEvent( int actionType, unsigned int playerGuid, const char* data );
};