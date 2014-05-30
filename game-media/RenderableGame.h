#pragma once

#include "game-media.h"
#include "game-core/Game.h"
#include "engine-core/World.h"
#include "engine-renderer/RenderingEngine.h"
#include "game-core/Sounds.h"

class GAMEMEDIADLL RenderableGame : public Game, IRenderingEngineDelegate
{
private:
	void *appHandle;

protected:
	virtual std::vector<Event *> inputTranslator(InputAdapter *inputAdapter);
	virtual Engine * makeEngineInstance( ConstructorTable<BaseObject> *objectCtors, ConstructorTable<ActionEvent>* eventCtors );

public:
	RenderableGame(void *appHandle);

	static RenderableGame * getGlobalInstance();
	RenderingEngine * getRenderingEngineInstance();

	virtual GameObjectCtorTable * makeCtorTable();

	virtual void init();
};

