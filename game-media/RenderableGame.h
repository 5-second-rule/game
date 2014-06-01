#pragma once

#include "game-media.h"
#include "game-core/Game.h"
#include "engine-core/World.h"
#include "engine-renderer/RenderingEngine.h"
#include "game-core/Sounds.h"
#include "RenderingGameManager.h"

class GAMEMEDIADLL RenderableGame : public Game
{
private:
	RenderingGameManager *gameManager;
	void *appHandle;

protected:
	virtual Engine * makeEngineInstance( ConstructorTable<BaseObject> *objectCtors, ConstructorTable<ActionEvent>* eventCtors );

public:
	RenderableGame(void *appHandle);

	static RenderableGame * getGlobalInstance();
	RenderingEngine * getRenderingEngineInstance();

	virtual GameObjectCtorTable * makeCtorTable();

	virtual void init();
	RenderingGameManager *getGameManager();

};

