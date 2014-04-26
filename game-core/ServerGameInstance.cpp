#include "ServerGameInstance.h"

#include "engine-core/ServerEngineInstance.h"

ServerGameInstance::ServerGameInstance(int minimumFrameTime) {
	this->minimumFrameTime = minimumFrameTime;
}

ServerGameInstance::~ServerGameInstance() {
}

EngineInstance * ServerGameInstance::makeEngineInstance(GameObjectCtorTable *ctors) {
	return new ServerEngineInstance(
		new World(),
		ctors,
		this->minimumFrameTime);
}

void ServerGameInstance::stop() {
	dynamic_cast<ServerEngineInstance *>(this->getEngineInstance())->stop();
}