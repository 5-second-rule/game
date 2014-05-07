#pragma once

#include "game-media.h"
#include "game-core/Game.h"
#include "engine-core/World.h"
#include "engine-renderer/RenderingEngine.h"

class GAMEMEDIADLL RenderableGame : public Game, IRenderingEngineDelegate
{
private:
	void *appHandle;

protected:
	virtual std::vector<Event *> inputTranslator(InputAdapter *inputAdapter);
	virtual GameObjectCtorTable * makeCtorTable();
	virtual Engine * makeEngineInstance(GameObjectCtorTable *ctors);

public:
	RenderableGame(void *appHandle);
	~RenderableGame();

	static RenderableGame * getGlobalInstance();
	RenderingEngine * getRenderingEngineInstance();

	virtual void init();
};

