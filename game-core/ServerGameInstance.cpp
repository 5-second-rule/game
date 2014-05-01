#include "ServerGameInstance.h"

#include "engine-core/ServerEngineInstance.h"

ServerGameInstance::ServerGameInstance(float frameTime) {
	this->frameTime = frameTime;
}

ServerGameInstance::~ServerGameInstance() {
}

EngineInstance * ServerGameInstance::makeEngineInstance(GameObjectCtorTable *ctors) {
	return new ServerEngineInstance(
		new World(),
		ctors,
		this->frameTime);
}

void ServerGameInstance::stop() {
	dynamic_cast<ServerEngineInstance *>(this->getEngineInstance())->stop();
}