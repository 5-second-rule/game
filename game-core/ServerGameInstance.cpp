#include "ServerGameInstance.h"
#include "MoveEvent.h"
#include "ShootEvent.h"

#include "engine-core/ServerEngine.h"

ServerGameInstance::ServerGameInstance(float frameTime) {
	this->frameTime = frameTime;
}

ServerGameInstance::~ServerGameInstance() {
}

Engine * ServerGameInstance::makeEngineInstance(GameObjectCtorTable *ctors) {
	Engine* eng  = new ServerEngine(
		new World(),
		ctors,
		this->frameTime);
	eng->delegate = this;

	return eng;
}

void ServerGameInstance::stop() {
	dynamic_cast<ServerEngine *>(this->getEngineInstance())->stop();
}

ActionEvent* ServerGameInstance::MakeActionEvent( int actionType, unsigned int playerGuid, const char* data ) {
	ActionEvent* evt = nullptr;
	
	switch( ActionType( actionType ) ) {
		case ActionType::MOVE:
			evt = new MoveEvent( playerGuid, *(reinterpret_cast<const MoveDirection*>(data)) );
			break;
		case ActionType::SHOOT:
			evt = new ShootEvent( playerGuid );
			break;
		case ActionType::USE:
			break;
		default:
			break;
	}

	return evt;
}