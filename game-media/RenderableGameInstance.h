#pragma once

#include "game-media.h"
#include "game-core/GameInstance.h"
#include "engine-core/World.h"
#include "engine-renderer/RenderingEngineInstance.h"

class GAMEMEDIADLL RenderableGameInstance : public GameInstance
{
private:
	void *appHandle;

protected:
	Event* inputTranslator(Transmission::Input::Key key, Transmission::Input::KeyState state);
	virtual GameObjectCtorTable * makeCtorTable();
	virtual EngineInstance * makeEngineInstance(GameObjectCtorTable *ctors);

public:
	RenderableGameInstance(void *appHandle);
	~RenderableGameInstance();

	static RenderableGameInstance * getGlobalInstance();
	RenderingEngineInstance * getRenderingEngineInstance();
};

