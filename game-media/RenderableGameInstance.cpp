#include "RenderableGameInstance.h"
#include "RenderableGameObjectCtorTable.h"
#include "engine-renderer/RenderableWorld.h"

RenderableGameInstance::RenderableGameInstance(void *appHandle)
{
	this->appHandle = appHandle;
}

RenderableGameInstance::~RenderableGameInstance()
{
}

EngineInstance * RenderableGameInstance::makeEngineInstance(GameObjectCtorTable *ctors) {
	return new RenderingEngineInstance(
		new RenderableWorld(), 
		ctors,
		this->appHandle);
}

GameObjectCtorTable * RenderableGameInstance::makeCtorTable() {
	return new RenderableGameObjectCtorTable();
}

RenderableGameInstance * RenderableGameInstance::getGlobalInstance() {
	RenderableGameInstance *renderableInstance =
		dynamic_cast<RenderableGameInstance *>(GameInstance::getGlobalInstance());

	if (renderableInstance == nullptr) {
		throw std::runtime_error("Game instance isn't a rendering version.");
	}

	return renderableInstance;
}

RenderingEngineInstance * RenderableGameInstance::getRenderingEngineInstance() {
	return dynamic_cast<RenderingEngineInstance *>(this->getEngineInstance());
}

