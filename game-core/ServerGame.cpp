#include "ServerGame.h"
#include "MoveEvent.h"
#include "ShootEvent.h"
#include "ActionType.h"

#include "engine-core/ServerEngine.h"

ServerGame::ServerGame(float frameTime) {
	this->frameTime = frameTime;
}

ServerGame::~ServerGame() {
}

Engine * ServerGame::makeEngineInstance(GameObjectCtorTable *ctors) {
	Engine* eng  = new ServerEngine(
		new World(),
		ctors,
		this->frameTime);
	eng->delegate = this;

	return eng;
}

void ServerGame::stop() {
	dynamic_cast<ServerEngine *>(this->getEngineInstance())->stop();
}

ActionEvent* ServerGame::MakeActionEvent( int actionType, unsigned int playerGuid, const char* data ) {
	ActionEvent* evt = nullptr;
	
	switch( ActionType( actionType ) ) {
		case ActionType::MOVE:
			evt = new MoveEvent(playerGuid, *(reinterpret_cast<const MoveEvent::MoveDirection*>(data)));
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