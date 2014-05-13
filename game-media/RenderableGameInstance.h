#pragma once

#include "game-media.h"
#include "game-core/GameInstance.h"
#include "engine-core/World.h"
#include "engine-renderer/RenderingEngine.h"

class GAMEMEDIADLL RenderableGameInstance : public GameInstance, IRenderingEngineDelegate
{
private:
	void *appHandle;

protected:
	virtual std::vector<Event *> inputTranslator(InputAdapter *inputAdapter);
	virtual GameObjectCtorTable * makeCtorTable();
	virtual Engine * makeEngineInstance(GameObjectCtorTable *ctors);

public:
	RenderableGameInstance(void *appHandle);
	~RenderableGameInstance();

	static RenderableGameInstance * getGlobalInstance();
	RenderingEngine * getRenderingEngineInstance();

	virtual void init();
	void handleTerminal();
};

