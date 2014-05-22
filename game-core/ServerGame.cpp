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

Engine * ServerGame::makeEngineInstance( ConstructorTable<BaseObject> *objectCtors, ConstructorTable<ActionEvent>* eventCtors ) {

	Engine* eng  = new ServerEngine(
		new World(),
		objectCtors,
		eventCtors,
		this->frameTime);

	return eng;
}

void ServerGame::run(){
	Game::run();
}

void ServerGame::stop() {
	dynamic_cast<ServerEngine *>(this->getEngineInstance())->stop();
}
